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
#include "board.h"

/*!
 * IO Extander pins objects
 */
Gpio_t Led1;
Gpio_t Led2;


/*
 * MCU objects
 */
Gpio_t GpsTx;


/*!
 * Initializes the unused GPIO to a know status
 */


/*!
 * Flag to indicate if the MCU is Initialized
 */
static bool McuInitialized = false;

void BoardInitPeriph( void )
{
    /* Init the GPIO extender pins */
    GpioInit( &Led1, LED_1, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );
    GpioInit( &Led2, LED_2, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );
    // Switch LED 1, 2,  OFF
    GpioWrite( &Led1, 1 );
    GpioWrite( &Led2, 1 );
}

void BoardInitMcu( void )
{
    if( McuInitialized == false )
    {
        // We use IRQ priority group 4 for the entire project
        // When setting the IRQ, only the preemption priority is used
        NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

        // Disable Systick
        SysTick->CTRL  &= ~SysTick_CTRL_TICKINT_Msk;    // Systick IRQ off 
        SCB->ICSR |= SCB_ICSR_PENDSTCLR_Msk;            // Clear SysTick Exception pending flag


        SpiInit( &SX1272.Spi, RADIO_MOSI, RADIO_MISO, RADIO_SCLK, NC );
        SX1272IoInit( );



#ifdef LOW_POWER_MODE_ENABLE
        RtcInit( );
#else
        TimerHwInit( );
#endif
        McuInitialized = true;
    }
}

void BoardDeInitMcu( void )
{
    Gpio_t oscHseIn;
    Gpio_t oscHseOut;  
    Gpio_t oscLseIn;
    Gpio_t oscLseOut;


    SpiDeInit( &SX1272.Spi );
    SX1272IoDeInit( );


    GpioInit( &oscHseIn, OSC_HSE_IN, PIN_ANALOGIC, PIN_PUSH_PULL, PIN_NO_PULL, 1 );
    GpioInit( &oscHseOut, OSC_HSE_OUT, PIN_ANALOGIC, PIN_PUSH_PULL, PIN_NO_PULL, 1 );

    GpioInit( &oscLseIn, OSC_LSE_IN, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_DOWN, 1 );
    GpioInit( &oscLseOut, OSC_LSE_OUT, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_DOWN, 1 );
    
    McuInitialized = false;
}

void BoardGetUniqueId( uint8_t *id )
{
    id[0] = ( ( *( uint32_t* )ID1 )+ ( *( uint32_t* )ID3 ) ) >> 24;
    id[1] = ( ( *( uint32_t* )ID1 )+ ( *( uint32_t* )ID3 ) ) >> 16;
    id[2] = ( ( *( uint32_t* )ID1 )+ ( *( uint32_t* )ID3 ) ) >> 8;
    id[3] = ( ( *( uint32_t* )ID1 )+ ( *( uint32_t* )ID3 ) );
    id[4] = ( ( *( uint32_t* )ID2 ) ) >> 24;
    id[5] = ( ( *( uint32_t* )ID2 ) ) >> 16;
    id[6] = ( ( *( uint32_t* )ID2 ) ) >> 8;
    id[7] = ( ( *( uint32_t* )ID2 ) );
}


