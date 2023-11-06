/*
 * motor.c
 *
 *  Created on: Oct 12, 2023
 *      Author: omars
 */

#include "gpio.h" /*to setup and write on the pins*/
#include "motor.h"
#include "pwm.h" /*to use pwm function*/

/*
 * Description:
 * Setup motor's two pins as OUTPUT pins
 * Write on motor's two pins LOW ,at the beginning the motor is stop
 *
 */

void DcMotor_Init(void){
GPIO_setupPinDirection(MOTOR_PORT_ID,MOTOR_FIRST_PIN_ID,PIN_OUTPUT);
GPIO_setupPinDirection(MOTOR_PORT_ID,MOTOR_SECONED_PIN_ID,PIN_OUTPUT);
GPIO_writePin(MOTOR_PORT_ID,MOTOR_FIRST_PIN_ID,LOW);
GPIO_writePin(MOTOR_PORT_ID,MOTOR_SECONED_PIN_ID,LOW);
}

/*
 * Description:
 * Make the motor stop or rotate CW or ACW
 * Make the motor rotate at specific speed from 0 to 100 by PWM waveform
 *
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	if(state==STOP){
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_FIRST_PIN_ID,LOW);
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_SECONED_PIN_ID,LOW);

	}
	else if(state==CW){
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_FIRST_PIN_ID,HIGH);
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_SECONED_PIN_ID,LOW);

	}
	else{
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_FIRST_PIN_ID,LOW);
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_SECONED_PIN_ID,HIGH);
	}
	PWM_Timer0_Start(speed); /*To generate the required signal to rotate at the required speed*/
}

