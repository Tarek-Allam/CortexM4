/*
 * Author : Abdullah Drwesh
 * Date   : 7/12/2021
 * Version: 1.0.0
 */
#include "GPIO.h"
#include "Keypad.h"
int main(void) {
	GPIO_EnableClock(0);

	Kepad_init();

	GPIO_EnableClock(1);

	GPIO_Init(1, 5, OUTPUT, PUSH_PULL);
	GPIO_Init(1, 6, OUTPUT, PUSH_PULL);
	GPIO_Init(1, 7, OUTPUT, PUSH_PULL);
	GPIO_Init(1, 8, OUTPUT, PUSH_PULL);
	GPIO_Init(1, 9, OUTPUT, PUSH_PULL);
	GPIO_Init(1, 10, OUTPUT, PUSH_PULL);
	GPIO_Init(1, 12, OUTPUT, PUSH_PULL);
	while (1) {

		Keypad_manage();

	}
	return 0;
}
void Keypadcall_btnpressednotifin() {
	char keyvalue = Keypad_Getkey();
	switch (keyvalue) {
	case 0:
		GPIO_WritePin(1, 5, 1);
		GPIO_WritePin(1, 6, 1);
		GPIO_WritePin(1, 7, 1);
		GPIO_WritePin(1, 8, 1);
		GPIO_WritePin(1, 9, 1);
		GPIO_WritePin(1, 10, 1);
		GPIO_WritePin(1, 12, 0);

		break;
	case 1:
		GPIO_WritePin(1, 5, 0);
		GPIO_WritePin(1, 6, 1);
		GPIO_WritePin(1, 7, 1);
		GPIO_WritePin(1, 8, 0);
		GPIO_WritePin(1, 9, 0);
		GPIO_WritePin(1, 10, 0);
		GPIO_WritePin(1, 12, 0);

		break;
	case 2:
		GPIO_WritePin(1, 5, 1);
		GPIO_WritePin(1, 6, 1);
		GPIO_WritePin(1, 7, 0);
		GPIO_WritePin(1, 8, 1);
		GPIO_WritePin(1, 9, 1);
		GPIO_WritePin(1, 10, 0);
		GPIO_WritePin(1, 12, 1);

		break;
	case 3:
		GPIO_WritePin(1, 5, 1);
		GPIO_WritePin(1, 6, 1);
		GPIO_WritePin(1, 7, 1);
		GPIO_WritePin(1, 8, 1);
		GPIO_WritePin(1, 9, 0);
		GPIO_WritePin(1, 10, 0);
		GPIO_WritePin(1, 12, 1);

		break;
	case 4:
		GPIO_WritePin(1, 5, 0);
		GPIO_WritePin(1, 6, 1);
		GPIO_WritePin(1, 7, 1);
		GPIO_WritePin(1, 8, 0);
		GPIO_WritePin(1, 9, 0);
		GPIO_WritePin(1, 10, 1);
		GPIO_WritePin(1, 12, 1);

		break;
	case 5:
		GPIO_WritePin(1, 5, 1);
		GPIO_WritePin(1, 6, 0);
		GPIO_WritePin(1, 7, 1);
		GPIO_WritePin(1, 8, 1);
		GPIO_WritePin(1, 9, 0);
		GPIO_WritePin(1, 10, 1);
		GPIO_WritePin(1, 12, 1);

		break;
	case 6:
		GPIO_WritePin(1, 5, 1);
		GPIO_WritePin(1, 6, 0);
		GPIO_WritePin(1, 7, 1);
		GPIO_WritePin(1, 8, 1);
		GPIO_WritePin(1, 9, 1);
		GPIO_WritePin(1, 10, 1);
		GPIO_WritePin(1, 12, 1);

		break;
	case 7:
		GPIO_WritePin(1, 5, 1);
		GPIO_WritePin(1, 6, 1);
		GPIO_WritePin(1, 7, 1);
		GPIO_WritePin(1, 8, 0);
		GPIO_WritePin(1, 9, 0);
		GPIO_WritePin(1, 10, 0);
		GPIO_WritePin(1, 12, 0);

		break;
	case 8:
		GPIO_WritePin(1, 5, 1);
		GPIO_WritePin(1, 6, 1);
		GPIO_WritePin(1, 7, 1);
		GPIO_WritePin(1, 8, 1);
		GPIO_WritePin(1, 9, 1);
		GPIO_WritePin(1, 10, 1);
		GPIO_WritePin(1, 12, 1);

		break;
	case 9:
		GPIO_WritePin(1, 5, 1);
		GPIO_WritePin(1, 6, 1);
		GPIO_WritePin(1, 7, 1);
		GPIO_WritePin(1, 8, 1);
		GPIO_WritePin(1, 9, 0);
		GPIO_WritePin(1, 10, 1);
		GPIO_WritePin(1, 12, 1);

		break;

	default:
		break;
	}
	/*
	 * get_key
	 * display_key
	 *
	 */
}

