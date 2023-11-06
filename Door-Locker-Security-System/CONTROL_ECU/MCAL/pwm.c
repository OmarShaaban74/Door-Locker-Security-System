/*
 * pwm.c
 *
 *  Created on: Oct 12, 2023
 *      Author: omars
 */
#include "gpio.h" /*to setup pins direction*/
#include "pwm.h"
#include <avr/io.h> /*to use I/O registers*/

/*
 * Description:
 * Generate a 500Hz PWM form with specific duty cycle from 0 to 100
 *
 */

void PWM_Timer0_Start(uint8 duty_cycle){

	/*1- WGM01=1,WGM00=1 to operate at fast PWM mode
	 *2- COM01=1 to operate at non-inverting mode
	 *3- CS01=1 to operate at Fcpu/8 (prescaler)
	 *4- TCNT0=0 to reset timer counter
	 * */
	TCCR0=(1<<WGM01)|(1<<WGM00)|(1<<COM01)|(1<<CS01);
	TCNT0=0;
	OCR0= (uint8)(((uint32)(duty_cycle*MAX_COMP_VALUE))/(100));
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);
}
