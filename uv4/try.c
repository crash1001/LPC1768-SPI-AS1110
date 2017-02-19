//#include<LPC17xx.h>

//#define MOSI (1<<18)
//#define MISO (1<<17)
//#define SCK (1<<15)
//#define SSEL (1<<16)

////SPI CONTRL REGISTER S0SPCR control function of SPI block

////SPI STATUS REGUSTER S0SPSR monitor SPI interface, normal functions, and exception condtions  
////	detect completion of data transfer->SPI interrupt Flagg (PIF) uin S0SPINT registers

////SPI Data Register(S0SPDR) is used to provide the transmit and recieve data bytes. No write buffer, a write to the data register goes directly
////into the internal shift register. Read data is buffered.

////SPI Clock Counter Register(S0SPCCR) control clock rate when the SPI block is master mode

////Prior to use, SPI configurations such as the master/slave settings, clock polarity, clock
////rate, etc. must be set up in the SPI Control Register and SPI Clock Counter Register.

////Master operation
////1. Set the SPI Clock Counter Register to the desired clock rate.
////2. Set the SPI Control Register to the desired settings for master mode

//void SPI_init() {
//	
//	LPC_SC->PCONP |= 1 <<21; //re-enable POWER to SSP0-SPI if required
//	LPC_SC->PCLKSEL1 |= 1<<10; //pclk = cclk
//	LPC_SSP0->CPSR |= 8; //internal divide
//	
//	LPC_PINCON->PINSEL0 |= 0x80000000;	//Pin P0.15 allocated to function 3 SCLK
//	LPC_PINCON->PINSEL1 |= 0x02<<0;	//Pin P0.16 allocated to function 3 NSS/SSEL
//	LPC_PINCON->PINSEL1 |= 0x02<<2;	//Pin P0.17 allocated to function 3 MISO
//	LPC_PINCON->PINSEL1 |= 0x02<<4;	//Pin P0.18 allocated to function 3 MOSI
//		
//	//Add GPIO pins for LE,OEN
//	 LPC_SSP0->CR0 |= (0<<6);	//CPOL
//	 LPC_SSP0->CR0 |= (0<<7);	//CPHA
//	
//	LPC_SSP0->CR0 &= ~(15<<0);	//Masking 0:3 bits
//	LPC_SSP0->CR0 |= (15<<0);	//16 bits transfer
//	
//	LPC_SSP0->CR0 &= ~(3<<4);		//Masking 4,5 bits
//	LPC_SSP0->CR0 |= (00<<4);		//Frame Formate SPI
//	
//	 	
//	LPC_SSP0->CR1 |= 1<<1;	//enable SSP
//	
//	LPC_GPIO0->FIODIR |= (1<<23);	//make output
//	  
//	
//	  
//	  
//	 
//}

//void SPI_send(char mo){
//	  	LPC_GPIO0->FIOCLR = 1<<23;
//		LPC_SSP0->DR = mo;
//		while(!(LPC_SSP0->SR & (1<<2)));
//	  LPC_GPIO0->FIOSET = 1<<23;
//		
//}
//int main()
//{
//	SPI_init();
//	SPI_send(0xFF);
//}

