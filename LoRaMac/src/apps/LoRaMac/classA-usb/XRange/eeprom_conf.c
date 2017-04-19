#include "eeprom_conf.h"
#include "board.h"
#include "stm32l1xx_hal_flash.h"

void EEROM_test()
{
	HAL_StatusTypeDef status;
	uint32_t Byte0Addr,Byte1Addr;

	HAL_FLASHEx_DATAEEPROM_Unlock();  //Unprotect the EEPROM to allow writing

	Byte0Addr = 0x08080000;
	Byte1Addr = 0x08080001;

//	HAL_FLASHEx_DATAEEPROM_Erase(TYPEPROGRAMDATA_BYTE,Byte0Addr);
//	HAL_FLASHEx_DATAEEPROM_Erase(TYPEPROGRAMDATA_BYTE,Byte1Addr);
	
 // Set the first byte to 99
 status = HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_BYTE, Byte0Addr, (uint32_t) 0xCC);
 if (status != HAL_OK) {
  //Error;
 }
 // Print values after setting byte 0

 status = HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_BYTE, Byte1Addr, (uint32_t) 0xDD);
 if (status != HAL_OK) {
  //Error_Handler();
 }
 // Print values after setting byte 1

 HAL_FLASHEx_DATAEEPROM_Lock();  //Unprotect the EEPROM to allow writing

}

bool eeprom_write(uint32_t address, uint8_t *data,uint8_t size)
{
	HAL_StatusTypeDef status;
	HAL_FLASHEx_DATAEEPROM_Unlock();  //Unprotect the EEPROM to allow writing

	for(int i = 0 ; i < size ; i++)
	{
		
		status = HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_BYTE, address+i , data[i]);
	
		if (status != HAL_OK)
		{
			HAL_FLASHEx_DATAEEPROM_Lock();
			return false;
		}
	}
	
	HAL_FLASHEx_DATAEEPROM_Lock();
	return true;
}

void eeprom_read(uint32_t address, uint8_t *data,uint8_t size)
{
	for(int i = 0 ; i < size ; i++)
	{
		data[i] = *((uint8_t*)address +i);
	}
}

uint8_t* get_eeprom_value(uint32_t address )
{
	return (uint8_t*)address ;	
}


uint8_t GetActivationMethod()
{
	
//	uint8_t data;
//	eeprom_read(ACTIVATION_METHOD, &data,ACTIVATION_METHOD_SIZE);
//	return data;
	return  *((uint8_t*)EEPROM_ACTIVATION_METHOD);
}

uint32_t GetAddress()
{
	
//	uint8_t data;
//	eeprom_read(ACTIVATION_METHOD, &data,ACTIVATION_METHOD_SIZE);
//	return data;
	return  *((uint32_t*)EEPROM_DEV_ADDR);
}


void SetActivationMethod(uint8_t method)
{
	HAL_FLASHEx_DATAEEPROM_Unlock();  //Unprotect the EEPROM to allow writing

	HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_BYTE, EEPROM_ACTIVATION_METHOD , method);
	
	HAL_FLASHEx_DATAEEPROM_Lock();
}
