#include <LPC17xx.h>
#include "GPIO.h"





//enum Func{PullUp, PullDown, None};
GPIO::GPIO()	{
}

// portNum.bitPos becomes high
void GPIO::setValue(uint8_t portNum, uint32_t bitPos)	{
	LPC_GPIO[portNum]->FIOMASK = ~(1<<bitPos);
	LPC_GPIO[portNum]->FIOSET |= (1<<bitPos);
}

//portNum.bitPos becomes low
void GPIO::clearValue(uint8_t portNum, uint32_t bitPos)	{
	LPC_GPIO[portNum]->FIOMASK = ~(1<<bitPos);
	LPC_GPIO[portNum]->FIOSET |= (1<<bitPos);
}

/*portNu.bitPos : set direction input/output
	direction = 1 output
  direction = 0 input*/
void setDirection(uint8_t portNum, uint32_t bitPos, uint8_t direction)	{
	if(direction)	{
		LPC_GPIO[portNum]->FIODIR |= (1<<bitPos);
	}
	else	{
		LPC_GPIO[portNum]->FIODIR &= ~(1<<bitPos);
	}
}
//portNum.bitPos becomes an input pin
//void GPIO::Input(uint8_t portNum, uint32_t bitPos)	{
//	LPC_GPIO[portNum]->FIODIR &= ~(1<<bitPos);
//}

////portNum.bitPos becomes an output pin
//void GPIO::Output(uint8_t portNum, uint32_t bitPos) {
//	LPC_GPIO[portNum]->FIODIR |= (1<<bitPos);
//}

/*pinModeSelect = 0 :  00 portNum.bitPos has a pull-up resistor enabled
	pinModeSelect = 1 :  01 portNum.bitPos has a pull-down resistor enabled
	pinModeSelect = 2 :	 10 portNum.bitPos has neither pull-up nor pull-down enabled
	pinModeSelect = default*/
void GPIO::PinModeConfig(uint8_t pinModeSelect,uint8_t portNum, uint32_t bitPos)	{
	uint32_t pinModeSetUp;
	switch(pinModeSelect)
	{
		case 0:		//PullUp
			pinModeSetUp =	00;
			break;
		case 1:		//PullDown
			pinModeSetUp = 11;
			break;
		case 2:	//no pull up/down resistor
			pinModeSetUp = 10;
			break;
		
		default:
			pinModeSetUp = 00;
			break;
	}
	
	switch(portNum)	{
		
		case 0:			
				if(bitPos < 16) {
					bitPos = bitPos * 2;
					LPC_PINCON->PINMODE0 = pinModeSetUp<<bitPos;
				}
				else if(bitPos > 15) {
					bitPos = bitPos - 16;
					bitPos = bitPos *2;
					LPC_PINCON->PINMODE0 = pinModeSetUp<<bitPos;
				}
				break;
			
		case 1:
				if(bitPos < 16) {
					bitPos = bitPos * 2;
					LPC_PINCON->PINMODE2 = pinModeSetUp<<bitPos;
				}
				else if(bitPos > 15) {
					bitPos = bitPos - 16;
					bitPos = bitPos *2;
					LPC_PINCON->PINMODE2 = pinModeSetUp<<bitPos;
				}
				break;
				
		case 2:
				if(bitPos < 14) {
					bitPos = bitPos * 2;
					LPC_PINCON->PINMODE4 = pinModeSetUp<<bitPos;
				}
				break;
				
		case 3:
				if(bitPos == 25) {
					LPC_PINCON->PINMODE0 = pinModeSetUp<<18;
				}
				else if(bitPos == 26) {
					LPC_PINCON->PINMODE0 = pinModeSetUp<<20;
				}
				break;
				
		case 4:
				if(bitPos == 28)	{
					LPC_PINCON->PINMODE0 = pinModeSetUp<<24;
				}
				else if(bitPos == 29) {
					LPC_PINCON->PINMODE0 = pinModeSetUp<<26;
				}
				break;
				
		default:
				break;
				
	}
}

/*pinModeSetUp = 0 : portNum.bitPos in the normal(not open drain) mode
	pinModeSetUP = 1 : portNum.bitPos in the open drain mode							*/
void PinModeOpenDrainConfig(uint32_t pinModeSetUp,uint8_t portNum, uint32_t bitPos)	{
	
	switch(portNum)	{
		case 0:
				if(bitPos != (12 | 13 | 14 | 27 | 28 | 31))	{
					LPC_PINCON->PINMODE_OD0 = pinModeSetUp<<bitPos;
				}
				break;
			
		case 1:
				if(bitPos != (2 | 3 | 5 | 6 | 7 | 11 | 12 | 13))	{
					LPC_PINCON->PINMODE_OD1 = pinModeSetUp<<bitPos;
				}
				break;
			
		case 2:
				if(bitPos < 14)	{
					LPC_PINCON->PINMODE_OD2 = pinModeSetUp<<bitPos;
				}
				break;
			
		case 3:
				if(bitPos == 25) {
					LPC_PINCON->PINMODE_OD3 = pinModeSetUp<<bitPos;
				}
				else if(bitPos == 26)
				{
					LPC_PINCON->PINMODE_OD3 = pinModeSetUp<<bitPos;
				}
				break;
				
		case 4:
				if(bitPos == 28) {
					LPC_PINCON->PINMODE_OD4 = pinModeSetUp<<bitPos;
				}
				else if(bitPos == 29)
				{
					LPC_PINCON->PINMODE_OD4 = pinModeSetUp<<bitPos;
				}
				break;
	}
}

//Read value of portNum.bitPos
uint32_t GPIO::Read(uint8_t portNum, uint32_t bitPos)
{
    uint32_t val;
    LPC_GPIO[portNum]->FIOMASK = ~(1<<bitPos);
    val = LPC_GPIO[portNum]->FIOPIN;
    val = val >> bitPos;
    return val;
}