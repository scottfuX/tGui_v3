#include "demo/UserCalculate.h"

UserCalculate::UserCalculate(int32 x,int32 y,TImage* img,const char* n, TWidget* obj,int offset)
	:TDialog(x,y,img,n,obj,offset)
{

    label = new TLabel(263,97,new TImage("1:/calculate_pic/calcu-comeout.png"),"0",ALIGN_MID_RIGHT,this);
    
    btn0 = new TPushButton(263,379,new TImage("1:/calculate_pic/btn-0.png"),NULL,NULL, this);
    btn_point = new TPushButton(332,379,new TImage("1:/calculate_pic/btn-point.png"),NULL,NULL, this);
    btn_plus = new TPushButton(401,379,new TImage("1:/calculate_pic/btn-plus.png"),NULL,NULL, this);
    
    btn1 = new TPushButton(263,326,new TImage("1:/calculate_pic/btn-1.png"),NULL,NULL, this);
    btn2 = new TPushButton(332,326,new TImage("1:/calculate_pic/btn-2.png"),NULL,NULL, this);
    btn3 = new TPushButton(401,326,new TImage("1:/calculate_pic/btn-3.png"),NULL,NULL, this);
    btn_equ = new TPushButton(470,326,new TImage("1:/calculate_pic/btn-equ.png"),NULL,NULL, this);

    btn4 = new TPushButton(263,273,new TImage("1:/calculate_pic/btn-4.png"),NULL,NULL, this);
    btn5 = new TPushButton(332,273,new TImage("1:/calculate_pic/btn-5.png"),NULL,NULL, this);
    btn6 = new TPushButton(401,273,new TImage("1:/calculate_pic/btn-6.png"),NULL,NULL, this);
    btn_de = new TPushButton(470,273,new TImage("1:/calculate_pic/btn-de.png"),NULL,NULL, this);

    btn7 = new TPushButton(263,220,new TImage("1:/calculate_pic/btn-7.png"),NULL,NULL, this);
    btn8 = new TPushButton(332,220,new TImage("1:/calculate_pic/btn-8.png"),NULL,NULL, this);
    btn9 = new TPushButton(401,220,new TImage("1:/calculate_pic/btn-9.png"),NULL,NULL, this);
    btn_mul = new TPushButton(470,220,new TImage("1:/calculate_pic/btn-multiply.png"),NULL,NULL, this);
    
       
    btn_ac = new TPushButton(263,167,new TImage("1:/calculate_pic/btn-ac.png"),NULL,NULL, this);
    btn_c = new TPushButton(332,167,new TImage("1:/calculate_pic/btn-c.png"),NULL,NULL, this);
    btn_mode = new TPushButton(401,167,new TImage("1:/calculate_pic/btn.png"),NULL,NULL, this); 
    btn_div = new TPushButton(470,167,new TImage("1:/calculate_pic/btn-div.png"),NULL,NULL, this);

    // btn0->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::addNum));
    // btn1->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::addNum));
    // btn2->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::addNum));
    // btn3->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::addNum));
    // btn4->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::addNum));
    // btn5->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::addNum));
    // btn6->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::addNum));
    // btn7->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::addNum));
    // btn8->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::addNum));
    // btn9->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::addNum));
    // btn_plus->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::addOperat));
    // btn_de->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::addOperat));
    // btn_mul->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::addOperat));
    // btn_div->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::addOperat));
    // btn_equ->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::addOperat));
    // btn_mode->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::addOperat));  
    // btn_point->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::addNum));   
    // btn_ac->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::clearData));
    // btn_c->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::clearData));

    // close_btn = new TPushButton(710,20,new TImage("1:/tgui_pic/check2_sel.png"),NULL,NULL, this);
    // close_btn->connect((func)(&TPushButton::sig_release),this,(func)(&UserCalculate::closeCalculate));    					    
}

UserCalculate::~UserCalculate()
{
    
}

void UserCalculate::addNum(int32 d1,int32 d2)
{
    switch(d1)
    {
//        case ((int32)btn0):{}break;
//        case ((int32)btn1):{}break;
//        case ((int32)btn2):{}break;
//        case ((int32)btn3):{}break;
//        case ((int32)btn4):{}break;
//        case ((int32)btn5):{}break;
//        case ((int32)btn6):{}break;
//        case ((int32)btn7):{}break;
//        case ((int32)btn8):{}break;
//        case ((int32)btn9):{}break;
//        case ((int32)btn_point):{}break;
        default:break;
    }
}

void UserCalculate::addOperat(int32 d1,int32 d2)
{

}

void UserCalculate::clearData(int32 d1,int32 d2)
{

}

void UserCalculate::closeCalculate()
{
    //(getParents())
}

void UserCalculate::show()
{
	refresh();
}



