#include "piclib.h"

extern u32 *ltdc_framebuf[2];	//LTDC LCD帧缓存数组指针,必须指向对应大小的内存区域
	
_pic_info picinfo;	 	//图片信息
_pic_phy pic_phy;		//图片显示物理接口	

u8 ob_filetype(u8 *fname);
//////////////////////////////////////////////////////////////////////////
u32 piclib_read_point(u16 x,u16 y) ;
void piclib_draw_point(u16 x,u16 y,u32 color);
void piclib_draw_hline(u16 x0,u16 y0,u16 len,u32 color) ;
void piclib_fill_color(u16 x,u16 y,u16 width,u16 height,u32 color) ;
void piclib_fill_colors(u16 x,u16 y,u16 width,u16 height,u8 *color) ;

//////////////////////////////////////////////////////////////////////////

u8 jpg_decode_file(u8** out_buf,u16* width,u16* height,const char * filename)
{
	u8 res;	
	piclib_init(NULL,0,0);
	res = jpg_decode_buf(out_buf,width,height,filename);
	return res;
}

u8 bmp_decode_file(u8** out_buf,u16* width,u16* height,const char * filename)
{
	u8 res;	
	piclib_init(NULL,0,0);
	res = bmp_decode_buf(out_buf,width,height,filename);
	return res;
}



//////////////////////////////////////////////////////////////////////////
//画图初始化,在画图之前,必须先调用此函数
//指定画点/读点
void piclib_init(u8* addr,u16 width,u16 height)
{
	pic_phy.read_point 	= piclib_read_point;  	//读点函数实现,仅BMP需要
	pic_phy.draw_point 	= piclib_draw_point;	//画点函数实现
	pic_phy.fill 		= piclib_fill_color;	//填充函数实现,仅GIF需要
	pic_phy.draw_hline 	= piclib_draw_hline;  	//画线函数实现,仅GIF需要
	pic_phy.fillcolor 	= piclib_fill_colors;  	//颜色填充函数实现,仅TJPGD需要 

	picinfo.bufaddr  	=  addr;
	picinfo.bufwidth  	=  width;		//得到LCD的宽度像素
	picinfo.bufheight  	=  height;		//得到LCD的高度像素

	picinfo.ImgWidth 	= 0;	//初始化宽度为0
	picinfo.ImgHeight	= 0;	//初始化高度为0
	picinfo.Div_Fac 	= 0;	//初始化缩放系数为0
	picinfo.S_Width 	= 0;	//初始化设定的宽度为0
	picinfo.S_Height 	= 0;	//初始化设定的高度为0
	picinfo.S_XOFF 		= 0;	//初始化x轴的偏移量为0
	picinfo.S_YOFF 		= 0;	//初始化y轴的偏移量为0
	picinfo.staticx 	= 0;	//初始化当前显示到的x坐标为0
	picinfo.staticy 	= 0;	//初始化当前显示到的y坐标为0
}


//初始化智能画点
//内部调用
void ai_draw_init(void)
{
	float temp,temp1;	   
	temp = (float) picinfo.S_Width / picinfo.ImgWidth;
	temp1 = (float) picinfo.S_Height / picinfo.ImgHeight;						 
	if(temp < temp1)
		temp1 = temp;//取较小的那个	 
	if(temp1 > 1)
		temp1 = 1;	  
	//使图片处于所给区域的中间
	picinfo.S_XOFF += (picinfo.S_Width-temp1 * picinfo.ImgWidth) / 2;
	picinfo.S_YOFF += (picinfo.S_Height-temp1 * picinfo.ImgHeight) / 2;
	temp1 *= 8192;//扩大8192倍	 
	picinfo.Div_Fac = temp1;
	picinfo.staticx = 0xffff;
	picinfo.staticy = 0xffff;//放到一个不可能的值上面			 										    
}   
//判断这个像素是否可以显示
//(x,y) :像素原始坐标
//chg   :功能变量. 
//返回值:0,不需要显示.1,需要显示
u8 is_element_ok(u16 x,u16 y,u8 chg)
{				  
	if(x!=picinfo.staticx||y!=picinfo.staticy)
	{
		if(chg==1)
		{
			picinfo.staticx=x;
			picinfo.staticy=y;
		} 
		return 1;
	}else return 0;
}
//智能画图
//FileName:要显示的图片文件  BMP/JPG/JPEG/GIF
//x,y,width,height:坐标及显示区域尺寸
//fast:使能jpeg/jpg小图片(图片尺寸小于等于液晶分辨率)快速解码,0,不使能;1,使能.
//图片在开始和结束的坐标点范围内显示
u8 ai_load_picfile(const char *filename,u16 x,u16 y,u16 width,u16 height,u8 fast)
{	
	u8	res;//返回值
	u8 type;
	if((x+width)>picinfo.bufwidth)
		return PIC_WINDOW_ERR;		//x坐标超范围了.
	if((y+height)>picinfo.bufheight)
		return PIC_WINDOW_ERR;		//y坐标超范围了.  
	//得到显示方框大小	  	 
	if(width==0||height==0)
		return PIC_WINDOW_ERR;	//窗口设定错误
	picinfo.S_Height=height;
	picinfo.S_Width=width;
	//显示区域无效
	if(picinfo.S_Height==0||picinfo.S_Width==0)
	{
		picinfo.S_Height=picinfo.bufheight;
		picinfo.S_Width=picinfo.bufwidth;
		return FALSE;   
	}
	if(pic_phy.fillcolor==NULL)
	fast=0;//颜色填充函数未实现,不能快速显示
	//显示的开始坐标点
	picinfo.S_YOFF=y;
	picinfo.S_XOFF=x;
	//文件名传递		 
	type=ob_filetype((u8*)filename);	//得到文件的类型
	switch(type)
	{											  
		
		case JPG:
		case JPEG:
			res=jpg_decode(filename,fast);				//解码JPG/JPEG	 
			break;
		case PNG:
  			//res = lodepng_decode32_file(&image, &w, &h, filename);		//解码png	  
			break;
		case BMP:
			res=stdbmp_decode(filename); 				//解码bmp	  	  
			break;
		case GIF:
			res=gif_decode(filename,x,y,width,height);	//解码gif  	  
			break;
		default:
	 		res=PIC_FORMAT_ERR;  						//非图片格式!!!  
			break;
	}  		
	if(!res)
		printf("decode is ok\n") ;  
	else
		printf("decode is failed , num is : %d \n",res) ; 									   
	return res;
}
// -------------------------- //

u32 piclib_read_point(u16 x,u16 y) 
{
	#if GUI_PIXELSIZE == 4
		u32 point = *(uint32_t* )(picinfo.bufaddr + (y * picinfo.bufwidth + x) * GUI_PIXELSIZE);
	#elif GUI_PIXELSIZE == 3
		u32 point =	*(uint8_t* )(picinfo.bufaddr + (y * picinfo.bufwidth + x) * GUI_PIXELSIZE +2);
		point += ((uint16_t)(*(uint8_t* )(picinfo.bufaddr + (y * picinfo.bufwidth + x ) * GUI_PIXELSIZE + 1))) << 8 ;
		point += ((uint32_t)(*(uint8_t* )(picinfo.bufaddr + (y * picinfo.bufwidth + x ) * GUI_PIXELSIZE ))) << 16 ;
	#elif	GUI_PIXELSIZE == 2
		u32 point = *(uint16_t* )(picinfo.bufaddr + (y * picinfo.bufwidth + x) * GUI_PIXELSIZE);
	#endif 
	return point ;
}

void piclib_draw_point(u16 x,u16 y,u32 color)
{
	gui_dma2d_memset((uint32_t*)picinfo.bufaddr,picinfo.bufwidth,color,x ,y ,1,1);
}

//lcd.h没有提供划横线函数,需要自己实现
void piclib_draw_hline(u16 x0,u16 y0,u16 len,u32 color)
{
	if((len==0)||(x0>picinfo.bufwidth)||(y0>picinfo.bufheight))
		return;
	gui_dma2d_memset((uint32_t* )picinfo.bufaddr,picinfo.bufwidth,color,x0,y0,len,1);
}

void piclib_fill_color(u16 x,u16 y,u16 width,u16 height,u32 color)
{
	gui_dma2d_memset((uint32_t* )picinfo.bufaddr,picinfo.bufwidth,color,x ,y ,width,height);
}
//填充颜色
//x,y:起始坐标
//width，height：宽度和高度。
//*color：颜色数组
void piclib_fill_colors(u16 x,u16 y,u16 width,u16 height,u8 *color)
{  
	u32 color_tmp;
	u32 offset;
	u16 i,j;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{ 
			offset = (i * width  + j) * JPEG_PIXELSIZE;
#if JPEG_PIXELSIZE == 2
			color_tmp += (color[offset] << 8);
			color_tmp += (color[offset + 1]);
#else
			color_tmp += (color[offset] << 16);
			color_tmp += (color[offset + 1] << 8);
			color_tmp += (color[offset + 2]);
			color_tmp |= 0xFF000000;
#endif
			gui_dma2d_memset((uint32_t* )picinfo.bufaddr,picinfo.bufwidth, color_tmp , x + j , y + i , 1 , 1);
			color_tmp = 0;
		}
	}
}


//快速ALPHA BLENDING算法.
//src:源颜色
//dst:目标颜色
//alpha:透明程度(0~32)
//返回值:混合后的颜色.
u32 piclib_alpha_blend(u32 src,u32 dst,u8 alpha)
{

	//RGB 565
	u32 src2;
	u32 dst2;	 
	//Convert to 32bit |-----GGGGGG-----RRRRR------BBBBB|
	src2=((src<<16)|src)&0x07E0F81F;
	dst2=((dst<<16)|dst)&0x07E0F81F;   
	//Perform blending R:G:B with alpha in range 0..32
	//Note that the reason that alpha may not exceed 32 is that there are only
	//5bits of space between each R:G:B value, any higher value will overflow
	//into the next component and deliver ugly result.
	dst2=((((dst2-src2)*alpha)>>5)+src2)&0x07E0F81F;
	return (dst2>>16)|dst2;  
}

//动态分配内存
void *pic_memalloc (u32 size)			
{
	return (void*)malloc(size);
}
//释放内存
void pic_memfree (void* mf)		 
{
	free(mf);
}



//-----------------------------------------------------------


//将小写字母转为大写字母,如果是数字,则保持不变.
u8 c_upper(u8 c)
{
	if(c<'A')return c;//数字,保持不变.
	if(c>='a')return c-0x20;//变为大写.
	else return c;//大写,保持不变
}	      

u8 ob_filetype(u8 *fname)
{
	u8 tbuf[5];
	u8 *attr='\0';//后缀名
	u8 i=0;
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
	 	tbuf[i] = c_upper(tbuf[i]);//全部变为大写 
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























