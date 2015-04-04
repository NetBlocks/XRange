/*
 * www.netblocks.eu
 * XRange sx1272 LoRa RF module
 * Data sheet at www.netblocks.eu/xrange-sx1272-lora-datasheet/
 */

/*! 
 * \file       spi.h
 * \brief      SPI hardware driver
 *
 * \version    1.0
 * \date       Feb 12 2010
 * \author     Miguel Luis
 */
#ifndef __SPI_H__
#define __SPI_H__

void SpiInit( void );
uint8_t SpiInOut( uint8_t outData );

#endif //__SPI_H__
