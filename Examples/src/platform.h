/*
 * www.netblocks.eu
 * XRange sx1272 LoRa RF module
 * Data sheet at www.netblocks.eu/xrange-sx1272-lora-datasheet/
 */


#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifndef __GNUC__
#define inline
#endif

/*!
 * Radio choice. Please uncomment the wanted radio and comment the others
 * or add/change wanted radio definition on the compiler Defines option
 */

#define USE_SX1272_RADIO
#define PLATFORM XRANGE-SMA

#include "XRange-Hal.h"
#include "utility.h"

#endif // __PLATFORM_H__
