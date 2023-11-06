/*
 * buzzer.h
 *
 *  Created on: Nov 2, 2023
 *      Author: omars
 */

#ifndef BUZZER_H_
#define BUZZER_H_

/*********************************************************************
 *                          Definitions                              *
 **********************************************************************/
#define BUZZER_PORT_ID PORTA_ID
#define BUZZER_PIN_ID PIN0_ID

#define BUZZER_OFF 0
#define BUZZER_ON 1

/*********************************************************************
 *                          Functions Prototype                       *
 **********************************************************************/

/*
 * Description:
 * Setup the direction for the buzzer pin as output pin.
 * Turn off the buzzer through the GPIO.
 */
void Buzzer_init(void);

/*
 * Description:
 * Enable the Buzzer through the GPIO
 */
void Buzzer_on(void);

/*
 * Description:
 * Disable the Buzzer through the GPIO
 */
void Buzzer_off(void);

#endif /* BUZZER_H_ */
