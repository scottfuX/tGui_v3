#include "TWidget/TWindow.h"

TWindow::TWindow(TApplication* app,const char* n, TWidget* obj)
    :TWidget(0,0,GUI_WIDTH,GUI_HIGH,n,obj)
{
    this->app = app;
    TBufPainter p(getBuffer()->getBufAddr(),getRect());
	p.setColors(GOLD, GOLD);
	p.drawFullRect(0,0,width(),height()); 
}

TWindow::TWindow(const char* filename ,TApplication* app, const char* n,TWidget* obj)
    :TWidget(0,0,GUI_WIDTH,GUI_HIGH,n,obj)
{
    this->app = app;
    TImage img(getBuffer(), GUI_WIDTH, GUI_HIGH, filename);
}

TWindow::~TWindow()
{

}

void TWindow::show()
{
   
    refresh();
}


void TWindow::slot_close() //发送信号给application
{
  app->setSignal(this,Event_Close);
}