#ifndef _TPAINTDIVER_H_
#define _TPAINTDIVER_H_

#include "tGlobal.h"


void setDivFont(tFont* f);
void setDivColor(colorDef textcolor, colorDef backcolor);
void drawDivPoint(int32 x, int32 y);
void drawDivLine(int32 x1, int32 y1, int32 x2, int32 y2);
void drawDivFullRect(int32 x, int32 y, int32 w, int32 h);
void drawDivRoundRect(int32 x, int32 y, int32 w, int32 h, int32 r);

bool isShadow(colorDef c);



#endif // !_TPAINTDIVER_H_
