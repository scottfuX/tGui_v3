#include "interface_conf/tgui_conf.h"

//id 数值 设置其实ID
volatile int32_t win_id = 0;
volatile int32_t TouchX_pre = -1;
volatile int32_t TouchY_pre = -1;
volatile int32_t TouchX = -1;
volatile int32_t TouchY = -1;
volatile int8_t state = 0;

void guiGetPrePoint(int32_t* x,int32_t* y)
{
	(*x) = TouchX_pre;
	(*y) = TouchY_pre;
}

void guiTouchDown(int32_t pre_x,int32_t pre_y,int32_t x,int32_t y)
{
	TouchX_pre = pre_x;
	TouchY_pre = pre_y;
	TouchX = x;
	TouchY = y;
	state = 1;
}

void guiTouchUp(int32_t xid,int32_t yid)
{
	state = 0;
}

int8_t getState(void)
{
	return state;
}

int32_t getTouchX(void)
{
	return TouchX;
}
int32_t getTouchY(void)
{
	return TouchY;
}


