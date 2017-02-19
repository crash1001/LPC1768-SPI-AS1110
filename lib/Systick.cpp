#include <LPC17xx.h>
#include "Systick.h"

static __IO uint32_t sysTickCounter;


/****************************************
	0 *SystemFrequency/100       10ms 
	1 *SystemFrequency/1000      1ms         *
	2 *SystemFrequency/100000    10us        *
	3 *SystemFrequency/1000000   1us         *
	 *****************************************/

void systickInit(uint8_t delaySelect)	{
	
	switch(delaySelect)	{
		
		case 0:	//100 ms delay
			SysTick_Config((SystemCoreClock / 10)-1);
			
		
		case 1:	//1ms delay
			SysTick_Config((SystemCoreClock / 1000)-1);
			
		
		case 2:	//100us delay
			SysTick_Config((SystemCoreClock / 10000)-1);
			
		
		case 3:	//1us delay
			SysTick_Config((SystemCoreClock / 1000000)-1);
			
			
		default:	//10ms delay
				SysTick_Config((SystemCoreClock / 100)-1);

	}
}

void _delay(uint32_t delay)	{
	sysTickCounter = delay;
	while(sysTickCounter !=0);
}
	
void TimeTick_Decrement(void) {
	if(sysTickCounter != 0)	{
		sysTickCounter--;
	}
}

void SysTick_Handler(void) {
	TimeTick_Decrement();
}
			

