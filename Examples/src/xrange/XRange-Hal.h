/*
 * www.netblocks.eu
 * XRange sx1272 LoRa RF module
 * Data sheet at www.netblocks.eu/xrange-sx1272-lora-datasheet/
 */

#ifndef __XRANGE_HAL_H__
#define __XRANGE_HAL_H__

#include "platform.h"
#include "xrange-hw-ver.h"

#include <stdint.h>
#include <stdbool.h>

#include "stm32l1xx.h"



/*!
 *  LED DEFINES
*/

// RED
#define LED1_PIN                                    GPIO_Pin_8
#define LED1_GPIO_PORT                              GPIOA
#define LED1_GPIO_CLK                               RCC_AHBPeriph_GPIOA
// GREEN
#define LED2_PIN                                    GPIO_Pin_7
#define LED2_GPIO_PORT                              GPIOA
#define LED2_GPIO_CLK                               RCC_AHBPeriph_GPIOA


/*!
 *  SPI DEFINES
*/

#define SPI_INTERFACE                               SPI2
#define SPI_CLK                                     RCC_APB1Periph_SPI2

#define SPI_PIN_SCK_PORT                            GPIOB
#define SPI_PIN_SCK_PORT_CLK                        RCC_AHBPeriph_GPIOB
#define SPI_PIN_SCK                                 GPIO_Pin_13
#define SPI_SCK_AF_PIN                              GPIO_PinSource13

#define SPI_PIN_MISO_PORT                           GPIOB
#define SPI_PIN_MISO_PORT_CLK                       RCC_AHBPeriph_GPIOB
#define SPI_PIN_MISO                                GPIO_Pin_14
#define SPI_MISO_AF_PIN   					        GPIO_PinSource14

#define SPI_PIN_MOSI_PORT                           GPIOB
#define SPI_PIN_MOSI_PORT_CLK                       RCC_AHBPeriph_GPIOB
#define SPI_PIN_MOSI                                GPIO_Pin_15
#define SPI_MOSI_AF_PIN   					        GPIO_PinSource15


/*!
 * SX127x definitions
 */

/*!
 * SX1272 RESET I/O definitions
 */
#define RESET_IOPORT                                GPIOB
#define RESET_PIN                                   GPIO_Pin_2

/*!
 * SX1272 SPI NSS I/O definitions
 */
#define NSS_IOPORT                                  GPIOB
#define NSS_PIN                                     GPIO_Pin_12

/*!
 * SX1272 DIO pins  I/O definitions
 */
#define DIO0_IOPORT                                 GPIOA
#define DIO0_PIN                                    GPIO_Pin_10

#define DIO1_IOPORT                                 GPIOA
#define DIO1_PIN                                    GPIO_Pin_9

#define DIO2_IOPORT                                 GPIOC
#define DIO2_PIN                                    GPIO_Pin_13

#define DIO3_IOPORT                                 GPIOB
#define DIO3_PIN                                    GPIO_Pin_0

#define DIO4_IOPORT                                 GPIOB
#define DIO4_PIN                                    GPIO_Pin_4

#define DIO5_IOPORT                                 GPIOB
#define DIO5_PIN                                    GPIO_Pin_10

//FEM_CTX_PIN
#define RXTX_IOPORT                                 GPIOB
#define RXTX_PIN                                    GPIO_Pin_11



/*!
 * Initializes board peripherals
 */
void BoardInit( void );



#endif //__XRANGE_HAL_H__

