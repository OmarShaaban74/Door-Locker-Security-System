/*
 * uart.c
 *
 *  Created on: Oct 17, 2023
 *      Author: omars
 */

/*********************************************************************
 *                          Includes                                 *
 **********************************************************************/
#include <avr/io.h>
#include "uart.h"
#include "Common_Macros_OS.h"

/*********************************************************************
 *                          Functions Definition                      *
 **********************************************************************/
/*Description: Function to initialize UART
 * 1-U2X=1  for double speed mode
 * 2-RXEN=1 Enable receiver ,TXEN=1 Enable transmitter
 * 3-URSEL=1 to write in UCSRC
 * 4- Select parity,stop bit,character size
 * 5-URSEL=0 to write in UBRR
 * 5-UBRR = baud rate
 */

void UART_init(const UART_ConfigType *config_Ptr ){
	uint16 ubrrValue;

	UCSRA = (1<<U2X);
	UCSRB=(1<<RXEN)|(1<<TXEN);
	UCSRC = (1 << URSEL) | ((config_Ptr->parity << 4) | (config_Ptr->stop_bit << 3));


	UCSRB= (UCSRB& 0xFB) | (GET_BIT(config_Ptr->bit_data,2)<<2);
	UCSRC= (UCSRC& 0xFD) | (GET_BIT(config_Ptr->bit_data,0)<<1);
	UCSRC= (UCSRC& 0xFB) | (GET_BIT(config_Ptr->bit_data,1)<<2);

	ubrrValue = (uint16)(((UART_F_CPU / ((config_Ptr->baud_rate) * 8))) - 1);
	UCSRC&=~(1<<URSEL);
	UBRRH = ubrrValue>>8;
	UBRRL = ubrrValue;
}
/*
 * Description:
 * Function to send byte
 */

void UART_sendByte(const uint8 transmittedData){
	while(GET_BIT(UCSRA,UDRE)==0); /*wait until data register is empty to avoid overwriting*/
	UDR=transmittedData;

}

/*
 * Description:
 * Function to receive byte
 */
uint8 UART_recieveByte(void){
	while(GET_BIT(UCSRA,RXC)==0); /*wait until the data be received*/
	return UDR;
}
/*
 * Description:
 * Function to send string
 */

void UART_sendString(const uint8 *str){
	uint8 i=0;
	while(str[i]!='\0'){
		UART_sendByte(str[i]);
		i++;
	}
}

/*
 * Description:
 * Function to receive string
 */
void UART_recieveString(uint8 *str)
{
	uint8 i = 0;

	/* Receive the first byte */
	str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(str[i] != '#')
	{
		i++;
		str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	str[i] = '\0';
}
