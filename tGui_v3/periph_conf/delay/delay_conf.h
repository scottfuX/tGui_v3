#ifndef _DELAY_H_
#define _DELAY_H_

#include "stm32f4xx_conf.h"

void DelayMSConfig();
void Delay10USConfig();
void DelayUSConfig();
// Systick延迟 需要先配置时钟
void DelayHandler(int num);

//普通延迟 循环延迟
void Delay(__IO uint32_t nCount);

#endif //!_DELAY_H_

