/*
 * buzzer.c
 *
 *  Created on: Nov 2, 2023
 *      Author: omars
 */

/*********************************************************************
 *                          Includes                                 *
 **********************************************************************/
#include "buzzer.h"
#include "gpio.h"

/*********************************************************************
 *                          Functions Definition                      *
 **********************************************************************/
/*
 * Description:
 * Setup the direction for the buzzer pin as output pin.
 * Turn off the buzzer through the GPIO.
 */
 void Buzzer_init(void){
	 GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
	 GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,BUZZER_OFF);
 }

 /*
  * Description:
  * Enable the Buzzer through the GPIO
  */
 void Buzzer_on(void){
	 GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,BUZZER_ON);

 }
 /*
  * Description:
  * Disable the Buzzer through the GPIO
  */
 void Buzzer_off(void){
	 GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,BUZZER_OFF);

 }


