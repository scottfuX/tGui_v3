#ifndef _TGUIMAIN_H_
#define _TGUIMAIN_H_

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "led/led_conf.h"
#include "usart/usart_conf.h"
#include "flash/flash_conf.h"
#include "fatfs/ff.h"
#include "lcd/lcd_conf.h"
#include "touch/gt9xx.h"
#include "delay/delay_conf.h"
#include "test/fstest.h"
#include "test/lcdtest.h"
#include "test/lcdpalette.h"

#include "interface_conf/tgui_conf.h"
#ifdef __cplusplus
}
#endif

#include "tContainter/tString.h"
#include "tObject/tWidget.h"
#include "tObject/tPushButton.h"
#include "tObject/tDirver.h"
#include "tObject/tApplication.h"

#include"demo/User.h"
#include "tGlobal.h"



void tGuiRun(void);


#endif //!_TGUIMAIN_H_
