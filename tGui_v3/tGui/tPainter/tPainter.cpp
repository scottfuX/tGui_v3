#include "tPainter/tPainter.h"


tPainter::tPainter()
{
	font = &Font16x24;
	textcolor = 0;
	backcolor = 0;
}

void tPainter::setColors(colorDef text, colorDef back)
{
	textcolor = text;
	backcolor = back; 
	setDivColor(text, back); 
};
/**
* 窗口画图方法 用于窗口和按键
*/
void tPainter::drawWinShades(int32 x, int32 y, int32 w, int32 h,
	colorDef c1, colorDef c2, colorDef c3, colorDef c4, colorDef back)
{
	setTextColor(c1); //上外框
	drawDivLine(x, y + h - 2, x, y);
	drawDivLine(x, y, x + w - 2, y);
	setTextColor(c2);//下外框
	drawDivLine( x, y + h - 1, x + w - 1, y + h - 1);
	drawDivLine( x + w - 1, y + h - 1, x + w - 1, y);
	setTextColor(c3);//上内框
	drawDivLine(x + 1, y + h - 3, x + 1, y + 1);
	drawDivLine(x + 1, y + 1, x + w - 3, y + 1);
	setTextColor(c4);//下内框
	drawDivLine(x + 1, y + h - 2, x + w - 2, y + h - 2);
	drawDivLine(x + w - 2, y + h - 2, x + w - 2, y + 1);
	setTextColor(back);
	drawDivFullRect(x + 2 , y + 2, w - 4, h - 4);
}

//button isPress 表示是否按下状态
void tPainter::drawButton(int32 x, int32 y, int32 w, int32 h, const char* str, int32 len ,bool isPress, colorDef back)
{
	if (isPress)//按下
		drawWinShades(x, y, w, h, MIDLIGHT, LIGHT, DARK, MIDLIGHT, back);
	else//未按下
		drawWinShades(x, y, w, h, LIGHT, DARK, MIDLIGHT, MIDDARK, back);
	setColors(BLACK,back);
	drawCenterText(x, y, w, h, str, len);
}

void tPainter::drawCenterText(int32 x, int32 y, int32 w, int32 h, const char* str, int32 len, bool isAllShow)
{
	 x += (w - font->Width*len )/ 2;
	 y += (h - font->Height) / 2;
	if (x < 0 || y < 0)
		//自动缩小字体，通过存字体的列表，这里先不做处理
		return;
	else
		drawDivText(x, y, str, len);
}