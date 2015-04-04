/*
 * www.netblocks.eu
 * XRange sx1272 LoRa RF module
 * Data sheet at www.netblocks.eu/xrange-sx1272-lora-datasheet/
 */


#ifndef __LED_H__
#define __LED_H__

#define LED_INV                                     0

typedef enum
{
    LED_RED = 0,
    LED_GREEN = 1,
} tLed;



#define LED_NB                           2


#if LED_INV
#define LED_ON                           Bit_RESET
#define LED_OFF                          Bit_SET
#else
#define LED_ON                           Bit_SET
#define LED_OFF                          Bit_RESET
#endif

void LedInit( tLed led );

void LedOn( tLed led );

void LedOff( tLed led );

void LedToggle( tLed led );

#endif // __LED_H__
