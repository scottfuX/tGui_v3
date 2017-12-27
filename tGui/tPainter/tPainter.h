#ifndef _TPAINTER_H_
#define _TPAINTER_H_

#include "tGlobal.h"
#include "tContainter/tRectList.h"
#include "tPainter/tPaintDiver.h"



class tPainter
{
public:
	tPainter(tRectList* list = NULL,tRect* invaild = NULL);
	~tPainter() {};
	void setFont(tFont* f) { font = f; setDivFont(f); };
	void setColors(colorDef text, colorDef back);
	void setTextColor(colorDef text) { textcolor = text; setDivColor(text, backcolor);}
	void setBackColor(colorDef back) { backcolor = back; setDivColor(textcolor, back);}

	//basic
	void drawPoint(int32 x, int32 y);
	void drawLine(int32 x1, int32 y1, int32 x2, int32 y2);
	void drawRect(int32 x, int32 y, int32 w, int32 h);
	void drawCircle(int32 x, int32 y, int32 r);
	void drawEllipse(int32 x, int32 y, int32 r1, int32 r2);
	void drawTriangle(int32 x1, int32 y1, int32 x2, int32 y2, int32 x3,  int32 y3);

	void drawFullRect(int32 x, int32 y, int32 w, int32 h);
	void drawFullCircle(int32 x, int32 y, int32 r);
	void drawFullEllipse(int32 x, int32 y, int32 r1, int32 r2);
	void drawFullTriangle(int32 x1, int32 y1, int32 x2, int32 y2, int32 x3, int32 y3);
	void drawRoundRect(int32 x, int32 y, int32 w, int32 h, int32 r = 0);
	void drawText(int32 x, int32 y, const char* str ,int32 len=-1);

	//void drawImage();
	//void drawArrow();
	void drawButton(int32 x, int32 y, int32 w, int32 h, const char* str,bool isPress = false);
	void drawCheck(int32 x, int32 y, int32 w, int32 h, const char* str, bool Selected = false, bool isPress = false, colorDef back = WHITE);
	void drawRadio(int32 x, int32 y, int32 w, int32 h, const char* str, bool Selected = false, bool isPress = false, colorDef back = WHITE);
	void drawHorizSlider(int32 x, int32 y, int32 w, int32 h, int32 value = 0, int32 value_pre = -1, bool isPress = false, colorDef back = WHITE);
	void drawVertSlider(int32 x, int32 y, int32 w, int32 h, int32 value = 0, int32 value_pre = -1, bool isPress = false, colorDef back = WHITE);
	void drawLabel(int32 x, int32 y, int32 w, int32 h, const char* str, colorDef text = BLACK, colorDef back = WHITE);
	
	void drawCenterText(int32 x, int32 y, int32 w, int32 h, const char* str, colorDef text = BLACK,colorDef back = WHITE,bool isAllShow = false);
private:
	tFont*	font;
	colorDef textcolor;
	colorDef backcolor;
	tRectList* rectlist;
	tRect* invaildArea;
	int8 nestingNum;

	void rectCut( tRect *srcRect);
	void paintMeta(tRect* srcRect);
	void drawWinShades(int32 x, int32 y, int32 w, int32 h,
		colorDef c1, colorDef c2, colorDef c3, colorDef c4, colorDef back);
};

//basic

inline void tPainter::drawRoundRect(int32 x, int32 y, int32 w, int32 h, int32 r)
{
	drawDivRoundRect(x, y, w, h, r);
}

inline void tPainter::drawText(int32 x, int32 y, const char* str, int32 len)
{
	drawDivText(x, y, str, len);
}
 

#endif // !_TPAINTER_H_
