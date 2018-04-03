#include "TWidget/TImageBox.h"


TImageBox::TImageBox(int32 x, int32 y,TImage* img, const char* name, TWidget* obj)
	:TWidget(x, y, img->imgW(),img->imgH(), name, obj)
{
    this->img = img;
    imgLoadInterface(0,0,img);
    TBufPainter p(getBuffer()->getBufAddr(),getRect());
    p.drawCenterText(0,0,getRect()->width(),getRect()->height(),getName());
    if(img)
        delete img;
}


TImageBox::TImageBox(int32 x, int32 y,uint16 w,uint16 h,const char* filename, const char* name, TWidget* obj,bool DrawInBuf)
    :TWidget(x, y, w , h, name, obj,DrawInBuf)
{
    if(DrawInBuf)
    {
        TImage img(getBuffer()->getBufAddr(), w, h, filename);
        TBufPainter p(getBuffer()->getBufAddr(),getRect());
        p.drawCenterText(0,0,getRect()->width(),getRect()->height(),getName());
    }
    else
    {
        TImage img((uint8*)GUI_FG_BUFADDR,GUI_WIDTH,GUI_HIGH,filename);
        TRect rect(0,0,GUI_WIDTH,GUI_HIGH);
        TBufPainter p((uint8*)GUI_FG_BUFADDR,&rect);
        p.drawCenterText(0,0,getRect()->width(),getRect()->height(),getName());
    }
}

TImageBox::~TImageBox()
{
    
}


void TImageBox::show()
{
   
    refresh();
}

