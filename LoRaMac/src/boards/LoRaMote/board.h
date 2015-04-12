/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Target board general functions implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "stm32l1xx.h"
#include "utilities.h"
#include "timer.h"
#include "delay.h"
#include "gpio.h"
//#include "adc.h"
#include "spi.h"
//#include "i2c.h"
//#include "uart.h"
#include "radio.h"
#include "sx1272/sx1272.h"
//#include "mag3110.h"
//#include "mma8451.h"
//#include "mpl3115.h"
//#include "sx9500.h"
//#include "gps.h"
//#include "gps-board.h"
#include "rtc-board.h"
#include "timer-board.h"
#include "sx1272-board.h"
//#include "uart-board.h"

#if defined( USE_USB_CDC )
#include "usb-cdc-board.h"
#endif


/*!
 * NULL definition
 */
#ifndef NULL
    #define NULL                                    ( ( void * )0 )
#endif

/*!
 * Generic definition
 */
#ifndef SUCCESS
#define SUCCESS                                     1
#endif

#ifndef FAIL
#define FAIL                                        0  
#endif

/*!
 * Battery level ratio (battery dependent)
 */
#define BATTERY_STEP_LEVEL                          0.23


/*!
 * Unique Devices IDs register set ( STM32L1xxx )
 */
#define         ID1                                 ( 0x1FF80050 )
#define         ID2                                 ( 0x1FF80054 )
#define         ID3                                 ( 0x1FF80064 )

/*!
 * Random seed generated using the MCU Unique ID
 */
#define RAND_SEED                                   ( ( *( uint32_t* )ID1 ) ^ \
                                                      ( *( uint32_t* )ID2 ) ^ \
                                                      ( *( uint32_t* )ID3 ) )

/*!
 * Board IO Extender pins definitions
 */
#define LED_1                                       PA_7 //IOE_12
#define LED_2                                       PA_8 //IOE_13
#define SPARE_IO_NC                                 IOE_15

/*!
 * Board MCU pins definitions
 */

#define RADIO_RESET                                 PB_2 //PA_2

#define RADIO_MOSI                                  PB_15 //PA_7
#define RADIO_MISO                                  PB_14  //PA_6
#define RADIO_SCLK                                  PB_13  //PA_5
#define RADIO_NSS                                   PB_12 //PB_0

#define RADIO_DIO_0                                 PA_10 //PB_1
#define RADIO_DIO_1                                 PA_9  //PB_10
#define RADIO_DIO_2                                 PC_13  //PB_11
#define RADIO_DIO_3                                 PB_0  //PB_7
#define RADIO_DIO_4                                 PB_4  //PB_5
#define RADIO_DIO_5                                 PB_10 //PB_4

#define RADIO_ANT_SWITCH_TX                         PB_11 //PA_4

#define OSC_LSE_IN                                  PC_14
#define OSC_LSE_OUT                                 PC_15

#define OSC_HSE_IN                                  PH_0
#define OSC_HSE_OUT                                 PH_1

#define USB_DM                                      PA_11
#define USB_DP                                      PA_12

#define JTAG_TMS                                    PA_13
#define JTAG_TCK                                    PA_14
#define JTAG_TDI                                    PA_15
#define JTAG_TDO                                    PB_3
#define JTAG_NRST                                   PB_4

#define I2C_SCL                                     PB_8
#define I2C_SDA                                     PB_9

#define CON_EXT_1                                   PB_13                                                                        
#define CON_EXT_3                                   PB_15                                
#define CON_EXT_7                                   PB_12   
#define CON_EXT_8                                   PB_14
#define CON_EXT_9                                   PA_1     
#define BAT_LEVEL                                   PA_3

#define BOOT_1                                      PB_2
    
#define GPS_PPS                                     PA_8
#define UART_TX                                     PA_9
#define UART_RX                                     PA_10    

#define PIN_PB6                                     PB_6    
#define WKUP1                                       PA_0 


/*!
 * LED GPIO pins objects
 */
extern Gpio_t Led1;
extern Gpio_t Led2;


/*!
 * Debug GPIO pins objects
 */
#if defined( USE_DEBUG_PINS )
extern Gpio_t DbgPin1;
extern Gpio_t DbgPin2;
extern Gpio_t DbgPin3;
extern Gpio_t DbgPin4;
#endif

/*!
 * MCU objects
 */
//extern Adc_t Adc;
//extern I2c_t I2c;
//extern Uart_t Uart1;
//#if defined( USE_USB_CDC )
//extern Uart_t UartUsb;
//#endif

//extern Gpio_t GpsPps;
//extern Gpio_t GpsRx;
extern Gpio_t GpsTx;

/*!
 * \brief Initializes the target board peripherals.
 */
void BoardInitMcu( void );

/*!
 * \brief Initializes the boards peripherals.
 */
void BoardInitPeriph( void );

/*!
 * \brief De-initializes the target board peripherals to decrease power
 *        consumption.
 */
void BoardDeInitMcu( void );

/*!
 * \brief Measure the Battery level
 *
 * \retval value  battery level ( 0: very low, 254: fully charged )
 */
uint8_t BoardMeasureBatterieLevel( void );

/*!
 * \brief Gets the board 64 bits unique ID 
 *
 * \param [IN] id Pointer to an array that will contain the Unique ID
 */
void BoardGetUniqueId( uint8_t *id );

#endif // __BOARD_H__
