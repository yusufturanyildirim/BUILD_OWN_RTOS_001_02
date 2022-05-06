#include "led.h"


#define GPIOA_CLOCK (1U<<0)
#define GPIOB_CLOCK (1U<<1)
#define GPIOC_CLOCK (1U<<2)
#define GPIOD_CLOCK (1U<<3)

#define GREEN_BIT	(01U<<24)
#define ORANGE_BIT	(01U<<26)
#define RED_BIT		(01U<<28)
#define BLUE_BIT 	(01U<<30)

#define BLUE		(1U<<15)
#define RED			(1U<<14)
#define ORANGE		(1U<<13)
#define GREEN		(1U<<12)



void RCC_Config(void)
{
	/* Enable GPIO Port D */
	RCC->AHB1ENR |= GPIOD_CLOCK;
	RCC->CR |= (1U<<16);

	/* Check HSE ready */
	while(!((RCC->CR) & (1U<<17)));

}

void GPIO_Config(void)
{
	GPIOD->MODER |= GREEN_BIT| ORANGE_BIT| RED_BIT| BLUE_BIT;
}

void LED_ON(void)
{
	/* Set Led Pin HIGH */
	GPIOD->ODR |= GREEN| ORANGE| RED| BLUE;


}


void LED_OFF(void)
{
	/* Set Led Pin LOW */
	GPIOD->ODR &= ~ (GREEN| ORANGE| RED| BLUE);

}

