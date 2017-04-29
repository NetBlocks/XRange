#ifndef __EEPROM_CONF_H__
#define __EEPROM_CONF_H__

#include <stdbool.h>
#include <stdint.h>


#define EEPROM_START_ADDR 0x08080000
#define APPLICATION_KEY_SIZE 16
#define DEVICE_EUI_SIZE 8
#define APPLICATION_EUI_SIZE 8
#define NWKSKEY_SIZE 16 
#define APPSKEY_SIZE 16
#define ACTIVATION_METHOD_SIZE 1
#define DEV_ADDR_SIZE 4

#define	ACTIVATION_METHOD_OTAA  0
#define	ACTIVATION_METHOD_ABP   1

#define EEPROM_APPLICATION_KEY_ADDR (EEPROM_START_ADDR)
#define EEPROM_APPLICATION_EUI_ADDR (EEPROM_APPLICATION_KEY_ADDR + APPLICATION_KEY_SIZE)
//#define EEPROM_DEVICE_EUI_ADDR (EEPROM_APPLICATION_EUI_ADDR + APPLICATION_EUI_SIZE)
#define EEPROM_NWKSKEY (EEPROM_APPLICATION_EUI_ADDR + APPLICATION_EUI_SIZE)
#define EEPROM_APPSKEY (EEPROM_NWKSKEY + NWKSKEY_SIZE)
#define EEPROM_ACTIVATION_METHOD (EEPROM_APPSKEY + APPSKEY_SIZE )
#define EEPROM_DEV_ADDR (EEPROM_ACTIVATION_METHOD + ACTIVATION_METHOD_SIZE )

bool eeprom_write(uint32_t address, uint8_t *data,uint8_t size);
void eeprom_read(uint32_t address, uint8_t *data,uint8_t size);
uint8_t* get_eeprom_value(uint32_t address );
uint32_t GetAddress( void);

uint8_t GetActivationMethod(void);
void SetActivationMethod(uint8_t method);

#endif
