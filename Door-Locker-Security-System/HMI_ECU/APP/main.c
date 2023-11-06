/*
 * main.c
 *
 *  Created on: Nov 2, 2023
 *      Author: omars
 */

/*********************************************************************
 *
 *                             HMI ECU                                *
 *
 **********************************************************************/

/*********************************************************************
 *                          Includes                                  *
 **********************************************************************/
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "timer1.h"
#include <avr/io.h>
#include <util/delay.h>

/*********************************************************************
 *                          Global variables                         *
 **********************************************************************/

volatile uint8 g_tick = 0;

/*********************************************************************
 *                          Functions Definition                      *
 **********************************************************************/

/*
 * Description:
 * Just increment g_tick every second
 */
void timer1_callBack(void) {
	g_tick++;

}
/*
 * Description:
 * Take the password from the user and send it to CONTROL ECU via UART
 *
 */
void TakeThePassword(void){
	uint8 key,i;
	for (i = 0; i < 5; i++) {
		key = KEYPAD_getPressedKey();
		if (key >= 0 && key <= 9) {
			LCD_displayCharacter('*');
			UART_sendByte(key);

		} else {
			i--;
		}
		_delay_ms(500);
	}

	while (key != ENTER_BUTTON) {
		key = KEYPAD_getPressedKey();
		_delay_ms(500);

	}
}
/*
 * Description:
 * Display the main options and get the option from user then send it to CONTROL ECU via UART
 *
 */
void MainSystemOption(uint8 *mainInput){
	LCD_clearScreen();
	LCD_displayString("+ : Open Door");
	LCD_displayStringRowColumn(1, 0, "- : Change Pass");
	while ((*mainInput) != '+' && (*mainInput) != '-') {
		*mainInput = KEYPAD_getPressedKey();
	}
	UART_sendByte(*mainInput);

}
/*
 * Description:
 * Function to monitoring door motion
 */
void DoorMotion(Timer1_ConfigType* TIMER1_config ){
	Timer1_init(TIMER1_config);
	LCD_clearScreen();
	LCD_displayString("Door is");
	LCD_displayStringRowColumn(1, 0,"Unlocking....");
	while (g_tick != 15);
	g_tick = 0;
	LCD_clearScreen();
	LCD_displayString("Holding...");
	while (g_tick != 3);
	g_tick = 0;
	LCD_clearScreen();
	LCD_displayString("Door is");
	LCD_displayStringRowColumn(1, 0,"Locking....");
	while (g_tick != 15);
	g_tick = 0;
	LCD_clearScreen();
	Timer1_deInit();
}

/*
 * Description:
 * Function to monitoring alarm system
 */
void AlarmSystem(Timer1_ConfigType* TIMER1_config){
	LCD_clearScreen();
	Timer1_init(TIMER1_config);
	while (g_tick != 60){
		LCD_displayStringRowColumn(0, 3,"!!THIEFS!!");
		LCD_displayStringRowColumn(1, 0,"Call the Police");
		LCD_clearScreen();

	}
	g_tick = 0;
	LCD_clearScreen();
	Timer1_deInit();
}

int main(void) {
	uint8  pssMatchFlag = 0, pssCorrectFlag = 0, wrongPssCounter =0, mainFlag = 1,mainInput=0;
	SREG |= (1 << 7);
	LCD_init();
	UART_ConfigType UART_config = { eightBit, Disabled, oneBit, 9600 };
	UART_init(&UART_config);
	Timer1_ConfigType TIMER1_config = { 0, 7813, F_CPU_1024, CTC };
	Timer1_setCallBack(timer1_callBack);
	LCD_displayStringRowColumn(0, 2,"Door Locker");
	LCD_displayStringRowColumn(1, 1, "Security System");
	_delay_ms(2000);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 5, "EDGES");
	LCD_displayStringRowColumn(1, 0,"Embedded Diploma");
	_delay_ms(2000);
	while (1) {
		LCD_clearScreen();
		LCD_displayString("plz enter pass:");
		LCD_moveCursor(1,0);
		TakeThePassword();
		LCD_clearScreen();
		LCD_displayString("plz re-enter the");
		LCD_displayStringRowColumn(1, 0, "same pass: ");
		TakeThePassword();

		pssMatchFlag = UART_recieveByte();
		if(pssMatchFlag){
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 4, "Matched!");
			_delay_ms(2000);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "System has");
			LCD_displayStringRowColumn(1, 0,"password now");
			_delay_ms(2000);
		}
		else{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 3, "Un-Matched!");
			LCD_displayStringRowColumn(1, 2,"Plz try again");
			_delay_ms(2000);


		}


		while (pssMatchFlag) {

			if (mainFlag) {
				MainSystemOption(&mainInput);
				mainFlag = 0;
				wrongPssCounter = 0;
			}
			LCD_clearScreen();
			LCD_displayString("plz enter pass:");
			LCD_moveCursor(1,0);
			TakeThePassword();
			pssCorrectFlag = UART_recieveByte();

			switch (mainInput) {
			case '+':
				if (pssCorrectFlag) {
					UART_sendByte(MOVE_DOOR);
					DoorMotion(&TIMER1_config );
					pssCorrectFlag = 0;
					mainFlag = 1;
					mainInput=0;

				} else if (wrongPssCounter == 2) {
					UART_sendByte(TRIG_ALARM);
					AlarmSystem(&TIMER1_config);
					mainFlag = 1;
					mainInput=0;

				} else {
					wrongPssCounter++;
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "Wrong Password!");
					_delay_ms(2000);
				}
				break;
			case '-':
				if (pssCorrectFlag) {
					pssCorrectFlag = 0;
					pssMatchFlag = 0;
					mainFlag = 1;
					mainInput=0;
				} else if (wrongPssCounter == 2) {
					UART_sendByte(TRIG_ALARM);
					AlarmSystem(&TIMER1_config);
					mainFlag = 1;
					mainInput=0;
				} else {
					wrongPssCounter++;
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "Wrong Password!");
					_delay_ms(2000);
				}
				break;

			}
		}
	}

}



