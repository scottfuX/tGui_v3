#ifndef _TPAINTER_H_
#define _TPAINTER_H_

#include "tGlobal.h"
#include "tPainter/tPaintDiver.h"



class tPainter
{
public:
	tPainter();
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
	void drawButton(int32 x, int32 y, int32 w, int32 h, const char* str,bool isPress = false,colorDef back = MID);
	void drawCheck(int32 x, int32 y, int32 w, int32 h, const char* str, bool Selected = false, bool isPress = false, colorDef back = WHITE);
	void drawRadio(int32 x, int32 y, int32 w, int32 h, const char* str, bool Selected = false, bool isPress = false, colorDef back = WHITE);
	void drawSlider(int32 x, int32 y, int32 w, int32 h, int32 value = 0, int32 value_pre = -1, bool isPress = false, colorDef back = MID);
	void drawCenterText(int32 x, int32 y, int32 w, int32 h, const char* str,bool isAllShow = false);
private:
	tFont*	font;
	colorDef textcolor;
	colorDef backcolor;

	void drawWinShades(int32 x, int32 y, int32 w, int32 h,
		colorDef c1, colorDef c2, colorDef c3, colorDef c4, colorDef back);
};

//basic
inline void tPainter::drawPoint(int32 x, int32 y)
{
	drawDivPoint(x, y);
}
inline void tPainter::drawLine(int32 x1, int32 y1, int32 x2, int32 y2)
{
	drawDivLine(x1, y1, x2, y2);
}
inline void tPainter::drawRect(int32 x, int32 y, int32 w, int32 h)
{
	drawDivRect( x,  y,  w,  h);
}
inline void tPainter::drawCircle(int32 x, int32 y, int32 r)
{
	drawDivCircle(x, y, r);
}
inline void tPainter::drawEllipse(int32 x, int32 y, int32 r1, int32 r2)
{
	drawDivEllipse(x, y, r1, r2);
}
inline void tPainter::drawTriangle(int32 x1, int32 y1, int32 x2, int32 y2, int32 x3, int32 y3)
{
	drawDivTriangle( x1,  y1,  x2,  y2,  x3,  y3);
}

inline void tPainter::drawFullRect(int32 x, int32 y, int32 w, int32 h)
{
	drawDivFullRect( x,  y,  w,  h);
}
inline void tPainter::drawFullCircle(int32 x, int32 y, int32 r)
{
	drawDivFullCircle(x, y, r);
}
inline void tPainter::drawFullEllipse(int32 x, int32 y, int32 r1, int32 r2)
{
	drawDivFullEllipse(x, y, r1, r2);
}
inline void tPainter::drawFullTriangle(int32 x1, int32 y1, int32 x2, int32 y2, int32 x3, int32 y3)
{
	drawDivFullTriangle(x1, y1, x2, y2, x3, y3);
}
inline void tPainter::drawRoundRect(int32 x, int32 y, int32 w, int32 h, int32 r)
{
	drawDivRoundRect(x, y, w, h, r);
}
inline void tPainter::drawText(int32 x, int32 y, const char* str, int32 len)
{
	drawDivText(x, y, str, len);
}
 

#endif // !_TPAINTER_H_