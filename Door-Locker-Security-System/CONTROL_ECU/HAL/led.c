/*
 * led.c
 *
 *  Created on: Nov 6, 2023
 *      Author: omars
 */
/*********************************************************************
 *                          Includes                                 *
 **********************************************************************/
#include "led.h"
#include "gpio.h"
#include"util/delay.h"

/*********************************************************************
 *                          Functions Definition                      *
 **********************************************************************/
/*
 * Description:
 * Setup the direction for the Red led pin as output pin.
 * Turn off the Red led through the GPIO.
 */
 void redLed_init(void){
	 GPIO_setupPinDirection(redLed_PORT_ID,redLed_PIN_ID,PIN_OUTPUT);
	 GPIO_writePin(redLed_PORT_ID,redLed_PIN_ID,LED_OFF);
 }

 /*
  * Description:
  * Enable the Red led through the GPIO
  */
 void redLed_on(void){
	 GPIO_writePin(redLed_PORT_ID,redLed_PIN_ID,LED_ON);

 }
 /*
  * Description:
  * Disable the Red led through the GPIO
  */
 void redLed_off(void){
	 GPIO_writePin(redLed_PORT_ID,redLed_PIN_ID,LED_OFF);

 }

 /*
  * Description:
  * Setup the direction for the Green led pin as output pin.
  * Turn off the Green led through the GPIO.
  */
  void greenLed_init(void){
 	 GPIO_setupPinDirection(greenLed_PORT_ID,greenLed_PIN_ID,PIN_OUTPUT);
 	 GPIO_writePin(greenLed_PORT_ID,greenLed_PIN_ID,LED_OFF);
  }

  /*
   * Description:
   * Enable the Green led through the GPIO
   */
  void greenLed_on(void){
 	 GPIO_writePin(greenLed_PORT_ID,greenLed_PIN_ID,LED_ON);

  }
  /*
   * Description:
   * Disable the Green led through the GPIO
   */
  void greenLed_off(void){
 	 GPIO_writePin(greenLed_PORT_ID,greenLed_PIN_ID,LED_OFF);

  }
/*
 * Description:
 * Toggle the two leds every 0.25s
 */
  void toggle_leds(void){
	  GPIO_writePin(redLed_PORT_ID,redLed_PIN_ID,LED_ON);
	  GPIO_writePin(greenLed_PORT_ID,greenLed_PIN_ID,LED_OFF);
	  _delay_ms(250);
	  GPIO_writePin(redLed_PORT_ID,redLed_PIN_ID,LED_OFF);
	  GPIO_writePin(greenLed_PORT_ID,greenLed_PIN_ID,LED_ON);
	   _delay_ms(250);

  }

