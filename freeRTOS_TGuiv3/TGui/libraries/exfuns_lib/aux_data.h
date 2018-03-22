#ifndef __AUX_DATA_H
#define	__AUX_DATA_H

#include "stm32f4xx.h"
#include "usart/usart_conf.h"
#include "flash/flash_conf.h"
#include "sdio/sdio_sd_conf.h"
#include "fatfs/ff.h"
#include "string.h"


//SD卡及flash的根目录
#define SD_ROOT       "0:"
#define FLASH_ROOT    "1:"

typedef enum 
{
    AUX_DATA_ERROR = -1,
  
    AUX_XBF_XINSONGTI_25, 
    AUX_XBF_XINSONGTI_19, 
    AUX_UNIGBK, 
    AUX_WIFI_FW,
    AUX_WIFI_PARA1,
    AUX_WIFI_PARA2,
    AUX_GB2312_H2424,  
    AUX_FILE_SYSTEM,      //FLASH文件系统
  
    AUX_MAX_NUM,
} aux_data_t; 


                                       
                                       
 // ==== LOGGING ====
#define SHORT_FILE strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__
 
// ==== BRANCH PREDICTION & EXPRESSION EVALUATION ====
#if( !defined( unlikely ) )
    //#define unlikely( EXPRESSSION )     __builtin_expect( !!(EXPRESSSION), 0 )
   #define unlikely( EXPRESSSION )     !!(EXPRESSSION)
#endif
  
FRESULT copy_file_sd2flash(char *src_path,char *dst_path); 

#endif /* __BURN_DATA_H */
