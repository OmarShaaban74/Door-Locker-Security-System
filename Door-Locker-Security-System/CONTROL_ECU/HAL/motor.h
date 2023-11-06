/*
 * motor.h
 *
 *  Created on: Oct 12, 2023
 *      Author: omars
 */

#ifndef MOTOR_H_
#define MOTOR_H_
/************************************Definitions************************************/
#define MOTOR_PORT_ID PORTB_ID
#define MOTOR_FIRST_PIN_ID PIN0_ID
#define MOTOR_SECONED_PIN_ID PIN1_ID

#define SPEED0 0
#define SPEED1 25
#define SPEED2 50
#define SPEED3 75
#define SPEED4 100

/************************************Types Declaration************************************/
/*Motor state*/
typedef enum{
	STOP,CW,ACW
}DcMotor_State;
/************************************Functions Prototype************************************/

/*
 * Description:
 * Setup motor's two pins as OUTPUT pins
 * Write on motor's two pins LOW ,at the beginning the motor is stop
 *
 */
void DcMotor_Init(void);

/*
 * Description:
 * Make the motor stop or rotate CW or ACW
 * Make the motor rotate at specific speed by PWM waveform
 *
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* MOTOR_H_ */
