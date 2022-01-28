/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
	0. Enable the bus APB2
	1. Enable system configuration External Interrupt Configuration
	2. Disable the EXTI Mask using Interrupt Mask Register (IMR)
	3. Configure the Rising Edge / Falling Edge Trigger
	4. Core peripheral set  NVIC_ISER0
	4. ISR function put it in startup file IRQ handler
	5. clear pending register

	********************************************************/

#include "GPIO.h"
#include "EXTI.h"
unsigned int *EXT_REGS[]={APB2ENR,EXTICR1,IMR,RTSR,FTSR,PR,ISER0};
void Delay_fn (void);
int main(void) {

	GPIO_EnableClock(0);
// input pin
	GPIO_Init(0, 0, INPUT, PULL_UP);

	GPIO_Init(0, 2, OUTPUT, PUSH_PULL);
	GPIO_Init(0, 3, OUTPUT, PUSH_PULL);
	GPIO_Init(0, 4, OUTPUT, PUSH_PULL);
	GPIO_Init(0, 5, OUTPUT, PUSH_PULL);

//	0. Enable the bus APB2 APB2ENR location 0
*EXT_REGS[0]|=(1<<14);
//1. Enable system configuration External Interrupt Configuration EXT0[0:3] for GPIO
// write in 4 bits to define the required pin
//// Bits[3:2:1:0] = (0:0:0:0)  -> configure EXTI0 line for PA0
*EXT_REGS[1]  &= ~(0xf<<0);
//2. Disable the EXTI Mask using Interrupt Mask Register (IMR)
*EXT_REGS[2]|=(1<<0);
//3. Configure the Rising Edge / Falling Edge Trigger
*EXT_REGS[4]|=(1<<0);
//4. Core peripheral set  NVIC_ISER0 write 1 on bit #6
*EXT_REGS[6]|=(1<<6);

	while (1) {



	}
	return 0;
}

void Delay_fn (void)
{
	int i ;
	for (i=0; i<500000; i++)
	{}
}
void MYINT(void)
{
	for (int counter1 = 2; counter1 <=5; counter1 ++)
	{
		GPIO_WritePin(0, counter1, 1);
		 Delay_fn();
	}
	for (int counter1 = 2; counter1 <=5; counter1 ++)
	{
		GPIO_WritePin(0, counter1, 0);
		 Delay_fn();
	}

	 //clear pr // Clear the interrupt flag by writing a 1 pin 0
	 *EXT_REGS[5]|=(1<<0);

}
