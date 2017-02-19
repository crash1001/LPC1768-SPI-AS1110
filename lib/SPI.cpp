#include <LPC17xx.h>
#include "GPIO.h"
#include "SPI.h"
static LPC_SSP_TypeDef (* const LPC_SSP[2]) = { LPC_SSP0, LPC_SSP1};
	
void SSP_Init(uint8_t portNum)	{
	
	LPC_SC->PCONP |= 1 <<21; //re-enable POWER to SSP0-SPI if required
	LPC_SC->PCLKSEL1 |= 1<<10; //pclk = cclk
	LPC_SSP0->CPSR |= 8; //internal divide
	
	LPC_PINCON->PINSEL0 |= 0x80000000;	//Pin P0.15 allocated to function 3 SCLK
	LPC_PINCON->PINSEL1 |= 0x02<<0;	//Pin P0.16 allocated to function 3 NSS/SSEL
	LPC_PINCON->PINSEL1 |= 0x02<<2;	//Pin P0.17 allocated to function 3 MISO
	LPC_PINCON->PINSEL1 |= 0x02<<4;	//Pin P0.18 allocated to function 3 MOSI
		
	//Add GPIO pins for LE,OEN
	 LPC_SSP0->CR0 |= (0<<6);	//CPOL
	 LPC_SSP0->CR0 |= (0<<7);	//CPHA
	
	LPC_SSP0->CR0 &= ~(15<<0);	//Masking 0:3 bits
	LPC_SSP0->CR0 |= (15<<0);	//16 bits transfer
	
	LPC_SSP0->CR0 &= ~(3<<4);		//Masking 4,5 bits
	LPC_SSP0->CR0 |= (00<<4);		//Frame Formate SPI
	
	LPC_SSP0->CR1 |=  (0<<2);	//enable master mode 	
	LPC_SSP0->CR1 |= (1<<1);	//enable SSP
}

void SSPInit(uint8_t portNum, SSP_CFG_Type *SSP_ConfigStruct)	{
	uint32_t tmp;
	if(portNum == 0) {				
			
	}
	
	else if(portNum == 1) {
	}
	else {
		return;
	}
	
}