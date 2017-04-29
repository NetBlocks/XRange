/**
  ******************************************************************************
  * @file    debug.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-October-2011
  * @brief   This file provide functions to retarget the C library printf function
  *          to the USART.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <stdarg.h>
#include "board.h"
#include "uart-usb-board.h"
#include "usb-printf.h"
#include "tiny_vsnprintf.h"

#ifdef USE_USB_CDC
#define VCOM_BUFF_SIZE 64

static char vcom_buffer[VCOM_BUFF_SIZE];

void vcom_Send(const char *format, ...)
{
	if (UartUsbIsUsbCableConnected())
	{	
		va_list args;
		uint8_t len = 0;

		va_start(args, format);

		len = tiny_vsnprintf_like(vcom_buffer, VCOM_BUFF_SIZE, format, args);

		UartUsbPutBuffer( &UartUsb , (uint8_t*)vcom_buffer , len );


		va_end(args);
	}
}
#endif
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
