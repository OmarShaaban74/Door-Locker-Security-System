/*
 * keypad.c
 *
 *  Created on: Oct 3, 2023
 *      Author: omars
 */

/*********************************************************************
 *                          Includes                                 *
 **********************************************************************/
#include <util/delay.h>
#include "keypad.h"
#include "gpio.h"

/*********************************************************************
 *                          Functions Definition                      *
 **********************************************************************/

#ifndef STANDERD_KEYPAD
#if(KEYPAD_COLUMNS_NUM==3)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 KEYPAD_key);
#elif (KEYPAD_COLUMNS_NUM==4)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 KEYPAD_key);
#endif
#endif


uint8 KEYPAD_getPressedKey(void){
	uint8 KEYPAD_raw_loop,KEYPAD_column_loop;
	GPIO_setupPinDirection(KEYPAD_RAW_PORT,KEYPAD_FIRST_PIN_RAW,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_RAW_PORT,KEYPAD_FIRST_PIN_RAW+1,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_RAW_PORT,KEYPAD_FIRST_PIN_RAW+2,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_RAW_PORT,KEYPAD_FIRST_PIN_RAW+3,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COLUMN_PORT,KEYPAD_FIRST_PIN_COLUMN,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COLUMN_PORT,KEYPAD_FIRST_PIN_COLUMN+1,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COLUMN_PORT,KEYPAD_FIRST_PIN_COLUMN+2,PIN_INPUT);
#if (KEYPAD_COLUMNS_NUM==4)
	GPIO_setupPinDirection(KEYPAD_COLUMN_PORT,KEYPAD_FIRST_PIN_COLUMN+3,PIN_INPUT);
#endif
while(1){
	for(KEYPAD_raw_loop=0;KEYPAD_raw_loop<KEYPAD_RAWS_NUM;KEYPAD_raw_loop++){/* loop for rows */
		/*
		 * Each time setup the direction for all keypad port as input pins,
		 * except this row will be output pin
		 */
		GPIO_setupPinDirection(KEYPAD_RAW_PORT,KEYPAD_FIRST_PIN_RAW+KEYPAD_raw_loop,PIN_OUTPUT);
		GPIO_writePin(KEYPAD_RAW_PORT,KEYPAD_FIRST_PIN_RAW+KEYPAD_raw_loop,KEYPAD_BUTTON_PRESSED);
		for(KEYPAD_column_loop=0;KEYPAD_column_loop<KEYPAD_COLUMNS_NUM;KEYPAD_column_loop++){/* loop for columns */
			/* Check if the switch is pressed in this column */
			if(GPIO_readPin(KEYPAD_COLUMN_PORT,KEYPAD_FIRST_PIN_COLUMN+KEYPAD_column_loop)==KEYPAD_BUTTON_PRESSED){
#ifdef STANDERD_KEYPAD
				return (KEYPAD_raw_loop*KEYPAD_COLUMNS_NUM)+KEYPAD_column_loop+1;
#else
#if(KEYPAD_COLUMNS_NUM==3)
				return KEYPAD_4x3_adjustKeyNumber((KEYPAD_raw_loop*KEYPAD_COLUMNS_NUM)+KEYPAD_column_loop+1);
#elif (KEYPAD_COLUMNS_NUM==4)
				return KEYPAD_4x4_adjustKeyNumber((KEYPAD_raw_loop*KEYPAD_COLUMNS_NUM)+KEYPAD_column_loop+1);
#endif
#endif
			}
		}
		GPIO_setupPinDirection(KEYPAD_RAW_PORT,KEYPAD_FIRST_PIN_RAW+KEYPAD_raw_loop,PIN_INPUT);
		_delay_ms(5);
	}
}
 return 0;
}
#ifndef STANDERD_KEYPAD
#if (KEYPAD_COLUMNS_NUM==3)
/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x3 shape
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 KEYPAD_key){
	switch(KEYPAD_key){
	case 10:
		KEYPAD_key='*';
		break;
	case 11:
		KEYPAD_key=0;
		break;
	case 12:
		KEYPAD_key='#';
		break;

	}
	return KEYPAD_key;
}
#elif(KEYPAD_COLUMNS_NUM==4)
/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 KEYPAD_key){
	switch (KEYPAD_key) {
	case 1:
		KEYPAD_key = 7;
		break;
	case 2:
		KEYPAD_key = 8;
		break;
	case 3:
		KEYPAD_key = 9;
		break;
	case 4:
		KEYPAD_key = '/';
		break;
	case 5:
		KEYPAD_key = 4;
		break;
	case 6:
		KEYPAD_key = 5;
		break;
	case 7:
		KEYPAD_key = 6;
		break;
	case 8:
		KEYPAD_key = '*';
		break;
	case 9:
		KEYPAD_key = 1;
		break;
	case 10:
		KEYPAD_key = 2;
		break;
	case 11:
		KEYPAD_key = 3;
		break;
	case 12:
		KEYPAD_key = '-';
		break;
	case 13:
		KEYPAD_key =ENTER_BUTTON;
		break;
	case 14:
		KEYPAD_key = 0;
		break;
	case 15:
		KEYPAD_key = '=';
		break;
	case 16:
		KEYPAD_key = '+';
		break;
	}
	return KEYPAD_key;
}
#endif
#endif
