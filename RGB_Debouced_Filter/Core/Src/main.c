/*
 *********************************************
GPIO Configuration for stm32f401cc
 *********************************************
 */
/*
 *********************************************
Red Terminal connected to pin 5, is the least significant bit
Green Terminal connected to pin 6
Blue Terminal connected to pin 7
 *********************************************
 */
#include "stm32f401cc_interface.h"
void MYOUTPUT (void);
void INPUT (void);
void Delay_fn (void);
int count = 0;
int main(void)
{

  while (1)
  {

INPUT();
MYOUTPUT();
Delay_fn();
		  if(!(GPIOB_IDR & (1<<3)))
		  {
			while(!(GPIOB_IDR & (1<<3)));
			count++;
		  }
switch (count%9)
{
	case 1:
		GPIOB_ODR &= ~((1<<5)|(1<<6)|(1<<7));
		Delay_fn();
		break;
	case 2:
		GPIOB_ODR &= ~((1<<6)|(1<<7));
		GPIOB_ODR |= (1<<5);
		Delay_fn();
		break;
	case 3:
		GPIOB_ODR &= ~((1<<5)|(1<<7));
		GPIOB_ODR |= (1<<6);
		Delay_fn();
		break;
	case 4:
		GPIOB_ODR &= ~(1<<7);
		GPIOB_ODR |= ((1<<5)|(1<<6));
		Delay_fn();
		break;
	case 5:
		GPIOB_ODR &= ~((1<<5)|(1<<6));
		GPIOB_ODR |= (1<<7);
		Delay_fn();
		break;
	case 6:
		GPIOB_ODR &= ~(1<<6);
		GPIOB_ODR |= ((1<<5)|(1<<7));
		Delay_fn();
		break;
	case 7:
		GPIOB_ODR &= ~(1<<5);
		GPIOB_ODR |= ((1<<6)|(1<<7));
		Delay_fn();
		break;
	case 8:
		GPIOB_ODR |= ((1<<5)|(1<<6)|(1<<7));
		Delay_fn();
		count = 0;
		break;
	default:
		break;
}
/*
	if(count%9 == 1)
	{
		GPIOB_ODR &= ~(1<<5);	// RESET PIN B5
		GPIOB_ODR &= ~(1<<6);	// RESET PIN B6
		GPIOB_ODR &= ~(1<<7);	// RESET PIN B7
	}
	else if (count%9 == 2)
	{
		GPIOB_ODR |= (1<<5);	// SET PIN B5 AS HIGH RED: 1
		GPIOB_ODR &= ~(1<<6);	// RESET PIN B5
		GPIOB_ODR &= ~(1<<7);	// RESET PIN B6

		Delay_fn();
	}
	else if (count%9 == 3)
	{
		GPIOB_ODR &= ~(1<<5);// RESET PIN B5
		GPIOB_ODR |= (1<<6);	// SET PIN B6 AS HIGH green
		GPIOB_ODR &= ~(1<<7);	// RESET PIN B7
		Delay_fn();
	}
	else if (count%9 == 4)
	{
		GPIOB_ODR &= ~(1<<5);// RESET PIN B5
		GPIOB_ODR |= (1<<6);	// SET PIN B6 AS HIGH green
		GPIOB_ODR |= (1<<7);	// SET PIN B7 AS HIGH  blue
		Delay_fn();
	}
	else if (count%9 == 5)
	{
		GPIOB_ODR |= (1<<5);//SET PIN B5 AS HIGH red
		GPIOB_ODR &= ~(1<<6);	// RESET PIN B6
		GPIOB_ODR &= ~(1<<7);	// RESET PIN B7
		Delay_fn();
	}
	else if (count%9 == 6)
	{
		GPIOB_ODR |= (1<<5);//SET PIN B5 AS HIGH red
		GPIOB_ODR &= ~(1<<6);	// RESET PIN B6
		GPIOB_ODR |= (1<<7);	// SET PIN B7 AS HIGH  blue
		Delay_fn();
	}
	else if (count%9== 7)
	{
		GPIOB_ODR |= (1<<5);//SET PIN B5 AS HIGH red
		GPIOB_ODR |= (1<<6);	// SET PIN B6 AS HIGH green
		GPIOB_ODR &= ~(1<<7);	// RESET PIN B7
		Delay_fn();
	}	else if (count%9 == 8)
	{
		GPIOB_ODR |= (1<<5);//SET PIN B5 AS HIGH red
		GPIOB_ODR |= (1<<6);	// SET PIN B6 AS HIGH green
		GPIOB_ODR |= (1<<7);	// SET PIN B7 AS HIGH  blue
		Delay_fn();
		count = 0;
	}
*/
  }
  return 0;
}
void Delay_fn (void)
{
	int i ;
	for (i=0; i<50000; i++)
	{}
}
void MYOUTPUT (void)
{
	/************** STEPS TO FOLLOW *****************
	1. Enable GPIOA clock
	2. Set the PINs 5,6,7 as OUTPUT
	3. Configure the OUTPUT Type mode
	4. Configure PULLING register
	************************************************/

	// 1. Enable GPIOB clock
	RCC_AHB1ENR |= (1<<1);
	// 2. Set the PIN PB5,6,7 as output size 2bit
	GPIOB_MODER |= ((0x01<<10)|(0x01<<12)|(0x01<<14));
	// 3.choose the output type push-pull size 1 bit
	GPIOB_OTYPER &= ~((0x01<<5)|(1<<6)|(1<<7));
	// 4.  NO PULL UP OR PULL DOWN
	GPIOB_PUPDR &= ~((0x01<<10)|(0x01<<12)|(0x01<<14));
}
void INPUT (void)
{
	/************** STEPS TO FOLLOW *****************
	1. Enable GPIOB clock
	2. Set the PIN PB3 as input
	3. Configure the Pull UP mode
	************************************************/
	// 1. Enable GPIOB clock
	RCC_AHB1ENR |= (1<<1);
	// 2. Set the PIN PB3 as input pin #6 and pin #7 must be 00
	GPIOB_MODER &= ~(0x01<<6);
	// 3.Configure PULLING register
	GPIOB_PUPDR |= (0x01<<6);
}
