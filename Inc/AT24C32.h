/** 
Edit by modify: Huynhbv
**/

#include "stm32f1xx_hal.h"

void readEEPROM(uint16_t memAdres, uint8_t * receive_data);
void writeEEPROM(uint16_t memAdres, uint8_t value);
void writeEEPROMString(uint16_t memAdres, uint8_t *value);
void readEEPROMString(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint16_t len, uint8_t * retValue);