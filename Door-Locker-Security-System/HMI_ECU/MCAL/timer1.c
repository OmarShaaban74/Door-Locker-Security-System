/*
 * timer1.c
 *
 *  Created on: Nov 1, 2023
 *      Author: omars
 */
/*********************************************************************
 *                          Includes                                 *
 **********************************************************************/

#include "timer1.h"
#include <avr/io.h>
#include "Common_Macros_OS.h"
#include <avr/interrupt.h>

/*********************************************************************
 *                          Global Variables                          *
 **********************************************************************/

static volatile void (*g_callBackPtr)(void) = NULL_PTR;


/*********************************************************************
 *                          Functions Definition                      *
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

void Timer1_init(const Timer1_ConfigType * Config_Ptr){
	TCCR1A=(1<<FOC1A)|(GET_BIT(Config_Ptr->mode,0)<<WGM10)|(GET_BIT(Config_Ptr->mode,1)<<WGM11);
	TCCR1B=(GET_BIT(Config_Ptr->mode,2)<<WGM12)|(GET_BIT(Config_Ptr->mode,3)<<WGM13)|(Config_Ptr->prescaler);
	TCNT1=(Config_Ptr->initial_value);
	if((Config_Ptr->mode)==CTC){
		OCR1A=(Config_Ptr->compare_value);
		TIMSK|=(1<<OCIE1A);
	}
	else{
		TIMSK|=(1<<TOIE1);
	}

}

/*Description: Turn-off the timer
 * 1-CS10,CS11,CS12 = 000
 * 2-TCNT1=0 remove counting value
 * 3-Disable Interrupt
 * */
void Timer1_deInit(void){
	TCCR1B|=NO_CLOCK;
	TCNT1=0;
	TIMSK&=~(1<<OCIE1A)&~(1<<TOIE1);
}

/*Description:
 * Set call back function to work after the interrupt
 * */
void Timer1_setCallBack(void(*a_ptr)(void)){
	g_callBackPtr = a_ptr;
}
/*Interrupt Handler for normal mode*/
ISR(TIMER1_OVF_vect){

	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)();
		}
}
/*Interrupt Handler for ctc mode*/
ISR(TIMER1_COMPA_vect){
	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)();

		}
}
