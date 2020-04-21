/** 
Edit by modify: Huynhbv
**/

#include "stm32f1xx_hal.h"

void Set_DateTime(uint8_t second, uint8_t minute, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year);

float Get_Temp (void);

void Get_DateTime(uint8_t * , uint8_t * , uint8_t * , uint8_t * , uint8_t * ,uint8_t * ,uint8_t * );

uint8_t BCD2DEC(uint8_t data);

uint8_t DEC2BCD(uint8_t data);
