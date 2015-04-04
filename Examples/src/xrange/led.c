#include "led.h"
#include "platform.h"

GPIO_TypeDef* LedPort[LED_NB] =
{
    LED1_GPIO_PORT,
    LED2_GPIO_PORT
};
const uint16_t LedPin[LED_NB] =
{
    LED1_PIN,
    LED2_PIN,

};
const uint32_t LedClk[LED_NB] =
{
    LED1_GPIO_CLK,
    LED2_GPIO_CLK,
};

void LedInit( tLed led )
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHBPeriphClockCmd( LedClk[led], ENABLE );
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

    GPIO_InitStructure.GPIO_Pin = LedPin[led];
    GPIO_Init( LedPort[led], &GPIO_InitStructure );
    GPIO_WriteBit( LedPort[led], LedPin[led], LED_OFF );
}

void LedOn( tLed led )
{
    GPIO_WriteBit( LedPort[led], LedPin[led], LED_ON );
}

void LedOff( tLed led )
{
    GPIO_WriteBit( LedPort[led], LedPin[led], LED_OFF );
}

void LedToggle( tLed led )
{
    LedPort[led]->ODR ^= LedPin[led];
}

