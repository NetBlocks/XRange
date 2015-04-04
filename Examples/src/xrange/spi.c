/*
 * THE FOLLOWING FIRMWARE IS PROVIDED: (1) "AS IS" WITH NO WARRANTY; AND
 * (2)TO ENABLE ACCESS TO CODING INFORMATION TO GUIDE AND FACILITATE CUSTOMER.
 * CONSEQUENTLY, SEMTECH SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
 * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
 * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * Copyright (C) SEMTECH S.A.
 *
 * Modification NetBlocks
 * www.netblocks.eu
 */
/*!
 * \file       spi.c
 * \brief      SPI hardware driver
 *
 * \version    1.0
 * \date       Feb 12 2010
 * \author     Miguel Luis
 */
#include <stdint.h>
#include "stm32l1xx_spi.h"
#include "spi.h"
#include "platform.h"



void SpiInit( void )
{
    SPI_InitTypeDef SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable peripheral clocks --------------------------------------------------*/
    /* Enable SPIy clock and GPIO clock for SPIy */
    RCC_AHBPeriphClockCmd( SPI_PIN_MISO_PORT_CLK | SPI_PIN_MOSI_PORT_CLK |
                           SPI_PIN_SCK_PORT_CLK, ENABLE );
    RCC_APB1PeriphClockCmd( SPI_CLK, ENABLE );

    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = SPI_PIN_SCK;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(SPI_PIN_SCK_PORT, &GPIO_InitStructure);

    /*!< Configure LM75_I2C pins: MISO */
    GPIO_InitStructure.GPIO_Pin = SPI_PIN_MISO;
    GPIO_Init(SPI_PIN_MISO_PORT, &GPIO_InitStructure);

    /*!< Configure SPI pins: MOSI */
    GPIO_InitStructure.GPIO_Pin = SPI_PIN_MOSI;
    GPIO_Init(SPI_PIN_MOSI_PORT, &GPIO_InitStructure);

    /* Connect PB.13 to SPI SCK */
    GPIO_PinAFConfig(SPI_PIN_SCK_PORT, SPI_SCK_AF_PIN, GPIO_AF_SPI2);

    /* Connect PB.14 to SPI MISO */
    GPIO_PinAFConfig(SPI_PIN_MISO_PORT, SPI_MISO_AF_PIN, GPIO_AF_SPI2);

    /* Connect PB.15 to SPI MOSI */
    GPIO_PinAFConfig(SPI_PIN_MOSI_PORT, SPI_MOSI_AF_PIN, GPIO_AF_SPI2);

    /* SPI_INTERFACE Config -------------------------------------------------------------*/
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    //SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; // 5 MHz
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; // 10 MHz
    //SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init( SPI_INTERFACE, &SPI_InitStructure );
    SPI_Cmd( SPI_INTERFACE, ENABLE );
}

uint8_t SpiInOut( uint8_t outData )
{
    /* Send SPIy data */
    SPI_I2S_SendData( SPI_INTERFACE, outData );
    while( SPI_I2S_GetFlagStatus( SPI_INTERFACE, SPI_I2S_FLAG_RXNE ) == RESET );
    return SPI_I2S_ReceiveData( SPI_INTERFACE );
}

