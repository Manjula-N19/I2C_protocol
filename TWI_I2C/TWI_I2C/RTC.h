/*
 * RTC.h
 *
 * Created: 22/07/2021 11:51:34
 *  Author: cvc
 */ 


#ifndef RTC_H_
#define RTC_H_

//#define RTC_ADDRESS (0x68<<1)
#define RTC_ADDRESS 0b11010000

void RTC_Init();
uint8_t RTC_set_time_and_date(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t day, uint8_t date, uint8_t month, uint8_t year);
void RTC_get_time_and_date(uint8_t *seconds, uint8_t *minutes, uint8_t *hours, uint8_t *day, uint8_t *date, uint8_t *month, uint8_t *year);


#endif /* RTC_H_ */