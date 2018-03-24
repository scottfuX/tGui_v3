#include "TWidget/TCheckBox.h"


TCheckBox::TCheckBox(int32 x, int32 y, int32 w, int32 h, const char* name, TWidget* obj)
	:TAbstractButton(x, y, w, h, name, obj)
{
	norImg = NULL;
	selImg = NULL;
	next = this; 
	selected = false; 

	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawCheck(0,0, width(), height(), getName(), selected, state, getBackColor());
}


TCheckBox::TCheckBox(TRect* rect,TImage* norImg,TImage* selImg, const char* name, TWidget* obj)
	:TAbstractButton(rect->left(), rect->top(), rect->width(), rect->height(), name, obj)
{
	next = this; 
	selected = false; 
	delete rect;

	this->norImg = norImg;
	this->selImg = selImg;

	norImg->ImgLoad(0,(height() - norImg->imgH())/2,getBuffer());
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawEnText(norImg->imgW(),0, getName());
}

TCheckBox::~TCheckBox() 
{
	if(norImg)
		delete norImg;
	if(selImg)
		delete selImg;
};

void TCheckBox::sig_depress(int32 d1, int32 d2)
{
	if(norImg)
	{
	}
	else
	{
		//TPainter p(getInvalidList(),getPaintInvaild());
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawCheck(0, 0, width(), height(), getName(),selected, true, getBackColor());
		refresh();
	}
	state = true;
	callSlot((func)&TCheckBox::sig_depress,d1,d2);
}


void TCheckBox::sig_release(int32 d1, int32 d2)
{
	changeSelected();
	if(norImg)
	{
		if(selected)
			selImg->ImgLoad(0,(height() - selImg->imgH())/2,getBuffer());
		else
			norImg->ImgLoad(0,(height() - norImg->imgH())/2,getBuffer());
		refresh();
	}
	else
	{
		//TPainter p(getInvalidList(),getPaintInvaild());
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawCheck(0, 0, width(), height(), getName(), selected, false, getBackColor());
		refresh();
	}
	state = false;
	callSlot((func)&TCheckBox::sig_release,d1,d2);
}

void TCheckBox::release()
{
	changeSelected();
	if(norImg)
	{
		if(selected)
			selImg->ImgLoad(0,(height() - selImg->imgH())/2,getBuffer());
		else
			norImg->ImgLoad(0,(height() - norImg->imgH())/2,getBuffer());
		refresh();
	}
	else
	{
		//TPainter p(getInvalidList(),getPaintInvaild());
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawCheck(0, 0, width(), height(), getName(), selected, false, getBackColor());
		refresh();
	}
	state = false;
}

void TCheckBox::show()
{
	//TPainter p(getInvalidList(),getPaintInvaild());
	refresh();
}
