/**
  ******************************************************************************
  * @file    aux_data.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   用于从SD卡烧录FLASH出厂数据
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F429 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */  


#include "aux_data.h"



/***************************************************************************************************************/
/*
【 ！】外部Flash使用情况说明（W25Q128）	

本程序正常运行后，会给FLASH芯片刷成如下内容。
//Tab = 4个空格

|-------------------------------------------------------------------------------------------------------------------|												
|序号	|文件名/工程					|功能										|起始地址		|长度				|
|-------|---------------------------|-------------------------------------------|---------------|-------------------|
|1		|外部flash读写例程			|预留给裸机Flash测试							|0				|4096 (BYTE)		|
|-------|---------------------------|-------------------------------------------|---------------|-------------------|
|2		|预留						|预留										|1*4096			|59*4096 (BYTE)		|
|-------|---------------------------|-------------------------------------------|---------------|-------------------|
|3		|app.c						|XBF字库文件（emWin使用,新宋体25.xbf）		|60*4096		|649*4096(1.23MB)	|
|-------|---------------------------|-------------------------------------------|---------------|-------------------|
|4		|app.c						|XBF字库文件(emWin使用,新宋体19.xbf)			|710*4096		|529*4096(172KB)	|
|-------|---------------------------|-------------------------------------------|---------------|-------------------|
|4		|firecc936.c				|文件系统中文支持字库(emWin使用,UNIGBK.BIN)	|1240*4096		|43*4096(172KB)		|
|-------|---------------------------|-------------------------------------------|---------------|-------------------|
|5		|EMW1062模块				|WIFI模块固件(BCM43362-5.90.230.12.bin)		|1284*4096		|62*4096(248KB)		|
|5.1	|EMW1062模块				|WIFI模块参数1(预留，不需要写文件)		    |1347*4096		|1*4096(4KB)		|
|5.2	|EMW1062模块				|WIFI模块参数2(预留，不需要写文件)		    |1348*4096		|1*4096(4KB)		|
|-------|---------------------------|-------------------------------------------|---------------|-------------------|
|6		|裸机中文显示例程			|裸机中文字库（GB2312_H2424.FON）			|1360*4096		|144*4096(576KB)	|
|-------|---------------------------|-------------------------------------------|---------------|-------------------|
|7		|diskio.c					|FATFS文件系统（emWin使用）					|1536*4096		|2560*4096(10MB)	|
|-------------------------------------------------------------------------------------------------------------------|
*/
/*******************************************************************************************************************/




//SD卡源数据路径！！
char src_dir[255]="0:/srcdata";

//要拷贝到的FLASH路径
char dst_dir[255]= FLASH_ROOT;

char flash_scan_dir[255]= FLASH_ROOT;
char sd_scan_dir[255]= SD_ROOT;


static int copy_dir(char *src_path,char *dst_path);
static int copy_file(char *src_path,char *dst_path);
static FRESULT scan_files (char* path) ; 
static FRESULT copy_all (char* src_path,char* dst_path); 


/*flash及sd卡的文件系统句柄*/
FATFS flash_fs;
FATFS sd_fs;													/* Work area (file system object) for logical drives */
 
/**
  * @brief  复制文件(若目录下有文件夹，会递归复制)
  * @param  src_path:要复制的文件(或文件夹)
  * @param  dst_path:要复制到哪个文件夹
  * @retval result:文件系统的返回值
  */
FRESULT copy_file_sd2flash(char *src_path,char *dst_path) 
{
  FRESULT result; 

  printf("-------------------------------------"); 
  //复制文件到flash的文件系统区域    
  printf("即将拷贝文件到FLASH的文件系统区域...");

  //挂载flash
  result = f_mount(&flash_fs,FLASH_ROOT,1);
  
  printf("正在格式化FLASH..."); 

  //格式化FLASH
  result = f_mkfs(FLASH_ROOT,0,0);							

  //重新挂载flash
  result = f_mount(NULL,FLASH_ROOT,1);
  result = f_mount(&flash_fs,FLASH_ROOT,1);
  
  printf("*****************************************"); 
  printf("\r\n 即将要复制的SD卡文件： \r\n"); 
  scan_files(sd_scan_dir);
  
  printf("*****************************************"); 
  
  printf("\r\n 开始复制： \r\n"); 
  result = copy_all(src_dir,dst_dir);   
  if(result != FR_OK)
  {
    printf("复制文件到FLASH失败，错误码：%d",result);
    //LED_RED;
    return result;
  }   

  printf("*****************************************"); 
  printf("\r\n 复制后的FLASH文件(文件系统部分)： \r\n"); 
  scan_files(flash_scan_dir);

  printf("*****************************************"); 
  printf("所有文件均已复制成功！（文件系统部分）");
  //LED_BLUE;
  
  return result;

}


/**
  * @brief  scan_files 递归扫描FatFs内的文件
  * @param  path:初始扫描路径
  * @retval result:文件系统的返回值
  */
static FRESULT scan_files (char* path)  
{ 
  FRESULT res; 		//部分在递归过程被修改的变量，不用全局变量	
  FILINFO fno; 
  DIR dir; 
  int i;            
  char *fn;        // 文件名	
	
#if _USE_LFN 
  /* 长文件名支持 */
  /* 简体中文需要2个字节保存一个“字”*/
  static char lfn[_MAX_LFN*2 + 1]; 	
  fno.lfname = lfn; 
  fno.lfsize = sizeof(lfn); 
#endif 
  //打开目录
  res = f_opendir(&dir, path); 
  if (res == FR_OK) 
	{ 
    i = strlen(path); 
    for (;;) 
		{ 
      //读取目录下的内容，再读会自动读下一个文件
      res = f_readdir(&dir, &fno); 								
      //为空时表示所有项目读取完毕，跳出
      if (res != FR_OK || fno.fname[0] == 0) break; 	
#if _USE_LFN 
      fn = *fno.lfname ? fno.lfname : fno.fname; 
#else 
      fn = fno.fname; 
#endif 
      //点表示当前目录，跳过			
      if (*fn == '.') continue; 	
      //目录，递归读取      
      if (fno.fattrib & AM_DIR)         
			{ 			
        //合成完整目录名        
        sprintf(&path[i], "/%s", fn); 
        printf("文件夹：%s",path);
        //递归遍历         
        res = scan_files(path);	
        path[i] = 0;         
        //打开失败，跳出循环        
        if (res != FR_OK) 
					break; 
      } 
			else 
			{ 
				printf("%s/%s", path, fn);								//输出文件名	
        /* 可以在这里提取特定格式的文件路径 */        
      }//else
    } //for
  } 
  return res; 
}


#define COPY_UNIT 4096

static FIL fsrc,fdst;													/* 文件对象 */
static BYTE read_buf[COPY_UNIT]={0};        /* 读缓冲区 */
static UINT real_read_num;            					  /* 文件成功读写数量 */
static UINT real_write_num;            					  /* 文件成功读写数量 */

char newfn[255];

/**
  * @brief  复制文件
  * @param  src_path:源文件路径
  * @param  dst_path:文件将要复制到的目录(不含文件名)
  * @retval result:文件系统的返回值
  */
static int copy_file(char *src_path,char *dst_path)
{
    FRESULT res = FR_OK; 	    
    char *sub_dir = NULL;  
  
    res = f_open(&fsrc,src_path,FA_READ); 
    do                                                                                                  
    {                                                                                                   
        FRESULT        localErr;                                                                       
                                                                                                        
        localErr = (FRESULT)(res);                                                                     
        if( unlikely( localErr != 0 ) )                                                                 
        {                                                                                               
            printf("error!\n");       
            goto exit;                                                                                 
        }                                                                                               
                                                                                                        
    }   while( 1==0 )  ; 
  
    //获取子文件路径
    sub_dir =  strrchr(src_path,'/'); 
    do                                                                                                  
    {                                                                                                   
        FRESULT        localErr;                                                                       
                                                                                                        
        localErr = (FRESULT)(!sub_dir);                                                                     
        if( unlikely( localErr != 0 ) )                                                                 
        {                                                                                               
            printf("error!\n");       
            goto exit;                                                                                 
        }                                                                                               
                                                                                                        
    }   while( 1==0 )  ; 
  
    //拼接成新路径
    sprintf(newfn,"%s%s",dst_path,sub_dir);
  
    printf("正在复制文件 %s ...",newfn);
    res = f_open(&fdst,newfn,FA_CREATE_ALWAYS|FA_WRITE|FA_READ);
    do                                                                                                  
    {                                                                                                   
        FRESULT        localErr;                                                                       
                                                                                                        
        localErr = (FRESULT)(res);                                                                     
        if( unlikely( localErr != 0 ) )                                                                 
        {                                                                                               
            printf("error!\n");       
            goto exit;                                                                                 
        }                                                                                               
                                                                                                        
    }   while( 1==0 )  ;   
  
    //拷贝文件
    while(res == FR_OK)
    {
      res = f_read(&fsrc,&read_buf,COPY_UNIT,&real_read_num);  
      do                                                                                                  
      {                                                                                                   
          FRESULT        localErr;                                                                       
                                                                                                          
          localErr = (FRESULT)(res);                                                                     
          if( unlikely( localErr != 0 ) )                                                                 
          {                                                                                               
              printf("error!\n");       
              goto exit;                                                                                 
          }                                                                                               
                                                                                                          
      }   while( 1==0 )  ;
      
      res = f_write(&fdst,&read_buf,real_read_num,&real_write_num);
      do                                                                                                  
      {                                                                                                   
          FRESULT        localErr;                                                                       
                                                                                                          
          localErr = (FRESULT)(res);                                                                     
          if( unlikely( localErr != 0 ) )                                                                 
          {                                                                                               
              printf("error!\n");       
              goto exit;                                                                                 
          }                                                                                               
                                                                                                          
      }   while( 1==0 )  ;
      
      if(real_read_num != COPY_UNIT)
        break;
    }
    
    f_close(&fsrc);
    f_close(&fdst);
    
    //printf("复制成功！");

exit:
    return res;
}


/**
  * @brief  创建文件夹
  * @param  src_path:源文件夹路径
  * @param  dst_path:要在哪里创建该文件夹
  * @retval result:文件系统的返回值
  */
static int copy_dir(char *src_path,char *dst_path)
{
    FRESULT res; 	    
    char *sub_dir = NULL;
    
    //获取子文件夹路径
    sub_dir =  strrchr(src_path,'/'); 
    do                                                                                                  
    {                                                                                                   
        FRESULT        localErr;                                                                       
                                                                                                        
        localErr = (FRESULT)(!sub_dir);                                                                     
        if( unlikely( localErr != 0 ) )                                                                 
        {                                                                                               
            printf("error!\n");       
            goto exit;                                                                                 
        }                                                                                               
                                                                                                        
    }   while( 1==0 )  ;    
    
    printf("将要创建的路径：%s",dst_path);
  
    //创建路径
    res = f_mkdir(dst_path); 
  
    //文件夹本来就存在,正常
    if(res == FR_EXIST)
      res = FR_OK;
  
    //检查
    do                                                                                                  
    {                                                                                                   
        FRESULT        localErr;                                                                       
                                                                                                        
        localErr = (FRESULT)(res);                                                                     
        if( unlikely( localErr != 0 ) )                                                                 
        {                                                                                               
            printf("error!\n");       
            goto exit;                                                                                 
        }                                                                                               
                                                                                                        
    }   while( 1==0 )  ;  

exit:
    return res;
}


//用于缓存源文件的名字
static char fntemp[_MAX_LFN*2 + 1];

/**
  * @brief  复制文件(若目录下有文件夹，会递归复制)
  * @param  src_path:要复制的文件(或文件夹)
  * @param  dst_path:要复制到哪个文件夹
  * @retval result:文件系统的返回值
  */
static FRESULT copy_all (char* src_path,char* dst_path)  
{ 
  FRESULT res; 		//部分在递归过程被修改的变量，不用全局变量	
  FILINFO fno; 
  DIR dir; 
  int i,j;            
  char *fn;        // 文件名	
	
#if _USE_LFN 
  /* 长文件名支持 */
  /* 简体中文需要2个字节保存一个“字”*/
  static char lfn[_MAX_LFN*2 + 1]; 	
  fno.lfname = lfn; 
  fno.lfsize = sizeof(lfn); 
#endif 
   
  //打开目录
  res = f_opendir(&dir, src_path); 
  if (res == FR_OK) 
	{ 
    i = strlen(src_path);//源文件路径
    j = strlen(dst_path);//目标路径
    for (;;) 
		{ 
      //读取目录下的内容，再读会自动读下一个文件
      res = f_readdir(&dir, &fno); 								
      //为空时表示所有项目读取完毕，跳出
      if (res != FR_OK || fno.fname[0] == 0) break; 	
#if _USE_LFN 
      fn = *fno.lfname ? fno.lfname : fno.fname; 
#else 
      fn = fno.fname; 
#endif 
      //点表示当前目录，跳过			
      if (*fn == '.') continue; 	
      //目录，递归读取      
      if (fno.fattrib & AM_DIR)         
			{ 			
        //合成完整目录名        
        sprintf(&src_path[i], "/%s", fn); 
        printf("src dir=%s",src_path);
        
        sprintf(&dst_path[j], "/%s", fn);
        printf("dst dir=%s",dst_path);        
        copy_dir(src_path,dst_path);

        //递归遍历         
        res = copy_all(src_path,dst_path);	
        src_path[i] = 0;   
        dst_path[j] = 0;           
        //打开失败，跳出循环        
        if (res != FR_OK) 
					break; 
      } 
			else 
			{ 
				printf("%s/%s", src_path, fn);								//输出文件名	
        sprintf(fntemp,"%s/%s",src_path,fn);
        printf("%s",fntemp);
        printf("dst_path = %s",dst_path);
        /* 可以在这里提取特定格式的文件路径 */        
        copy_file(fntemp,dst_path);
      }//else
    } //for
  } 
  return res; 
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



