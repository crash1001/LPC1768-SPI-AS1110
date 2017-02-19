//#include <LPC17xx.h>

//void	Init() {
//LPC_SC->PCONP |= 1 <<21;	//enable POWER to SSP0 (redundant following reset)
//LPC_SC->PCLKSEL1 |= 1<<10;	//pclk = cclk
//LPC_SSP0->CPSR |= 8;	//internal divider
//LPC_PINCON->PINSEL0 |= 0x80000000;	//Pin P0.15 allocated to function 3 SCLK
//LPC_PINCON->PINSEL1 |= 0x02<<0;	//Pin P0.16 allocated to function 3 NSS/SSEL
//LPC_PINCON->PINSEL1 |= 0x02<<2;	//Pin P0.17 allocated to function 3 MISO
//LPC_PINCON->PINSEL1 |= 0x02<<4;	//Pin P0.18 allocated to function 3 MOSI
//LPC_SSP0->CR0 |= 3<<6;	//clock phase
//LPC_SSP0->CR0 |= 7<<0;	// 8 bits
//LPC_SSP0->CR1 |= 1<<1;	//enable SSP
//LPC_GPIO0->FIODIR |= (1<<23);	//make output
//}

//char	spi_tfr(char mo) {
//LPC_GPIO0->FIOCLR = 1<<23;	//select slave
//LPC_SSP0->DR = mo;
//while (!(LPC_SSP0->SR & (1<<2)));
//LPC_GPIO0->FIOSET = 1<<23;	//release slave
//return (LPC_SSP0->DR);
//}
//int	main () {
//			char mi;
//			Init();
//			
//			while(1) {
//			mi = spi_tfr(0x5A);
//			}
//}