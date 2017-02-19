#include "lpc17xx_ssp.h"
#include "lpc_types.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include <LPC17xx.h>
//#include "debug_frmwrk.h"
#include "lpc17xx_gpio.h"


/* Example group ----------------------------------------------------------- */
//Variables
volatile unsigned long SysTickCnt;
const uint8_t BUFFER_SIZE = 16;
volatile unsigned int i =0;
const uint32_t LE = (1<<19);				//P0.19 as LatchEnable
const uint32_t OE = (1<<20);				//P0.20 as OutputEnable

//Functions
void SysTick_Handler (void);
void _delayus(unsigned long tick);
int entry(void);



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
	SSP_ConfigStruct.Databit = SSP_DATABIT_16;
	SSP_ConfigStruct.Mode = 0;
	SSP_ConfigStruct.FrameFormat = 0;
	SSP_ConfigStruct.ClockRate = 125000000;
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
	
	
	
//	SSP_SendData(LPC_SSP0, 0xFF00);
//	_delayus(5);
//	
//	//Turning on Latch
//	GPIO_SetValue(1, LE);
//	_delayus(15);
//	GPIO_ClearValue(1, LE);
//	
//	//OutputEnable
//	GPIO_ClearValue(1, OE);
//	_delayus(100);
//	GPIO_SetValue(1, OE);
//	i++;
//	return i;
}

void send(uint16_t data1)	{
	uint16_t data= data1;
	SSP_SendData(LPC_SSP0, data);
	_delayus(5);

	//Turning on Latch
	GPIO_SetValue(0, LE);
	_delayus(15);
	GPIO_ClearValue(0, LE);
	
	//OutputEnable
	GPIO_ClearValue(0, OE);
	_delayus(100);
	GPIO_SetValue(0, OE);
}


int main(void)	{
	uint16_t data;
	uint32_t i=0;
	ssp_entry();
	while(1<100)	{
//		_delayus(10000000);
		send(data);
		i++;
		data=data+i;
	
	}
}

