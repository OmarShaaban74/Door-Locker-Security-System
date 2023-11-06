/*
 * led.h
 *
 *  Created on: Nov 6, 2023
 *      Author: omars
 */

#ifndef LED_H_
#define LED_H_

/*********************************************************************
 *                          Definitions                              *
 **********************************************************************/
#define redLed_PORT_ID PORTD_ID
#define redLed_PIN_ID PIN2_ID

#define greenLed_PORT_ID PORTD_ID
#define greenLed_PIN_ID PIN3_ID

#define LED_ON 1
#define LED_OFF 0

/*********************************************************************
 *                          Functions Prototype                       *
 **********************************************************************/
/*
 * Description:
 * Setup the direction for the Red led pin as output pin.
 * Turn off the Red led through the GPIO.
 */
void redLed_init(void);
/*
 * Description:
 * Enable the Red led through the GPIO
 */
void redLed_on(void);
/*
 * Description:
 * Disable the Red led through the GPIO
 */
void redLed_off(void);
/*
 * Description:
 * Setup the direction for the Green led pin as output pin.
 * Turn off the Green led through the GPIO.
 */
void greenLed_init(void);
/*
 * Description:
 * Enable the Green led through the GPIO
 */
void greenLed_on(void);
/*
 * Description:
 * Disable the Green led through the GPIO
 */
void greenLed_off(void);
/*
 * Description:
 * Toggle the two leds every 0.25s
 */
void toggle_leds(void);

#endif /* LED_H_ */
