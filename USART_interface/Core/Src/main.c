#include "GPIO.h"
#include "USART.h"

void Delay_fn(void);

void UART2_SendChar(char c);
char UART2_GetChar(void);
void UART2_SendString(char *string);

/******* STEPS FOLLOWED ********

 1. Enable the UART CLOCK and GPIO CLOCK
 2. Configure the UART PINs for ALternate Functions
 3. Enable the USART by writing the UE bit in USART_CR1 register to 1.
 4. Program the M bit in USART_CR1 to define the word length.
 5. Select the desired baud rate using the USART_BRR register.
 6. Enable the Transmitter/Receiver by Setting the TE and RE bits in USART_CR1 Register
 // datasheet steps
 Procedure:
 1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
 2. Program the M bit in USART_CR1 to define the word length.
 3. Program the number of stop bits in USART_CR2.
 4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
 place. Configure the DMA register as explained in multibuffer communication.
 5. Select the desired baud rate using the USART_BRR register.
 6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
 7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
 for each data to be transmitted in case of single buffer.
 8. After writing the last data into the USART_DR register, wait until TC=1. This indicates
 that the transmission of the last frame is complete. This is required for instance when
 the USART is disabled or enters the Halt mode to avoid corrupting the last
 transmission.
 ********************************/

void Delay_fn(void) {
	int i;
	for (i = 0; i < 500000; i++) {
	}
}
int main() {
	//enable the Clock for the GPIOA Port
	GPIO_EnableClock(0);
	//Then select the Pins PA2 and PA3 in the Alternate Function mode
	GPIO_Init(0, 2, ALTERNATE_FUN, PUSH_PULL);
	GPIO_Init(0, 3, ALTERNATE_FUN, PUSH_PULL);

	//Alternate Function Register for port A
	//Selecting an alternate function AF7 USART1 lower register AFRL[0:31]
	// 4 bits control the alternate function of 1 pin from pin0 to pin 7
	// pin A2 set AFRL with 0111 to the corresponding 4 bits
	// Bites (11:10:9:8) = 0:1:1:1  --> AF7 Alternate function for USART2 at Pin PA2
	*UART_REGS[1] |= (7 << 8);
	// Bites (15:14:13:12) = 0:1:1:1  --> AF7 Alternate function for USART2 at Pin PA3
	*UART_REGS[1] |= (7 << 12);

////enable the bus APB1 APB1ENR bit 17 for UART2
	*UART_REGS[0] |= (1 << 17);
////Enable the USART by writing the UE bit in USART_CR1 register to 1 Bit 13 UE: USART enable
	*UART_REGS[2] |= (1 << 13);
////Program the M bit in USART_CR1 to define the word length.0: 1 Start bit, 8 Data bits, n Stop bit
	*UART_REGS[2] &= ~(1 << 12);
///Select the desired baud rate using the USART_BRR register.
// baud rate 9600 clock
//fixed point representation  it takes 0x68(104) and 0x03 in fraction part
	*UART_REGS[5] = 0x683;

	// RE=1.. Enable the Receiver
	*UART_REGS[2] |= (1 << 2);
	// TE=1.. Enable Transmitter
	*UART_REGS[2] |= (1 << 3);
	//Bits 13:12 STOP: STOP bits
	*UART_REGS[3] |= (0x00 << 12);
	///////______________________________//

	while (1) {
		Delay_fn();
		UART2_SendString("hello world \n\r");
//				char  data = UART2_GetChar ();
//				UART2_SendChar (data);

	}
	return 0;
}
void UART2_SendChar(char c) {
	/*********** STEPS FOLLOWED *************

	 1. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
	 for each data to be transmitted in case of single buffer.
	 2. After writing the last data into the USART_DR register, wait until TC=1. This indicates
	 that the transmission of the last frame is complete. This is required for instance when
	 the USART is disabled or enters the Halt mode to avoid corrupting the last transmission.

	 ****************************************/

	*UART_REGS[4] = c;

	while (!(*UART_REGS[6] & (1 << 6)))
		;
	// Wait for TC to SET.. This indicates that the data has been transmitted

}

char UART2_GetChar(void) {
	/*********** STEPS FOLLOWED *************

	 1. Wait for the RXNE bit to set. It indicates that the data has been received and can be read.
	 2. Read the data from USART_DR  Register. This also clears the RXNE bit

	 ****************************************/
	char Temp;

	while (!(*UART_REGS[6] & (1 << 5)))
		; // Wait for RXNE to SET.. This indicates that the data has been Received
	Temp = *UART_REGS[4];  // Read the data.
	return Temp;
}
void UART2_SendString(char *string) {
	int i = 0;
	while (string[i] != 0) {
		UART2_SendChar(string[i]);
		i++;
	}
//	while (*string) UART2_SendChar (*string++);
}
