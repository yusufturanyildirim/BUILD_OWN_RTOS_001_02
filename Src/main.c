#include "led.h"
#include "uart.h"

int main(void)
{
	RCC_Config();
	GPIO_Config();
	UART_TRANSMIT_Config();

	while(1)
	{
		printf("Hello My Precious...\n\r");
		for(int i = 0; i < 60000;i++);
	}
}
