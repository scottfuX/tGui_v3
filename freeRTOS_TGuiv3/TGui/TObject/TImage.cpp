#include "TObject/TImage.h"

//图像png加载出来一定是8888的格式

 TImage::TImage(const char* filename)
 {
    this->filename = filename;
    imgBufAddr = NULL;
	imgType = 0;
    Decode();			//解码 并 根据图片来确定Image类的参数大小
 }

 TImage::~TImage()
 {
     if(imgBufAddr)
        free(imgBufAddr);
 }


void TImage::Decode()
{
	uint8 res = 0;
	unsigned int wpng,hpng;
    imgType = ObFileType(filename);	//得到文件的类型
    switch(imgType)
	{											  
		case T_JPG:
		case T_JPEG:
			res = jpg_decode_file(&imgBufAddr, &width, &height, filename);				//解码JPG/JPEG	 
			break;
		case T_PNG:
  			res = lodepng_decode32_file(&imgBufAddr, &wpng, &hpng, filename);		//解码png	  
			  width = wpng;
			  height = hpng;
			break;
		case T_BMP:
			res = bmp_decode_file(&imgBufAddr, &width, &height, filename); 				//解码bmp	    	  
			break;
		case T_GIF:                    //先不实现 需要对有TIM
			//res = gif_decode(filename,x,y,width,height);								//解码gif  	    -->需要把 bufaddr ， width ，height 获取过来
			break;
		default:
	 		//res = PIC_FORMAT_ERR;  						//非图片格式!!!  
			break;
	}  	
	if(res)
		printf("\t\n>> decode is failed! the num is %d\t\n",res	);
}

void TImage::ImgLoad(int32 offX, int32 offY,TBuffer* buf)
{

	if(buf->getBufW()  < width + offX )
		return ;
	if(buf->getBufH()  < height + offY)
		return ;
	if(imgType == T_PNG || imgType == T_BMP) 
	{
		ImgBlendLoad(offX,offY,buf);
	}
	else		//其他图片解码都是经过 gui 的绘图函数填充的 ，所以可以直接覆盖即可--快
	{
		uint8* des_addr = buf->getBufAddr() + (offX + offY * buf->getBufW()) * GUI_PIXELSIZE;
		uint8* src_addr = imgBufAddr;
		for(int i = 0;i < height;  i++)
		{
			//memcpy 模式
			memcpy(des_addr,src_addr,width * GUI_PIXELSIZE);
			//dma 模式
			//--------------------------
			src_addr += width * GUI_PIXELSIZE;
			des_addr += buf->getBufW() * GUI_PIXELSIZE;
		}
	}
}


//只针对于 ARGB8888
void TImage::ImgBlendLoad(int32 offX, int32 offY,TBuffer* buf)
{

#if defined ARGB_8888
	uint8* addr = buf->getBufAddr() + (offX + offY * buf->getBufW()) * GUI_PIXELSIZE;
	uint8* imgaddr = imgBufAddr;
	uint8  a = 255; //前景透明色
	uint8 r1,g1,b1; //背景
	uint8 r2,g2,b2; //前景
	uint32 offF = 0;
	uint32 offB = 0; //前后背景的偏移
	if(imgType == T_PNG) //RGBA
	{
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				a = imgaddr[offF + 3];
				r2 = imgaddr[offF];
				g2 = imgaddr[offF + 1];
				b2 = imgaddr[offF + 2];
				r1 = addr[offB + 1];
				g1 = addr[offB + 2];
				b1 = addr[offB + 3];
				addr[offB + 1] = ((r1 * (255 - a)+ r2 * a) >> 8);
				addr[offB + 2] = ((g1 * (255 - a)+ g2 * a) >> 8);
				addr[offB + 3] = ((b1 * (255 - a)+ b2 * a) >> 8);
				offF += GUI_PIXELSIZE;
				offB += GUI_PIXELSIZE;
			}
			offB += (buf->getBufW() - width) * GUI_PIXELSIZE;
		}
	}
	else //ARGB
	{
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				a = imgaddr[offF ];
				r2 = imgaddr[offF + 1];
				g2 = imgaddr[offF + 2];
				b2 = imgaddr[offF + 3];
				r1 = addr[offB + 1];
				g1 = addr[offB + 2];
				b1 = addr[offB + 3];
				addr[offB + 1] = ((r1 * (255 - a)+ r2 * a) >> 8);
				addr[offB + 2] = ((g1 * (255 - a)+ g2 * a) >> 8);
				addr[offB + 3] = ((b1 * (255 - a)+ b2 * a) >> 8);
				offF += GUI_PIXELSIZE;
				offB += GUI_PIXELSIZE;
			}
			offB += (buf->getBufW() - width) * GUI_PIXELSIZE;
		}
	}
#elif defined  ARGB_1555


#endif


}



uint8 TImage::ObFileType(const char *filename)
{
	uint8 *fname = (uint8 *)filename;
	uint8 tbuf[5];
	uint8 *attr='\0';//后缀名
	uint8 i=0;
	while(i<250)
	{
		i++;
		if(*fname=='\0')
			break;//偏移到了最后了.
		fname++;
	}
	if(i==250)return 0XFF;//错误的字符串.
 	for(i=0;i<5;i++)//得到后缀名
	{
		fname--;
		if(*fname=='.')
		{
			fname++;
			attr=fname;
			break;
		}
  	}
	strcpy((char *)tbuf,(const char*)attr);//copy
 	for(i=0;i<4;i++)
	 	tbuf[i] = UPPER(tbuf[i]);//全部变为大写 
	if(strcmp("JPG",(const char *)tbuf)==0)
		return 0x0f;
	else if(strcmp("JPEG",(const char *)tbuf)==0)
		return 0x1f;
	else if(strcmp("PNG",(const char *)tbuf)==0)
		return 0x2f;
	else if(strcmp("BMP",(const char *)tbuf)==0)
		return 0x3f;
	else if(strcmp("GIF",(const char *)tbuf)==0)
		return 0x4f;
	else
		return 0Xff;  //没找到	 			   
}	 





