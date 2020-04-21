#include "DS3231.h"
extern I2C_HandleTypeDef hi2c2;  // change your handler here accordingly
#define DS3231_I2CChanel &hi2c2

#define SLAVE_ADDRESS_DS3231 0x68 // change this according to ur setup

void Set_DateTime(uint8_t second, uint8_t minute, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year)
{
		uint8_t send_data[7];
		send_data[0]=DEC2BCD(second);
		send_data[1]=DEC2BCD(minute);
		send_data[2]=DEC2BCD(hour);
		
		send_data[3]=DEC2BCD(day);
		send_data[4]=DEC2BCD(date);
		send_data[5]=DEC2BCD(month);
		send_data[6]=DEC2BCD(year);
		HAL_I2C_Mem_Write_IT(DS3231_I2CChanel,SLAVE_ADDRESS_DS3231<<1,0,I2C_MEMADD_SIZE_8BIT,send_data,7);
}

void Get_DateTime(uint8_t * second, uint8_t * minute, uint8_t * hour, uint8_t * day, uint8_t * date, uint8_t * month, uint8_t * year)
{
	uint8_t receive_data[7];
	HAL_I2C_Mem_Read(DS3231_I2CChanel, SLAVE_ADDRESS_DS3231<<1, 0, I2C_MEMADD_SIZE_8BIT, receive_data, 7, 1000);
		
	*second=BCD2DEC(receive_data[0]);
	*minute=BCD2DEC(receive_data[1]);
	*hour=BCD2DEC(receive_data[2]);		
	*day=BCD2DEC(receive_data[3]);
	*date=BCD2DEC(receive_data[4]);
	*month=BCD2DEC(receive_data[5]);
	*year= BCD2DEC(receive_data[6]);
}
	
float Get_Temp (void)
{
	uint8_t temp[2];
	HAL_I2C_Mem_Read(DS3231_I2CChanel, SLAVE_ADDRESS_DS3231<<1, 0x11, I2C_MEMADD_SIZE_8BIT, temp, 2, 1000);
	return ((temp[0])+(temp[1]>>6)/4.0);
}

uint8_t BCD2DEC(uint8_t data)
{
	return (data>>4)*10 + (data&0x0f);
}

uint8_t DEC2BCD(uint8_t data)
{
	return (data/10)<<4|(data%10);
}
