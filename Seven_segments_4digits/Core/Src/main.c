#include "GPIO.h"
#include "EXTI.h"
// Interrupt registers addresses
unsigned int *EXT_REGS[]={APB2ENR,EXTICR1,IMR,RTSR,FTSR,PR,ISER0,ICER0};
//////////////////////

void Delay_fn (void);
void SevenSegment_Update(unsigned int number);
void Decrement(void);
void Increament(void);

// Segment numbers stored in the array
unsigned int segmentNumber[11] = {
        0x3f,  // 0
        0x06,  // 1
        0x5b,  // 2
        0x4f,  // 3
        0x66,  // 4
        0x6d,  // 5
        0x7d,  // 6
        0x07,  // 7
        0x7f,  // 8
        0x67,   // 9
		0x40	//-
};
unsigned int counter = 0;
unsigned int temp1, temp2, temp3, temp4,temp5;

void SevenSegment_Update(unsigned int number){
	GPIO_WritePin(1, 0, ((number>>0)&0x01));
	GPIO_WritePin(1, 1, ((number>>1)&0x01));
	GPIO_WritePin(1, 2, ((number>>2)&0x01));
	GPIO_WritePin(1, 3, ((number>>3)&0x01));
	GPIO_WritePin(1, 4, ((number>>4)&0x01));
	GPIO_WritePin(1, 5, ((number>>5)&0x01));
	GPIO_WritePin(1, 6, ((number>>6)&0x01));
}
void Delay_fn (void)
{
	int i ;
	for (i=0; i<100; i++)
	{}
}
void Increament(void)
{
	counter=counter+1;
	//clear pr // Clear the interrupt flag by writing a 1 pin A0
	 *EXT_REGS[5]|=(1<<0);

}
void Decrement(void)
{
	counter=counter-1;
	//clear pr // Clear the interrupt flag by writing a 1 pin A1
	*EXT_REGS[5]|=(1<<1);
}
int main(void)
{
	GPIO_EnableClock(0);
	GPIO_EnableClock(1);
	//	GPIO_Init(1, 12, OUTPUT, PUSH_PULL);
		GPIO_Init(1, 13, OUTPUT, PUSH_PULL);
	////output for 4digits display
	for(int i=0; i<=10; i++)
	{
		GPIO_Init(1, i, OUTPUT, PUSH_PULL);
	}

	/////inputs for interrupt
	GPIO_Init(0, 0, INPUT, PULL_UP);
	GPIO_Init(0, 1, INPUT, PULL_UP);
	/////////////////// interrupt configuration
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
	/////////////////////////////////////////////////////
	int localcount = counter;

	while(1)
	{

							//////////////////////////////
					  		*EXT_REGS[7] = (1<<6);
					  		*EXT_REGS[7] = (1<<7);
					  			localcount = counter;
					  		//	*EXT_REGS[7]&=~(1<<6);
					  		//	*EXT_REGS[7]&=~(1<<7);
					  		*EXT_REGS[6] =(1<<6);
					  		*EXT_REGS[6] =(1<<7);
					  		//////////////////////////////
//



		  /* USER CODE BEGIN 3 */ // counter = 1234
			  temp1 = localcount/1000; //1 - 1st digit
			  temp2 = ((localcount/100)%10); //2 - 2nd digit
			  temp3 = ((localcount/10)%10); //3 - 3rd digit
			  temp4 = (localcount%10); //4 - 4th digit


			  SevenSegment_Update(segmentNumber[temp1]);
			  GPIO_WritePin(1, 7, 0);
			  Delay_fn();
			  GPIO_WritePin(1, 7, 1);

			  SevenSegment_Update(segmentNumber[temp2]);
			  GPIO_WritePin(1, 8, 0);
			  Delay_fn();
			  GPIO_WritePin(1, 8, 1);

			  SevenSegment_Update(segmentNumber[temp3]);
			  GPIO_WritePin(1, 9, 0);
			  Delay_fn();
			  GPIO_WritePin(1, 9, 1);

			  SevenSegment_Update(segmentNumber[temp4]);
			  GPIO_WritePin(1, 10, 0);
			  Delay_fn();
			  GPIO_WritePin(1, 10, 1);

			  SevenSegment_Update(segmentNumber[10]);
			  GPIO_WritePin(1, 12, 0);
			  Delay_fn();
			  GPIO_WritePin(1, 12, 1);


//			  counter++;
//
//			  	  if (counter >= 1000) {
//			  		counter = 0;
//			  	  }
	}
	return 0;
}
