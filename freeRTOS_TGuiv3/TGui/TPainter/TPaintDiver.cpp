#include "TPainter/TPaintDiver.h"

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

void drawDivFullRect(int32 x, int32 y, int32 w, int32 h)
{
	LCD_DrawFullRect(x, y, w, h);
}

void drawDivRoundRect(int32 x, int32 y, int32 w, int32 h, int32 r )
{

}

bool isShadow(colorDef c)
{
#ifdef ARB8888
	int32 B =  c & 0x000000FF;
	int32 G = (c & 0x0000FF00) >> 8;
	int32 R = (c & 0x00FF0000) >> 16;
#endif 	
	
#ifdef RGB888
	int32 B =  c & 0x0000FF;
	int32 G = (c & 0x00FF00) >> 8;
	int32 R = (c & 0xFF0000) >> 16;
#endif // DEBUG

#ifdef RGB565
	nt32 B = c & 0x1F;
	int32 G = (c & 0x7E0) >> 5;
	int32 R = (c & 0xF800) >> 11;
#endif
	if (R * 299 / 1000 + G * 587 / 1000 + B * 114 / 1000 >= 192) //亮
		return false;
	return true;

}
