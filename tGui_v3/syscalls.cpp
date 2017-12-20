#include <stdio.h>
#include <sys/stat.h>
#include "usart/usart_conf.h"


// add printf function
extern "C"
{
	int _fstat(int fd, struct stat *pStat)
	{
		pStat->st_mode = S_IFCHR;
		return 0;
	}

	int _close(int)
	{
		return -1;
	}

	int _write(int fd, char *pBuffer, int size)
	{
		for (int i = 0; i < size; i++)
		{
			while (!(USART1->SR & USART_SR_TXE))
			{
			}
			USART_SendData(USART1, pBuffer[i]);
		}
		return size;
	}

	int _isatty(int fd)
	{
		return 1;
	}

	int _lseek(int, int, int)
	{
		return -1;
	}

	int _read(int fd, char *pBuffer, int size)
	{
		for (int i = 0; i < size; i++)
		{
			while ((USART1->SR & USART_SR_RXNE) == 0)
			{
			}

			pBuffer[i] = USART_ReceiveData(USART1);
		}
		return size;
	}

	caddr_t _sbrk(int increment)
	{
		extern char end asm("end");
		register char *pStack asm("sp");

		static char *s_pHeapEnd;

		if (!s_pHeapEnd)
			s_pHeapEnd = &end;

		if (s_pHeapEnd + increment > pStack)
			return (caddr_t)-1;

		char *pOldHeapEnd = s_pHeapEnd;
		s_pHeapEnd += increment;
		return (caddr_t)pOldHeapEnd;
	}
	//重定向c库函数printf到串口，重定向后可使用printf函数

	// int fputc(int ch, FILE *f)
	//{
	//	// 发送一个字节数据到串口 
	//	USART_SendData(USART1, (uint8_t) ch);
	//		
	//	// 等待发送完毕 
	//	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
	//		;		
	//	return (ch);
	//}
	//
	////重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
	//int fgetc(FILE *f)
	//{
	//	// 等待串口输入数据 
	//	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
	//		;
	//	return (int)USART_ReceiveData(USART1);
	//}
}