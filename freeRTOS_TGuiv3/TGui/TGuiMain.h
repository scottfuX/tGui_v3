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


#include "interface_conf/tgui_conf.h"
#ifdef __cplusplus
}
#endif

#include "TContainter/TString.h"
#include "TPainter/TBufPainter.h"
#include "TObject/TDirver.h"
#include "TObject/TApplication.h"
#include "TWidget/TWindow.h"
// #include "TWidget/TDialog.h"
// #include "TWidget/TWidget.h"
// #include "TWidget/TPushButton.h"
// #include "TWidget/TCheckBox.h"
// #include "TWidget/TRadioButton.h"
// #include "TWidget/TLabel.h"
// #include "TWidget/TSlider.h"
// #include "TWidget/TImageBox.h"
// #include "TWidget/TSwitch.h"
#include "TGlobal.h"

#include "demo/User.h"
#include "demo/Desktop.h"
//#include "demo/UserPhoto.h"


void TGuiRun(void);


#endif //!_TGUIMAIN_H_
