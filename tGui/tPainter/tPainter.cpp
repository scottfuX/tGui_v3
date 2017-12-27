#include "tPainter/tPainter.h"


tPainter::tPainter(tRectList* list,tRect* invaild)
{
	font = &Font16x24;
	textcolor = 0;
	backcolor = 0;
	rectlist = list;
	invaildArea = invaild;
	nestingNum = COVERNUM;
}

void tPainter::setColors(colorDef text, colorDef back)
{
	textcolor = text;
	backcolor = back; 
	setDivColor(text, back); 
};


void tPainter::drawPoint(int32 x, int32 y)
{
	tRect rect(x, y, 1, 1);
	paintMeta(&rect);
}

void tPainter::drawLine(int32 x1, int32 y1, int32 x2, int32 y2)
{
	if (x1 == x2)
	{
		if (y2 > y1)
		{
			tRect rect(x1, y1, 1, y2 - y1 + 1);
			paintMeta(&rect);
		}
		else
		{
			tRect rect(x1, y2, 1, y1 - y2 + 1);
			paintMeta(&rect);
		}
	}
	else if (y1 == y2)
	{
		if (x2 > x1)
		{
			tRect rect(x1, y1, x2 - x1 + 1, 1);
			paintMeta(&rect);
		}
		else
		{
			tRect rect(x2, y1, x1 - x2 + 1, 1);
			paintMeta(&rect);
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

void tPainter::drawRect(int32 x, int32 y, int32 w, int32 h)
{
	drawLine(x, y, x, y + h - 1);
	drawLine(x, y, x + w - 1, y);
	drawLine(x, y + h - 1, x + w - 1, y + h - 1);
	drawLine(x + w - 1, y, x + w - 1, y + h - 1);
}

void tPainter::drawTriangle(int32 x1, int32 y1, int32 x2, int32 y2, int32 x3, int32 y3)
{
	drawLine(x1, y1, x2, y2);
	drawLine(x1, y1, x3, y3);
	drawLine(x3, y3, x2, y2);

}

void tPainter::drawCircle(int32 x, int32 y, int32 r)
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

void tPainter::drawEllipse(int32 x, int32 y, int32 r1, int32 r2)
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

void tPainter::drawFullEllipse(int32 x, int32 y, int32 r1, int32 r2)
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
			LCD_DrawLine((x + xt), (y - (uint16_t)(yt / K)), (2 * (uint16_t)(yt / K) + 1), LCD_DIR_VERTICAL);
			LCD_DrawLine((x - xt), (y - (uint16_t)(yt / K)), (2 * (uint16_t)(yt / K) + 1), LCD_DIR_VERTICAL);

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
			LCD_DrawLine((x - (uint16_t)(xt / K)), (y + yt), (2 * (uint16_t)(xt / K) + 1), LCD_DIR_HORIZONTAL);
			LCD_DrawLine((x - (uint16_t)(xt / K)), (y - yt), (2 * (uint16_t)(xt / K) + 1), LCD_DIR_HORIZONTAL);

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

void tPainter::drawFullRect(int32 x, int32 y, int32 w, int32 h)
{
	tRect rect(x, y, w, h);
	paintMeta(&rect);
}


void tPainter::drawFullCircle(int32 x, int32 y, int32 r)
{
	int32_t  D;    /* Decision Variable */
	uint32_t  CurX;/* Current X Value */
	uint32_t  CurY;/* Current Y Value */

	D = 3 - (r << 1);

	CurX = 0;
	CurY = r;

	while (CurX <= CurY)
	{
		if (CurY > 0)
		{
			LCD_DrawLine(x - CurX, y - CurY, 2 * CurY, LCD_DIR_VERTICAL);
			LCD_DrawLine(x + CurX, y - CurY, 2 * CurY, LCD_DIR_VERTICAL);
		}

		if (CurX > 0)
		{
			LCD_DrawLine(x - CurY, y - CurX, 2 * CurX, LCD_DIR_VERTICAL);
			LCD_DrawLine(x + CurY, y - CurX, 2 * CurX, LCD_DIR_VERTICAL);
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

void tPainter::drawFullTriangle(int32 x1, int32 y1, int32 x2, int32 y2, int32 x3, int32 y3)
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
void tPainter::drawWinShades(int32 x, int32 y, int32 w, int32 h,
	colorDef c1, colorDef c2, colorDef c3, colorDef c4, colorDef back)
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
	setTextColor(back);
	drawFullRect(x + 2 , y + 2, w - 4, h - 4);
}

//button isPress 表示是否按下状态
void tPainter::drawButton(int32 x, int32 y, int32 w, int32 h, const char* str ,bool isPress)
{
	if (isPress)//按下
		drawWinShades(x, y, w, h, MIDLIGHT, LIGHT, DARK, MIDLIGHT, MID);
	else//未按下
		drawWinShades(x, y, w, h, LIGHT, DARK, MIDLIGHT, MIDDARK, MID);
	setColors(BLACK, MID);
	drawCenterText(x, y, w, h, str, BLACK, MID);
}

void tPainter::drawCheck(int32 x, int32 y, int32 w, int32 h, const char* str, bool Selected, bool isPress, colorDef back)
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
	setColors(BLACK, back);
	drawCenterText(x+h, y, w-h, h, str);	
}

void tPainter::drawRadio(int32 x, int32 y, int32 w, int32 h, const char* str, bool Selected, bool isPress, colorDef back)
{
	int32 xt, yt, rt;
	xt = x + h / 2;
	yt = y + h / 2;
	rt = h / 2;
	if (isPress)//按下
	{
		setColors(MIDDARK, WHITE);
		drawFullCircle(xt, yt, rt);
		setColors(DARK, WHITE);
		drawFullCircle(xt, yt, 3 * rt /4);
		setColors(WHITE, WHITE);
		drawFullCircle(xt, yt, rt / 2);
	}
	else
	{
		setColors(MID, WHITE);
		drawFullCircle(xt, yt, rt);
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
	setColors(BLACK, back);
	drawCenterText(x + h, y, w - h, h, str);
}


void tPainter::drawHorizSlider(int32 x, int32 y, int32 w, int32 h,int32 value, int32 value_pre, bool isPress,colorDef back)
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
		tRect rect(x + value_pre*(w / 10) / 10 - sliderW / 2 , y ,  sliderW , h);
		//绘画之前的区域
		invaildArea = &rect;
		setColors(back, back);
		drawFullRect(x, y, w, h);
		drawWinShades(x, y + sliderBackH, w, sliderBackH, MIDDARK, MID, DARK, MIDDARK, MIDLIGHT);//背景 
		invaildArea =NULL;
	}
	//实际物体
	sliderX = x + value*( w / 10)/10 - sliderW/2;
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

void tPainter::drawVertSlider(int32 x, int32 y, int32 w, int32 h, int32 value, int32 value_pre, bool isPress, colorDef back)
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
		tRect rect(x , y + value_pre*(h / 10) / 10 - sliderH / 2, w, sliderH);
		//绘画之前的区域
		invaildArea = &rect;
		setColors(back, back);
		drawFullRect(x, y, w, h);
		drawWinShades(x + sliderBackW, y,  sliderBackW, h , MIDDARK, MID, DARK, MIDDARK, MIDLIGHT);//背景 
		invaildArea = NULL;
	}
	//实际物体
	sliderY = y + value*(h / 10) / 10 - sliderH / 2;
	if (sliderY < y)sliderY = y;
	if (sliderY >(y + h - sliderH))sliderY = (y + h - sliderH);
	drawButton(x, sliderY, w, sliderH, NULL, isPress);
	setColors(BLACK, MID);
	int32 ystart = sliderY + sliderH / 4;
	drawLine(x + w / 5, ystart, x + w - w / 5, ystart);
	ystart = sliderY + sliderH / 2;
	drawLine(x + w / 5, ystart, x + w - w / 5, ystart);
	ystart = sliderY + sliderH - sliderH / 4;
	drawLine(x + w / 5, ystart, x + w - w / 5, ystart);
}


void tPainter::drawLabel(int32 x, int32 y, int32 w, int32 h, const char* str,colorDef text , colorDef back )
{
	setTextColor(back);
	drawFullRect(x, y, w, h);
	drawCenterText(x, y, w, h, str, text, back);
}


void tPainter::drawCenterText(int32 x, int32 y, int32 w, int32 h, const char* str, colorDef text, colorDef back,  bool isAllShow)
{
	setBackColor(back);
	setTextColor(text);
	if (!str)
		return;
	int32 len = -1;
	char* p = (char*)str;
	while (p[++len] != '\0')
		;
	 x += (w - font->Width*len )/ 2;
	 y += (h - font->Height) / 2;
	if (x < 0 || y < 0)
		//自动缩小字体，通过存字体的列表，这里先不做处理
		return;
	else
		drawDivText(x, y, str, len);
}


/*
*|----------------| 5个矩形----进行递归
*|--|----------|--|
*|	| invlidal |  |
*|--|----------|--|
*|----------------|
*/

void tPainter::paintMeta(tRect* srcRect)
{
	if (invaildArea)//恢复无效区
	{ 
		tRect rect = srcRect->intersect(*invaildArea);
		if (rect.isValid())
			rectCut(&rect);
	}
	else//剪切并画剪切域
		rectCut(srcRect);
}

void tPainter::rectCut(tRect* srcRect)
{
	if (!srcRect)//小于一个值时
		return;
	if(rectlist && nestingNum > 0)
	{ 
		tRect rect = srcRect->intersect(*(rectlist->getCurrent()->getData())) ;
		nestingNum--;
		if (!rect.isValid())
		{
			while (rectlist->getNext())
			{
				rect = srcRect->intersect(*(rectlist->getCurrent()->getData()));
				if (rect.isValid())
					break;
			}
		}
		if (rectlist->getCurrent())//未遍历完
		{
			int32 currIndex = rectlist->at();
			tLNode<tRect*>* currNode = rectlist->getCurrent();
			tRect tmp;
			//Area of up
			if (srcRect->left() < srcRect->right() && srcRect->top() < rect.top())
			{
				rectlist->setCurNode(currNode);
				rectlist->setCurIndex(currIndex);
				tmp.setLeft(srcRect->left());
				tmp.setTop(srcRect->top());
				tmp.setRight(srcRect->right());
				tmp.setBottom(rect.top());
			}
			//Area of left
			if (srcRect->left() < rect.right() && rect.top() < rect.bottom())
			{
				rectlist->setCurNode(currNode);
				rectlist->setCurIndex(currIndex);
				tmp.setLeft(srcRect->left());
				tmp.setTop(rect.top());
				tmp.setRight(rect.right());
				tmp.setBottom(rect.bottom());
				rectCut(&tmp);
			}
			//Area of right
			if (rect.left() < rect.top() && srcRect->right() < rect.bottom())
			{
				rectlist->setCurNode(currNode);
				rectlist->setCurIndex(currIndex);
				tmp.setLeft(rect.left());
				tmp.setTop(rect.top());
				tmp.setRight(srcRect->right());
				tmp.setBottom(rect.bottom());
				rectCut(&tmp);
			}
			//Area of down
			if (srcRect->left() < rect.bottom() && srcRect->right() < srcRect->bottom())
			{
				rectlist->setCurNode(currNode);
				rectlist->setCurIndex(currIndex);
				tmp.setLeft(srcRect->left());
				tmp.setTop(rect.bottom());
				tmp.setRight(srcRect->right());
				tmp.setBottom(srcRect->bottom());
				rectCut(&tmp);
			}
		}
	}
	else//链表遍历完了，或没有覆盖物了
	{
		drawDivFullRect(srcRect->left(), srcRect->top(), srcRect->width(), srcRect->height());
	}
}