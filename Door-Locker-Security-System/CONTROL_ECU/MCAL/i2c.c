/*
 * i2c.c
 *
 *  Created on: Nov 1, 2023
 *      Author: omars
 */

/*********************************************************************
 *                          Includes                                 *
 **********************************************************************/
#include <avr/io.h>
#include "Common_Macros_OS.h"
#include "i2c.h"

/*********************************************************************
 *                          Functions Definition                      *
 **********************************************************************/

/*
 * Description: Function to initialize Twi
 * 1-TWEN=0 Disable twi
 * 2-TWBR=baud rate
 * 3-TWSR=0 prescaler=1
 * 4-TWAR=address in case this MC is a slave
 * 5-TWEN=1 Enable twi in the new settings
 */

void TWI_init(const TWI_ConfigType * Config_Ptr){
	TWCR&=~(1<<TWEN);
	TWBR=(Config_Ptr->bit_rate);
	TWSR=0;
	TWAR=(Config_Ptr->address);
	TWCR|=(1<<TWEN);
}

/*
 * Description:
 * Function to send start bit
 */
void TWI_start(void){
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(GET_BIT(TWCR,TWINT)==0); /*Wait until the bit to be sent*/
}

/*
 * Description:
 * Function to send stop bit
 */
void TWI_stop(void){
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);

}

/*
 * Description:
 * Function to send byte
 */
void TWI_writeByte(uint8 data){
	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(GET_BIT(TWCR,TWINT)==0); /*Wait until the data to be sent*/
}

/*
 * Description:
 * Function to read byte with sending Acknowledgment
 */
uint8 TWI_readByteWithACK(void){
	 TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while(GET_BIT(TWCR,TWINT)==0); /*Wait until the data to be received*/
	return TWDR;
}
/*
 * Description:
 * Function to read byte without sending Acknowledgment
 */
uint8 TWI_readByteWithNACK(void){
	 TWCR = (1 << TWINT) | (1 << TWEN);
	while(GET_BIT(TWCR,TWINT)==0); /*Wait until the data to be received*/
	return TWDR;
}
/*
 * Description:
 * Function get the status of the action that had happened
 */
uint8 TWI_getStatus(void){
	uint8 status;
	status=(TWSR&0xF8);
	return status;
}
