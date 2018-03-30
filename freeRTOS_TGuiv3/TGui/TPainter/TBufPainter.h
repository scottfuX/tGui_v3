#ifndef _TBUFPAINTER_H_
#define _TBUFPAINTER_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "interface_conf/tgui_conf.h"
#ifdef __cplusplus
}
#endif

#include "TGlobal.h"
#include "TWidget/TWidget.h"
#include "TObject/TFont.h"


class TBufPainter
{
public:
	TBufPainter(uint8* addr,TRect* rect);
	~TBufPainter();
	TFont* getFontCH() { return fontCH; }
	void setFontCH(const char *filename,uint16 width,uint16 height,uint8 codetype = T_GBK);
	T_ASCII_FONT* getFontEn() { return fontEn; }
	void setFontEn(T_ASCII_FONT* f){fontEn = f;};
	void setColors(colorDef text, colorDef back);
	void setTextColor(colorDef text) { textcolor = text;}
	void setBackColor(colorDef back) { backcolor = back;}

	//basic
	void drawPoint(int32 x, int32 y);
	void drawLine(int32 x1, int32 y1, int32 x2, int32 y2);
	void drawNLine(int32 x1, int32 y1, int32 x2, int32 y2);
	void drawVLine(int32 x, int32 y,int32 len);
	void drawHLine(int32 x, int32 y,int32 len);
	void drawRect(int32 x, int32 y, int32 w, int32 h);
	void drawCircle(int32 x, int32 y, int32 r);
	void drawEllipse(int32 x, int32 y, int32 r1, int32 r2);
	void drawTriangle(int32 x1, int32 y1, int32 x2, int32 y2, int32 x3,  int32 y3);

	void drawFullRect(int32 x, int32 y, int32 w, int32 h);
	void drawFullCircle(int32 x, int32 y, int32 r);
	void drawFullEllipse(int32 x, int32 y, int32 r1, int32 r2);
	void drawFullTriangle(int32 x1, int32 y1, int32 x2, int32 y2, int32 x3, int32 y3);
	void drawRoundRect(int32 x, int32 y, int32 w, int32 h, int32 r = 0);

	void drawAlignText(const char* str,uint8 align = ALIGN_CENTER, colorDef text = BLACK );
	void drawAlignText(int32 x, int32 y,const char* str,uint8 align = ALIGN_CENTER, colorDef text = BLACK );
	void drawString(int32 x, int32 y, const char* str,colorDef text = BLACK);
	// void drawEnAlignText(int32 x, int32 y, const char* str,uint8 align = ALIGN_CENTER, colorDef text = BLACK );
	// void drawCHAlignText(int32 x, int32 y, const char* str,uint8 align = ALIGN_CENTER, colorDef text = BLACK );
	void drawCenterText(int32 x, int32 y, int32 w, int32 h, const char* str, colorDef text = BLACK,colorDef back = WHITE, bool hasBack = false);

	void drawButton(int32 x, int32 y, int32 w, int32 h, const char* str,bool isPress = false);
	void drawCheck(int32 x, int32 y, int32 w, int32 h, const char* str, bool Selected = false, bool isPress = false, colorDef back = WHITE);
	void drawRadio(int32 x, int32 y, int32 w, int32 h, const char* str, bool Selected = false, bool isPress = false, colorDef back = WHITE);
	void drawHorizSlider(int32 x, int32 y, int32 w, int32 h, int32 value = 0, int32 value_pre = -1, bool isPress = false, colorDef back = WHITE);
	void drawVertSlider(int32 x, int32 y, int32 w, int32 h, int32 value = 0, int32 value_pre = -1, bool isPress = false, colorDef back = WHITE);
	void drawHorizScroll(int32 x, int32 y, int32 w, int32 h, int32 scrollLen , int32 value = 0, int32 value_pre = -1, bool isPress = false, colorDef back = WHITE);
	void drawVertScroll(int32 x, int32 y, int32 w, int32 h, int32 scrollLen ,int32 value = 0, int32 value_pre = -1, bool isPress = false, colorDef back = WHITE);
	void drawLabel(int32 x, int32 y, int32 w, int32 h, const char* str, colorDef text = BLACK, colorDef back = WHITE);
	void drawDialog(int32 x, int32 y, int32 w, int32 h, const char* str, bool hasFocus = true, colorDef back = MIDLIGHT);
	void drawDialogTitle(int32 x, int32 y, int32 w, const char* str, bool hasFocus = true);
private:
	T_ASCII_FONT* fontEn;
	TFont*	fontCH;
	colorDef textcolor;
	colorDef backcolor;
	uint8* bufAddr;
    TRect*  bufRect;

	void paintMeta(TRect* srcRect);
	void displayEnChar(int32 x,int32 y,uint8 Ascii, bool hasBack);
	void displayCHChar(int32 x,int32 y,uint8* code,bool hasBack);
	void drawWinShades(int32 x, int32 y, int32 w, int32 h,colorDef c1, 
		colorDef c2,colorDef c3, colorDef c4, colorDef back, bool hasBack = true);
};

#endif //!_TBUFPAINTER_H_
