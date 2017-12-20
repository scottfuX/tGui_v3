#include "tPainter/tPaintDiver.h"

void setDivFont(tFont* f)
{
	LCD_SetFont(f);
}

void setDivColor(colorDef textcolor, colorDef backcolor)
{
	LCD_SetColors(textcolor, backcolor);
}

void drawDivPoint(int32 x, int32 y)
{
	PutPixel(x, y);
}

void drawDivLine(int32 x1, int32 y1, int32 x2, int32 y2)
{
	if (x1 == x2)
		if(y1 < y2)
			LCD_DrawLine(x1, y1,y2 - y1, LCD_DIR_VERTICAL);
		else
			LCD_DrawLine(x1, y2, y1- y2  , LCD_DIR_VERTICAL);
	else if (y1 == y2)
		if (x1 < x2)
		LCD_DrawLine(x1, y1,  x2 - x1, LCD_DIR_HORIZONTAL);
		else
			LCD_DrawLine(x2, y1, x1 - x2, LCD_DIR_HORIZONTAL);
	else
		LCD_DrawUniLine(x1, y1, x2, y2);
}

void drawDivRect(int32 x, int32 y, int32 w, int32 h)
{
	LCD_DrawRect(x, y, w, h);
}

void drawDivCircle(int32 x, int32 y, int32 r)
{
	LCD_DrawCircle(x, y, r);
}

void drawDivEllipse(int32 x, int32 y, int32 r1, int32 r2)
{
	LCD_DrawEllipse(x, y, r1, r2);
}

void drawDivTriangle(int32 x1, int32 y1, int32 x2, int32 y2, int32 x3, int32 y3)
{
	drawDivLine(x1, y1, x2, y2);
	drawDivLine(x2, y2, x3, y3);
	drawDivLine(x3, y3, x1, y1);
}

void drawDivFullRect(int32 x, int32 y, int32 w, int32 h)
{
	LCD_DrawFullRect(x, y, w, h);
}
void drawDivFullCircle(int32 x, int32 y, int32 r)
{
	LCD_DrawFullCircle(x, y, r);
}
void drawDivFullEllipse(int32 x, int32 y, int32 r1, int32 r2)
{
	LCD_DrawFullEllipse(x, y, r1, r2);
}
void drawDivFullTriangle(int32 x1, int32 y1, int32 x2, int32 y2, int32 x3, int32 y3)
{
	LCD_FillTriangle(x1, x2, x3, y1, y2, y3);
}
void drawDivRoundRect(int32 x, int32 y, int32 w, int32 h, int32 r )
{

}
void drawDivText(int32 x, int32 y, const char* str, int32 len )
{
	const char* pstr = str;
	for(int i=0;i<len;i++)
	{
		LCD_DisplayChar(y, x + i*(LCD_GetFont()->Width), *(pstr+i));
	}
}