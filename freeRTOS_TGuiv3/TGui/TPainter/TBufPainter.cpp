#include "TPainter/TBufPainter.h"




TBufPainter::TBufPainter(uint8* addr,TRect* rect)
{
	if(TFON_TYPE != 0)
		fontCH = new TFont(TFON_FILE,TFON_WIDTH,TFON_HEIGHT,TFON_TYPE);
	fontEn = &TFON_ASCII;
	textcolor = 0;
	backcolor = 0;
    bufAddr = addr;
    bufRect = rect;
}


TBufPainter::~TBufPainter()
{
	if(fontCH)
		delete fontCH;
}

void TBufPainter::setColors(colorDef text, colorDef back)
{
	textcolor = text;
	backcolor = back; 
};


void TBufPainter::setFontCH(const char *filename,uint16 width,uint16 height,uint8 codetype)
{
	if(fontCH)
		delete fontCH;
	fontCH = new TFont(filename, width, height, codetype);
}

void TBufPainter::drawPoint(int32 x, int32 y)
{
		TRect rect(x, y, 1, 1);
		paintMeta(&rect);
}

void TBufPainter::drawHLine(int32 x, int32 y,int32 len)
{
    TRect rect(x, y,len,1);
	paintMeta(&rect);
}

void TBufPainter::drawVLine(int32 x, int32 y,int32 len)
{
    TRect rect(x, y,1,len);
	paintMeta(&rect);
}

void TBufPainter::drawNLine(int32 x1, int32 y1, int32 x2, int32 y2)
{
	int32 deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
			yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
			curpixel = 0;

		deltax = ABS(x2 - x1);        /* The difference between the x's */
		deltay = ABS(y2 - y1);        /* The difference between the y's */
		x = x1;                       /* Start x off at the first pixel */
		y = y1;                       /* Start y off at the first pixel */

		if (x2 >= x1)                 /* The x-values are increasing */
		{
			xinc1 = 1;
			xinc2 = 1;
		}
		else                          /* The x-values are decreasing */
		{
			xinc1 = -1;
			xinc2 = -1;
		}

		if (y2 >= y1)                 /* The y-values are increasing */
		{
			yinc1 = 1;
			yinc2 = 1;
		}
		else                          /* The y-values are decreasing */
		{
			yinc1 = -1;
			yinc2 = -1;
		}

		if (deltax >= deltay)         /* There is at least one x-value for every y-value */
		{
			xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
			yinc2 = 0;                  /* Don't change the y for every iteration */
			den = deltax;
			num = deltax / 2;
			numadd = deltay;
			numpixels = deltax;         /* There are more x-values than y-values */
		}
		else                          /* There is at least one y-value for every x-value */
		{
			xinc2 = 0;                  /* Don't change the x for every iteration */
			yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
			den = deltay;
			num = deltay / 2;
			numadd = deltax;
			numpixels = deltay;         /* There are more y-values than x-values */
		}

		for (curpixel = 0; curpixel <= numpixels; curpixel++)
		{
			drawPoint(x, y);             /* Draw the current pixel */
			num += numadd;              /* Increase the numerator by the top of the fraction */
			if (num >= den)             /* Check if numerator >= denominator */
			{
				num -= den;               /* Calculate the new numerator value */
				x += xinc1;               /* Change the x as appropriate */
				y += yinc1;               /* Change the y as appropriate */
			}
			x += xinc2;                 /* Change the x as appropriate */
			y += yinc2;                 /* Change the y as appropriate */
		}
}

void TBufPainter::drawLine(int32 x1, int32 y1, int32 x2, int32 y2)
{
	if (x1 == x2)//竖直
	{
		if (y2 > y1)
		{
			drawVLine(x1,y1,y2 - y1 + 1);
		}
		else
		{
			drawVLine(x1,y2,y1 - y2 + 1);
		}
	}
	else if (y1 == y2)//水平
	{
		if (x2 > x1)
		{
			drawHLine(x1, y1, x2 - x1 + 1);
		}
		else
		{
			drawHLine(x2, y1, x1 - x2 + 1);
		}
	}
	else
	{
	
		int32 deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
			yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
			curpixel = 0;

		deltax = ABS(x2 - x1);        /* The difference between the x's */
		deltay = ABS(y2 - y1);        /* The difference between the y's */
		x = x1;                       /* Start x off at the first pixel */
		y = y1;                       /* Start y off at the first pixel */

		if (x2 >= x1)                 /* The x-values are increasing */
		{
			xinc1 = 1;
			xinc2 = 1;
		}
		else                          /* The x-values are decreasing */
		{
			xinc1 = -1;
			xinc2 = -1;
		}

		if (y2 >= y1)                 /* The y-values are increasing */
		{
			yinc1 = 1;
			yinc2 = 1;
		}
		else                          /* The y-values are decreasing */
		{
			yinc1 = -1;
			yinc2 = -1;
		}

		if (deltax >= deltay)         /* There is at least one x-value for every y-value */
		{
			xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
			yinc2 = 0;                  /* Don't change the y for every iteration */
			den = deltax;
			num = deltax / 2;
			numadd = deltay;
			numpixels = deltax;         /* There are more x-values than y-values */
		}
		else                          /* There is at least one y-value for every x-value */
		{
			xinc2 = 0;                  /* Don't change the x for every iteration */
			yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
			den = deltay;
			num = deltay / 2;
			numadd = deltax;
			numpixels = deltay;         /* There are more y-values than x-values */
		}

		for (curpixel = 0; curpixel <= numpixels; curpixel++)
		{
			drawPoint(x, y);             /* Draw the current pixel */
			num += numadd;              /* Increase the numerator by the top of the fraction */
			if (num >= den)             /* Check if numerator >= denominator */
			{
				num -= den;               /* Calculate the new numerator value */
				x += xinc1;               /* Change the x as appropriate */
				y += yinc1;               /* Change the y as appropriate */
			}
			x += xinc2;                 /* Change the x as appropriate */
			y += yinc2;                 /* Change the y as appropriate */
		}
	}
	
}

void TBufPainter::drawRect(int32 x, int32 y, int32 w, int32 h)
{
	drawLine(x, y, x, y + h - 1);
	drawLine(x, y, x + w - 1, y);
	drawLine(x, y + h - 1, x + w - 1, y + h - 1);
	drawLine(x + w - 1, y, x + w - 1, y + h - 1);
}

void TBufPainter::drawTriangle(int32 x1, int32 y1, int32 x2, int32 y2, int32 x3, int32 y3)
{
	drawLine(x1, y1, x2, y2);
	drawLine(x1, y1, x3, y3);
	drawLine(x3, y3, x2, y2);

}

void TBufPainter::drawCircle(int32 x, int32 y, int32 r)
{
	int a, b, num;
	a = 0;
	b = r;
	while (22 * b * b >= r * r)          // 1/8圆即可  
	{
		drawPoint(x + a, y - b); // 0~1  
		drawPoint(x - a, y - b); // 0~7  
		drawPoint(x - a, y + b); // 4~5  
		drawPoint(x + a, y + b); // 4~3  

		drawPoint(x + b, y + a); // 2~3  
		drawPoint(x + b, y - a); // 2~1  
		drawPoint(x - b, y - a); // 6~7  
		drawPoint(x - b, y + a); // 6~5  
		a++;
		num = (a * a + b * b) - r*r;
		if (num > 0)
		{
			b--;
			a--;
		}
	}
}

void TBufPainter::drawEllipse(int32 x, int32 y, int32 r1, int32 r2)
{
	double sqa = r1*r1;
	double sqb = r2*r2;

	double d = sqb + sqa*(0.25 - r2);
	int xt = 0;
	int yt = r2;

	// 1
	drawPoint((x + xt), (y + yt));
	// 2
	drawPoint((x + xt), (y - yt));
	// 3
	drawPoint((x - xt), (y - yt));
	// 4
	drawPoint((x - xt), (y + yt));

	// 1
	while (sqb*(xt + 1) < sqa*(yt - 0.5))
	{
		if (d < 0)
		{
			d += sqb*(2 * xt + 3);
		}
		else
		{
			d += (sqb*(2 * xt + 3) + sqa*((-2)*yt + 2));
			--yt;
		}
		++xt;
		drawPoint((x + xt), (y + yt));
		drawPoint((x + xt), (y - yt));
		drawPoint((x - xt), (y - yt));
		drawPoint((x - xt), (y + yt));
	}
	d = (r2 * (xt + 0.5)) * 2 + (r1 * (yt - 1)) * 2 - (r1 * r2) * 2;
	// 2
	while (yt > 0)
	{
		if (d < 0)
		{
			d += sqb * (2 * xt + 2) + sqa * ((-2) * yt + 3);
			++xt;
		}
		else
		{
			d += sqa * ((-2) * yt + 3);
		}
		--yt;
		drawPoint((x + xt), (y + yt));
		drawPoint((x + xt), (y - yt));
		drawPoint((x - xt), (y - yt));
		drawPoint((x - xt), (y + yt));
	}
}

void TBufPainter::drawFullEllipse(int32 x, int32 y, int32 r1, int32 r2)
{
	int xt = -r1, yt = 0, err = 2 - 2 * r1, e2;
	float K = 0, rad1 = 0, rad2 = 0;

	rad1 = r1;
	rad2 = r2;

	if (r1 > r2)
	{
		do
		{
			K = (float)(rad1 / rad2);
			drawLine((x + xt), (y - (uint16)(yt / K)), (x + xt), (y - (uint16)(yt / K))+ (2 * (uint16)(yt / K) + 1));
			drawLine((x - xt), (y - (uint16)(yt / K)), (x - xt), (y - (uint16)(yt / K))+ (2 * (uint16)(yt / K) + 1));

			e2 = err;
			if (e2 <= yt)
			{
				err += ++yt * 2 + 1;
				if (-xt == yt && e2 <= xt) e2 = 0;
			}
			if (e2 > xt) err += ++xt * 2 + 1;

		} while (xt <= 0);
	}
	else
	{
		yt = -r2;
		xt = 0;
		do
		{
			K = (float)(rad2 / rad1);
			drawLine((x - (uint16)(xt / K)), (y + yt), (x - (uint16)(xt / K)) + (2 * (uint16)(xt / K) + 1), (y + yt));
			drawLine((x - (uint16)(xt / K)), (y - yt), (x - (uint16)(xt / K)) + (2 * (uint16)(xt / K) + 1), (y - yt));

			e2 = err;
			if (e2 <= xt)
			{
				err += ++xt * 2 + 1;
				if (-yt == x && e2 <= yt) e2 = 0;
			}
			if (e2 > yt) err += ++yt * 2 + 1;
		} while (yt <= 0);
	}
}

void TBufPainter::drawFullRect(int32 x, int32 y, int32 w, int32 h)
{
	TRect rect(x, y, w, h);
	paintMeta(&rect);
}


void TBufPainter::drawFullCircle(int32 x, int32 y, int32 r)
{
	int32  D;    /* Decision Variable */
	int32  CurX;/* Current X Value */
	int32  CurY;/* Current Y Value */

	D = 3 - (r << 1);

	CurX = 0;
	CurY = r;

	while (CurX <= CurY)
	{
		if (CurY > 0)
		{
			drawVLine(x - CurX, y - CurY, 2 * CurY);
      		drawVLine(x + CurX, y - CurY, 2 * CurY);
			// drawLine(x - CurX, y - CurY, x - CurX, y - CurY + 2 * CurY);
			// drawLine(x + CurX, y - CurY, x + CurX, y - CurY + 2 * CurY);
		}

		if (CurX > 0)
		{
			drawVLine(x - CurY, y - CurX, 2 * CurX);
      		drawVLine(x + CurY, y - CurX, 2 * CurX);
			// drawLine(x - CurY, y - CurX, x - CurY, y - CurX+ 2 * CurX);
			// drawLine(x + CurY, y - CurX, x + CurY, y - CurX +2 * CurX);
		}
		if (D < 0)
		{
			D += (CurX << 2) + 6;
		}
		else
		{
			D += ((CurX - CurY) << 2) + 10;
			CurY--;
		}
		CurX++;
	}
	drawCircle(x, y, r);
}

void TBufPainter::drawFullTriangle(int32 x1, int32 y1, int32 x2, int32 y2, int32 x3, int32 y3)
{
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
		yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
		curpixel = 0;

	deltax = ABS(x2 - x1);        /* The difference between the x's */
	deltay = ABS(y2 - y1);        /* The difference between the y's */
	x = x1;                       /* Start x off at the first pixel */
	y = y1;                       /* Start y off at the first pixel */

	if (x2 >= x1)                 /* The x-values are increasing */
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else                          /* The x-values are decreasing */
	{
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1)                 /* The y-values are increasing */
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else                          /* The y-values are decreasing */
	{
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay)         /* There is at least one x-value for every y-value */
	{
		xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
		yinc2 = 0;                  /* Don't change the y for every iteration */
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;         /* There are more x-values than y-values */
	}
	else                          /* There is at least one y-value for every x-value */
	{
		xinc2 = 0;                  /* Don't change the x for every iteration */
		yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;         /* There are more y-values than x-values */
	}

	for (curpixel = 0; curpixel <= numpixels; curpixel++)
	{
		drawLine(x, y, x3, y3);

		num += numadd;              /* Increase the numerator by the top of the fraction */
		if (num >= den)             /* Check if numerator >= denominator */
		{
			num -= den;               /* Calculate the new numerator value */
			x += xinc1;               /* Change the x as appropriate */
			y += yinc1;               /* Change the y as appropriate */
		}
		x += xinc2;                 /* Change the x as appropriate */
		y += yinc2;                 /* Change the y as appropriate */
	}
}

/**
* 窗口画图方法 用于窗口和按键
*/
void TBufPainter::drawWinShades(int32 x, int32 y, int32 w, int32 h,
	colorDef c1, colorDef c2, colorDef c3, colorDef c4, colorDef back,bool hasBack)
{
	setTextColor(c1); //上外框
	drawLine(x, y + h - 2, x, y);
	drawLine(x, y, x + w - 2, y);
	setTextColor(c2);//下外框
	drawLine( x, y + h - 1, x + w - 1, y + h - 1);
	drawLine( x + w - 1, y + h - 1, x + w - 1, y);
	setTextColor(c3);//上内框
	drawLine(x + 1, y + h - 3, x + 1, y + 1);
	drawLine(x + 1, y + 1, x + w - 3, y + 1);
	setTextColor(c4);//下内框
	drawLine(x + 1, y + h - 2, x + w - 2, y + h - 2);
	drawLine(x + w - 2, y + h - 2, x + w - 2, y + 1);
	if (hasBack)
	{
		setTextColor(back);
		drawFullRect(x + 2, y + 2, w - 4, h - 4);
	}
}

//button isPress 表示是否按下状态
void TBufPainter::drawButton(int32 x, int32 y, int32 w, int32 h, const char* str ,bool isPress)
{
	if (isPress)//按下
		drawWinShades(x, y, w, h, MIDLIGHT, LIGHT, DARK, MIDLIGHT, MID);
	else//未按下
		drawWinShades(x, y, w, h, LIGHT, DARK, MIDLIGHT, MIDDARK, MID);
	drawCenterText(x, y, w, h, str, BLACK, MID);
}

void TBufPainter::drawCheck(int32 x, int32 y, int32 w, int32 h, const char* str, bool Selected, bool isPress, colorDef back)
{
	if (isPress)//按下
		drawWinShades(x, y, h, h, LIGHT, DARK, MIDLIGHT, MIDDARK, WHITE);
	else//未按下
		drawWinShades(x, y, h, h, MIDLIGHT, LIGHT, DARK, MIDLIGHT, WHITE);
	if (Selected)
	{
		setColors(BLACK, WHITE);
		drawLine(x + 2, y + h / 2, x + h / 2, y + h - 2);
		drawLine(x + h / 2, y + h - 2, x + h - 2, y + 2);
	}
	drawCenterText(x+h, y, w-h, h, str, BLACK, back,false);
}

void TBufPainter::drawRadio(int32 x, int32 y, int32 w, int32 h, const char* str, bool Selected, bool isPress, colorDef back)
{
	//setColors(back, back);
	//drawFullRect(x, y, h, h);
	int32 xt, yt, rt;
	xt = x + h / 2;
	yt = y + h / 2;
	rt = h / 2;
	if (isPress)//按下
	{
		setColors(MIDDARK, WHITE);
		drawFullCircle(xt, yt, rt-1);
		setColors(DARK, WHITE);
		drawFullCircle(xt, yt, 3 * rt /4);
		setColors(WHITE, WHITE);
		drawFullCircle(xt, yt, rt / 2);
	}
	else
	{
		setColors(MID, WHITE);
		drawFullCircle(xt, yt, rt-1);
		setColors(MIDDARK, WHITE);
		drawFullCircle(xt, yt, 3 * rt / 4);
		setColors(WHITE, WHITE);
		drawFullCircle(xt, yt, rt / 2);
	}
	if (Selected)
	{
		setColors(BLACK, WHITE);
		drawFullCircle(xt, yt, rt / 3);
	}
	drawCenterText(x + h, y, w - h, h, str, BLACK, back);
}

void TBufPainter::drawHorizSlider(int32 x, int32 y, int32 w, int32 h,int32 value, int32 value_pre, bool isPress,colorDef back)
{
	int32 sliderBackH, sliderX,sliderW;
	sliderBackH = h / 3;
	sliderX = x;
	sliderW = h * 4 / 3;
	if(value_pre < 0)
	{
		setColors(back, back);
		drawFullRect(x, y, w, h);
		drawWinShades(x, y + sliderBackH, w, sliderBackH, MIDDARK, MID, DARK, MIDDARK, MIDLIGHT);//背景 
	}
	else
	{
		TRect rect(x + value_pre*w / 100 - sliderW / 2 , y ,  sliderW , h);
		setColors(back, back);
		drawFullRect(x, y, w, h);
		drawWinShades(x, y + sliderBackH, w, sliderBackH, MIDDARK, MID, DARK, MIDDARK, MIDLIGHT);//背景 
	}
	//实际物体
	sliderX = x + value* w / 100 - sliderW/2;
	if (sliderX < x)sliderX = x;
	if (sliderX >( x + w - sliderW))sliderX = (x + w - sliderW);
	drawButton(sliderX, y, sliderW, h, NULL, isPress);
	setColors(BLACK, MID);
	int32 xstart = sliderX + sliderW / 4;
	drawLine(xstart, y + h / 5, xstart, y + h - h / 5);
	xstart = sliderX + sliderW / 2;
	drawLine(xstart, y + h / 5, xstart, y + h - h / 5);
	xstart = sliderX + sliderW - sliderW / 4;
	drawLine(xstart, y + h / 5, xstart, y + h - h / 5);
}

void TBufPainter::drawVertSlider(int32 x, int32 y, int32 w, int32 h, int32 value, int32 value_pre, bool isPress, colorDef back)
{
	int32 sliderBackW, sliderY, sliderH;
	sliderBackW = w / 3;
	sliderY = y;
	sliderH = w * 4 / 3;
	
	if (value_pre < 0)
	{
		setColors(back, back);
		drawFullRect(x, y, w, h);
		drawWinShades(x + sliderBackW, y , sliderBackW, h, MIDDARK, MID, DARK, MIDDARK, MIDLIGHT);//背景 
	}
	else
	{
		TRect rect(x , y + value_pre*h / 100 - sliderH / 2, w, sliderH);
		setColors(back, back);
		drawFullRect(x, y, w, h);
		drawWinShades(x + sliderBackW, y,  sliderBackW, h , MIDDARK, MID, DARK, MIDDARK, MIDLIGHT);//背景 
	}
	//实际物体
	sliderY = y + value * h / 100 - sliderH / 2;
	if (sliderY < y)sliderY = y;
	if (sliderY > (y + h - sliderH))sliderY = (y + h - sliderH);
	drawButton(x, sliderY, w, sliderH, NULL, isPress);
	setColors(BLACK, MID);
	int32 ystart = sliderY + sliderH / 4;
	drawLine(x + w / 5, ystart, x + w - w / 5, ystart);
	ystart = sliderY + sliderH / 2;
	drawLine(x + w / 5, ystart, x + w - w / 5, ystart);
	ystart = sliderY + sliderH - sliderH / 4;
	drawLine(x + w / 5, ystart, x + w - w / 5, ystart);
}

void TBufPainter::drawHorizScroll(int32 x, int32 y, int32 w, int32 h, int32 scrollLen, int32 value, int32 value_pre, bool isPress, colorDef back)
{
	if (value_pre < 0) //开始的时候画下背景
	{
		drawWinShades( x, y, w, h, MIDDARK, MID, DARK, MIDDARK, MIDLIGHT);//背景 
	}
	else
	{
		TRect rect(x + value_pre * w / 100 - scrollLen / 2, y , scrollLen, h);
		//绘画之前的区域
		//TRect* tmp = invalidArea;
		//invalidArea = &rect;
		drawWinShades(x, y, w, h, MIDDARK, MID, DARK, MIDDARK, MIDLIGHT);//背景 
		//invalidArea = tmp;
	}
	//实际物体
	int32 scrollX = x + value * w / 100 - scrollLen / 2;;
	if (scrollX < x + 2)scrollX = x + 2;
	if (scrollX > (x + w - scrollLen - 2))scrollX = (x + w - scrollLen - 2);
	drawButton(scrollX, y + 2, scrollLen, h - 4, NULL, isPress);
}

void TBufPainter::drawVertScroll(int32 x, int32 y, int32 w, int32 h, int32 scrollLen, int32 value, int32 value_pre, bool isPress, colorDef back)
{
	if (value_pre < 0) //开始的时候画下背景
	{
		drawWinShades(x, y, w, h, MIDDARK, MID, DARK, MIDDARK, MIDLIGHT);//背景 
	}
	else
	{
		TRect rect(x, y + value_pre * h / 100 - scrollLen / 2, w, scrollLen);
		//绘画之前的区域
		//TRect* tmp = invalidArea;
		//invalidArea = &rect;
		drawWinShades(x, y, w, h, MIDDARK, MID, DARK, MIDDARK, MIDLIGHT);//背景 
		//invalidArea = tmp;
	}
	//实际物体
	int32 scrollY = y + value * h / 100 - scrollLen / 2;
	if (scrollY < y + 2)scrollY = y + 2;
	if (scrollY > (y + h - scrollLen - 2))scrollY = (y + h - scrollLen - 2);
	drawButton( x + 2, scrollY, w - 4,scrollLen, NULL, isPress);
}


void TBufPainter::drawLabel(int32 x, int32 y, int32 w, int32 h, const char* str,colorDef text , colorDef back )
{
	setTextColor(back);
	drawFullRect(x, y, w, h);
	drawCenterText(x, y, w, h, str, text, back);
}

void TBufPainter::drawDialog(int32 x, int32 y, int32 w, int32 h, const char* str,bool hasFocus,colorDef back)
{
	drawWinShades(x , y, w, h, LIGHT, DARK, MIDLIGHT, MIDDARK, back,false);
	drawWinShades(x + 2, y + WIN_TITLE_H + 2, w - 4, h - WIN_TITLE_H - 4, MIDDARK, MIDLIGHT, DARK, MID, back);
	drawDialogTitle(x, y, w, str, hasFocus);
}

void TBufPainter::drawDialogTitle(int32 x, int32 y, int32 w, const char* str, bool hasFocus)
{
	if(hasFocus)
	{
		setTextColor(SKYBLUE);
		drawFullRect(x + 2, y + 2, w - 4, WIN_TITLE_H);
		drawCenterText(x + 2, y + 2, w - 4, WIN_TITLE_H, str, BLACK, SKYBLUE);
	}
	else
	{
		setTextColor(MID);
		drawFullRect(x + 2, y + 2, w - 4, WIN_TITLE_H);
		drawCenterText(x + 2, y + 2, w - 4, WIN_TITLE_H, str, BLACK, MID);
	}
}


//---------------En---------------

void TBufPainter::drawCenterText(int32 x, int32 y, int32 w, int32 h, const char* str, colorDef text, colorDef back ,bool hasBack)
{
	setBackColor(back);
	setTextColor(text);
	if (!str)
		return;
	int32 len = 0;
	char* p = (char*)str;
	while (p[++len] != '\0')
		;
	 x += (bufRect->width() - fontCH->fontW()/2 * len )/ 2;
	 y += (h - fontCH->fontH()) / 2;
	if (x < 0 || y < 0)
		//自动缩小字体，通过存字体的列表，这里先不做处理
		return;
	drawString(x,y,str,text);
}

void TBufPainter::displayEnChar(int32 x, int32 y,uint8 Ascii, bool hasBack)
{
	Ascii -= 32;
	uint16 y0=y;
	uint8 temp;
	uint8 csize=(fontCH->fontW()/8+((fontCH->fontW()%8)?1:0))*(fontCH->fontW()/2);		//得到字体一个字符对应点阵集所占的字节数	
	uint8* add = fontEn->table + csize * Ascii;
	for(int t=0;t<csize;t++)
	{   
		temp = add[t];

		for(int t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)
			{
				setTextColor(textcolor);
				drawPoint(x,y);
			}
			else
			{
				if(hasBack)
				{
					setTextColor(backcolor);
					drawPoint(x,y);
				}
			}
			temp<<=1;
			y++;
			if((y-y0) == fontCH->fontW())
			{
				y=y0;
				x++;
				break;
			}
		}  	 
	}  	    	   	 	  
}

//----------------CH----------------
void TBufPainter::displayCHChar ( int32 x,int32 y, uint8* code,bool hasBack)
{
	uint8* fontBuf;
	fontBuf = fontCH->getWordCode(code);
	//int32 tmpX = x;
	int32 tmpY = y;
	uint8 temp;	
	uint8 csize = (fontCH->fontW()/8+((fontCH->fontW()%8)?1:0))*(fontCH->fontW());			//得到字体一个字符对应点阵集所占的字节数	 

	for(int t=0 ; t<csize ; t++)
	{   												   
		temp=fontBuf[t];			//得到点阵数据                          
		for(int t1=0 ; t1 < 8 ; t1++)
		{
			if(temp & 0x80)
			{//字体色
				setTextColor(textcolor);
				drawPoint(x,y);
			}
			else if(hasBack)
			{//背景色
				setTextColor(backcolor);
				drawPoint(x,y);
			}
			temp<<=1;
			y++;
			if((y-tmpY)==fontCH->fontW())
			{
				y=tmpY;
				x++;
				break;
			}
		}  	 
	} 
}

//----------------All---------------
void TBufPainter::drawString(int32 x, int32 y, const char* str, colorDef text)
{
	uint8* p = (uint8*)str;
	int32 x0=x;
	int32 y0=y;
	uint8 bHz=0;     //字符或者中文  
	while(*p != 0)
	{
		if(!bHz)
		{
			if(*p>0x80)
				bHz=1;//中文 
			else              //英文字符
			{      
				displayEnChar(x,y,*p,false);//有效部分写入 
				p++; 
				x += fontCH->fontW()/2; //字符,为全字的一半 
			}
		}else//中文 
		{     
			bHz=0;//有汉字库    					     
			displayCHChar(x,y,p,false); //显示这个汉字,空心显示 
			p+=2; 
			x += fontCH->fontW();//下一个汉字偏移	    
		}		
	}
}

void TBufPainter::drawAlignText( const char* str,uint8 align, colorDef text)
{
	drawAlignText(0,0,str,align,text);
}

void TBufPainter::drawAlignText(int32 x, int32 y, const char* str,uint8 align, colorDef text)
{
	if(!str)
		return;
	setTextColor(text);
	uint8* p = (uint8*)str;
	int32 len = -1;
	while (p[++len] != '\0')
		;
	if(bufRect->width() - fontCH->fontW()/2 * len + x < 0 || bufRect->height() - fontCH->fontH() < 0)
		return;//自动缩小字体，通过存字体的列表，这里先不做处理

	switch(align)
	{
		case ALIGN_UP_LEFT  :
			break;
		case ALIGN_UP_MID   :  
		{
			x += (bufRect->width() - fontCH->fontW()/2 *len )/ 2;
		}
			break;  
		case ALIGN_UP_RIGHT :  
		{
			x +=  bufRect->width() - fontCH->fontW()/2 *len;
		}  
			break;
		case ALIGN_MID_LEFT  : 
		{
			y += (bufRect->height() - fontCH->fontH()) / 2;
		}
			break;
		case ALIGN_CENTER    :  
		{
			 x += (bufRect->width() - fontCH->fontW()/2 * len )/ 2;
			 y += (bufRect->height() - fontCH->fontH()) / 2;
		}
			break;
		case ALIGN_MID_RIGHT : 
		{
			x += bufRect->width() - fontCH->fontW()/2 * len;
			y += (bufRect->height() - fontCH->fontH()) / 2;
		}   
			break;
		case ALIGN_LOW_LEFT  :   
		{
			y += (bufRect->height() - fontCH->fontH());
		}
			break;
		case ALIGN_LOW_MID   :  
		{
			 x += (bufRect->width() - fontCH->fontW()/2 * len )/ 2;
			 y += (bufRect->height() - fontCH->fontH());
		}  
			break;
		case ALIGN_LOW_RIGHT :    
		{
			 x += bufRect->width() - fontCH->fontW()/2 * len ;
			 y += (bufRect->height() - fontCH->fontH());
		}
	}
	drawString(x,y,str,text);
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void TBufPainter::paintMeta(TRect* srcRect)
{
	//先进行混合颜色

	//在搬运到TBuffer上
	gui_dma2d_memset((uint32_t*)bufAddr,bufRect->width(),textcolor,srcRect->x(),srcRect->y(),srcRect->width(),srcRect->height());
}



