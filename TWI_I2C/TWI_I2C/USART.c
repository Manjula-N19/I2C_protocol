/*
 * USART.c
 *
 * Created: 16/07/2021 11:58:54
 *  Author: cvc
 */ 

#include <avr/io.h>
#include "USART.h"


/* Initialize the USART to transmit and receive the data */
void USART_Init(){
	UBRR0H = 0x01;   // 2400 baud rate --> UBRRn = 416 dec = 1A0 hex ; UBRR0H = 0x01 and UBRR0L = 0xA0
	UBRR0L = 0xA0;
	UCSR0B = (1<<TXEN0) | (1<<RXEN0);
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
}

/* Receive the character from UDR0 */
char USART_Rx(){
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

/* Transmit the character from UDR0 */
void USART_Tx(char data){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

/* Transmit the string */
void USART_Tx_string(char text[]){
	int i=0;
	while(i<255){
		if (text[i] == '\0')
		break;
		USART_Tx(text[i]);
		i++;
	}
}
