#include "tGuiMain.h"

//信号都是从root开始分发，如果需要就使用
void distribute(tEvent* event)
{
	//遍历树

}
static void function()
{
	printf("signal function!\n");
}

static void slotfun()
{
	printf("slot run!\n");
}
void tGuiRun()
{
	printf("hello world!\n");
	//设置事件队列
	tQueue<tEvent*>* queue = new tQueue<tEvent*>();
	//驱动调用，当产生中断的时候调用,生成Event并进队列
	//driverCall(&queue);
	//循环查看队列
	tEvent e(Event_None);
	queue->enqueue(&e);
	tEvent* tempEvent;
	while (1)
	{
		tempEvent = NULL;
		if (queue->isEmpty())
			continue;
		tempEvent = queue->dequeue();
		distribute(tempEvent);
	}
}