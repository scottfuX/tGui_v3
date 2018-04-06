#include "TWidget/TLabel.h"

TLabel::TLabel(int32 x, int32 y, int32 w, int32 h, const char* n, TWidget* obj,uint8 align , bool needBack ,colorDef text ,colorDef back)
	:TFrame(x,y,w,h,n,obj)
{
	haveImg = false;
	labelAlign = align;
	haveBack = needBack;
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	textColor = text;
	setBackColor(back);
	if(haveBack)
	{
		p.setTextColor(getBackColor());
		p.drawFullRect(x,y,w,h);
	}
	else
	{
		if(getParents())
			getBuffer()->obPareBack(getPareBufCorreAddr(),((TWidget*)getParents())->width());
	}
    p.drawAlignText(0,0,getName(),labelAlign,textColor);
}

TLabel::TLabel(int32 x, int32 y,TImage* img, const char* name,uint8 align, TWidget* obj)
	:TFrame(x, y, img->imgW(),img->imgH(), name, obj)
{
	haveImg = true;
	labelImg = img;
	labelAlign = align;
    imgLoadInterface(0,0,img);
    TBufPainter p(getBuffer()->getBufAddr(),getRect());
    p.drawAlignText(0,0,getName(),labelAlign);
}

TLabel::~TLabel() 
{
	if(haveImg)
		delete labelImg;
};

void TLabel::show()
{
	
	refresh();
}

void TLabel::slot_showValue(int32 d1,int32 d2)
{
	if(d1 > 0 && d2 == 0 )
	{	
		TRect r(x(),y(),width(),height());
		//移动位置到d1处  要先改变 要不无法清楚之前的痕迹
		getRect()->moveTopLeft(d1 - width()/2,y());
		//清除之前的痕迹
		cleanShowed(&r);
		
	}
	else if(d1 == 0 && d2 > 0 )
	{
		TRect r(x(),y(),width(),height());
		//移动位置到d2处
		getRect()->moveTopLeft(x(),d2 - height()/2);
		//清除之前的痕迹
		cleanShowed(&r);
	}
	else
	{ //d1 < 0
		switch(d1)
		{
			case TYPE_INT:
			{
				TString* temp = new TString();
				temp->setNum(d2);
				setName(temp);
			}break;
			default:
				break;
		}
	}
	if(haveImg)
	{
		//getBuffer()->obPareBack(getPareBufCorreAddr(),((TWidget*)getParents())->width() );
		imgLoadInterface(0,0,labelImg);
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawAlignText(0,0,getName(),labelAlign);
	}
	else
	{
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		if(haveBack)
		{
			p.setTextColor(getBackColor());
			p.drawFullRect(x(),y(),width(),height());
		}
		else
		{
			if(getParents())
				getBuffer()->obPareBack(getPareBufCorreAddr(),((TWidget*)getParents())->width());
		}
		p.drawAlignText(0,0,getName(),labelAlign,textColor);
	}
	refresh();
}

