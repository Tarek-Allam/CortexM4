/*
 * Author : Abdullah Drwesh
 * Date   : 8/12/2021
 * Version: 1.0.0
 */
#include "Keypad.h"
unsigned char buttonState = 0;
unsigned char key;

void delay30ms() {
	unsigned int i;
	for (i = 0; i < 30000; i++) {
	}
}
/* Keypad Button Values*/
unsigned char arr[4][3] = { { 0x01, 0x02, 0x03 }, { 0x04, 0x05, 0x06 }, { 0x07,
		0x08, 0x09 }, { 0x00, 0x00, 0x00 } };
void Kepad_init() {

//set the rows as output push_pull
	for (int i = 0; i < 4; i++) {
		GPIO_Init(0, i, OUTPUT, PUSH_PULL);
	}
//set the columns as inputs pulled pulled up
	for (int i = 0; i < 3; i++) {
		GPIO_Init(0, i + 4, INPUT, PULL_UP);
	}
}
char Keypad_Getkey() {
	/*
	 * 1-check pressed
	 * 2-if pressed -> released
	 * 3-return key
	 *
	 */
	if (buttonState == 1) {
		buttonState = 0;
		return key;
	}

	return -1;
}

void Keypad_manage(void) {
	/*
	 * Check button state if released got read keypad
	 * if pressed save button in global variable
	 *  then make state pressed
	 *  call function call out _button pressed notification
	 */
	if (buttonState == 0) {
		for (int i = 0; i < 4; i++) {
			GPIO_WritePin(0, i, 0);

			for (int j = 0; j < 3; j++) {

				if (GPIO_ReadPin(0, j + 4) == 0) {
					delay30ms();
					if (GPIO_ReadPin(0, j + 4) == 0) {
						key = arr[i][j];
						buttonState = 1;
						Keypadcall_btnpressednotifin();
					}
				}

			}
			GPIO_WritePin(0, i, 1);

		}

	}

}

