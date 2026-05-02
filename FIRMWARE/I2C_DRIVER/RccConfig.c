#include "stm32f10x.h"


void SysClockConfig(void){
	
	//enable HSE and wait for HSE to be ready 
	RCC-> CR |= RCC_CR_HSEON ;
  while(!(RCC->CR & RCC_CR_HSERDY)) ;
	//set the powr enable clock and VR 
	RCC-> APB1ENR |= RCC_APB1ENR_PWREN ;
	//config the flash prefetch and the latency 
	FLASH-> ACR= FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_2 ;
	// the prescalers 
	//AHB
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	//APB1
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
	//APB2
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
	
   // Configure the PLL: Source = HSE, Multiplier = x9
  RCC->CFGR |= RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9;
	// 6. Turn on the PLL and wait for it to be ready
   RCC->CR |= RCC_CR_PLLON ;
	 while(!(RCC->CR & RCC_CR_PLLRDY));
	// 7. Switch the System Clock to the PLL
	 RCC->CFGR |= RCC_CFGR_SW_PLL ;
	 //8. Wait until the system confirms the clock has switched successfully
	 while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}