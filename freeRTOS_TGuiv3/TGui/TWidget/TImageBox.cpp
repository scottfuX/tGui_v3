#include "TWidget/TImageBox.h"


TImageBox::TImageBox(int32 x, int32 y,TImage* img, const char* name, TWidget* obj)
	:TWidget(x, y, img->imgW(),img->imgH(), name, obj)
{
    imgLoadInterface(0,0,img);
    TBufPainter p(getBuffer()->getBufAddr(),getRect());
    p.drawCenterText(0,0,getRect()->width(),getRect()->height(),getName());
    if(img)
        delete img;
}

//x,y为绝对地址
//readType 为读点方式
TImageBox::TImageBox(int32 x, int32 y,TImage* img,uint8 readType,const char* name, TWidget* obj)
	:TWidget(x, y, img->imgW(),img->imgH(), name, obj)
{
    imgLoadInterface(0,0,img,NULL,readType);
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
        TImage img ((uint8*)GUI_FG_BUFADDR,GUI_WIDTH,GUI_HIGH, filename);
        TRect rect(0,0,GUI_WIDTH,GUI_HIGH);
        // this->img =  new TImage((uint8*)(GUI_FG_BUFADDR + (x + y * GUI_WIDTH) * GUI_PIXELSIZE),w,h,filename);
        // TRect rect(x,y,w,h);
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

