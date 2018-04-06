#include "TObject/TImage.h"

//图像png加载出来一定是8888的格式

//fast for png need imgload
 TImage::TImage(const char* filename)  
 {
    this->filename = filename;
    imgBufAddr = NULL;
	imgType = 0;
    Decode();			//解码 并 根据图片来确定Image类的参数大小
 }

//fast for bmp/jpg need have buf
TImage::TImage(uint8* addr,uint16 w,uint16 h,const char* filen) 
{
	imgBufAddr = NULL;
	unsigned int wpng,hpng;
	this->filename = filen;
	imgType = ObFileType(filename);	//得到文件的类型
	switch(imgType)
	{	
		case T_PNG:
		{
			lodepng_decode32_file(&imgBufAddr, &wpng, &hpng, filename);			//解码png	  
			width = wpng;
			height = hpng;
		}break;								  
		case T_JPG:
		case T_JPEG:
		case T_BMP:
			piclib_init(addr,w,h);		
			ai_load_picfile(filename,0,0,w,h,1);
			break;
		case T_GIF: 
				
			break;
		default:
	 		//res = PIC_FORMAT_ERR;  													//非图片格式!!!  
			break;
	}
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
  			res = lodepng_decode32_file(&imgBufAddr, &wpng, &hpng, filename);			//解码png	  
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
	 		//res = PIC_FORMAT_ERR;  													//非图片格式!!!  
			break;
	}  	
	if(res)
		printf("\r\n>> decode is failed! the num is %d\r\n",res	);
}


//混合
// readAddr:	开始 读 的地址
// readSize:	被 读 的区域所在的buf大小
// writeAddr:	开始 写 的地址
// writeSize:	被 写 的区域所在的buf大小
// imgRect:		图片混合的区域

void TImage::imgLoad(uint8* readAddr,TSize* readSize,uint8* writeAddr,TSize* writeSize,TRect* imgTRect)
{
	TRect* imgRect = imgTRect;
	if(imgTRect == NULL) //null 就是全部 
	{
		TRect r(0,0,imgW(),imgH());
		imgRect = &r;
	}
		 
	// if(readSize->width() < imgRect->width() || readSize->height() < imgRect->height() ||
	// 	 writeSize->height() < imgRect->height() || writeSize->width() < imgRect->width() )
	// 	return;

	uint32 point ,color = 0;
	uint8* imgaddr = imgBufAddr;
	uint8  a = 255; //前景透明色
	uint32 r,g,b; 
	uint32 offF = (imgRect->x() + imgRect->y() * width) * GUI_PIXELSIZE; //开始的地址
	
	//------------------------------- blend ---------------- 目前只支持PNG ------------------
	if(imgType == T_PNG /*|| imgType == T_BMP */)
	{
		if(imgType == T_PNG) //RGBA
		{
			for(int i=0;i<imgRect->height();i++)
			{
				for(int j=0;j< imgRect->width() ;j++)
				{
					point = *((uint32*)(readAddr + (j + i * readSize->width()) * GUI_PIXELSIZE)); //读point

					a = imgaddr[offF + 3];
					r = imgaddr[offF];
					g = imgaddr[offF + 1];
					b = imgaddr[offF + 2];
					color |= point & 0xff000000;
					color |= ((((point >> 16) & 0xff)  * (0xff - a) + r * a)  >> 8) << 16;
					color |= ((((point >> 8) & 0xff ) * (0xff - a) + g * a)  >> 8) << 8;
					color |= (((point & 0xff) * (0xff - a) + b * a)  >> 8);

					*((uint32*)(writeAddr + (j + i * writeSize->width()) * GUI_PIXELSIZE)) = color; //写point

					color = 0;
					offF += GUI_PIXELSIZE;
				}
				offF +=  (width - imgRect->width() ) * GUI_PIXELSIZE;
			}
		}
		else //ARGB
		{
			for(int i=0;i< imgRect->height();i++)
			{
				for(int j=0;j< imgRect->width();j++)
				{
					point = *(readAddr +  (j + i * readSize->width()) * GUI_PIXELSIZE);//读point

					a = imgaddr[offF];
					r = imgaddr[offF + 1];
					g = imgaddr[offF + 2];
					b = imgaddr[offF + 3];
					color |= point & 0xff000000;
					color |= ((((point >> 16) & 0xff)  * (0xff - a) + r * a)  >> 8) << 16;
					color |= ((((point >> 8) & 0xff ) * (0xff - a) + g * a)  >> 8) << 8;
					color |= (((point & 0xff) * (0xff - a) + b * a)  >> 8);

					*(writeAddr + (j + i * writeSize->width()) * GUI_PIXELSIZE) = color;//写point

					color = 0;
					offF += GUI_PIXELSIZE;
				}
				offF +=  (width - imgRect->width() ) * GUI_PIXELSIZE;
			}
		}
	}
	//------------------------------- memcpy ------------------ 直接传送 ------------------
	else
	{
		uint8* des_addr = writeAddr;
		uint8* src_addr = imgBufAddr + offF;
		for(int i = 0;i < imgRect->height();  i++)
		{
			gui_memcpy(des_addr,src_addr,imgRect->width() * GUI_PIXELSIZE);
			src_addr += width * GUI_PIXELSIZE;
			des_addr += writeSize->width() * GUI_PIXELSIZE;
		}
	}
		
}


//一个半透明 其中一个是点 进行混合 -- 》加载
void TImage::blendPoint(uint32 argb_color,uint8* readAddr,TSize* readSize,uint8* writeAddr,TSize* writeSize,TRect* imgTRect)
{
	TRect* imgRect = imgTRect;
	if(imgTRect == NULL) //null 就是全部 
	{
		TRect r(0,0,imgW(),imgH());
		imgRect = &r;
	}
		 
	uint32 point,color = 0;
	uint8* imgaddr = imgBufAddr;
	uint8  a = 255; //前景透明色
	uint32 r,g,b; 

	uint8 a1 = argb_color >>24;
	uint8 r1 = (argb_color & 0x00ff0000) >> 16;
	uint8 g1 = (argb_color & 0x0000ff00) >> 8;
	uint8 b1 = (argb_color & 0x000000ff);

	uint32 offF = (imgRect->x() + imgRect->y() * width)*GUI_PIXELSIZE; //开始的地址
	if(imgType == T_PNG) //RGBA
	{
		for(int i=0;i<imgRect->height();i++)
		{
			for(int j=0;j< imgRect->width() ;j++)
			{
				a = imgaddr[offF + 3];
				r = imgaddr[offF];
				g = imgaddr[offF + 1];
				b = imgaddr[offF + 2];
				
				r = (r  * (0xff - a1) + r1 * a1) >> 8;//r
				g = (g  * (0xff - a1) + g1 * a1) >> 8;
				b = (b  * (0xff - a1) + b1 * a1) >> 8;

				point = *((uint32*)(readAddr + (j + i * readSize->width()) * GUI_PIXELSIZE)); //读point

				color |= point & 0xff000000;
				color |= ((((point >> 16) & 0xff)  * (0xff - a) + r * a)  >> 8) << 16;
				color |= ((((point >> 8) & 0xff ) * (0xff - a) + g * a)  >> 8) << 8;
				color |= (((point & 0xff) * (0xff - a) + b * a)  >> 8);

				*((uint32*)(writeAddr + (j + i * writeSize->width()) * GUI_PIXELSIZE)) = color; //写point

				color = 0;
				offF += GUI_PIXELSIZE;
			}
			offF +=  (width - imgRect->width() ) * GUI_PIXELSIZE;
		}
	}
	else //ARGB
	{
		for(int i=0;i< imgRect->height();i++)
		{
			for(int j=0;j< imgRect->width();j++)
			{
				a = imgaddr[offF];
				r = imgaddr[offF + 1];
				g = imgaddr[offF + 2];
				b = imgaddr[offF + 3];

				r = (r  * (0xff - a1) + r1 * a1) >> 8;//r
				g = (g  * (0xff - a1) + g1 * a1) >> 8;
				b = (b  * (0xff - a1) + b1 * a1) >> 8;

				point = *((uint32*)(readAddr + (j + i * readSize->width()) * GUI_PIXELSIZE)); //读point

				color |= point & 0xff000000;
				color |= ((((point >> 16) & 0xff)  * (0xff - a) + r * a)  >> 8) << 16;
				color |= ((((point >> 8) & 0xff ) * (0xff - a) + g * a)  >> 8) << 8;
				color |= (((point & 0xff) * (0xff - a) + b * a)  >> 8);

				*(writeAddr + (j + i * writeSize->width()) * GUI_PIXELSIZE) = color;//写point

				color = 0;
				offF += GUI_PIXELSIZE;
			}
			offF +=  (width - imgRect->width() ) * GUI_PIXELSIZE;
		}
	}
}


//两个半透明 其中一个是点 进行混合 -- 》加载
void TImage::doubleBlendPoint(uint32 argb_color,uint8* readAddr,TSize* readSize,uint8* writeAddr,TSize* writeSize,TRect* imgTRect)
{
	TRect* imgRect = imgTRect;
	if(imgTRect == NULL) //null 就是全部 
	{
		TRect r(0,0,imgW(),imgH());
		imgRect = &r;
	}
		 
	uint32 point,color = 0;
	uint8* imgaddr = imgBufAddr;
	uint8  a = 255; //前景透明色
	uint32 r,g,b; 

	uint8 a1 = argb_color >>24;
	uint8 r1 = (argb_color & 0x00ff0000) >> 16;
	uint8 g1 = (argb_color & 0x0000ff00) >> 8;
	uint8 b1 = (argb_color & 0x000000ff);

	uint32 offF = (imgRect->x() + imgRect->y() * width)*GUI_PIXELSIZE; //开始的地址
	if(imgType == T_PNG) //RGBA
	{
		for(int i=0;i<imgRect->height();i++)
		{
			for(int j=0;j< imgRect->width() ;j++)
			{
				a = imgaddr[offF + 3];
				r = imgaddr[offF];
				g = imgaddr[offF + 1];
				b = imgaddr[offF + 2];
				a = (a+a1-a*a1/255) ;
				r = doubleBlendFunc(a1,r1,a,r) ;//r
				g = doubleBlendFunc(a1,g1,a,g) ;
				b = doubleBlendFunc(a1,b1,a,b);

				point = *((uint32*)(readAddr + (j + i * readSize->width()) * GUI_PIXELSIZE)); //读point

				color |= point & 0xff000000;
				color |= ((((point >> 16) & 0xff)  * (0xff - a) + r * a)  >> 8) << 16;
				color |= ((((point >> 8) & 0xff ) * (0xff - a) + g * a)  >> 8) << 8;
				color |= (((point & 0xff) * (0xff - a) + b * a)  >> 8);

				*((uint32*)(writeAddr + (j + i * writeSize->width()) * GUI_PIXELSIZE)) = color; //写point

				color = 0;
				offF += GUI_PIXELSIZE;
			}
			offF +=  (width - imgRect->width() ) * GUI_PIXELSIZE;
		}
	}
	else //ARGB
	{
		for(int i=0;i< imgRect->height();i++)
		{
			for(int j=0;j< imgRect->width();j++)
			{
				a = imgaddr[offF];
				r = imgaddr[offF + 1];
				g = imgaddr[offF + 2];
				b = imgaddr[offF + 3];

				a = (a+a1-a*a1/255);//a
				r = doubleBlendFunc(a1,r1,a,r) ;//r
				g = doubleBlendFunc(a1,g1,a,g) ;
				b = doubleBlendFunc(a1,b1,a,b);

				point = *((uint32*)(readAddr + (j + i * readSize->width()) * GUI_PIXELSIZE)); //读point

				color |= point & 0xff000000;
				color |= ((((point >> 16) & 0xff)  * (0xff - a) + r * a)  >> 8) << 16;
				color |= ((((point >> 8) & 0xff ) * (0xff - a) + g * a)  >> 8) << 8;
				color |= (((point & 0xff) * (0xff - a) + b * a)  >> 8);

				*(writeAddr + (j + i * writeSize->width()) * GUI_PIXELSIZE) = color;//写point

				color = 0;
				offF += GUI_PIXELSIZE;
			}
			offF +=  (width - imgRect->width() ) * GUI_PIXELSIZE;
		}
	}
}



// R   =   R1   *   Alpha1   +   R2   *   Alpha2   *   (1-Alpha1)   
// G   =   G1   *   Alpha1   +   G2   *   Alpha2   *   (1-Alpha1)     
// B   =   B1   *   Alpha1   +   B2   *   Alpha2   *   (1-Alpha1)   
// Alpha   =   1   -   (1   -   Alpha1)   *   (1   -   Alpha2)   
// R   =   R   /   Alpha   
// G   =   G   /   Alpha   
// B   =   B   /   Alpha   
// R1、G1、B1、Alpha1指上层的颜色值   
// R2、G2、B2、Alpha2指下层的颜色值   

//c12 = ( cb * ab * (1 - af) + cf * af )/( ab + af - ab * af )
//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
//c12 = (cb * ab * (255 - af) + 255 * (cf * af)) /(255 * (ab + af) - ab * af)

uint8 TImage::doubleBlendFunc(uint8 af,uint8 cf,uint8 ab,uint8 cb)
{
	return (cb * ab * (255 - af) + 255 * (cf * af)) /(255 * (ab + af) - ab * af);
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





