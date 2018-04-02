#include "TWidget/TCheckBox.h"


TCheckBox::TCheckBox(int32 x, int32 y, int32 w, int32 h, const char* name, TWidget* obj)
	:TAbstractButton(x, y, w, h, false,name, obj)
{
	next = this; 
	selected = false; 

	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawCheck(0,0, width(), height(), getName(), selected, state, getBackColor());
}



TCheckBox::TCheckBox(TRect rect,TImage* norImg,TImage* selImg, const char* name, TWidget* obj)
	:TAbstractButton(rect.x(),rect.y(),rect.width(),rect.height(), true,name, obj)
{
	next = this; 
	selected = false; 
	this->norImg = norImg;
	this->selImg = selImg;
	getBuffer()->obPareBack(getPareBufCorreAddr(),((TWidget*)getParents())->width());
	imgLoadInterface(0,(height() - norImg->imgH())/2,norImg);
	TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.drawAlignText(norImg->imgW(),0, getName(),ALIGN_MID_LEFT);

}

TCheckBox::~TCheckBox() 
{
	
};

void TCheckBox::sig_depress(int32 d1, int32 d2)
{
	if(haveImg)
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
	if(haveImg)
	{
		if(selected)
		{
			imgLoadInterface(0,(height() - selImg->imgH())/2,selImg);
			TBufPainter p(getBuffer()->getBufAddr(),getRect());
			p.drawAlignText(selImg->imgW(),0, getName(),ALIGN_MID_LEFT);
		}
		else
		{
			imgLoadInterface(0,(height() - norImg->imgH())/2,norImg);
			TBufPainter p(getBuffer()->getBufAddr(),getRect());
			p.drawAlignText(norImg->imgW(),0, getName(),ALIGN_MID_LEFT);
		}
	}
	else
	{
		//TPainter p(getInvalidList(),getPaintInvaild());
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawCheck(0, 0, width(), height(), getName(), selected, false, getBackColor());
	}
	refresh();
	state = false;
	callSlot((func)&TCheckBox::sig_release,d1,d2);
}

void TCheckBox::release()
{
	changeSelected();
	if(haveImg)
	{
		if(selected)
		{
			imgLoadInterface(0,(height() - selImg->imgH())/2,selImg);
			TBufPainter p(getBuffer()->getBufAddr(),getRect());
			p.drawAlignText(selImg->imgW(),0, getName(),ALIGN_MID_LEFT);
		}
		else
		{
			imgLoadInterface(0,(height() - norImg->imgH())/2,norImg);
			TBufPainter p(getBuffer()->getBufAddr(),getRect());
			p.drawAlignText(norImg->imgW(),0, getName(),ALIGN_MID_LEFT);
		}
	}
	else
	{
		//TPainter p(getInvalidList(),getPaintInvaild());
		TBufPainter p(getBuffer()->getBufAddr(),getRect());
		p.drawCheck(0, 0, width(), height(), getName(), selected, false, getBackColor());
		
	}
	refresh();
	state = false;
}

void TCheckBox::show()
{
	//TPainter p(getInvalidList(),getPaintInvaild());
	refresh();
}
