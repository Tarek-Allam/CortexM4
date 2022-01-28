/*
 * Author : Abdullah Drwesh
 * Date   : 8/12/2021
 * Version: 1.0.0
 */

#ifndef KEYPAD_H
#define KEYPAD_H
#include "GPIO.h"
void Kepad_init(void);
char Keypad_Getkey(void);
void Keypadcall_btnpressednotifin(void);
void Keypad_manage(void);

#endif /* KEYPAD_H */
