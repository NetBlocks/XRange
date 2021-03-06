/*
 * www.netblocks.eu
 * XRange sx1272 LoRa RF module
 * Data sheet at www.netblocks.eu/xrange-sx1272-lora-datasheet/
 */

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "platform.h"
#include "led.h"
#include <stdio.h>
#include "radio/sx1272-LoRaMisc.h"

#if USE_UART
#include "uart.h"
#endif

#include "radio/radio.h"
#include "sx1272-LoRa.h"

#define BUFFER_SIZE                                 9 // Define the payload size here


static uint16_t BufferSize = BUFFER_SIZE;			// RF buffer size
static uint8_t Buffer[BUFFER_SIZE];					// RF buffer


static uint8_t EnableMaster = true; 				// Master/Slave selection
tRadioDriver *Radio = NULL;

const uint8_t PingMsg[] = "PING";
const uint8_t PongMsg[] = "PONG";

tLoRaSettings LoRaSettings =
{
    870000000,        // RFFrequency
    20,               // Power
    0,                // SignalBw [0: 125 kHz, 1: 250 kHz, 2: 500 kHz, 3: Reserved]
    12,                // SpreadingFactor [6: 64, 7: 128, 8: 256, 9: 512, 10: 1024, 11: 2048, 12: 4096  chips]
    4,                // ErrorCoding [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
    true,             // CrcOn [0: OFF, 1: ON]
    false,            // ImplicitHeaderOn [0: OFF, 1: ON]
    1,                // RxSingleOn [0: Continuous, 1 Single]
    0,                // FreqHopOn [0: OFF, 1: ON]
    4,                // HopPeriod Hops every frequency hopping period symbols
    500,              // TxPacketTimeout
    1000,              // RxPacketTimeout
    128,              // PayloadLength (used for implicit header mode)
};


void LedGreeBlink()
{
    LedOn(LED_GREEN);
    Delay(300);
    LedOff(LED_GREEN);
}


void LedBlueBlink()
{
    LedOn(LED_RED);
    Delay(300);
    LedOff(LED_RED);
}

/*
 * Manages the master operation
 */
void OnMaster( void )
{
    uint8_t i;

    switch( Radio->Process( ) )
    {
    case RF_RX_TIMEOUT:
        // Send the next PING frame
        Buffer[0] = 'P';
        Buffer[1] = 'I';
        Buffer[2] = 'N';
        Buffer[3] = 'G';
        for( i = 4; i < BufferSize; i++ )
        {
            Buffer[i] = i - 4;
        }
        Radio->SetTxPacket( Buffer, BufferSize );
        break;
    case RF_RX_DONE:
        Radio->GetRxPacket( Buffer, ( uint16_t* )&BufferSize );

        if( BufferSize > 0 )
        {
            if( strncmp( ( const char* )Buffer, ( const char* )PongMsg, 4 ) == 0 )
            {
                // Indicates on a LED that the received frame is a PONG
                LedToggle( LED_GREEN );

                // Send the next PING frame
                Buffer[0] = 'P';
                Buffer[1] = 'I';
                Buffer[2] = 'N';
                Buffer[3] = 'G';
                // We fill the buffer with numbers for the payload
                for( i = 4; i < BufferSize; i++ )
                {
                    Buffer[i] = i - 4;
                }
                Radio->SetTxPacket( Buffer, BufferSize );
            }
            else if( strncmp( ( const char* )Buffer, ( const char* )PingMsg, 4 ) == 0 )
            {
                // A master already exists then become a slave
                EnableMaster = false;
                LedOff( LED_RED );
            }
        }
        break;
    case RF_TX_DONE:
        // Indicates on a LED that we have sent a PING
        LedToggle( LED_RED );
        Radio->StartRx( );
        break;
    default:
        break;
    }
}


/*
 * Manages the slave operation
 */
void OnSlave( void )
{
    uint8_t i;

    switch( Radio->Process( ) )
    {
    case RF_RX_DONE:
        Radio->GetRxPacket( Buffer, ( uint16_t* )&BufferSize );

        if( BufferSize > 0 )
        {
            if( strncmp( ( const char* )Buffer, ( const char* )PingMsg, 4 ) == 0 )
            {
                // Indicates on a LED that the received frame is a PING
                LedToggle( LED_GREEN );

                // Send the reply to the PONG string
                Buffer[0] = 'P';
                Buffer[1] = 'O';
                Buffer[2] = 'N';
                Buffer[3] = 'G';
                // We fill the buffer with numbers for the payload
                for( i = 4; i < BufferSize; i++ )
                {
                    Buffer[i] = i - 4;
                }

                Radio->SetTxPacket( Buffer, BufferSize );
            }
        }
        break;
    case RF_TX_DONE:
        // Indicates on a LED that we have sent a PONG
        LedToggle( LED_RED );
        Radio->StartRx( );
        break;
    default:
        break;
    }
}


void OnReceive( void )
{
    switch( Radio->Process( ) )
    {
    case RF_RX_DONE:
        Radio->GetRxPacket( Buffer, ( uint16_t* )&BufferSize );

        if( BufferSize > 0 )
        {
            if( strncmp( ( const char* )Buffer, ( const char* )PingMsg, 4 ) == 0 )
            {
                LedGreeBlink();
            }
        }

        Radio->StartRx();
        break;
    default:
        break;
    }
}

/*
 * Main application entry point.
 */
int main( void )
{
    BoardInit( );

    Radio = RadioDriverInit( );

    Radio->Init( );

    Radio->StartRx( );

    while( 1 )
    {
        if( EnableMaster == true )
        {
            OnMaster( );
        }
        else
        {
            OnSlave( );
        }
    }
#ifdef __GNUC__
    return 0;
#endif
}

