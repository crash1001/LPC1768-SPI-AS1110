#ifndef __SYSTICK_H
#define __SYSTICK_H

#ifdef __cplusplus
extern "C"
{
#endif
	

//Set up Global variables for a module with an extern declaation in headder file and
//defination declartion in .cpp file

/****************************************
	1 *SystemFrequency/1000      1ms         *
	2 *SystemFrequency/100000    10us        *
	3 *SystemFrequency/1000000   1us         *
	 *****************************************/
	
void systickInit(uint8_t delaySelect);
void _delay(uint32_t delay);
void TimeTick_Decrement(void);
extern void SysTick_Handler(void);


#ifdef __cplusplus
}
#endif

#endif