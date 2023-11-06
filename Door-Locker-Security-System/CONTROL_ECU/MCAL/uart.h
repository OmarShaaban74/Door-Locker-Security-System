/*
 * uart.h
 *
 *  Created on: Oct 17, 2023
 *      Author: omars
 */

#ifndef UART_H_
#define UART_H_
#include "Standerd_Types_OS.h"

/*********************************************************************
 *                          Definitions                              *
 **********************************************************************/

#define UART_BaudRate uint32
#define UART_F_CPU 16000000

#define PSS_MATCH 1
#define PSS_UNMATCH 0

#define MOVE_DOOR 99
#define TRIG_ALARM 150
/*********************************************************************
 *                          Variable Types Deceleration                *
 **********************************************************************/
/*To choose parity check*/
typedef enum{
	Disabled,Even=2,Odd
}UART_Parity;

/*To choose number of stop bit*/
typedef enum{
	oneBit,twoBit
}UART_StopBit;

/*To choose character size*/
typedef enum{
	fiveBit,sixBit,sevenBit,eightBit,nineBit=7
}UART_BitData;

/*Structure to initialize UART */
typedef struct{
	UART_BitData bit_data;
	UART_Parity parity;
	UART_StopBit stop_bit;
	UART_BaudRate baud_rate;
}UART_ConfigType;

/*********************************************************************
 *                          Functions Prototype                       *
 **********************************************************************/

/*Description: Function to initialize UART
 * 1-U2X=1  for double speed mode
 * 2-RXEN=1 Enable receiver ,TXEN=1 Enable transmitter
 * 3-URSEL=1 to write in UCSRC
 * 4- Select parity,stop bit,character size
 * 5-URSEL=0 to write in UBRR
 * 5-UBRR = baud rate
 */
void UART_init(const UART_ConfigType *config_Ptr);
/*
 * Description:
 * Function to receive byte
 */
uint8 UART_recieveByte(void);
/*
 * Description:
 * Function to send byte
 */
void UART_sendByte(const uint8 transmittedData);
/*
 * Description:
 * Function to send string
 */
void UART_sendString(const uint8 *str);

/*
 * Description:
 * Function to receive string
 */
void UART_recieveString(uint8 *str);


#endif /* UART_H_ */
