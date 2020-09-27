#include "main.h"
#include "stm32f1xx.h"
#include "stm32f103xb.h"
#include "RCCinit.h"
#include "TimerInit.h"


char DownOn = 0;
char UpON = 0;
char Resetlite = 0;

char Status = 0;
int SpeedLite = 10;         // Скорость зажигания
int SmoothnessLite = 900;	// Плавность зажигания
int Step = 6;				// Количество ступенек
int MaxLite = 1000;			// Максимальная яркость
int MaxLiteDuti = 200;		// Дежурная яркость

int StepValue[12];			// Ххранение значения яркости ступенек

//Настройка портов
void PortInit(void)
{
	//APB2
	  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;    // Включение тактирования PC
	  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;    // Включаем тактирование PA
	  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;	 //Включаю тактирование РВ
	  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;    // Тактирование альтернативных функций GPIO
	  //RCC->APB2ENR |= RCC_APB2ENR_USART1EN;  // Тактирование модуля USART1
	  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   // Включить тактирование  TIM2

	  // Тактирование  GPIOA , TIM1, альтернативных функций порта
	  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_TIM1EN | RCC_APB2ENR_AFIOEN;
	  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN |RCC_APB1ENR_TIM3EN |RCC_APB1ENR_TIM4EN;


	  // Светодиод на плате
	  GPIOC->CRH |= GPIO_CRH_MODE13_1;      // выход максимально 50mhz
	  GPIOC->CRH |= GPIO_CRH_MODE13_0;

	  GPIOC->CRH &=~ GPIO_CRH_CNF13_1;		// настройка на выход порта С13
	  GPIOC->CRH &=~ GPIO_CRH_CNF13_0;

	  // Настройка выводов под ШИМ
	  // TIM1

	  GPIOA->CRH &= ~GPIO_CRH_CNF8;
	  GPIOA->CRH |= GPIO_CRH_CNF8_1;
	  GPIOA->CRH &= ~GPIO_CRH_MODE8;
	  GPIOA->CRH |= GPIO_CRH_MODE8_1;

	  GPIOA->CRH &= ~GPIO_CRH_CNF9;
	  GPIOA->CRH |= GPIO_CRH_CNF9_1;
	  GPIOA->CRH &= ~GPIO_CRH_MODE9;
	  GPIOA->CRH |= GPIO_CRH_MODE9_1;

	  GPIOA->CRH &= ~GPIO_CRH_CNF10;
	  GPIOA->CRH |= GPIO_CRH_CNF10_1;
	  GPIOA->CRH &= ~GPIO_CRH_MODE10;
	  GPIOA->CRH |= GPIO_CRH_MODE10_1;

	  GPIOA->CRH &= ~GPIO_CRH_CNF11;
	  GPIOA->CRH |= GPIO_CRH_CNF11_1;
	  GPIOA->CRH &= ~GPIO_CRH_MODE11;
	  GPIOA->CRH |= GPIO_CRH_MODE11_1;

	  //настрока выводов под шим TIM2

	  GPIOA->CRL &= ~GPIO_CRL_CNF0;
	  GPIOA->CRL |= GPIO_CRL_CNF0_1;
	  GPIOA->CRL &= ~GPIO_CRL_MODE0;
	  GPIOA->CRL |= GPIO_CRL_MODE0_1;

	  GPIOA->CRL &= ~GPIO_CRL_CNF1;
	  GPIOA->CRL |= GPIO_CRL_CNF1_1;
	  GPIOA->CRL &= ~GPIO_CRL_MODE1;
	  GPIOA->CRL |= GPIO_CRL_MODE1_1;

	  GPIOA->CRL &= ~GPIO_CRL_CNF2;
	  GPIOA->CRL |= GPIO_CRL_CNF2_1;
	  GPIOA->CRL &= ~GPIO_CRL_MODE2;
	  GPIOA->CRL |= GPIO_CRL_MODE2_1;

	  GPIOA->CRL &= ~GPIO_CRL_CNF3;
	  GPIOA->CRL |= GPIO_CRL_CNF3_1;
	  GPIOA->CRL &= ~GPIO_CRL_MODE3;
	  GPIOA->CRL |= GPIO_CRL_MODE3_1;

	  //настрока выводов TIM3

	  GPIOA->CRL &= ~GPIO_CRL_CNF6;
	  GPIOA->CRL |= GPIO_CRL_CNF6_1;
	  GPIOA->CRL &= ~GPIO_CRL_MODE6;
	  GPIOA->CRL |= GPIO_CRL_MODE6_1;

	  GPIOA->CRL &= ~GPIO_CRL_CNF7;
	  GPIOA->CRL |= GPIO_CRL_CNF7_1;
	  GPIOA->CRL &= ~GPIO_CRL_MODE7;
	  GPIOA->CRL |= GPIO_CRL_MODE7_1;

	  GPIOB->CRL &= ~GPIO_CRL_CNF0;
	  GPIOB->CRL |= GPIO_CRL_CNF0_1;
	  GPIOB->CRL &= ~GPIO_CRL_MODE0;
	  GPIOB->CRL |= GPIO_CRL_MODE0_1;

	  GPIOB->CRL &= ~GPIO_CRL_CNF1;
	  GPIOB->CRL |= GPIO_CRL_CNF1_1;
	  GPIOB->CRL &= ~GPIO_CRL_MODE1;
	  GPIOB->CRL |= GPIO_CRL_MODE1_1;

	  //настрока выводов TIM4
	  GPIOB->CRL &= ~GPIO_CRL_CNF6;
	  GPIOB->CRL |= GPIO_CRL_CNF6_1;
	  GPIOB->CRL &= ~GPIO_CRL_MODE6;
	  GPIOB->CRL |= GPIO_CRL_MODE6_1;

	  GPIOB->CRL &= ~GPIO_CRL_CNF7;
	  GPIOB->CRL |= GPIO_CRL_CNF7_1;
	  GPIOB->CRL &= ~GPIO_CRL_MODE7;
	  GPIOB->CRL |= GPIO_CRL_MODE7_1;

	  GPIOB->CRH &= ~GPIO_CRH_CNF8;
	  GPIOB->CRH |= GPIO_CRH_CNF8_1;
	  GPIOB->CRH &= ~GPIO_CRH_MODE8;
	  GPIOB->CRH |= GPIO_CRH_MODE8_1;

	  GPIOB->CRH &= ~GPIO_CRH_CNF9;
	  GPIOB->CRH |= GPIO_CRH_CNF9_1;
	  GPIOB->CRH &= ~GPIO_CRH_MODE9;
	  GPIOB->CRH |= GPIO_CRH_MODE9_1;


	   GPIOB->CRH &= ~(GPIO_CRH_MODE15 | GPIO_CRH_CNF15);
	   //MODE: вход, оставляем в нуле
	   //CNF: вход с pull-up / pull-down
	   GPIOB->CRH |= (0x00 << GPIO_CRH_MODE15_Pos) | (0x02 << GPIO_CRH_CNF15_Pos);
	   GPIOB->ODR |= (1<<15); //Включаем подтяжку вверх

	   GPIOB->CRH &= ~(GPIO_CRH_MODE14 | GPIO_CRH_CNF14);
	   GPIOB->CRH |= (0x00 << GPIO_CRH_MODE14_Pos) | (0x02 << GPIO_CRH_CNF14_Pos);
	   GPIOB->ODR |= (1<<14);

}

void TIM1_UP_IRQHandler(void){
        GPIOC->ODR ^= GPIO_ODR_ODR13;
    	TIM1->CNT = 0;

    	if (DownOn == 1){
    		StepSetDown();
    	}

    	TIM1->SR &= ~TIM_SR_UIF;        	// Сбрасываю флаг прерывания
}

// Функция Включения ступенек
void StepSetDown(void){
	Status = 1;
	int x = 0;
	if (SV(x) <= MaxLite){
	SV(x) += SpeedLite;
	}
	for (x = 1 ; x <=Step ; x++ ){
		if ((SV(x-1) >= SmoothnessLite) && (SV(x) < MaxLite)){
			SV(x) += SpeedLite;
		}
	if (SV(Step) == 1000){
		DownOn = 0;
		Status = 2;
	}

	Resetlite = 1;
	}

}

// Функция гашения ступенек
void StepDark(void){

}



int main(void)
{
    ClockInit();
    PortInit();
    TimerInit();
    GPIOC->ODR ^= GPIO_ODR_ODR13;

    SV(1) = MaxLiteDuti;
    SV(2) = 0;
    SV(3) = 0;
    SV(4) = 0;
    SV(5) = 0;
    SV(6) = 0;
    SV(7) = 0;
    SV(8) = 0;
    SV(9) = 0;
    SV(10) = 0;
    SV(11) = 0;
    SV(12) = MaxLiteDuti;

    Resetlite = 1;

    __enable_irq ();  // разрешить прерывания if((GPIOB->IDR & (1<<15)) == 1)

    while(1){

	if(GPIOB->IDR & (1<<15)){
		DownOn = 1;

/*
	//GPIOC->ODR ^= GPIO_ODR_ODR13;

	delay(100000);


	TIM2->CCR4 = 600;
	TIM2->CCR3 = 600;
	TIM2->CCR2 = 600;
	TIM2->CCR1 = 600;
	TIM3->CCR4 = 600;
	TIM3->CCR3 = 600;
	TIM3->CCR2 = 600;
	TIM3->CCR1 = 600;
	TIM4->CCR4 = 600;
	TIM4->CCR3 = 600;
	TIM4->CCR2 = 600;
	TIM4->CCR1 = 600;
	//GPIOC->ODR ^= GPIO_ODR_ODR13;

	delay(100000);


	TIM2->CCR4 = 800;
	TIM2->CCR3 = 800;
	TIM2->CCR2 = 800;
	TIM2->CCR1 = 800;
	TIM3->CCR4 = 800;
	TIM3->CCR3 = 800;
	TIM3->CCR2 = 800;
	TIM3->CCR1 = 800;
	TIM4->CCR4 = 800;
	TIM4->CCR3 = 800;
	TIM4->CCR2 = 800;
	TIM4->CCR1 = 800;

	//GPIOC->ODR ^= GPIO_ODR_ODR13;
	delay(100000);


	TIM2->CCR4 = 900;
	TIM2->CCR3 = 900;
	TIM2->CCR2 = 900;
	TIM2->CCR1 = 900;
	TIM3->CCR4 = 900;
	TIM3->CCR3 = 900;
	TIM3->CCR2 = 900;
	TIM3->CCR1 = 900;
	TIM4->CCR4 = 900;
	TIM4->CCR3 = 900;
	TIM4->CCR2 = 900;
	TIM4->CCR1 = 900;
	//GPIOC->ODR ^= GPIO_ODR_ODR13;
	delay(100000);


	TIM2->CCR4 = 100;
	TIM2->CCR3 = 100;
	TIM2->CCR2 = 100;
	TIM2->CCR1 = 100;
	TIM3->CCR4 = 100;
	TIM3->CCR3 = 100;
	TIM3->CCR2 = 100;
	TIM3->CCR1 = 100;
	TIM4->CCR4 = 100;
	TIM4->CCR3 = 100;
	TIM4->CCR2 = 100;
	TIM4->CCR1 = 100;
	//GPIOC->ODR ^= GPIO_ODR_ODR13;

	delay(100000);


	TIM2->CCR4 = 400;
	TIM2->CCR3 = 400;
	TIM2->CCR2 = 400;
	TIM2->CCR1 = 400;
	TIM3->CCR4 = 400;
	TIM3->CCR3 = 400;
	TIM3->CCR2 = 400;
	TIM3->CCR1 = 400;
	TIM4->CCR4 = 400;
	TIM4->CCR3 = 400;
	TIM4->CCR2 = 400;
	TIM4->CCR1 = 400;
	}
	else {

	    TIM2->CCR4 = 1000;
	    TIM2->CCR3 = 1000;
	    TIM2->CCR2 = 1000;
	    TIM2->CCR1 = 1000;
	    TIM3->CCR4 = 1000;
	    TIM3->CCR3 = 1000;
	    TIM3->CCR2 = 1000;
	    TIM3->CCR1 = 1000;
	    TIM4->CCR4 = 1000;
	    TIM4->CCR3 = 1000;
	    TIM4->CCR2 = 1000;
	    TIM4->CCR1 = 1000;

	}
	*/
    }

	if (Resetlite == 1){
		OUT1 = SV(1);
		OUT2 = SV(2);
		OUT3 = SV(3);
		OUT4 = SV(4);
		OUT5 = SV(5);
		OUT6 = SV(6);
		OUT7 = SV(7);
		OUT8 = SV(8);
		OUT9 = SV(9);
		OUT10 = SV(10);
		OUT11 = SV(11);
		OUT12 = SV(12);
		Resetlite = 0;
	}

	if (Status == 2){
		SV(1) = MaxLiteDuti;
		SV(2) = 0;
		SV(3) = 0;
		SV(4) = 0;
		SV(5) = 0;
		SV(6) = 0;
		SV(7) = 0;
		SV(8) = 0;
		SV(9) = 0;
		SV(10) = 0;
		SV(11) = 0;
		SV(12) = MaxLiteDuti;

		Resetlite = 1;

		Status = 0;
	}
    }
return 0;
}
