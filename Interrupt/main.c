

#include "stm32f10x.h"                  // Device header


void EXTI_basla(void);
void buton_led_ayari(void);

uint8_t durum=0; 


void  EXTI0_IRQHandler()
{
	 
	if(EXTI->PR & (1<<0))
	{
		while(GPIOB->IDR & (1<<0));//Butona basili kaldigi surece burada kal.
		durum++;
		EXTI->PR = 0x00000001;//Temizleme.
		
	}

	

}

int main()
{

	
	buton_led_ayari();
	EXTI_basla();
 
	while(1)
	{
		
	  if(durum==1)
			GPIOA->BRR =1<<1;//A1 yak
		if(durum==2)
		{
			GPIOA->BSRR=1<<1;//A1 sondur.
			durum=0;
		}
			
	
	}
 


}

void buton_led_ayari()
{
	RCC->APB2ENR |=1<<2;//A portu aktif.  
	RCC->APB2ENR |=1<<3;//B portu aktif.
	
	//Buton ve led ayarlari
	GPIOA->CRL =0;//A portu temizlendi.
	GPIOA->CRL =0x00000020;//A1 output.
	GPIOA->BSRR=1<<1;//A1 sondur.
	
	GPIOB->CRL =0;//B portu temizlendi.
	GPIOB->CRL  |=0x00000008;//A0 input.
	
	
}

void EXTI_basla()
{
	RCC->APB2ENR |=1<<0;//AFIO aktif.
	EXTI->IMR |=1<<0;//Interrupt istegi.
  EXTI->RTSR |=1<<0;//Yükselen modu.
	AFIO->EXTICR[0]=0x00000001;//PB0 için interrupt.
	NVIC->ISER[0] |=1<<6;//EXTI0 AKTIF.
	
	
}

