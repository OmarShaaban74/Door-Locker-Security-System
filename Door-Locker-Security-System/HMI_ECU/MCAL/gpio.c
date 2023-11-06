/*
 * gpio.c
 *
 *  Created on: Sep 29, 2023
 *      Author: omars
 */
#include <avr/io.h> /*to use I/O registers*/
#include "Common_Macros_OS.h" /*to use macros like SET_BIT*/
#include "gpio.h"


/*Description:
 * Function setup the pin direction input or output
 * if the pin or the port are not correct the function will not handle the request
 * */
void GPIO_setupPinDirection (uint8 port_num,uint8 pin_num,GPIO_PinDirectionType direction){
	/*check if the port_ID and the pin_ID are correct or not */
	if ((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT)) {
		/*do nothing*/
	} else {
		/*make the pin input or output*/
		switch (port_num) {
		case PORTA_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRA, pin_num);
			} else if (direction == PIN_INPUT) {
				CLEAR_BIT(DDRA, pin_num);
			}
			break;
		case PORTB_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRB, pin_num);
			} else if (direction == PIN_INPUT) {
				CLEAR_BIT(DDRB, pin_num);
			}
			break;
		case PORTC_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRC, pin_num);
			} else if (direction == PIN_INPUT) {
				CLEAR_BIT(DDRC, pin_num);
			}
			break;
		case PORTD_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRD, pin_num);
			} else if (direction == PIN_INPUT) {
				CLEAR_BIT(DDRD, pin_num);
			}
			break;
		}
	}
}

/*Description:
 * Function write on the pin HIGH or LOW
 * if the pin or the port are not correct the function will not handle the request
 * if the pin is input, this function will enable/disable the internal pull-up resistor.
 * */
void GPIO_writePin(uint8 port_num,uint8 pin_num,uint8 value){
	/*check if the port_ID and the pin_ID are correct or not */
	if ((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT)) {
		/*do nothing*/
		}
	else {
		/*write on the pin*/
		switch(port_num){
		case PORTA_ID:
			if(value==HIGH){
				SET_BIT(PORTA,pin_num);
			}
			else if(value==LOW){
				CLEAR_BIT(PORTA,pin_num);
			}
			break;
		case PORTB_ID:
			if(value==HIGH){
				SET_BIT(PORTB,pin_num);
			}
			else if(value==LOW){
				CLEAR_BIT(PORTB,pin_num);
			}
			break;
		case PORTC_ID:
			if(value==HIGH){
				SET_BIT(PORTC,pin_num);
			}
			else if(value==LOW){
				CLEAR_BIT(PORTC,pin_num);
			}
			break;
		case PORTD_ID:
			if(value==HIGH){
				SET_BIT(PORTD,pin_num);
			}
			else if(value==LOW){
				CLEAR_BIT(PORTD,pin_num);
			}
			break;
		}
	}
}
/*Description:
 * Function read the pin and check if it is HIGH or LOW
 * if the pin or the port are not correct the function will return zero
 * */

uint8 GPIO_readPin(uint8 port_num,uint8 pin_num){
	uint8 returnValue=LOW;
	/*check if the port_ID and the pin_ID are correct or not */
	if ((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT)) {
		/*do nothing*/
			}
		else {
			/*read the pin*/
		switch (port_num) {
		case PORTA_ID:
			returnValue = GET_BIT(PINA, pin_num);
			break;
		case PORTB_ID:
			returnValue = GET_BIT(PINB, pin_num);
			break;
		case PORTC_ID:
			returnValue = GET_BIT(PINC, pin_num);
			break;
		case PORTD_ID:
			returnValue = GET_BIT(PIND, pin_num);
			break;
		}

		}
	return returnValue;
}

/*Description:
 * Function setup the port direction input or output
 * if the port is not correct the function will not handle the request
 * */
void GPIO_setupPortDirection(uint8 port_num,GPIO_PortDirectionType direction){
	/*check if the port_ID is correct or not */
	if (port_num >= NUM_OF_PORTS) {
		/*do nothing*/
	}
	else{
		/*make the port input or output*/
		switch (port_num) {
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}
/*
 * Description:
 * write on all pins in the port HIGH or Low
 * if the port_ID is not correct the function will not handle the request
 * if any pin is INPUT pin the function will enable/disable the internal pull-up resistor of this pin
 * */
void GPIO_writePort(uint8 port_num,uint8 value){
	/*check if the port_ID is correct or not*/
	if (port_num >= NUM_OF_PORTS) {
		/*do nothing*/
		}
		else {
			/*write on the port*/
		switch (port_num) {
		case PORTA_ID:
			PORTA = value;
			break;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
			}
		}
}
/*
 * Description:
 * read the data of all pins of the port
 * if the port is not correct the function  will return zero
 * */
uint8 GPIO_readPort(uint8 port_num){
	uint8 returnValue=LOW;
	/*check if the port_ID is correct or not*/
	if (port_num >= NUM_OF_PORTS) {
		/*do nothing*/
			}
			else {
				/*read the port*/
		switch (port_num) {
		case PORTA_ID:
			returnValue = PINA;
			break;
		case PORTB_ID:
			returnValue = PINB;
			break;
		case PORTC_ID:
			returnValue = PINC;
			break;
		case PORTD_ID:
			returnValue = PIND;
			break;
				}
			}
	return returnValue;
}

