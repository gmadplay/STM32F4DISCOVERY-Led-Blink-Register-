#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int count = 0;

delay(uint32_t timer){
	while(timer--);

}
void RCC_Config(void){

	/// 168 mHz olarak ayarlayacaðýz.

	RCC->CR &= ~(1 << 0);                     // Burada dahili osilatörü kapatýyorum. {~} Bu tersleme iþaretidir.
	RCC->CR |= 1 << 16; // 16. Bite 1 yazýyorum ve external osilatörü açýyorum.
	while((!(RCC->CR & 1<<17))); // burada flagin 1lenmesini bekliyorum. Bu beklemeyi yapmazsam açýldý zannedip açmadan kodlarýma devam edebilir
	RCC ->CR |= 1 << 19; // CLOCK GÜVENLÝÐÝNÝ AÇIYORUM
//	RCC ->PLLCFGR &= ~(1 << 0); // PL M0 BÝTÝNÝ 0 YAPMIÞ OLDUK // BU VE ALTTAKÝ ADIMLAR SAYESÝNDE BÖLME ORANI 4 OLARAK AYARLANDI.
//	RCC ->PLLCFGR &= ~(1 << 1); // PL M1 BÝTÝNÝ 0 YAPMIÞ OLDUK
//	RCC ->PLLCFGR |= ~(1 << 2); // PL M2 BÝTÝNÝ 1 YAPMIÞ OLDUK
//	RCC ->PLLCFGR &= ~(1 << 3); // PL M3 BÝTÝNÝ 0 YAPMIÞ OLDUK
//	RCC ->PLLCFGR &= ~(1 << 4); // PL M4 BÝTÝNÝ 0 YAPMIÞ OLDUK
//	RCC ->PLLCFGR &= ~(1 << 5); // PL M5 BÝTÝNÝ 0 YAPMIÞ OLDUK

// Bu üstteki gösterim zor olan gösterimdi bunu aþaðýdaki gibi 168 << 6 þeklinde yazmak daha basit olur.


	RCC->PLLCFGR  = 0x00000000;               //Tüm deðerler 0lanýyor.
	RCC -> PLLCFGR |= (1 << 22); // PLL SOURCE HSE
    RCC -> PLLCFGR |= (4<<0);
	RCC -> PLLCFGR |= (168 << 6); // PLL N DEÐERÝ 168 OLARAK AYARLANMIÞ OLDU
    RCC -> CR|= (1 << 24); // PL ON
	while((!(RCC->CR & 1<<25))); // PLLin aktif olmasýný bekliyorum.
	RCC -> CFGR &= ~(1 << 0);
	RCC -> CFGR |= 1 << 1;           // SYSTEM CLOCK PLL OLARAK AYARLANDI.

	while((!(RCC->CFGR & (1<<1)))); // SYSTEM CLOCK PLL CLOK OLARAK AYARLANDI MI AYARLANMADI MI SORGUSU

}

void GPIO_Config(){
    RCC-> AHB1ENR |= (1<<0);


	RCC->AHB1ENR |= 1 << 3; //GPIOD CLOCK ENABLE
	GPIOD->MODER |= 1 << 24; //GPIOD NIN 12. PÝNÝ OUTPUT OLDU BU ÝKÝ KOMUT ÝÇÝN
	GPIOD->MODER &= ~(1 << 25);

	GPIOD->MODER |= 1 << 26; //GPIOD NIN 13. PÝNÝ OUTPUT OLDU BU ÝKÝ KOMUT ÝÇÝN
	GPIOD->MODER &= ~(1 << 27);

	GPIOD->MODER |= 1 << 28; //GPIOD NIN 14. PÝNÝ OUTPUT OLDU BU ÝKÝ KOMUT ÝÇÝN
	GPIOD->MODER &= ~(1 << 29);

	GPIOD->MODER |= 1 << 30; //GPIOD NIN 15. PÝNÝ OUTPUT OLDU BU ÝKÝ KOMUT ÝÇÝN
	GPIOD->MODER &= ~(1 << 31);

	GPIOD->OSPEEDR |= 0xFF000000;
}
int main(void)
{
RCC_Config();
SystemCoreClockUpdate();
GPIO_Config();

  while (1)
  {
	  if(GPIOA->IDR & 0x00000001){
		  while(GPIOA->IDR & 0x00000001);
		  delay(1680000);
		  count ++;
	  }
	  if(count == 1){
		  GPIOD->ODR |= 1<<12;

	  }else if(count == 2){
		  GPIOD->ODR |= 1<<13;
	  }else if(count == 3){
		  GPIOD->ODR |= 1<<14;
	  }else if(count == 4){
		  GPIOD->ODR |= 1<<15;
	  }else if(count >4){
		  GPIOD->ODR = 0x00000000;
		  count = 0;
	  }




  }
}



void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
