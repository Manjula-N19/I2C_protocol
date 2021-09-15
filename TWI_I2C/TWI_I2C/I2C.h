/*
 * I2C.h
 *
 * Created: 21/07/2021 18:45:57
 *  Author: cvc
 */ 

#ifndef I2C_H_
#define I2C_H_

#define SCL_CLOCK 100000
#define I2C_WRITE 0
#define I2C_READ  1

void I2C_Init(void);
void I2C_start(unsigned char address);
void I2C_start_wait(unsigned char address);
void I2C_rep_start(unsigned char address);
unsigned char I2C_write(unsigned char data);
unsigned char I2C_read_ack(void);
unsigned char I2C_read_nack(void);
void I2C_stop(void);

#endif /* I2C_H_ */