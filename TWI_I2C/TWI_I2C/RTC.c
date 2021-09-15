/*
 * RTC.c
 *
 * Created: 22/07/2021 11:35:29
 *  Author: cvc
 */ 


#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#include "I2C.h"
#include "RTC.h"

uint8_t day;

uint8_t BCD2DEC(uint8_t val){
	
	return((val/16*10) + (val%16));
}

uint8_t DEC2BCD(uint8_t val){
	
	return((val/10*16) + (val%10));
}

void RTC_Init(){
	
	I2C_Init();
	_delay_us(10);
}

uint8_t RTC_set_time_and_date(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t day, uint8_t date, uint8_t month, uint8_t year){
	
	I2C_start_wait(RTC_ADDRESS | I2C_WRITE);
	I2C_write(0x00);
	I2C_write(DEC2BCD(seconds));
	I2C_write(DEC2BCD(minutes));
	I2C_write(DEC2BCD(hours));
	I2C_write(DEC2BCD(day));
	I2C_write(DEC2BCD(date));
	I2C_write(DEC2BCD(month));
	I2C_write(DEC2BCD(year));
	I2C_stop();
	return(1);	
}

void RTC_get_time_and_date(uint8_t *seconds, uint8_t *minutes, uint8_t *hours, uint8_t *day, uint8_t *date, uint8_t *month, uint8_t *year){
	
	I2C_start_wait(RTC_ADDRESS | I2C_WRITE);
	I2C_write(0x00);
	I2C_stop();
	
	I2C_rep_start(RTC_ADDRESS | I2C_READ);
	*seconds = BCD2DEC(I2C_read_ack());
	*minutes = BCD2DEC(I2C_read_ack());
	*hours = BCD2DEC(I2C_read_ack());	
	*day = BCD2DEC(I2C_read_ack());
	*date = BCD2DEC(I2C_read_ack());
	*month = BCD2DEC(I2C_read_ack());
	*year = BCD2DEC(I2C_read_nack());
	I2C_stop();	
}

