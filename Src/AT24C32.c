#include "AT24C32.h"
extern I2C_HandleTypeDef hi2c2;  // change your handler here accordingly
#define AT24C32_I2CChanel &hi2c2

#define SLAVE_ADDRESS_AT24C32 0x57 // change this according to ur setup
HAL_StatusTypeDef ret;

void readEEPROM(uint16_t memAdres, uint8_t * receive_data) 
{
	HAL_I2C_Mem_Read(AT24C32_I2CChanel, SLAVE_ADDRESS_AT24C32<<1, memAdres, I2C_MEMADD_SIZE_16BIT, receive_data,1,1000);	
}

void writeEEPROM(uint16_t memAdres, uint8_t value) 
{
	HAL_I2C_Mem_Write(AT24C32_I2CChanel, SLAVE_ADDRESS_AT24C32<<1, memAdres, I2C_MEMADD_SIZE_16BIT, &value, 1, 1000);	
}

void writeEEPROMString(uint16_t memAdres, uint8_t *value)
{
	int pos = 0; //char ch[] = "Selam"; 'S', 'e', 'l', 'a', 'm', '\0';
	while (*value != '\0') {
		writeEEPROM(memAdres + pos, *value++);
		pos++;
	}
}

void readEEPROMString(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint16_t len, uint8_t * retValue) 
{
	for (int i = 0; i < len; i++) 
	{
		readEEPROM(memAdres + i, retValue++);
	}
}

void eraseEEPROM()
{
	for (uint16_t i = 0; i < 4096; i += 32) {
		uint8_t val2[34] = { 0 };
		val2[0] = ((i) >> 8) & 0xFF;
		val2[1] = ((i) & 0xFF);
		ret = HAL_I2C_Master_Transmit(i2cbus, devAdres, val2, 34, 1000);
		HAL_Delay(10);
	}
	uint8_t buf2[50] = { 0 };
	if (ret != HAL_OK) {
	} else {
	}
}

//void _fillEEPROM(I2C_HandleTypeDef *i2cbus, uint8_t devAdres) {
//	uint8_t fc = 32;
//	for (uint16_t memAdres = 0; memAdres < 4096; memAdres += 32) {
//		uint8_t val2[34] = { 0 };
//		val2[0] = (memAdres >> 8) & 0xFF;
//		val2[1] = (memAdres & 0xFF);
//		for (uint8_t j = 2; j <= 33; j++) {
//			val2[j] = fc++;
//			if (fc > 127) fc = 32;
//		}
//		ret = HAL_I2C_Master_Transmit(i2cbus, devAdres, val2, 34, 1000);
//		HAL_Delay(10);
//	}
//	uint8_t buf2[50] = { 0 };
//	if (ret != HAL_OK) {
//	} else {
//	}
//}

//void _readAllEEPROM(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint16_t len, uint8_t retValue[]) {
//	uint8_t val[2] = { 0 };
//	val[0] = (memAdres >> 8) & 0xFF;
//	val[1] = (memAdres & 0xFF);
//	uint8_t buf2[50] = { 0 };
//	ret = HAL_I2C_Master_Transmit(i2cbus, devAdres, val, 2, 1000);
//	HAL_Delay(10);
//	if (ret != HAL_OK) {
//	} else {
//		ret = HAL_I2C_Master_Receive(i2cbus, devAdres, retValue, len, HAL_MAX_DELAY);
//		HAL_Delay(10);
//		if (ret != HAL_OK) {
//		} else {
//		}
//	}
//}
