#ifndef _TPAINTDIVER_H_
#define _TPAINTDIVER_H_

#include "tGlobal.h"


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

void setDivFont(tFont* f);
void setDivColor(colorDef textcolor, colorDef backcolor);

void drawDivPoint(int32 x, int32 y);
void drawDivLine(int32 x1, int32 y1, int32 x2, int32 y2);
void drawDivRect(int32 x, int32 y, int32 w, int32 h);
void drawDivCircle(int32 x, int32 y, int32 r);
void drawDivEllipse(int32 x, int32 y, int32 r1, int32 r2);
void drawDivTriangle(int32 x1, int32 y1, int32 x2, int32 y2, int32 x3, int32 y3);
void drawDivFullRect(int32 x, int32 y, int32 w, int32 h);
void drawDivFullCircle(int32 x, int32 y, int32 r);
void drawDivFullEllipse(int32 x, int32 y, int32 r1, int32 r2);
void drawDivFullTriangle(int32 x1, int32 y1, int32 x2, int32 y2, int32 x3, int32 y3);


void drawDivRoundRect(int32 x, int32 y, int32 w, int32 h, int32 r );
void drawDivText(int32 x, int32 y, const char* str, int32 len );

#endif // !_TPAINTDIVER_H_
