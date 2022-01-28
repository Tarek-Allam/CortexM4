/*
 * Author : Abdullah Drwesh
 * Date   : 7/12/2021
 * Version: 1.0.0
 */

#include "GPIO.h"

#define GPIO_REG(PORT_ID,REG_ID) ((unsigned int *)(PORT_ID+REG_ID))

#define AHB1ENR			 GPIO_REG(0x40023800,0x30)

#define GPIOA_MODER 	 GPIO_REG(0x40020000,0x00)
#define GPIOA_OTYPER  	 GPIO_REG(0x40020000,0x04)
#define GPIOA_OSPEEDR 	 GPIO_REG(0x40020000,0x08)
#define GPIOA_PUPDR  	 GPIO_REG(0x40020000,0x0C)
#define GPIOA_IDR 	     GPIO_REG(0x40020000,0x10)
#define GPIOA_ODR  		 GPIO_REG(0x40020000,0x14)
#define GPIOA_BSRR  	 GPIO_REG(0x40020000,0x18)
#define GPIOA_LCKR  	 GPIO_REG(0x40020000,0x1C)
#define GPIOA_AFRL  	 GPIO_REG(0x40020000,0x20)
#define GPIOA_AFRH  	 GPIO_REG(0x40020000,0x24)


#define GPIOB_MODER 	 GPIO_REG(0x40020400,0x00)
#define GPIOB_OTYPER  	 GPIO_REG(0x40020400,0x04)
#define GPIOB_OSPEEDR 	 GPIO_REG(0x40020400,0x08)
#define GPIOB_PUPDR  	 GPIO_REG(0x40020400,0x0C)
#define GPIOB_IDR 	     GPIO_REG(0x40020400,0x10)
#define GPIOB_ODR  		 GPIO_REG(0x40020400,0x14)
#define GPIOB_BSRR  	 GPIO_REG(0x40020400,0x18)
#define GPIOB_LCKR  	 GPIO_REG(0x40020400,0x1C)
#define GPIOB_AFRL  	 GPIO_REG(0x40020400,0x20)
#define GPIOB_AFRH  	 GPIO_REG(0x40020400,0x24)

unsigned int *bass_add[2][11] = { { GPIOA_MODER, GPIOA_OTYPER, GPIOA_OSPEEDR,
		GPIOA_PUPDR, GPIOA_IDR, GPIOA_ODR, GPIOA_BSRR, GPIOA_LCKR, GPIOA_AFRL,
		GPIOA_AFRH, AHB1ENR }, { GPIOB_MODER, GPIOB_OTYPER, GPIOB_OSPEEDR,
				GPIOB_PUPDR, GPIOB_IDR, GPIOB_ODR, GPIOB_BSRR, GPIOB_LCKR, GPIOB_AFRL,
				GPIOB_AFRH,AHB1ENR } };

#define _OUTTYPE_MASK  ((unsigned char)0x01)
#define _OUTTYPE_SHIFT 0

#define _PUPD_MASK ((unsigned char)0x06)
#define _PUPD_SHIFT 1

void GPIO_EnableClock(unsigned char Port_ID) {
	switch (Port_ID) {
	case 0:
		*bass_add[Port_ID][10] |= (0x01 << 0);
		break;
	case 1:
		*bass_add[Port_ID][10] |= (0x01 << 1);
		break;
	default:
		break;
	}
}

void GPIO_Init(unsigned char Port_ID, unsigned char PinNum,
		unsigned char PinMode, unsigned char DefaultState) {

	// Configure moder register for pin direction location column 0
	*bass_add[Port_ID][0] &= ~(0x03 << 2 * PinNum);
	*(bass_add[Port_ID][0]) |= PinMode << 2 * PinNum;
	// configure output type register OTYPER location column 1
	*bass_add[Port_ID][1] &= ~(1 << PinNum);
	*bass_add[Port_ID][1] |= ((DefaultState & _OUTTYPE_MASK) >> _OUTTYPE_SHIFT)
			<< PinNum;
	//confiure PULLUP PULL DOWN register location column 3
	*bass_add[Port_ID][3] &= ~(0x03 << 2 * PinNum);
	*bass_add[Port_ID][3] |= ((DefaultState & _PUPD_MASK) >> _PUPD_SHIFT) << (2 * PinNum);

}

unsigned char GPIO_WritePin(unsigned char Port_ID, unsigned char PinNum,
		unsigned char Data) {
	unsigned char result;
// the MODER SETTING FOR The OUTPUT MODE
	if (((*bass_add[Port_ID][0] & (0x03 << 2 * PinNum)) >> (2 * PinNum)) == 1) {
		if (Data) {
			//set OUTPUT data  location 5 register for the required pin
			*bass_add[Port_ID][5] |= (1 << PinNum);
		} else {
			//reset OUTPUT data register location 5 for the required pin
			*bass_add[Port_ID][5] &= ~(1 << PinNum);
		}
		result = OK;
	} else {
		result = NOK;
	}

return result;
}

unsigned char GPIO_ReadPin(unsigned char Port_ID, unsigned char PinNum) {
unsigned char data = 0;

data = (*bass_add[Port_ID][4] & (1 << PinNum)) >> PinNum;

return data;
}
