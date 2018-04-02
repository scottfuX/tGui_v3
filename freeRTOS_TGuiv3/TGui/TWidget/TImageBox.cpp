#include "TWidget/TImageBox.h"


TImageBox::TImageBox(int32 x, int32 y,TImage* img, const char* name, TWidget* obj)
	:TWidget(x, y, img->imgW(),img->imgH(), name, obj)
{
    this->img = img;
    imgLoadInterface(0,0,img);
    TBufPainter p(getBuffer()->getBufAddr(),getRect());
    p.drawCenterText(0,0,getRect()->width(),getRect()->height(),getName());
}


TImageBox::TImageBox(int32 x, int32 y,uint16 w,uint16 h,const char* filename, const char* name, TWidget* obj)
    :TWidget(x, y, w , h, name, obj)
{
    TImage img(getBuffer(), w, h, filename);
    TBufPainter p(getBuffer()->getBufAddr(),getRect());
    p.drawCenterText(0,0,getRect()->width(),getRect()->height(),getName());
}

TImageBox::~TImageBox()
{
    if(img)
        delete img;
}


void TImageBox::show()
{
   
    refresh();
}

