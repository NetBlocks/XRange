#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdbool.h>
#include <stdint.h>

//bool UsbIsCharRecived(uint8_t *ch);
//void UsbPutChar(char ch);
bool USB_get_cmd_line( void );
void ClearClmLineBuffer(void);

extern char cmd_line_buf[];
extern unsigned cmd_line_count;

void EEROM_test(void);
bool check_hex_str_format(const char *str);
bool convert_hex_to_array(uint8_t *data,int size,const char *str);
bool check_str_size(const char *str,uint8_t expected_size);

#endif
