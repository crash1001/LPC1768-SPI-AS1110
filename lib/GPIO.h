#ifndef __GPIO_H
#define __GPIO_H

#ifdef __cplusplus
extern "C"
{
#endif
	
	
static LPC_GPIO_TypeDef (* const LPC_GPIO[5]) = { LPC_GPIO0, LPC_GPIO1, LPC_GPIO2, LPC_GPIO3, LPC_GPIO4 };

class GPIO
{
	private:
		uint32_t portNumber;
		uint32_t bitPosition;
		
	
	public:
		GPIO();
		// portNum.bitPos becomes high
		void setValue(uint8_t portNum, uint32_t bitPos);	
	
		//portNum.bitPos becomes low
		void clearValue(uint8_t portNum, uint32_t bitPos);		
		
		//portNum.bitPos 
		void setDirection(uint8_t portNum, uint32_t bitPos, uint8_t direction);
	
//		//portNum.bitPos becomes an input pin
//		void Input(uint32_t portNum, uint32_t bitPos);			

//		//portNum.bitPos becomes an output pin
//		void Output(uint32_t portNum, uint32_t bitPos);		

		//Read value of portNum.bitPos
		uint32_t Read(uint8_t portNum, uint32_t bitPos);
	
		/*pinModeSelect = 0 :  00 portNum.bitPos has a pull-up resistor enabled
		pinModeSelect = 1 :  01 portNum.bitPos has a pull-down resistor enabled
		pinModeSelect = 2 :	 10 portNum.bitPos has neither pull-up nor pull-down enabled
		pinModeSelect = default*/
		void PinModeConfig(uint8_t pinModeSelect,uint8_t portNum, uint32_t bitPos);
		
		/*pinModeSetUp = 0 : portNum.bitPos in the normal(not open drain) mode
		pinModeSetUP = 1 : portNum.bitPos in the open drain mode							*/
		void PinModeOpenDrainConfig(uint8_t portNum, uint32_t bitPos);

};



#ifdef __cplusplus
}
#endif

#endif