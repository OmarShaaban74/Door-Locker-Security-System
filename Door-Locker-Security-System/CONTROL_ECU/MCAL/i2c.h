/*
 * i2c.h
 *
 *  Created on: Nov 1, 2023
 *      Author: omars
 */

#ifndef I2C_H_
#define I2C_H_

#include "Standerd_Types_OS.h"

/*********************************************************************
 *                          Definitions                              *
 **********************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

#define TWI_Address uint8
#define TWI_BaudRate uint8

/*********************************************************************
 *                          Variable Types Deceleration                *
 **********************************************************************/

/*Structure to initialize twi */
typedef struct{
 TWI_Address address; /*my address to be called*/
 TWI_BaudRate bit_rate; /*baud rate*/
}TWI_ConfigType;
/*********************************************************************
 *                          Functions Prototype                       *
 **********************************************************************/

/*
 * Description: Function to initialize Twi
 * 1-TWEN=0 Disable twi
 * 2-TWBR=baud rate
 * 3-TWSR=0 prescaler=1
 * 4-TWAR=address in case this MC is a slave
 * 5-TWEN=1 Enable twi in the new settings
 */

void TWI_init(const TWI_ConfigType * Config_Ptr);

/*
 * Description:
 * Function to send start bit
 */
void TWI_start(void);
/*
 * Description:
 * Function to send stop bit
 */
void TWI_stop(void);
/*
 * Description:
 * Function to send byte
 */
void TWI_writeByte(uint8 data);
/*
 * Description:
 * Function to read byte with sending Acknowledgment
 */
uint8 TWI_readByteWithACK(void);
/*
 * Description:
 * Function to read byte without sending Acknowledgment
 */
uint8 TWI_readByteWithNACK(void);
/*
 * Description:
 * Function get the status of the action that had happened
 */
uint8 TWI_getStatus(void);
#endif /* I2C_H_ */
