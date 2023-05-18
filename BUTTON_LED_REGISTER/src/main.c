#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int count = 0;

delay(uint32_t timer){
	while(timer--);

}
void RCC_Config(void){

	/// 168 mHz olarak ayarlayaca��z.

	RCC->CR &= ~(1 << 0);                     // Burada dahili osilat�r� kapat�yorum. {~} Bu tersleme i�aretidir.
	RCC->CR |= 1 << 16; // 16. Bite 1 yaz�yorum ve external osilat�r� a��yorum.
	while((!(RCC->CR & 1<<17))); // burada flagin 1lenmesini bekliyorum. Bu beklemeyi yapmazsam a��ld� zannedip a�madan kodlar�ma devam edebilir
	RCC ->CR |= 1 << 19; // CLOCK G�VENL���N� A�IYORUM
//	RCC ->PLLCFGR &= ~(1 << 0); // PL M0 B�T�N� 0 YAPMI� OLDUK // BU VE ALTTAK� ADIMLAR SAYES�NDE B�LME ORANI 4 OLARAK AYARLANDI.
//	RCC ->PLLCFGR &= ~(1 << 1); // PL M1 B�T�N� 0 YAPMI� OLDUK
//	RCC ->PLLCFGR |= ~(1 << 2); // PL M2 B�T�N� 1 YAPMI� OLDUK
//	RCC ->PLLCFGR &= ~(1 << 3); // PL M3 B�T�N� 0 YAPMI� OLDUK
//	RCC ->PLLCFGR &= ~(1 << 4); // PL M4 B�T�N� 0 YAPMI� OLDUK
//	RCC ->PLLCFGR &= ~(1 << 5); // PL M5 B�T�N� 0 YAPMI� OLDUK

// Bu �stteki g�sterim zor olan g�sterimdi bunu a�a��daki gibi 168 << 6 �eklinde yazmak daha basit olur.


	RCC->PLLCFGR  = 0x00000000;               //T�m de�erler 0lan�yor.
	RCC -> PLLCFGR |= (1 << 22); // PLL SOURCE HSE
    RCC -> PLLCFGR |= (4<<0);
	RCC -> PLLCFGR |= (168 << 6); // PLL N DE�ER� 168 OLARAK AYARLANMI� OLDU
    RCC -> CR|= (1 << 24); // PL ON
	while((!(RCC->CR & 1<<25))); // PLLin aktif olmas�n� bekliyorum.
	RCC -> CFGR &= ~(1 << 0);
	RCC -> CFGR |= 1 << 1;           // SYSTEM CLOCK PLL OLARAK AYARLANDI.

	while((!(RCC->CFGR & (1<<1)))); // SYSTEM CLOCK PLL CLOK OLARAK AYARLANDI MI AYARLANMADI MI SORGUSU

}

void GPIO_Config(){
    RCC-> AHB1ENR |= (1<<0);


	RCC->AHB1ENR |= 1 << 3; //GPIOD CLOCK ENABLE
	GPIOD->MODER |= 1 << 24; //GPIOD NIN 12. P�N� OUTPUT OLDU BU �K� KOMUT ���N
	GPIOD->MODER &= ~(1 << 25);

	GPIOD->MODER |= 1 << 26; //GPIOD NIN 13. P�N� OUTPUT OLDU BU �K� KOMUT ���N
	GPIOD->MODER &= ~(1 << 27);

	GPIOD->MODER |= 1 << 28; //GPIOD NIN 14. P�N� OUTPUT OLDU BU �K� KOMUT ���N
	GPIOD->MODER &= ~(1 << 29);

	GPIOD->MODER |= 1 << 30; //GPIOD NIN 15. P�N� OUTPUT OLDU BU �K� KOMUT ���N
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
