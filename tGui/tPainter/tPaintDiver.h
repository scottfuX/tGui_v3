#ifndef _TPAINTDIVER_H_
#define _TPAINTDIVER_H_

#include "tGlobal.h"


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
