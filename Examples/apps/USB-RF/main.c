/*
 * www.netblocks.eu
 * XRange sx1272 LoRa RF module
 * Data sheet at www.netblocks.eu/xrange-sx1272-lora-datasheet/
 */

#include "hw_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"


#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "platform.h"
#include "led.h"
#include <stdio.h>
#include "radio/sx1272-LoRaMisc.h"
#include <stdbool.h>



#if USE_UART
#include "uart.h"
#endif

#include "radio/radio.h"
#include "sx1272-LoRa.h"


#define BUFFER_SIZE                                 64 // Define the payload size here



extern __IO uint8_t Receive_Buffer[64];
extern __IO  uint32_t Receive_length ;
extern __IO  uint32_t length ;
uint8_t Send_Buffer[64];
uint32_t packet_sent=1;
uint32_t packet_receive=1;

static uint16_t BufferSize = BUFFER_SIZE;			// RF buffer size
static uint8_t Buffer[BUFFER_SIZE];					// RF buffer


tRadioDriver *Radio = NULL;

tLoRaSettings LoRaSettings =
{
    870000000,        // RFFrequency
    20,               // Power
    0,                // SignalBw [0: 125 kHz, 1: 250 kHz, 2: 500 kHz, 3: Reserved]
    7,                // SpreadingFactor [6: 64, 7: 128, 8: 256, 9: 512, 10: 1024, 11: 2048, 12: 4096  chips]
    1,                // ErrorCoding [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
    true,             // CrcOn [0: OFF, 1: ON]
    false,            // ImplicitHeaderOn [0: OFF, 1: ON]
    0,                // RxSingleOn [0: Continuous, 1 Single]
    0,                // FreqHopOn [0: OFF, 1: ON]
    4,                // HopPeriod Hops every frequency hopping period symbols
    500,              // TxPacketTimeout
    1000,              // RxPacketTimeout
    128,              // PayloadLength (used for implicit header mode)
};


void GreenLedBlink()
{
    LedOn(LED_GREEN);
    Delay(300);
    LedOff(LED_GREEN);
}


void RedLedBlink()
{
    LedOn(LED_RED);
    Delay(300);
    LedOff(LED_RED);
}


/*
 * Main application entry point.
 */



void RadioStart()
{
	bool bTX = false;
  BoardInit( );

  GreenLedBlink();
	RedLedBlink();


  Radio = RadioDriverInit();
  Radio->Init();

  Radio->StartRx( );

	while(1)
	{
	  switch(Radio->Process())
    {
    case RF_RX_DONE:
				Radio->GetRxPacket( Buffer, ( uint16_t* )&BufferSize );
				if( BufferSize > 0 )
        {
					if (bDeviceState == CONFIGURED)
					{
						if (packet_sent == 1)
						{
							CDC_Send_DATA ((unsigned char*)Buffer,BufferSize);
						}
					}
				}

				GreenLedBlink();
				Radio->StartRx( );

				break;
    case RF_TX_DONE:
				RedLedBlink();
        Radio->StartRx( );
				bTX = false;
        break;
    default:
			if (bDeviceState == CONFIGURED)
			{
				if(bTX) break;
				if (Receive_length  != 0)
				{
					Radio->SetTxPacket( (unsigned char*)Receive_Buffer,Receive_length );
					CDC_Receive_DATA();
					Receive_length = 0;
					bTX = true;
				}
			}
			break;
    }
	}
}



int main( void )
{

  Set_System();
  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();

  RadioStart();

#ifdef __GNUC__
    return 0;
#endif
}


