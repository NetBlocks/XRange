#include <stdint.h>
#include "spi.h"
#include "led.h"
#include "XRange-Hal.h"


void BoardInit( void )
{

    /* Setup SysTick Timer for 1 us interrupts ( not too often to save power ) */
    if( SysTick_Config( SystemCoreClock / 1000 ) )
    {
        /* Capture error */
        while (1);
    }


    // Initialize SPI
    SpiInit( );

    // Initialize LED
#if 1
    LedInit( LED_RED );
    LedInit( LED_GREEN );

    LedOn( LED_RED );
    LedOn( LED_GREEN );
    Delay(500);
    LedOff( LED_RED );
    LedOff( LED_GREEN );
    Delay(500);
#endif
}

