#ifndef _TGLOBAL_H_
#define _TGLOBAL_H_				 

extern "C" {
#include "interface_conf/tgui_conf.h"
}

#define RGB888    //定义显示屏每个像素类型



#define MAX(x,y) x>y?x:y
#define MIN(x,y) x<y?x:y
#define ABS(x)  ( (x)>0?(x):-(x) ) 

#define COVERNUM 5 
//copy from stm32
typedef signed long  int32;
typedef signed short int16;
typedef signed char  int8;
typedef signed long  const intc32; /* Read Only */
typedef signed short const intc16; /* Read Only */
typedef signed char  const intc8; /* Read Only */
typedef volatile signed long  vint32;
typedef volatile signed short vint16;
typedef volatile signed char  vint8;
typedef volatile signed long  const vintc32; /* Read Only */
typedef volatile signed short const vintc16; /* Read Only */
typedef volatile signed char  const vintc8; /* Read Only */
typedef unsigned long  uint32;
typedef unsigned short uint16;
typedef unsigned char  uint8;
typedef unsigned long  const uintc32; /* Read Only */
typedef unsigned short const uintc16; /* Read Only */
typedef unsigned char  const uintc8; /* Read Only */
typedef volatile unsigned long  vuint32;
typedef volatile unsigned short vuint16;
typedef volatile unsigned char  vuint8;
typedef volatile unsigned long  const vuintc32; /* Read Only */
typedef volatile unsigned short const vuintc16; /* Read Only */
typedef volatile unsigned char  const vuintc8; /* Read Only */

class tObject;
typedef void (tObject::*func)(int,int);

//信息与槽机制 传递参数类型 d1 = type 或 d1 = xpos ， d2 = data 或 d2 = ypos
#define TYPE_INT	-1
#define TYPE_CHAR	-2
#define TYPE_STRING -3

//RGB888
#define GREY0	0xF7F7F7
#define GREY1	0xE5E5E5
#define GREY2	0xDBDBDB
#define GREY3	0xC9C9C9
#define GREY4	0xB7B7B7
#define GREY5	0xABABAB
#define GREY6	0x8C8C8C
#define GREY7	0x696969
#define BLACK	0x000000
#define WHITE	0xFFFFFF
#define RED		0xFF0000
#define GREEN	0x008000
#define BLUE	0x0000FF
#define PUEPLE	0x800080
#define GOLD	0xFFD700
#define ROYALBLUE 0x4876FF
#define SKYBLUE 0x00B2EE
#define LIGHT	  GREY0
#define DARK	  GREY7
#define MID		  GREY2
#define MIDLIGHT  GREY1
#define MIDDARK   GREY5


#define WIN_TITLE_H  30

typedef int32 colorDef;
typedef sFONT tFont;

//__IO means volatile
//__I means volatile and const

#endif // !_TGLOBAL_H_

