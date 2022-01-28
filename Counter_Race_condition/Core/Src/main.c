/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
	0. Enable the bus APB2
	1. Enable system configuration External Interrupt Configuration
	2. Disable the EXTI Mask using Interrupt Mask Register (IMR)
	3. Configure the Rising Edge / Falling Edge Trigger
	4. Core peripheral set  NVIC_ISER0
	4. ISR function put it in startup file IRQ handler
	5. clear pending reg
	6.disable interrupt icer register
	7.display inside main
	8.enable interrupt icer register
	9. increment ISR function put it in startup file IRQ handler 0
	10.decrement ISR function put it in startup file IRQ handler 1

	********************************************************/

#include "GPIO.h"
#include "EXTI.h"
unsigned int *EXT_REGS[]={APB2ENR,EXTICR1,IMR,RTSR,FTSR,PR,ISER0,ICER0};

void Delay_fn (void);
void Display(int counterdeci);
int Dcount = 0;
int main(void) {

	GPIO_EnableClock(0);
	GPIO_EnableClock(1);

	GPIO_Init(0, 0, INPUT, PULL_UP);
	GPIO_Init(0, 1, INPUT, PULL_UP);

	GPIO_Init(1, 5, OUTPUT, PUSH_PULL);
	GPIO_Init(1, 6, OUTPUT, PUSH_PULL);
	GPIO_Init(1, 7, OUTPUT, PUSH_PULL);
	GPIO_Init(1, 8, OUTPUT, PUSH_PULL);
	GPIO_Init(1, 9, OUTPUT, PUSH_PULL);
	GPIO_Init(1, 10, OUTPUT, PUSH_PULL);
	GPIO_Init(1, 12, OUTPUT, PUSH_PULL);

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

//1. Enable system configuration External Interrupt Configuration EXT0[0:3] for GPIO
// write in 4 bits to define the required pin
//// Bits[7:6:5:4] = (0:0:0:0)  -> configure EXTI0 line for PA1
*EXT_REGS[1]  &= ~(0xf<<4);
//2. Disable the EXTI Mask using Interrupt Mask Register (IMR)
*EXT_REGS[2]|=(1<<1);
//3. Configure the Rising Edge / Falling Edge Trigger
*EXT_REGS[4]|=(1<<1);
//4. Core peripheral set  NVIC_ISER0 write 1 on bit #6
*EXT_REGS[6] =(1<<7);

int localcount = Dcount;


	while (1) {

		//////////////////////////////
		*EXT_REGS[7] = (1<<6);
		*EXT_REGS[7] = (1<<7);
			localcount = Dcount;
		//	*EXT_REGS[7]&=~(1<<6);
		//	*EXT_REGS[7]&=~(1<<7);
		*EXT_REGS[6] =(1<<6);
		*EXT_REGS[6] =(1<<7);
		//////////////////////////////

		Display(localcount);


	}
	return 0;
}

void Delay_fn (void)
{
	int i ;
	for (i=0; i<1000000; i++)
	{}
}
void Increament(void)
{
	Dcount=Dcount+1;
	//clear pr // Clear the interrupt flag by writing a 1 pin A0
	 *EXT_REGS[5]|=(1<<0);

}
void Decrement(void)
{
	Dcount=Dcount-1;
	//clear pr // Clear the interrupt flag by writing a 1 pin A1
	*EXT_REGS[5]|=(1<<1);
}
void Display(int counterdeci)
{

		switch (counterdeci%10)
		{
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
			Delay_fn();

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
}
