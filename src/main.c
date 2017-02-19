
#include<LPC17xx.h>


//SPI CONTRL REGISTER S0SPCR control function of SPI block

//SPI STATUS REGUSTER S0SPSR monitor SPI interface, normal functions, and exception condtions  
//	detect completion of data transfer->SPI interrupt Flagg (PIF) uin S0SPINT registers

//SPI Data Register(S0SPDR) is used to provide the transmit and recieve data bytes. No write buffer, a write to the data register goes directly
//into the internal shift register. Read data is buffered.

//SPI Clock Counter Register(S0SPCCR) control clock rate when the SPI block is master mode

//Prior to use, SPI configurations such as the master/slave settings, clock polarity, clock
//rate, etc. must be set up in the SPI Control Register and SPI Clock Counter Register.

//Master operation
//1. Set the SPI Clock Counter Register to the desired clock rate.
//2. Set the SPI Control Register to the desired settings for master mode

volatile uint32_t msTicks;	/* counts 1ms timeTicks */

void SysTick_Handler(void)
{
	msTicks++;	/* increment counter necessary in Delay() */
}

__inline static void _delay_ms(uint32_t del)
{
	uint32_t curTicks;
	curTicks = msTicks;

	while ((msTicks - curTicks) < del)
	{
		
	}
}
void SPI_init() {
	
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

void controlSignalInitialize(void) {
	//0.19 0.20
	LPC_GPIO0->FIODIR |= 1<<19;
	LPC_GPIO0->FIODIR |= 1<<20;
//	LPC_PINCON->PINSEL1 |= (0x00<19);
//	LPC_GPIO0->FIODIR0 &= ~(2<<19);
//	LPC_GPIO0->FIODIR0 |= (0x3<<19);	//latch enable low enable after data is sent
//	LPC_GPIO0->FIODIR |= (1<<20);  //output enable disable after Latch
	LPC_GPIO0->FIOCLR |= (1<<19);
	LPC_GPIO0->FIOSET |= (1<<20);
}

void latchEnable(int val) {
	if (!val) LPC_GPIO0->FIOCLR |= (1<<19);
	else LPC_GPIO0->FIOSET |= (1<<19);
}

void outputEnable(int val) {
	if (val) LPC_GPIO0->FIOSET |= (1<<20);
	else LPC_GPIO0->FIOCLR |= (1<<20);
}

void SPI_send(uint16_t value){
	  
		LPC_SSP0->DR = value;
		while(!(LPC_SSP0->SR & (1<<2)));
	  
//		LPC_GPIO0->FIOSET0 |= (1<<19);
//		for(i=0; i<1000;i++)
//		{
//				for(j=0; j<1000; j++){}
//		}
////		_delay_ms(10000);
//	  LPC_GPIO0->FIOCLR0 |= (1<<19);
//	  
//	  LPC_GPIO0->FIOCLR0 |= (1<<20);
////		_delay_ms(10000);
//		for(i=0; i<5000;i++)
//		{
//				for(j=0; j<5000; j++){}
//			
//		}
//		LPC_GPIO0->FIOSET0 |= (1<<20);
	
}
int main()
{
	int i;
//	SystemInit();
	SysTick_Config((SystemCoreClock / 1000000)-1);
	controlSignalInitialize();
	SPI_init();
	

	
	
//	for(i=0;i<500000;i++)
	{
	SPI_send(0xFF00);
		_delay_ms(2);
	latchEnable(1);
//	_delay_ms(1);
//	for(i=0; i<1000;i++)
//		{
//				for(j=0; j<1000; j++);
//		}
	
//	latchEnable(0);
	outputEnable(0);
//	_delay_ms(3);
//	for(i=0; i<1000;i++)
//		{
//				for(j=0; j<1000000; j++){}
//		}
//	outputEnable(1);	
	}
}