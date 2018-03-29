#ifndef _LCDCONFIG_H_
#define _LCDCONFIG_H_

#include "stm32f4xx_conf.h"
#include "sdram/sdram_conf.h"

/*把这个宏设置成非0值 液晶屏使用RGB888色彩，若为0则使用RGB565色彩*/
#define LCD_RGB_8888  1

#if  LCD_RGB_8888

/*******RGB8888头文件***********************RGB8888头文件***********************RGB8888头文件***********************RGB8888头文件***********************RGB8888头文件***********************RGB8888头文件***********************RGB8888头文件***********************RGB8888头文件***********************/




typedef struct 
{
  int16_t X;
  int16_t Y;
} Point, * pPoint;   
/**
  * @}
  */ 

/** @defgroup stm32f429i_discovery_LCD_Exported_Constants
  * @{
  */ 

/* LCD Size (Width and Height) */
#define  LCD_PIXEL_WIDTH    ((uint16_t)800)
#define  LCD_PIXEL_HEIGHT   ((uint16_t)480)

#define LCD_FRAME_BUFFER       ((uint32_t)0xD0400000)   //0xD0000000 
#define BUFFER_OFFSET          ((uint32_t)800*480*4)    //sdram为24位的,液晶RGB888
#define LCD_PIXCELS            ((uint32_t)800*480) 


/** 
  * @brief  LCD color  
  */ 


#define LCD_COLOR_WHITE          0xFFFFFFFF
#define LCD_COLOR_BLACK          0xFF000000
#define LCD_COLOR_GREY           0xFFC0C0C0
#define LCD_COLOR_BLUE           0xFF0000FF
#define LCD_COLOR_BLUE2          0xFF0000A0
#define LCD_COLOR_RED            0xFFFF0000
#define LCD_COLOR_MAGENTA        0xFFFF00FF
#define LCD_COLOR_GREEN          0xFF00FF00
#define LCD_COLOR_CYAN           0xFF00FFFF
#define LCD_COLOR_YELLOW         0xFFFFFF00


/** 
  * @brief  LCD Lines depending on the chosen fonts.  
  */
#define LCD_LINE_0               LINE(0)
#define LCD_LINE_1               LINE(1)
#define LCD_LINE_2               LINE(2)
#define LCD_LINE_3               LINE(3)
#define LCD_LINE_4               LINE(4)
#define LCD_LINE_5               LINE(5)
#define LCD_LINE_6               LINE(6)
#define LCD_LINE_7               LINE(7)
#define LCD_LINE_8               LINE(8)
#define LCD_LINE_9               LINE(9)
#define LCD_LINE_10              LINE(10)
#define LCD_LINE_11              LINE(11)
#define LCD_LINE_12              LINE(12)
#define LCD_LINE_13              LINE(13)
#define LCD_LINE_14              LINE(14)
#define LCD_LINE_15              LINE(15)
#define LCD_LINE_16              LINE(16)
#define LCD_LINE_17              LINE(17)
#define LCD_LINE_18              LINE(18)
#define LCD_LINE_19              LINE(19)
#define LCD_LINE_20              LINE(20)
#define LCD_LINE_21              LINE(21)
#define LCD_LINE_22              LINE(22)
#define LCD_LINE_23              LINE(23)
#define LCD_LINE_24              LINE(24)
#define LCD_LINE_25              LINE(25)
#define LCD_LINE_26              LINE(26)
#define LCD_LINE_27              LINE(27)
#define LCD_LINE_28              LINE(28)
#define LCD_LINE_29              LINE(29)
#define LCD_LINE_30              LINE(30)
#define LCD_LINE_31              LINE(31)
#define LCD_LINE_32              LINE(32)
#define LCD_LINE_33              LINE(33)
#define LCD_LINE_34              LINE(34)
#define LCD_LINE_35              LINE(35)
#define LCD_LINE_36              LINE(36)
#define LCD_LINE_37              LINE(37)
#define LCD_LINE_38              LINE(38)
#define LCD_LINE_39              LINE(39)

/** 
  * @brief LCD default font 
  */ 
#define LCD_DEFAULT_FONT         Font16x24

/** 
  * @brief  LCD Direction  
  */ 
#define LCD_DIR_HORIZONTAL       0x0000
#define LCD_DIR_VERTICAL         0x0001

/**
  * @}
  */ 

/** 
  * @brief  LCD Layer  
  */ 
#define LCD_BACKGROUND_LAYER     0x0000
#define LCD_FOREGROUND_LAYER     0x0001

/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_LCD_Exported_Macros
  * @{
  */ 
#define ASSEMBLE_RGB(R, G, B)    ((((R)& 0xF8) << 8) | (((G) & 0xFC) << 3) | (((B) & 0xF8) >> 3))  




/**
  * @}
  */ 
  
  

/*部分液晶信号线的引脚复用编号是AF9*/
#define GPIO_AF_LTDC_AF9          ((uint8_t)0x09)  


/**
  * @}
  */ 
//红色数据线
#define LTDC_R0_GPIO_PORT        	GPIOH
#define LTDC_R0_GPIO_CLK         	RCC_AHB1Periph_GPIOH
#define LTDC_R0_GPIO_PIN         	GPIO_Pin_2
#define LTDC_R0_PINSOURCE        	GPIO_PinSource2
#define LTDC_R0_AF			          GPIO_AF_LTDC

#define LTDC_R1_GPIO_PORT        	GPIOH
#define LTDC_R1_GPIO_CLK         	RCC_AHB1Periph_GPIOH
#define LTDC_R1_GPIO_PIN         	GPIO_Pin_3
#define LTDC_R1_PINSOURCE        	GPIO_PinSource3
#define LTDC_R1_AF			          GPIO_AF_LTDC

#define LTDC_R2_GPIO_PORT        	GPIOH
#define LTDC_R2_GPIO_CLK         	RCC_AHB1Periph_GPIOH
#define LTDC_R2_GPIO_PIN         	GPIO_Pin_8
#define LTDC_R2_PINSOURCE        	GPIO_PinSource8
#define LTDC_R2_AF			          GPIO_AF_LTDC

#define LTDC_R3_GPIO_PORT        	GPIOB
#define LTDC_R3_GPIO_CLK         	RCC_AHB1Periph_GPIOB
#define LTDC_R3_GPIO_PIN         	GPIO_Pin_0
#define LTDC_R3_PINSOURCE        	GPIO_PinSource0
#define LTDC_R3_AF			          GPIO_AF_LTDC_AF9

#define LTDC_R4_GPIO_PORT        	GPIOA
#define LTDC_R4_GPIO_CLK         	RCC_AHB1Periph_GPIOA
#define LTDC_R4_GPIO_PIN         	GPIO_Pin_11
#define LTDC_R4_PINSOURCE        	GPIO_PinSource11
#define LTDC_R4_AF			          GPIO_AF_LTDC

#define LTDC_R5_GPIO_PORT        	GPIOA
#define LTDC_R5_GPIO_CLK         	RCC_AHB1Periph_GPIOA
#define LTDC_R5_GPIO_PIN         	GPIO_Pin_12
#define LTDC_R5_PINSOURCE        	GPIO_PinSource12
#define LTDC_R5_AF			          GPIO_AF_LTDC

#define LTDC_R6_GPIO_PORT        	GPIOB
#define LTDC_R6_GPIO_CLK         	RCC_AHB1Periph_GPIOB
#define LTDC_R6_GPIO_PIN         	GPIO_Pin_1
#define LTDC_R6_PINSOURCE        	GPIO_PinSource1
#define LTDC_R6_AF			          GPIO_AF_LTDC_AF9

#define LTDC_R7_GPIO_PORT        	GPIOG
#define LTDC_R7_GPIO_CLK         	RCC_AHB1Periph_GPIOG
#define LTDC_R7_GPIO_PIN         	GPIO_Pin_6
#define LTDC_R7_PINSOURCE        	GPIO_PinSource6
#define LTDC_R7_AF			          GPIO_AF_LTDC
//绿色数据线
#define LTDC_G0_GPIO_PORT        	GPIOE
#define LTDC_G0_GPIO_CLK         	RCC_AHB1Periph_GPIOE
#define LTDC_G0_GPIO_PIN         	GPIO_Pin_5
#define LTDC_G0_PINSOURCE        	GPIO_PinSource5
#define LTDC_G0_AF			          GPIO_AF_LTDC

#define LTDC_G1_GPIO_PORT        	GPIOE
#define LTDC_G1_GPIO_CLK         	RCC_AHB1Periph_GPIOE
#define LTDC_G1_GPIO_PIN         	GPIO_Pin_6
#define LTDC_G1_PINSOURCE        	GPIO_PinSource6
#define LTDC_G1_AF			          GPIO_AF_LTDC

#define LTDC_G2_GPIO_PORT        	GPIOH
#define LTDC_G2_GPIO_CLK         	RCC_AHB1Periph_GPIOH
#define LTDC_G2_GPIO_PIN         	GPIO_Pin_13
#define LTDC_G2_PINSOURCE        	GPIO_PinSource13
#define LTDC_G2_AF			          GPIO_AF_LTDC

#define LTDC_G3_GPIO_PORT        	GPIOG
#define LTDC_G3_GPIO_CLK         	RCC_AHB1Periph_GPIOG
#define LTDC_G3_GPIO_PIN         	GPIO_Pin_10
#define LTDC_G3_PINSOURCE        	GPIO_PinSource10
#define LTDC_G3_AF			          GPIO_AF_LTDC_AF9

#define LTDC_G4_GPIO_PORT        	GPIOH
#define LTDC_G4_GPIO_CLK         	RCC_AHB1Periph_GPIOH
#define LTDC_G4_GPIO_PIN         	GPIO_Pin_15
#define LTDC_G4_PINSOURCE        	GPIO_PinSource15
#define LTDC_G4_AF			          GPIO_AF_LTDC

#define LTDC_G5_GPIO_PORT        	GPIOI
#define LTDC_G5_GPIO_CLK         	RCC_AHB1Periph_GPIOI
#define LTDC_G5_GPIO_PIN         	GPIO_Pin_0
#define LTDC_G5_PINSOURCE        	GPIO_PinSource0
#define LTDC_G5_AF			          GPIO_AF_LTDC

#define LTDC_G6_GPIO_PORT        	GPIOC
#define LTDC_G6_GPIO_CLK         	RCC_AHB1Periph_GPIOC
#define LTDC_G6_GPIO_PIN         	GPIO_Pin_7
#define LTDC_G6_PINSOURCE        	GPIO_PinSource7
#define LTDC_G6_AF			          GPIO_AF_LTDC

#define LTDC_G7_GPIO_PORT        	GPIOI
#define LTDC_G7_GPIO_CLK         	RCC_AHB1Periph_GPIOI
#define LTDC_G7_GPIO_PIN         	GPIO_Pin_2
#define LTDC_G7_PINSOURCE        	GPIO_PinSource2
#define LTDC_G7_AF			          GPIO_AF_LTDC

//蓝色数据线
#define LTDC_B0_GPIO_PORT        	GPIOE
#define LTDC_B0_GPIO_CLK         	RCC_AHB1Periph_GPIOE
#define LTDC_B0_GPIO_PIN         	GPIO_Pin_4
#define LTDC_B0_PINSOURCE        	GPIO_PinSource4
#define LTDC_B0_AF			          GPIO_AF_LTDC

#define LTDC_B1_GPIO_PORT        	GPIOG
#define LTDC_B1_GPIO_CLK         	RCC_AHB1Periph_GPIOG
#define LTDC_B1_GPIO_PIN         	GPIO_Pin_12
#define LTDC_B1_PINSOURCE        	GPIO_PinSource12
#define LTDC_B1_AF			          GPIO_AF_LTDC

#define LTDC_B2_GPIO_PORT        	GPIOD
#define LTDC_B2_GPIO_CLK         	RCC_AHB1Periph_GPIOD
#define LTDC_B2_GPIO_PIN         	GPIO_Pin_6
#define LTDC_B2_PINSOURCE        	GPIO_PinSource6
#define LTDC_B2_AF			          GPIO_AF_LTDC

#define LTDC_B3_GPIO_PORT        	GPIOG
#define LTDC_B3_GPIO_CLK         	RCC_AHB1Periph_GPIOG
#define LTDC_B3_GPIO_PIN         	GPIO_Pin_11
#define LTDC_B3_PINSOURCE        	GPIO_PinSource11
#define LTDC_B3_AF			          GPIO_AF_LTDC

#define LTDC_B4_GPIO_PORT        	GPIOI
#define LTDC_B4_GPIO_CLK         	RCC_AHB1Periph_GPIOI
#define LTDC_B4_GPIO_PIN         	GPIO_Pin_4
#define LTDC_B4_PINSOURCE        	GPIO_PinSource4
#define LTDC_B4_AF			          GPIO_AF_LTDC

#define LTDC_B5_GPIO_PORT        	GPIOA
#define LTDC_B5_GPIO_CLK         	RCC_AHB1Periph_GPIOA
#define LTDC_B5_GPIO_PIN         	GPIO_Pin_3
#define LTDC_B5_PINSOURCE        	GPIO_PinSource3
#define LTDC_B5_AF			          GPIO_AF_LTDC

#define LTDC_B6_GPIO_PORT        	GPIOB
#define LTDC_B6_GPIO_CLK         	RCC_AHB1Periph_GPIOB
#define LTDC_B6_GPIO_PIN         	GPIO_Pin_8
#define LTDC_B6_PINSOURCE        	GPIO_PinSource8
#define LTDC_B6_AF			          GPIO_AF_LTDC

#define LTDC_B7_GPIO_PORT        	GPIOB
#define LTDC_B7_GPIO_CLK         	RCC_AHB1Periph_GPIOB
#define LTDC_B7_GPIO_PIN         	GPIO_Pin_9
#define LTDC_B7_PINSOURCE        	GPIO_PinSource9
#define LTDC_B7_AF			          GPIO_AF_LTDC

//控制信号线
#define LTDC_CLK_GPIO_PORT        GPIOG
#define LTDC_CLK_GPIO_CLK         RCC_AHB1Periph_GPIOG
#define LTDC_CLK_GPIO_PIN         GPIO_Pin_7
#define LTDC_CLK_PINSOURCE        GPIO_PinSource7
#define LTDC_CLK_AF			          GPIO_AF_LTDC

#define LTDC_HSYNC_GPIO_PORT      GPIOI
#define LTDC_HSYNC_GPIO_CLK       RCC_AHB1Periph_GPIOI
#define LTDC_HSYNC_GPIO_PIN       GPIO_Pin_10
#define LTDC_HSYNC_PINSOURCE      GPIO_PinSource10
#define LTDC_HSYNC_AF			        GPIO_AF_LTDC

#define LTDC_VSYNC_GPIO_PORT      GPIOI
#define LTDC_VSYNC_GPIO_CLK       RCC_AHB1Periph_GPIOI
#define LTDC_VSYNC_GPIO_PIN       GPIO_Pin_9
#define LTDC_VSYNC_PINSOURCE      GPIO_PinSource9
#define LTDC_VSYNC_AF			        GPIO_AF_LTDC


#define LTDC_DE_GPIO_PORT         GPIOF
#define LTDC_DE_GPIO_CLK          RCC_AHB1Periph_GPIOF
#define LTDC_DE_GPIO_PIN          GPIO_Pin_10
#define LTDC_DE_PINSOURCE         GPIO_PinSource10
#define LTDC_DE_AF			          GPIO_AF_LTDC

#define LTDC_DISP_GPIO_PORT        GPIOD
#define LTDC_DISP_GPIO_CLK         RCC_AHB1Periph_GPIOD
#define LTDC_DISP_GPIO_PIN         GPIO_Pin_4

#define LTDC_BL_GPIO_PORT         GPIOD
#define LTDC_BL_GPIO_CLK          RCC_AHB1Periph_GPIOD
#define LTDC_BL_GPIO_PIN          GPIO_Pin_7




/** @defgroup STM32F429I_DISCOVERY_LCD_Exported_Functions
  * @{
  */ 
void		 LCDConfig(void);	

void     LCD_Init(void);
void     LCD_LayerInit(void);
void     LCD_ChipSelect(FunctionalState NewState);
void     LCD_SetLayer(uint32_t Layerx);
void     LCD_SetColors(uint32_t _TextColor, uint32_t _BackColor); 
void     LCD_GetColors(uint32_t *_TextColor, uint32_t *_BackColor);
void     LCD_SetTextColor(uint32_t Color);
void     LCD_SetBackColor(uint32_t Color);
void     LCD_SetTransparency(uint8_t transparency);
void     LCD_ClearLine(uint16_t Line);
void     LCD_Clear(uint32_t Color);
uint32_t LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void     LCD_SetColorKeying(uint32_t RGBValue);
void     LCD_ReSetColorKeying(void);


#else


#endif


#endif // !_LCDCONFIG_H_
