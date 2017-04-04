#include "lpc17xx_ssp.h"
#include "lpc_types.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "LPC17xx.h"
#include "lpc17xx_gpio.h"
#include "string.h"

//Variables
volatile unsigned long SysTickCnt;
volatile unsigned int i =0;
const uint32_t LE = (1<<19);				//P0.19 as LatchEnable
const uint32_t OE = (1<<20);				//P0.20 as OutputEnable

//NUMBER MAPPING
const uint8_t numbers[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};
const uint8_t numberOfDigits = 12;
uint8_t buffer[numberOfDigits];


//Functions
void SysTick_Handler (void);
void _delayus(unsigned long tick);
void addToBuffer(long long int digit);
void writeToBuffer();
void shiftOut(uint8_t shiftData);



void SysTick_Handler (void) {
  SysTickCnt++;
}


void _delayus (unsigned long tick) {
  unsigned long systickcnt;

  systickcnt = SysTickCnt;
  while ((SysTickCnt - systickcnt) < tick);
}


void ssp_entry(void)	{
	PINSEL_CFG_Type PinCfg;
	
	SSP_CFG_Type SSP_ConfigStruct;
	
	SysTick_Config(SystemCoreClock/1000000 - 1); /* Generate interrupt each 1 us   */
	/*
	 * Initialize SPI pin connect
	 * P0.15 - SCK;			SCK
	 * P0.16 - SSEL			no need
	 * P0.17 - MISO			no need
	 * P0.18 - MOSI			SI
	 * P0.19 - SDA     As LatchDisable LD
	 * P0.20 - SCL		 As OutputEnable OE
	 */
	//Initializing SSP SCK and MOSI
	PinCfg.Pinmode = 0;			//Internal Pullup, 2 Tristate , 3 internal pull-down
	PinCfg.OpenDrain = 0;
	PinCfg.Funcnum = 2;			//may be 3 try it
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 15;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 18;
	PINSEL_ConfigPin(&PinCfg);
	

	
	//Initizing SSP
	SSP_ConfigStruct.Databit = SSP_DATABIT_8;
	SSP_ConfigStruct.Mode = 0;
	SSP_ConfigStruct.FrameFormat = 0;
	SSP_ConfigStruct.ClockRate = 1000000;
	SSP_ConfigStruct.CPHA = 0;					//0
	SSP_ConfigStruct.CPOL =0 ;						//0
	SSP_Init(LPC_SSP0, &SSP_ConfigStruct);
	

		//Setting up LatchDisable and OutputEnable
	GPIO_SetDir(0, LE, 1);
	GPIO_SetDir(0, OE, 1);
	GPIO_ClearValue(0, LE);
	GPIO_SetValue(0, OE);


	// Enable SSP peripheral
	SSP_Cmd(LPC_SSP0, ENABLE);

}

void addToBuffer(long long digit) {
	uint8_t i =0;
	uint8_t num =0;
	
	//clear  buffer
	memset(buffer, 0 , sizeof(buffer));
	
	while(digit > 0 ) {
		num = numbers[digit % 10];
		buffer[i] = num;
		digit = digit / 10;
		i++;
	}
	writeToBuffer();	
}

void writeToBuffer() {
	int i=0;
//	GPIO_SetValue(0, OE);
	
	
	for (i = sizeof(buffer)-1; i>=0 ; i--) {
		_delayus(20);
		shiftOut(buffer[i]);
	}
	//Turning on Latch
	_delayus(10);
	GPIO_SetValue(0, LE);
	_delayus(60);
	GPIO_ClearValue(0, LE);
		//OutputEnable
//	_delayus(10);
	GPIO_ClearValue(0, OE);
	

	
}
void shiftOut(uint8_t shiftData) {
//	GPIO_SetValue(0, OE);
//	_delayus(1000);
	LPC_SSP0->DR = shiftData;
//	LPC_SSP0->DR = shiftData;
	while(!(LPC_SSP0->SR & (1<<2)));
	
}



int main(void)	{
	int i=0;
	ssp_entry();
		
	
	while(1)	{
//	addToBuffer(i);
//		i=i+99999;
//		
addToBuffer(i);
		_delayus(1000);
		i++;


	}
}
