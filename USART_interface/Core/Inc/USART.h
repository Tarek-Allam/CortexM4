
#ifndef USART_H
#define USART_H


#define USART_SET(BaseAddress , Offset) ((unsigned int *)(BaseAddress + Offset))

//enable the bus APB1 APB1ENR
#define APB1ENR 	 USART_SET(0x40023800 , 0x40)
#define GPIOA_AFRL	USART_SET(0x40020000,0x20)

#define USART_CR1 	 USART_SET(0x40004400 , 0x0C)
#define USART_CR2 	 USART_SET(0x40004400 , 0x10)
#define USART_DR	 USART_SET(0x40004400 , 0x04)
#define USART_BRR 	 USART_SET(0x40004400 , 0x08)
#define USART_SR	USART_SET(0x40004400 , 0x00)


unsigned int *UART_REGS[]={APB1ENR,GPIOA_AFRL,USART_CR1,USART_CR2,USART_DR,USART_BRR,USART_SR};





#endif
/*
 * USART_H
 */
