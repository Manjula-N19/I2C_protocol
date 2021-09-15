/*
 * TWI_I2C.c
 *
 * Created: 21/07/2021 12:52:57
 *  Author: cvc
 */ 

#define F_CPU 16000000   // CPU clock frequency
#include <avr/io.h>      // avr header files
#include <stdlib.h>      // to use functions like sprintf
#include <stdio.h>
#include <util/delay.h>  

#include "USART.h"      // Serial USART header file
#include "RTC.h"		// RTC header file


int main(void)
{
    USART_Init();		// Initialise USART
	USART_Tx_string("USART\r\n");
	RTC_Init();			// Initialise RTC (Slave device)
	USART_Tx_string("RTC_Initialised\r\n");
	
	uint8_t seconds=0, minutes = 0, hours = 0, day = 0, date = 0, month =0, year = 0;
	RTC_set_time_and_date(30, 59, 11, 6, 28, 2, 20);  // set the time and date in the above format - starting from seconds to year
	USART_Tx_string("SET_timeand date");	
    char buffer[50]; // buffer for sprintf - to transmit the string data	 
	while(1)
    {
        RTC_get_time_and_date(&seconds, &minutes, &hours, &day, &date, &month, &year);	
		//USART_Tx_string("GET_timeand date");	
        sprintf(buffer, "%d:%d:%d %d %d/%d/%d", seconds, minutes, hours, day, date, month, year);
        USART_Tx_string(buffer);  // Transmit string
        USART_Tx_string("\r\n");
        _delay_ms(1000);
	 
    }
}