/*
 * keypad.h
 *
 *  Created on: Oct 3, 2023
 *      Author: omars
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "Standerd_Types_OS.h"

/*********************************************************************
 *                          Definitions                              *
 **********************************************************************/
#define KEYPAD_COLUMNS_NUM 4
#define KEYPAD_RAWS_NUM 4

#define KEYPAD_RAW_PORT PORTB_ID
#define KEYPAD_FIRST_PIN_RAW PIN4_ID

#define KEYPAD_COLUMN_PORT PORTD_ID
#define KEYPAD_FIRST_PIN_COLUMN PIN2_ID

#define KEYPAD_BUTTON_PRESSED LOW
#define KEYPAD_BUTTON_RELEESED HIGH

#define ENTER_BUTTON 13

/*********************************************************************
 *                          Functions Prototype                       *
 **********************************************************************/

/*
 * Description :
 * Get the Keypad pressed button
 */
uint8 KEYPAD_getPressedKey(void);


#endif /* KEYPAD_H_ */
