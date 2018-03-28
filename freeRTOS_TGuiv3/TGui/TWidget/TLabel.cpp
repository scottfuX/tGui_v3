#include "TWidget/TLabel.h"

TLabel::TLabel(int32 x, int32 y, int32 w, int32 h, const char* n, TWidget* obj)
	:TFrame(x,y,w,h,n,obj)
{
	haveImg = false;
	textColor = BLACK;
	setBackColor(((TWidget*)getParents())->getBackColor());
		//TPainter p(getInvalidList(),getPaintInvaild());
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawLabel(0, 0, width(), height(), getName(),textColor,getBackColor());
}

TLabel::TLabel(int32 x, int32 y,TImage* img, const char* name, TWidget* obj)
	:TFrame(x, y, img->imgW(),img->imgH(), name, obj)
{
	haveImg = true;
	labelImg = img;
    labelImg->ImgLoad(0,0,getBuffer());
    TBufPainter p(getBuffer()->getBufAddr(),getRect());
    p.drawCenterEnText(0,0,getRect()->width(),getRect()->height(),getName());
}

TLabel::~TLabel() 
{
	if(haveImg)
		delete labelImg;
};

void TLabel::show()
{
	//TPainter p(getInvalidList(),getPaintInvaild());
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
		cleanShow(&r);
		
	}
	else if(d1 == 0 && d2 > 0 )
	{
		TRect r(x(),y(),width(),height());
		//移动位置到d2处
		getRect()->moveTopLeft(x(),d2 - height()/2);
		//清除之前的痕迹
		cleanShow(&r);
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
		getBuffer()->obPareBack(((TWidget*)getParents())->getBuffer()->getBufAddr() + (getOffsetWH()->width() +  getOffsetWH()->height() * ((TWidget*)getParents())->width())*GUI_PIXELSIZE,((TWidget*)getParents())->width() );
		labelImg->ImgLoad(0,0,getBuffer());
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawCenterEnText(0,0,getRect()->width(),getRect()->height(),getName());
	}
	else
	{
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawLabel(0, 0, width(), height(), getName(),textColor,getBackColor());
	}
	refresh();
}

