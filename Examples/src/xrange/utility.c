#include "utility.h"


// System tick (1ms)
volatile uint32_t TickCounter = 0;

void Delay ( uint32_t delay )
{
    // Wait delay ms
    uint32_t startTick = TickCounter;
    while( ( TickCounter - startTick ) < delay );
}

void LongDelay ( uint8_t delay )
{
    uint32_t longDelay;
    uint32_t startTick;

    longDelay = delay * 1000;

    // Wait delay s
    startTick = TickCounter;
    while( ( TickCounter - startTick ) < longDelay );
}

