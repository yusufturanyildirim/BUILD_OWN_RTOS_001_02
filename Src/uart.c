#include <stdio.h>
#include "uart.h"
#include "stm32f4xx.h"

#define GPIOA_CLOCK 			(1U<<0)
#define UART2_EN				(1U<<17)
#define SYSTEM_FREQ 			16000000
#define APB1_CLOCK				SYSTEM_FREQ
#define UART_BAUDRATE			115200  /* Optional */
#define UART_CR1_REGISTER_TE	(1U<<3)
#define UART_CR1_ENABLE			(1U<<13)
#define UART_ST_TXE				(1U<<7)



static uint16_t COMPUTE_UART_BAUDRATE(uint32_t peripheralClock, uint32_t baudRate);
static void UART_SET_BAUDRATE(uint32_t peripheralClock, uint32_t baudRate);

static void UART_WRITE(int ch);

int __io_putchar(int ch)
{
	UART_WRITE(ch);
	return ch;
}
void UART_TRANSMIT_Config(void)
{
	/* Enable Clock Access to GPIOA */
	/* USART2_TX -> PA2 */
	RCC->AHB1ENR |= GPIOA_CLOCK;

	/* Set PA2 pin as alternate function */
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |=  (1U<<5);


	/* Set alternate function type to AF7(UART2_TX -> From Alternate Function Mapping) */
	/* ARF[0] -> ARFLow ARF[1] -> ARFHigh */
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11); /* GPIOA->ARF[0] &= (1U<<11) */

	/* Enable Clock Access to UART*/
	RCC->APB1ENR |= UART2_EN;
	/* Configure boundrate */
	UART_SET_BAUDRATE(APB1_CLOCK,UART_BAUDRATE);
	/* Configure Transfer Direction */
	USART2->CR1 |= UART_CR1_REGISTER_TE;

	/* Enable UART Module */
	USART2->CR1 |= UART_CR1_ENABLE;
}

static void UART_WRITE(int ch)
{
	/* Make sure the transmit data register is empty */
	while(!(USART2->SR & UART_ST_TXE)){}

	/* Write to transmit data register */
	USART2->DR = (ch & 0xFF);
}


static void UART_SET_BAUDRATE(uint32_t peripheralClock, uint32_t baudRate)
{
	USART2->BRR = COMPUTE_UART_BAUDRATE(peripheralClock, baudRate);
}


static uint16_t COMPUTE_UART_BAUDRATE(uint32_t peripheralClock, uint32_t baudRate)
{
	return ((peripheralClock + (baudRate / 2))/ baudRate);

}


