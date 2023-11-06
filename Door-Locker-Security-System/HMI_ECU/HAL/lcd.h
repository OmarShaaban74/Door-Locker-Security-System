/*
 * lcd.h
 *
 *  Created on: Sep 30, 2023
 *      Author: omars
 */

#ifndef LCD_H_
#define LCD_H_

#include "Standerd_Types_OS.h"

/********************************************Definitions*********************************/
#define LCD_DATA_BITS_MODE 8


#define RS_PORT_ID PORTA_ID
#define RS_PIN_ID PIN1_ID

#define E_PORT_ID PORTA_ID
#define E_PIN_ID PIN2_ID

#define DATA_PORT_ID PORTC_ID

#if(LCD_DATA_BITS_MODE==4)
#define FIRST_DATA_PIN PIN3_ID
#define SECONED_DATA_PIN PIN4_ID
#define THIRD_DATA_PIN PIN5_ID
#define FOURTH_DATA_PIN PIN6_ID

#endif
/********************************************Commands Definition*********************************/

#define CLEAR_DISP 0x01
#define RET_HOME 0x02
#define SHIFT_CURSOR_LEFT 0x04
#define SHIFT_CURSOR_RIGHT 0x06
#define SHIFT_DISP_LEFT 0x07
#define SHIFT_DISP_RIGHT 0x05
#define DISPLAYOFF_CURSOROFF 0x08
#define DISPLAYOFF_CURSORON 0x0A
#define DISPLAYON_CURSOROFF 0x0C
#define DISPLAYON_CURSORON 0x0E
#define CUSROR_BLINKING 0x0F
#define SHIFT_CURSOR_POS_LEFT 0x10
#define SHIFT_CURSOR_POS_RIGHT 0x14
#define SHIFT_ENTIRE_DISP_LEFT 0x18
#define SHIFT_ENTIRE_DISP_RIGHT 0x1C
#define FORCE_FIRST 0x80
#define FORCE_SECONED 0xC0
#define FUNC_8BIT_2LINE 0x38
#define FUNC_8BIT_1LINE 0x30
#define FUNC_4BIT_2LINE 0x28
#define FUNC_4BIT_1LINE 0x20
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32

/**************************************Functions Prototype**************************************/

/*
 * Description:
 * Send command to LCD
 * */
void LCD_sendCommand (uint8 command);

/*
 * Description:
 * Display Character on LCD
 * */
void LCD_displayCharacter(uint8 data);

/*
 * Description:
 * LCD initializations
 * */
void LCD_init(void);

/*
 * Description:
 * Display String on LCD
 * */
void LCD_displayString(uint8 * str);

/*
 * Description:
 * Move cursor to any where on LCD
 * */
void LCD_moveCursor(uint8 row ,uint8 col);

/*
 * Description:
 * Display String at any where on LCD
 * */
void LCD_displayStringRowColumn(uint8 row,uint8 col,uint8 *str);

/*
 * Description:
 * Clear screen and return home
 * */
void LCD_clearScreen(void);

/*
 * Description:
 * Display integer on LCD
 * */
void LCD_intgerToString(int data);
#endif /* LCD_H_ */
