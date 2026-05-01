#include "stm32f10x.h"
#include "Delay_F103.h"

 void GPIO_Config_Clock(void){
	 RCC->APB2ENR|=(1<<4);
	 GPIOC->CRH |=(1<<20);

}
int main(){
	SystemInit(); 
  GPIO_Config_Clock();
	TIM2_Config ();
	
	while(1){
    GPIOC->BSRR |=(1<<13);
		Delay_ms(1000);
		GPIOC-> BSRR |=(1<<29);
    Delay_ms(1000);

}



}
