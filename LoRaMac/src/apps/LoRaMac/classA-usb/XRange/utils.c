#include "utils.h"

#include <stdio.h>
#include "board.h"
#include "uart-usb-board.h"
#include "usb-printf.h"

bool UsbIsCharRecived(uint8_t *ch)
{
#ifdef USE_USB_CDC
	if(UartUsbGetChar(&UartUsb,ch)==0) return true;
#endif		
	return false;
}


void UsbPutChar(char ch)
{
#ifdef USE_USB_CDC	
	if(UartUsbIsUsbCableConnected())
	{
		UartUsbPutChar(&UartUsb,ch);
	}
#endif	
}

#define CMD_LINE_BUF_SIZE 255

char cmd_line_buf[CMD_LINE_BUF_SIZE];
unsigned cmd_line_count = 0;


void ClearClmLineBuffer()
{
	cmd_line_count = 0;
}

bool USB_get_cmd_line( void )
{    
  uint8_t ch;  
	static char last_was_CR = 0;
	
 	if(UsbIsCharRecived(&ch))
    {
		if(ch == '\b')
        {
            if(cmd_line_count)
            {
                PRINTF("\b \b");
                cmd_line_count--;
            }
						return false;
        }

        if((ch == '\n') && last_was_CR)
        {
           last_was_CR = 0;
					 return false;
        }

        if((ch == '\r') || (ch == '\n') || (ch == 0x1b))
        {
            if(ch == '\r')
            {
                last_was_CR = 1;
            }

						goto finished;
        }

        if(cmd_line_count < CMD_LINE_BUF_SIZE -1 )
        {
            cmd_line_buf[cmd_line_count] = ch;
            cmd_line_count++;
						UsbPutChar(ch);
        }
    } //if

		return false;
		
		finished:
    cmd_line_buf[cmd_line_count] = 0;
		PRINTF("\r\n");
		return true;

}



static const char *allowed_char = "0123456789abcdefABCDEF";


bool check_hex_str_format(const char *str)
{
	int len = strlen(str);
  if(strspn(str,allowed_char) == len)
	{
			return true;
	}
	
	PRINTF("Bad hex string\r\n");
	
	return false;
}

bool check_str_size(const char *str,uint8_t expected_size)
{
  
	int len = strlen(str);
	if(expected_size*2 == len)
	{	
    return true;
	}
	
	PRINTF("Bad size the hex string size is %d must be %d\r\n",len , expected_size*2);
	return false;
}


bool convert_hex_to_array(uint8_t *data,int size,const char *str)
{
    char s_str[3];
    int hex = 0;
    int i=0;
    int v=0;

    int len = strlen(str);

    for(i =0,v=0 ;i < len;i+=2,v++)
    {
        if(v >= size) return false;
        s_str[0] = str[i];
        s_str[1] = str[i+1];
        s_str[2] = 0;
        hex = strtol(s_str,NULL,16);
        data[v] = hex;

    }
    return true;
}


