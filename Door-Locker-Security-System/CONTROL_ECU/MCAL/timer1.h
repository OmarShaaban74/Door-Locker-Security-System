/*
 * timer1.h
 *
 *  Created on: Nov 1, 2023
 *      Author: omars
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include "Standerd_Types_OS.h"

/*********************************************************************
 *                          Variable Types Deceleration                *
 **********************************************************************/

/*To choose prescaler*/
typedef enum{
	NO_CLOCK,F_CPU_1,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,FALLING_CLOCK,RISING_CLOCK
}Timer1_Prescaler;

/*To choose mode*/
typedef enum{
	Normal,CTC=4
}Timer1_Mode;

/*Structure to initialize Timer1 */
typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;

/*********************************************************************
 *                          Functions Prototype                       *
 **********************************************************************/

/*
 * Description: Function to initialize Timer1
 * 1- FOC1A=1 for non-pwm mode
 * 2- WGM10,WGM11,WGM12,WGM13 to choose the mode from CTC mode or Normal mode
 * 3-CS10,CS11,CS12 to choose the prescaler
 * 4-TCNT1=initial value of counting
 * 5-OCR1A=compare value if we choose ctc mode
 * 6-Enable interrupt
 */

void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*Description: Turn-off the timer
 * 1-CS10,CS11,CS12 = 000
 * 2-TCNT1=0 remove counting value
 * 3-Disable Interrupt
 * */
void Timer1_deInit(void);

/*Description:
 * Set call back function to work after the interrupt
 * */
void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMER1_H_ */
