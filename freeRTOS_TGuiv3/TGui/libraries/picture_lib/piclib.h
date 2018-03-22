#ifndef __PICLIB_H
#define __PICLIB_H	  		  
#include <stdlib.h>
#include "interface_conf/tgui_conf.h"
#include "bmp.h"
#include "tjpgd.h"
#include "gif.h"


#define JPEG_PIXELSIZE     3


#define PIC_FORMAT_ERR		0x27	//格式错误
#define PIC_SIZE_ERR		0x28	//图片尺寸错误
#define PIC_WINDOW_ERR		0x29	//窗口设定错误
#define PIC_MEM_ERR			0x11	//内存错误
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TRUE
#define TRUE    1
#endif
#ifndef FALSE
#define FALSE   0
#endif 

//图片显示物理层接口  
//在移植的时候,必须由用户自己实现这几个函数
typedef struct 
{
	u32(*read_point)(u16,u16);				//u32 read_point(u16 x,u16 y)						读点函数
	void(*draw_point)(u16,u16,u32);			//void draw_point(u16 x,u16 y,u32 color)		    画点函数
 	void(*fill)(u16,u16,u16,u16,u32);		///void fill(u16 sx,u16 sy,u16 ex,u16 ey,u32 color) 单色填充函数 	 
 	void(*draw_hline)(u16,u16,u16,u32);		//void draw_hline(u16 x0,u16 y0,u16 len,u16 color)  画水平线函数	 
 	void(*fillcolor)(u16,u16,u16,u16,u8*);	//void piclib_fill_color(u16 x,u16 y,u16 width,u16 height,u16 *color) 颜色填充
}_pic_phy; 

extern _pic_phy pic_phy;



#define 	JPG		0x0f
#define 	JPEG	0x1f
#define 	PNG		0x2f
#define  	BMP   	0x3f
#define 	GIF		0x4f
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//图像信息
typedef struct
{		
	u8* bufaddr;		//显存buf的地址
	u16 bufwidth;		//显存buf的宽度
	u16 bufheight;	//显存buf的高度

	u32 ImgWidth; 	//图像的实际宽度和高度
	u32 ImgHeight;

	u32 Div_Fac;  	//缩放系数 (扩大了8192倍的)
	
	u32 S_Height; 	//设定的高度和宽度
	u32 S_Width;
	
	u32	S_XOFF;	  	//x轴和y轴的偏移量
	u32 S_YOFF;

	u32 staticx; 	//当前显示到的ｘｙ坐标
	u32 staticy;																 	
}_pic_info;
extern _pic_info picinfo;//图像信息
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void piclib_init(u8* addr,u16 width,u16 height);
u8 jpg_decode_file(u8** out_buf,u16* width,u16* height,const char * filename);
u8 bmp_decode_file(u8** out_buf,u16* width,u16* height,const char * filename);


void piclib_fill_colors(u16 x,u16 y,u16 width,u16 height,u8 *color);
u32 piclib_alpha_blend(u32 src,u32 dst,u8 alpha);	//alphablend处理
void ai_draw_init(void);							//初始化智能画图
u8 ai_load_picfile(const char *filename,u16 x,u16 y,u16 width,u16 height,u8 fast);//智能画图
u8 is_element_ok(u16 x,u16 y,u8 chg);				//判断像素是否有效
void *pic_memalloc (u32 size);	//pic申请内存
void pic_memfree (void* mf);	//pic释放内存
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif






























