#include <stdint.h>
#include "reg.h"

/**
 * 
 * LED init
 * 
 */
void led_init(unsigned int led)
{
	SET_BIT(RCC_BASE + RCC_AHB1ENR_OFFSET, GPIO_EN_BIT(GPIO_PORTD));

	//MODER led pin = 01 => General purpose output mode
	CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_MODER_OFFSET, MODERy_1_BIT(led));
	SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_MODER_OFFSET, MODERy_0_BIT(led));

	//OT led pin = 0 => Output push-pull
	CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_OTYPER_OFFSET, OTy_BIT(led));

	//OSPEEDR led pin = 00 => Low speed
	CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_1_BIT(led));
	CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_0_BIT(led));

	//PUPDR led pin = 00 => No pull-up, pull-down
	CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_PUPDR_OFFSET, PUPDRy_1_BIT(led));
	SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_PUPDR_OFFSET, PUPDRy_0_BIT(led));
}

/**
 * 
 * blink LED forever
 * 
 */
void blink(unsigned int led)
{
	led_init(led);

	unsigned int i;

	while (1)
	{
		//set GPIOD led pin
		SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BSy_BIT(led));

		for (i = 0; i < 100000; i++)
			;

		//reset GPIOD led pin
		SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BRy_BIT(led));

		for (i = 0; i < 100000; i++)
			;
	}
}

void Button_init(void)
{
	SET_BIT(RCC_BASE +RCC_AHB1ENR_OFFSET, GPIO_EN_BIT(GPIO_PORTA));

	CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_MODER_OFFSET,MODERy_1_BIT(0));
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_MODER_OFFSET,MODERy_0_BIT(0));
}

void Button_check(unsigned int led)
{
	Button_init();
	while(1)
	{
		if(READ_BIT(GPIO_BASE(GPIO_PORTA)+GPIOx_IDR_OFFSET, 0))
		blink(led);
	}
}
