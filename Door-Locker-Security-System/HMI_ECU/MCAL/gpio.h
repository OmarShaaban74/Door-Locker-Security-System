/*
 * gpio.h
 *
 *  Created on: Sep 29, 2023
 *      Author: omars
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "Standerd_Types_OS.h"

/*********************Types Declaration***********************/

/*PIN state*/
typedef enum{
 PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

/*PORT state*/
typedef enum{
	PORT_Input,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

/************************Definitions************************/

#define PORTA_ID 0
#define PORTB_ID 1
#define PORTC_ID 2
#define PORTD_ID 3

#define PIN0_ID 0
#define PIN1_ID 1
#define PIN2_ID 2
#define PIN3_ID 3
#define PIN4_ID 4
#define PIN5_ID 5
#define PIN6_ID 6
#define PIN7_ID 7

#define NUM_OF_PORTS 4
#define NUM_OF_PINS_PER_PORT 8

/****************************** PUBLIC FUNCTIONS PROTOTYPES******************************/

/*Description:
 * Function setup the pin direction input or output
 * if the pin or the port are not correct the function will not handle the request
 * */
void GPIO_setupPinDirection (uint8 port_num,uint8 pin_num,GPIO_PinDirectionType direction);

/*Description:
 * Function write on the pin HIGH or LOW
 * if the pin or the port are not correct the function will not handle the request
 * if the pin is input, this function will enable/disable the internal pull-up resistor.
 * */
void GPIO_writePin(uint8 port_num,uint8 pin_num,uint8 value);

/*Description:
 * Function read the pin and check if it is HIGH or LOW
 * if the pin or the port are not correct the function will return zero
 * */
uint8 GPIO_readPin(uint8 port_num,uint8 pin_num);

/*Description:
 * Function setup the port direction input or output
 * if the port is not correct the function will not handle the request
 * */
void GPIO_setupPortDirection(uint8 port_num,GPIO_PortDirectionType direction);

/*
 * Description:
 * write on all pins in the port HIGH or Low
 * if the port_ID is not correct the function will not handle the request
 * if any pin is INPUT pin the function will enable/disable the internal pull-up resistor of this pin
 * */
void GPIO_writePort(uint8 port_num,uint8 value);

/*
 * Description:
 * read the data of all pins of the port
 * if the port is not correct the function  will return zero
 * */
uint8 GPIO_readPort(uint8 port_num);

#endif /* GPIO_H_ */
