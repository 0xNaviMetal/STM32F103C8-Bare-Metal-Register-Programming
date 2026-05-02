#include "stm32f10x.h"
#include "Delay_F103.h"
#include "RccConfig.h"

void I2C_Config(void){
	/**** STEPS FOLLOWED  ************
1. Enable the I2C CLOCK and GPIO CLOCK
2. Configure the I2C PINs for ALternate Functions
	a) Select Alternate Function in MODER Register
	b) Select Open Drain Output ,  Select SPEED for the PINs
	 
3. Reset the I2C 	
4. Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
5. Configure the clock control registers
6. Configure the rise time register
7. Program the I2C_CR1 register to enable the peripheral
*/
  RCC->APB1ENR |=(1<<21);
 	
	RCC->APB2ENR |= (1<<3);
	
  GPIOB->CRL &= ~((0xF << 24)|(0xF << 28)); 
  GPIOB->CRL |= (0xF << 24)|(0xF << 28);
	
	//reset the I2C
	I2C1->CR1 |=(1<<15);
	I2C1->CR1 &=~(1<<15);
	
	I2C1->CR2 |=(36<<0);
   
	 //configure the clock control register 
   I2C1->CCR = 180<<0;
	 
	 //the rise time ;
	 I2C1->TRISE =37;
    
		//enable the regester 
		I2C1->CR1 |=(1<<0);
		

}
 void I2c_Start(void){
//1. Enable the ACK
//2. Send the START condition 
//3. Wait for the SB ( Bit 0 in SR1) to set. This indicates that the start condition is generated
       //ACK
	  I2C1->CR1 |= (1<<10);
    I2C1->CR1 |= (1<<8);
   while (!(I2C1->SR1 & (1<<0))); 
	 
}
void I2C_write(uint8_t adress , uint8_t data){
	//SEND ADDRESS & WAIT FOR EV6
	I2C1->DR = adress;
	
	while(!(I2C1->SR1 & (1<<1)));
	//Clear EV6 by reading SR1 then SR2
	uint32_t temp = I2C1->SR1;
temp = I2C1->SR2;
(void)temp;
	 
  //SEND DATA & WAIT FOR EV8
	while(!(I2C1->SR1 & (1<<7)));
	 I2C1->DR = data ;
	while(!(I2C1->SR1 & (1<<2)));
	
}
void I2C_Stop(void){

	I2C1->CR1 |=(1<<9);
}


void I2C_WriteMulti(uint8_t *data, uint8_t size) {
    // 1. Wait for the TXE (bit 7 in SR1) to set. This indicates that the DR is empty
    while (!(I2C1->SR1 & (1<<7))); 
    
    // 2. Keep Sending DATA to the DR Register after performing the check if the TXE bit is set
    while (size) {
        while (!(I2C1->SR1 & (1<<7)));            // wait for TXE bit to set
        I2C1->DR = (volatile uint32_t )*data++;   // send data and move pointer forward
        size--;                                   // decrement the size counter
    }
    
    // 3. Once the DATA transfer is complete, Wait for the BTF (bit 2 in SR1) to set. 
    // This indicates the end of LAST DATA transmission
    while (!(I2C1->SR1 & (1<<2))); 
}

int main (void){
	SysClockConfig();
  TIM2_Config();
	I2C_Config();
	I2c_Start();
	I2C_write(0x76 << 1,0X0F);
	I2C_Stop();
   while(1){
 
 
  
 
 
 
 
 
 
 }










}