#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

/*!
 * Functions return codes definition
 */
typedef enum
{
    SX_OK,
    SX_ERROR,
    SX_BUSY,
    SX_EMPTY,
    SX_DONE,
    SX_TIMEOUT,
    SX_UNSUPPORTED,
    SX_WAIT,
    SX_CLOSE,
    SX_YES,
    SX_NO,
}tReturnCodes;

extern volatile uint32_t TickCounter;

/*!
 * Delay code execution for "delay" ms
 */
void Delay ( uint32_t delay );

/*!
 * Delay code execution for "delay" s
 */
void LongDelay ( uint8_t delay );

/*!
 * \brief Computes a random number between min and max
 *
 * \param [IN] min range minimum value
 * \param [IN] max range maximum value
 * \retval random random value in range min..max
 */
uint32_t randr( uint32_t min, uint32_t max );



#endif /* UTILITY_H_INCLUDED */
