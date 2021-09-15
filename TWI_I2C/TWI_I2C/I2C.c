/*
 * I2C.c
 *
 * Created: 21/07/2021 13:07:31
 *  Author: cvc
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/twi.h>  // For TWI communication in AVR

#include "I2C.h"		// I2C header file

void I2C_Init(void){
	
	TWSR = 0;		//Status register set to zero
	TWBR = (uint8_t)((F_CPU/SCL_CLOCK)-16)/2;   // Calculate the TWBR value
}

void I2C_start(unsigned char address){			// this function is used for repeat start while reading data
	
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);  // enable interrupt, enable I2C and TWSTA - start I2C
	while(!(TWCR & (1<<TWINT)));   // check if TWINT = 0
	
	TWDR = address;				// write the address 0x68 - slave address
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}

void I2C_start_wait(unsigned char address){		// this function is used initially
	
	while(1){
		TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);  // enable interrupt, enable I2C and TWSTA - start I2C
		while(!(TWCR & (1<<TWINT)));   // check if TWINT = 0
		
		TWDR = address;				// write the address 0x68 - slave address
		TWCR = (1<<TWINT) | (1<<TWEN);
		while(!(TWCR & (1<<TWINT)));
		break;
	}	// wait until communication starts	
}

void I2C_rep_start(unsigned char address){    // Repeat start
	
	I2C_start(address);
}

unsigned char I2C_write(unsigned char data){		// write operation
	
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}

unsigned char I2C_read_ack(void){
	
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);  // enable interrupt, enable I2C and 
												//The TWEA bit must be written to one to enable the acknowledgment of
												//the device’s own slave address or the general call address.
	while(!(TWCR & (1<<TWINT)));   // check if TWINT = 0
	return(TWDR);
}	

unsigned char I2C_read_nack(void){
	
	TWCR = (1<<TWINT) | (1<<TWEN); // no need to check TWEA
	while(!(TWCR & (1<<TWINT)));
	return(TWDR);
}

void I2C_stop(void){
	
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);  // enable interrupt, enable I2C and 
												// Writing the TWSTO bit to one in master mode will generate a STOP condition on 
												//the 2-wire serial bus. When the STOP
												//condition is executed on the bus, the TWSTO bit is cleared automatically.
	while(TWCR & (1<<TWSTO));
}


