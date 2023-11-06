/*
 * main.c
 *
 *  Created on: Nov 2, 2023
 *      Author: omars
 */

/*********************************************************************
 *
 *                             Control ECU                            *
 *
 **********************************************************************/


/*********************************************************************
 *                          Includes                                  *
 **********************************************************************/
#include "buzzer.h"
#include "external_eeprom.h"
#include "motor.h"
#include "uart.h"
#include "timer1.h"
#include <avr/io.h>
#include "i2c.h"
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
 * Function to set the system password in the first time or in changing password mode
 */
void SetupSystemPassword(uint8 *pssArr1,uint8* pssArr2,uint16 *pssLoc,uint8 *pssMatchFlag){
	uint8 i;
	/*Take the password for the first time*/
	for (i = 0; i < 5; i++) {
		pssArr1[i] = UART_recieveByte();
	}
	/*Take the password for the second time*/
	for (i = 0; i < 5; i++) {
		pssArr2[i] = UART_recieveByte();
	}
	/*Check if both passwords are match*/
		for (i = 0; i < 5; i++) {
			if (pssArr1[i] == pssArr2[i]) {

				if (i == 4) {
					for (i = 0; i < 5; i++) {
						EEPROM_writeByte(*pssLoc + i, pssArr1[i]); /*save the password digits in eeprom locations*/
						_delay_ms(15);
					}

					UART_sendByte(PSS_MATCH);
					*pssMatchFlag = 1;
				}
			} else {

				UART_sendByte(PSS_UNMATCH);
				break;

			}

		}

}
/*
 * Description:
 * Function to check if the input password matches with the saved password in eeprom
 */
void CheckUserPassword(uint8 *userPss,uint8* pssCorrectFlag,uint16*pssLoc){
	uint8 i, correctPassword = 0;
	for (i = 0; i < 5; i++) {
		userPss[i] = UART_recieveByte();
	}

	for (i = 0; i < 5; i++) {
		EEPROM_readByte(*pssLoc + i, &correctPassword);

		if (userPss[i] == correctPassword) {
			if (i == 4) {
				UART_sendByte(PSS_MATCH);
				*pssCorrectFlag = 1;
			}
		} else {
			UART_sendByte(PSS_UNMATCH);
			break;
		}
		_delay_ms(15);
	}
}
/*
 * Description:
 * Function to control door motion
 */
void DoorMotion(Timer1_ConfigType*TIMER1_config){
	Timer1_init(TIMER1_config); /*initialize the timer to start counting*/

	DcMotor_Rotate(CW, 100);
	greenLed_on();
	while (g_tick != 15);
	greenLed_off();
	g_tick = 0;

	DcMotor_Rotate(STOP, 0);
	while (g_tick != 3);
	g_tick = 0;

	DcMotor_Rotate(ACW, 100);
	redLed_on();
	while (g_tick != 15);
	DcMotor_Rotate(STOP, 0);
	redLed_off();
	g_tick = 0;

	Timer1_deInit();/*Disable the timer*/
}
/*
 * Description:
 * Function to handle alarm system
 */
void AlarmSystem(Timer1_ConfigType *TIMER1_config) {
	Timer1_init(TIMER1_config);
	Buzzer_on();
	while (g_tick != 60){
		toggle_leds();
	}
	greenLed_off();
	redLed_off();
	Buzzer_off();
	g_tick = 0;
	Timer1_deInit();
}

int main(void) {
	uint8  pssArr1[5]={0},pssArr2[5]={0},userPss[5]={0}, mainInput,wrongPssCounter = 0,
	pssMatchFlag = 0,mainFlag = 1, pssCorrectFlag = 0;
	uint16 pssLoc = 0x1234;
	SREG |= (1 << 7); /*Enable I-bit*/
	Buzzer_init();
	greenLed_init();
	redLed_init();
	TWI_ConfigType TWI_config = { 0x01, 0x02 };
	TWI_init(&TWI_config);
	DcMotor_Init();
	Timer1_ConfigType TIMER1_config = { 0, 7813, F_CPU_1024, CTC };
	Timer1_setCallBack(timer1_callBack);
	UART_ConfigType UART_config = { eightBit, Disabled, oneBit, 9600 };
	UART_init(&UART_config);

	while (1) { /*Outer loop*/
		SetupSystemPassword(pssArr1,pssArr2,&pssLoc,&pssMatchFlag);

		while (pssMatchFlag) {/*Inner loop*/
			if (mainFlag) {

				mainInput = UART_recieveByte();
				mainFlag = 0;
				wrongPssCounter=0;
			}

			CheckUserPassword(userPss,&pssCorrectFlag,&pssLoc);


			switch (mainInput) {
			case '+':
				if (pssCorrectFlag) {
					UART_recieveByte(); /*Wait until hmi ecu say MOVE_DOOR*/
					DoorMotion(&TIMER1_config);
					pssCorrectFlag = 0;
					mainFlag = 1;
					mainInput=0;

				} else if (wrongPssCounter == 2) {
					UART_recieveByte();/*Wait until hmi ecu say TRIG_ALARM*/
					AlarmSystem(&TIMER1_config);
					mainFlag = 1;
					mainInput=0;

				} else {
					wrongPssCounter++;
				}
				break;
			case '-':
				if (pssCorrectFlag) {
					pssCorrectFlag = 0;
					pssMatchFlag = 0;
					mainFlag = 1;
					mainInput=0;
				} else if (wrongPssCounter == 2) {
					UART_recieveByte();/*Wait until hmi ecu say TRIG_ALARM*/
					AlarmSystem(&TIMER1_config);
					mainFlag = 1;
					mainInput=0;
				} else {
					wrongPssCounter++;
				}
				break;

			}
		}/*Inner loop*/

	}/*Outer loop*/
}
