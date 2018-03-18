#include "delay/delay_conf.h"


/*T INT = VALUE LOAD / CLK AHB-------这里只需设置Value LOAD即可
		SystemCoreClock =180MHZ
		SystemCoreClock/1000=1ms
		SystemCoreClock/100000=10us
		SystemCoreClock/1000000=1us
*/

//普通延迟
void Delay(__IO uint32_t nCount)	 //简单的延时函数 大概为1/10000ms
{
	for (; nCount != 0; nCount--)
		;
}

