
#include "lcd/lcd_conf.h"


/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup STM32F4_DISCOVERY
  * @{
  */ 

/** @addtogroup STM32F429I_DISCOVERY
  * @{
  */
    
/** @defgroup STM32F429I_DISCOVERY_LCD 
  * @brief This file includes the LCD driver for (ILI9341) 
  * @{
  */ 

/** @defgroup STM32F429I_DISCOVERY_LCD_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */

/** @defgroup STM32F429I_DISCOVERY_LCD_Private_Defines
  * @{
  */

#define POLY_Y(Z)          ((int32_t)((Points + Z)->X))
#define POLY_X(Z)          ((int32_t)((Points + Z)->Y))   

#define ZOOMMAXBUFF 16384
uint8_t zoomBuff[ZOOMMAXBUFF] = {0};	//用于缩放的缓存，最大支持到128*128
/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_LCD_Private_Macros
  * @{
  */
#define ABS(X)  ((X) > 0 ? (X) : -(X))    
/**
  * @}
  */ 
	

#if  1//LCD_RGB_888
/****************RGB888驱动*****************************RGB888驱动*****************************RGB888驱动**********************************RGB888驱动**********************************RGB888驱动*********************************/
	
 


/** @defgroup STM32F429I_DISCOVERY_LCD_Private_Variables
  * @{
  */ 

/* Global variables to set the written text color */
static uint32_t CurrentTextColor   = 0xFF000000;
static uint32_t CurrentBackColor   = 0xFFFFFFFF;
/* Default LCD configuration with LCD Layer 1 */
static uint32_t CurrentFrameBuffer = LCD_FRAME_BUFFER;
static uint32_t CurrentLayer = LCD_BACKGROUND_LAYER;
/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_LCD_Private_FunctionPrototypes
  * @{
  */ 


static void LCD_PolyLineRelativeClosed(pPoint Points, uint16_t PointCount, uint16_t Closed);
static void LCD_GPIO_Config(void);

/**
  * @}
  */ 

 

/**
  * @brief  Initializes the LCD.
  * @param  None
  * @retval None
  */
/*根据液晶数据手册的参数配置*/
#define HBP  46		//HSYNC后的无效像素
#define VBP  23		//VSYNC后的无效行数

#define HSW   1		//HSYNC宽度
#define VSW   1		//VSYNC宽度

#define HFP  22		//HSYNC前的无效像素
#define VFP   22		//VSYNC前的无效行数


/**
  * @brief LCD参数配置
  * @note  这个函数用于配置LTDC外设:
  *        1)配置像素同步时钟CLK
  *        2)配置LTDC时间参数及信号极性
  * @retval  None 
  */
void LCD_Init(void)
{ 
  LTDC_InitTypeDef       LTDC_InitStruct;
  
  /* 使能LTDC外设时钟 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_LTDC, ENABLE);
  
  /* 使能DMA2D时钟 */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2D, ENABLE);
	
	/* 初始化LCD的控制引脚 */
  LCD_GPIO_Config();   
	
	/* 初始化SDRAM，以便使用SDRAM作显存 */
  SDRAMConfig();
	
	/* 配置 PLLSAI 分频器，它的输出作为像素同步时钟CLK*/
  /* PLLSAI_VCO 输入时钟 = HSE_VALUE/PLL_M = 1 Mhz */
  /* PLLSAI_VCO 输出时钟 = PLLSAI_VCO输入 * PLLSAI_N = 420 Mhz */
  /* PLLLCDCLK = PLLSAI_VCO 输出/PLLSAI_R = 420/6  Mhz */
  /* LTDC 时钟频率 = PLLLCDCLK / DIV = 420/6/8 = 8.75 Mhz */
	/* LTDC时钟太高会导花屏，若对刷屏速度要求不高，降低时钟频率可减少花屏现象*/
	/* 以下函数三个参数分别为：PLLSAIN,PLLSAIQ,PLLSAIR，其中PLLSAIQ与LTDC无关*/
  RCC_PLLSAIConfig(420,7, 6);
	/*以下函数的参数为DIV值*/
  RCC_LTDCCLKDivConfig(RCC_PLLSAIDivR_Div8);
  
  /* 使能 PLLSAI 时钟 */
  RCC_PLLSAICmd(ENABLE);
  /* 等待 PLLSAI 初始化完成 */
  while(RCC_GetFlagStatus(RCC_FLAG_PLLSAIRDY) == RESET)
  {
  }
  
  /* LTDC配置*********************************************************/  
  /*信号极性配置*/
  /* 行同步信号极性 */
  LTDC_InitStruct.LTDC_HSPolarity = LTDC_HSPolarity_AL;     
  /* 垂直同步信号极性 */  
  LTDC_InitStruct.LTDC_VSPolarity = LTDC_VSPolarity_AL;     
  /* 数据使能信号极性 */
  LTDC_InitStruct.LTDC_DEPolarity = LTDC_DEPolarity_AL;     
  /* 像素同步时钟极性 */ 
  LTDC_InitStruct.LTDC_PCPolarity = LTDC_PCPolarity_IPC;
  
  /* 配置LCD背景颜色 */                   
  LTDC_InitStruct.LTDC_BackgroundRedValue = 0;            
  LTDC_InitStruct.LTDC_BackgroundGreenValue = 0;          
  LTDC_InitStruct.LTDC_BackgroundBlueValue = 0;    
 
  /* 时间参数配置 */  
  /* 配置行同步信号宽度(HSW-1) */
  LTDC_InitStruct.LTDC_HorizontalSync =HSW-1;
  /* 配置垂直同步信号宽度(VSW-1) */
  LTDC_InitStruct.LTDC_VerticalSync = VSW-1;
  /* 配置(HSW+HBP-1) */
  LTDC_InitStruct.LTDC_AccumulatedHBP =HSW+HBP-1;
  /* 配置(VSW+VBP-1) */
  LTDC_InitStruct.LTDC_AccumulatedVBP = VSW+VBP-1;
  /* 配置(HSW+HBP+有效像素宽度-1) */
  LTDC_InitStruct.LTDC_AccumulatedActiveW = HSW+HBP+LCD_PIXEL_WIDTH-1;
  /* 配置(VSW+VBP+有效像素高度-1) */
  LTDC_InitStruct.LTDC_AccumulatedActiveH = VSW+VBP+LCD_PIXEL_HEIGHT-1;
  /* 配置总宽度(HSW+HBP+有效像素宽度+HFP-1) */
  LTDC_InitStruct.LTDC_TotalWidth =HSW+ HBP+LCD_PIXEL_WIDTH  + HFP-1; 
  /* 配置总高度(VSW+VBP+有效像素高度+VFP-1) */
  LTDC_InitStruct.LTDC_TotalHeigh =VSW+ VBP+LCD_PIXEL_HEIGHT  + VFP-1;

  LTDC_Init(&LTDC_InitStruct);
  
  LTDC_Cmd(ENABLE);

	LCD_LayerInit();
	LTDC_Cmd(ENABLE);
	/*把背景层刷黑色*/
	LCD_SetLayer(LCD_BACKGROUND_LAYER);  
	/*初始化后默认使用前景层*/
	LCD_SetLayer(LCD_FOREGROUND_LAYER); 
	/*默认设置不透明，该函数参数为不透明度，范围 0-0xff ，0为全透明，0xff为不透明*/
	LCD_SetTransparency(0xff);
}  

/**
  * @brief 初始化LTD的 层 参数
  *           - 设置显存空间
  *           - 设置分辨率
  * @param  None
  * @retval None
  */
void LCD_LayerInit(void)
{
  LTDC_Layer_InitTypeDef LTDC_Layer_InitStruct; 
  
  /* 层窗口配置 */
  /* 配置本层的窗口边界，注意这些参数是包含HBP HSW VBP VSW的 */    
	//一行的第一个起始像素，该成员值应用为 (LTDC_InitStruct.LTDC_AccumulatedHBP+1)的值
	LTDC_Layer_InitStruct.LTDC_HorizontalStart = HBP + HSW;
	//一行的最后一个像素，该成员值应用为 (LTDC_InitStruct.LTDC_AccumulatedActiveW)的值
	LTDC_Layer_InitStruct.LTDC_HorizontalStop = HSW+HBP+LCD_PIXEL_WIDTH-1;
	//一列的第一个起始像素，该成员值应用为 (LTDC_InitStruct.LTDC_AccumulatedVBP+1)的值
	LTDC_Layer_InitStruct.LTDC_VerticalStart =  VBP + VSW;
	//一列的最后一个像素，该成员值应用为 (LTDC_InitStruct.LTDC_AccumulatedActiveH)的值
	LTDC_Layer_InitStruct.LTDC_VerticalStop = VSW+VBP+LCD_PIXEL_HEIGHT-1;
	
  /* 像素格式配置*/
  LTDC_Layer_InitStruct.LTDC_PixelFormat = LTDC_Pixelformat_ARGB8888;
  /* 恒定Alpha值配置，0-255 */
  LTDC_Layer_InitStruct.LTDC_ConstantAlpha = 255; 
  /* 默认背景颜色，该颜色在定义的层窗口外或在层禁止时使用。 */          
  LTDC_Layer_InitStruct.LTDC_DefaultColorBlue = 0xFF;        
  LTDC_Layer_InitStruct.LTDC_DefaultColorGreen = 0xFF;       
  LTDC_Layer_InitStruct.LTDC_DefaultColorRed = 0xFF;         
  LTDC_Layer_InitStruct.LTDC_DefaultColorAlpha = 0xFF;
  /* 配置混合因子 CA表示使用恒定Alpha值，PAxCA表示使用像素Alpha x 恒定Alpha值 */       
  LTDC_Layer_InitStruct.LTDC_BlendingFactor_1 = LTDC_BlendingFactor1_CA;    
  LTDC_Layer_InitStruct.LTDC_BlendingFactor_2 = LTDC_BlendingFactor2_PAxCA;
  
  /* 该成员应写入(一行像素数据占用的字节数+3)
  Line Lenth = 行有效像素个数 x 每个像素的字节数 + 3 
  行有效像素个数 = LCD_PIXEL_WIDTH 
  每个像素的字节数 = 2（RGB565/RGB1555）/ 3 (RGB888)/ 4（ARGB8888） 
  */
  LTDC_Layer_InitStruct.LTDC_CFBLineLength = ((LCD_PIXEL_WIDTH * 4) + 3);
  /* 从某行的起始位置到下一行起始位置处的像素增量
  Pitch = 行有效像素个数 x 每个像素的字节数 */ 
  LTDC_Layer_InitStruct.LTDC_CFBPitch = (LCD_PIXEL_WIDTH * 4);
  
  /* 配置有效的行数 */  
  LTDC_Layer_InitStruct.LTDC_CFBLineNumber = LCD_PIXEL_HEIGHT;
  
  /* 配置本层的显存首地址 */    
  LTDC_Layer_InitStruct.LTDC_CFBStartAdress = LCD_FRAME_BUFFER;
  
  /* 以上面的配置初始化第 1 层*/
  LTDC_LayerInit(LTDC_Layer1, &LTDC_Layer_InitStruct);

  /*配置第 2 层，若没有重写某个成员的值，则该成员使用跟第1层一样的配置 */
  /* 配置本层的显存首地址，这里配置它紧挨在第1层的后面*/     
  LTDC_Layer_InitStruct.LTDC_CFBStartAdress = LCD_FRAME_BUFFER + BUFFER_OFFSET;

	/* 配置混合因子，使用像素Alpha参与混合 */       
  LTDC_Layer_InitStruct.LTDC_BlendingFactor_1 = LTDC_BlendingFactor1_PAxCA;    
  LTDC_Layer_InitStruct.LTDC_BlendingFactor_2 = LTDC_BlendingFactor2_PAxCA;

  /* 初始化第2层 */
  LTDC_LayerInit(LTDC_Layer2, &LTDC_Layer_InitStruct);
 
 /* 立即重载配置 */  
  LTDC_ReloadConfig(LTDC_IMReload);

 /*使能前景及背景层 */
  LTDC_LayerCmd(LTDC_Layer1, ENABLE); 
  LTDC_LayerCmd(LTDC_Layer2, ENABLE);
 
  /* 立即重载配置 */  
  LTDC_ReloadConfig(LTDC_IMReload);

}



/**
  * @brief  Sets the LCD Layer.
  * @param  Layerx: specifies the Layer foreground or background.
  * @retval None
  */
void LCD_SetLayer(uint32_t Layerx)
{
  if (Layerx == LCD_BACKGROUND_LAYER)
  {
    CurrentFrameBuffer = LCD_FRAME_BUFFER; 
    CurrentLayer = LCD_BACKGROUND_LAYER;
  }
  else
  {
    CurrentFrameBuffer = LCD_FRAME_BUFFER + BUFFER_OFFSET;
    CurrentLayer = LCD_FOREGROUND_LAYER;
  }
}  

/**
  * @brief  Configure the transparency.
  * @param  transparency: specifies the transparency, 
  *         This parameter must range from 0x00 to 0xFF.
  * @retval None
  */
void LCD_SetTransparency(uint8_t transparency)
{
  if (CurrentLayer == LCD_BACKGROUND_LAYER)
  {
    LTDC_LayerAlpha(LTDC_Layer1, transparency);
  }
  else
  {     
    LTDC_LayerAlpha(LTDC_Layer2, transparency);
  }
  LTDC_ReloadConfig(LTDC_IMReload);
}



static void LCD_GPIO_Config(void)
{ 
	GPIO_InitTypeDef GPIO_InitStruct;
  
  /* 使能LCD使用到的引脚时钟 */
                          //红色数据线
  RCC_AHB1PeriphClockCmd(LTDC_R0_GPIO_CLK | LTDC_R1_GPIO_CLK | LTDC_R2_GPIO_CLK| 
                         LTDC_R3_GPIO_CLK | LTDC_R4_GPIO_CLK | LTDC_R5_GPIO_CLK|
                         LTDC_R6_GPIO_CLK | LTDC_R7_GPIO_CLK |
                          //绿色数据线
                          LTDC_G0_GPIO_CLK|LTDC_G1_GPIO_CLK|LTDC_G2_GPIO_CLK|
                          LTDC_G3_GPIO_CLK|LTDC_G4_GPIO_CLK|LTDC_G5_GPIO_CLK|
                          LTDC_G6_GPIO_CLK|LTDC_G7_GPIO_CLK|
                          //蓝色数据线
                          LTDC_B0_GPIO_CLK|LTDC_B1_GPIO_CLK|LTDC_B2_GPIO_CLK|
                          LTDC_B3_GPIO_CLK|LTDC_B4_GPIO_CLK|LTDC_B5_GPIO_CLK|
                          LTDC_B6_GPIO_CLK|LTDC_B7_GPIO_CLK|
                          //控制信号线
                          LTDC_CLK_GPIO_CLK | LTDC_HSYNC_GPIO_CLK |LTDC_VSYNC_GPIO_CLK|
                          LTDC_DE_GPIO_CLK  | LTDC_BL_GPIO_CLK    |LTDC_DISP_GPIO_CLK ,ENABLE);

/* GPIO配置 */

 /* 红色数据线 */
  GPIO_InitStruct.GPIO_Pin = LTDC_R0_GPIO_PIN;                             
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  
  GPIO_Init(LTDC_R0_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_R0_GPIO_PORT, LTDC_R0_PINSOURCE, LTDC_R0_AF);

  GPIO_InitStruct.GPIO_Pin = LTDC_R1_GPIO_PIN;
  GPIO_Init(LTDC_R1_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_R1_GPIO_PORT, LTDC_R1_PINSOURCE, LTDC_R1_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_R2_GPIO_PIN;
  GPIO_Init(LTDC_R2_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_R2_GPIO_PORT, LTDC_R2_PINSOURCE, LTDC_R2_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_R3_GPIO_PIN;
  GPIO_Init(LTDC_R3_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_R3_GPIO_PORT, LTDC_R3_PINSOURCE, LTDC_R3_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_R4_GPIO_PIN;
  GPIO_Init(LTDC_R4_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_R4_GPIO_PORT, LTDC_R4_PINSOURCE, LTDC_R4_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_R5_GPIO_PIN;
  GPIO_Init(LTDC_R5_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_R5_GPIO_PORT, LTDC_R5_PINSOURCE, LTDC_R5_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_R6_GPIO_PIN;
  GPIO_Init(LTDC_R6_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_R6_GPIO_PORT, LTDC_R6_PINSOURCE, LTDC_R6_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_R7_GPIO_PIN;
  GPIO_Init(LTDC_R7_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_R7_GPIO_PORT, LTDC_R7_PINSOURCE, LTDC_R7_AF);
  
  //绿色数据线
  GPIO_InitStruct.GPIO_Pin = LTDC_G0_GPIO_PIN;
  GPIO_Init(LTDC_G0_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_G0_GPIO_PORT, LTDC_G0_PINSOURCE, LTDC_G0_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_G1_GPIO_PIN;
  GPIO_Init(LTDC_G1_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_G1_GPIO_PORT, LTDC_G1_PINSOURCE, LTDC_G1_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_G2_GPIO_PIN;
  GPIO_Init(LTDC_G2_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_G2_GPIO_PORT, LTDC_G2_PINSOURCE, LTDC_G2_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_G3_GPIO_PIN;
  GPIO_Init(LTDC_G3_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_G3_GPIO_PORT, LTDC_G3_PINSOURCE, LTDC_G3_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_G4_GPIO_PIN;
  GPIO_Init(LTDC_G4_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_G4_GPIO_PORT, LTDC_G4_PINSOURCE, LTDC_G4_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_G5_GPIO_PIN;
  GPIO_Init(LTDC_G5_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_G5_GPIO_PORT, LTDC_G5_PINSOURCE, LTDC_G5_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_G6_GPIO_PIN;
  GPIO_Init(LTDC_G6_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_G6_GPIO_PORT, LTDC_G6_PINSOURCE, LTDC_G6_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_G7_GPIO_PIN;
  GPIO_Init(LTDC_G7_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_G7_GPIO_PORT, LTDC_G7_PINSOURCE, LTDC_G7_AF);
  
  //蓝色数据线
  GPIO_InitStruct.GPIO_Pin = LTDC_B0_GPIO_PIN;
  GPIO_Init(LTDC_B0_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_B0_GPIO_PORT, LTDC_B0_PINSOURCE, LTDC_B0_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_B1_GPIO_PIN;
  GPIO_Init(LTDC_B1_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_B1_GPIO_PORT, LTDC_B1_PINSOURCE, LTDC_B1_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_B2_GPIO_PIN;
  GPIO_Init(LTDC_B2_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_B2_GPIO_PORT, LTDC_B2_PINSOURCE, LTDC_B2_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_B3_GPIO_PIN;
  GPIO_Init(LTDC_B3_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_B3_GPIO_PORT, LTDC_B3_PINSOURCE, LTDC_B3_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_B4_GPIO_PIN;
  GPIO_Init(LTDC_B4_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_B4_GPIO_PORT, LTDC_B4_PINSOURCE, LTDC_B4_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_B5_GPIO_PIN;
  GPIO_Init(LTDC_B5_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_B5_GPIO_PORT, LTDC_B5_PINSOURCE, LTDC_B5_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_B6_GPIO_PIN;
  GPIO_Init(LTDC_B6_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_B6_GPIO_PORT, LTDC_B6_PINSOURCE, LTDC_B6_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_B7_GPIO_PIN;
  GPIO_Init(LTDC_B7_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_B7_GPIO_PORT, LTDC_B7_PINSOURCE, LTDC_B7_AF);
  
  //控制信号线
  GPIO_InitStruct.GPIO_Pin = LTDC_CLK_GPIO_PIN;
  GPIO_Init(LTDC_CLK_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_CLK_GPIO_PORT, LTDC_CLK_PINSOURCE, LTDC_CLK_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_HSYNC_GPIO_PIN;
  GPIO_Init(LTDC_HSYNC_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_HSYNC_GPIO_PORT, LTDC_HSYNC_PINSOURCE, LTDC_HSYNC_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_VSYNC_GPIO_PIN;
  GPIO_Init(LTDC_VSYNC_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_VSYNC_GPIO_PORT, LTDC_VSYNC_PINSOURCE, LTDC_VSYNC_AF);
  
  GPIO_InitStruct.GPIO_Pin = LTDC_DE_GPIO_PIN;
  GPIO_Init(LTDC_DE_GPIO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(LTDC_DE_GPIO_PORT, LTDC_DE_PINSOURCE, LTDC_DE_AF);
  
  //BL DISP
  GPIO_InitStruct.GPIO_Pin = LTDC_DISP_GPIO_PIN;                             
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  
  GPIO_Init(LTDC_DISP_GPIO_PORT, &GPIO_InitStruct);
  
  
  GPIO_InitStruct.GPIO_Pin = LTDC_BL_GPIO_PIN; 
  GPIO_Init(LTDC_BL_GPIO_PORT, &GPIO_InitStruct);
  
  //拉高使能lcd
  GPIO_SetBits(LTDC_DISP_GPIO_PORT,LTDC_DISP_GPIO_PIN);
  GPIO_SetBits(LTDC_BL_GPIO_PORT,LTDC_BL_GPIO_PIN);


}


void LCDConfig(void)
{
	LCD_Init();
	LCD_LayerInit();
	LTDC_Cmd(ENABLE);
}

#else	

#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
