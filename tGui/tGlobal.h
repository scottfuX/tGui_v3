#ifndef _TGLOBAL_H_
#define _TGLOBAL_H_				 

extern "C" {
#include "interface_conf/tgui_conf.h"
}

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


//__IO means volatile
//__I means volatile and const

#endif // !_TGLOBAL_H_

