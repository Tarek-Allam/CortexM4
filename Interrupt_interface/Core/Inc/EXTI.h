#ifndef EXTI_H
#define EXTI_H


#define INTERRUPT_SET(BaseAddress , Offset) ((unsigned int *)(BaseAddress + Offset))
//enable the bus APB2
#define APB2ENR 	 INTERRUPT_SET(0x40023800 , 0x44)
//enable system configuration External Interrupt Configuration, base address system config
#define EXTICR1 	 INTERRUPT_SET(0x40013800 , 0x08)
//EXTI Mask using Interrupt Mask Register (IMR), base address EXTI
#define IMR 	 INTERRUPT_SET(0x40013C00 , 0x00)
// Configure the Rising Edge Trigger
#define RTSR 	 INTERRUPT_SET(0x40013C00 , 0x08)
// Configure the Falling Edge Trigger
#define FTSR 	 INTERRUPT_SET(0x40013C00 , 0x0C)
// clear pending register flag
#define PR 	 INTERRUPT_SET(0x40013C00 , 0x14)
// core peripheral NVIC_ISER0
#define ISER0 	 INTERRUPT_SET(0xE000E000 , 0x100)









#endif
/*
 * EXTI_H
 */
