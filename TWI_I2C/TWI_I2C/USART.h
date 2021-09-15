/*
 * USART.h
 *
 * Created: 16/07/2021 11:58:23
 *  Author: cvc
 */ 


#ifndef USART_H_
#define USART_H_

void USART_Init();
char USART_Rx();
void USART_Tx(char);
void USART_Tx_string (char *);

#endif /* USART_H_ */