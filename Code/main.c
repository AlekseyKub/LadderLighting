#include "main.h"
#include "stm32f1xx.h"
#include "stm32f103xb.h"

int lite=500;

//Настройка портов
void PortInit(void)
{
	//APB2
	  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;    // Включение тактирования PC
	  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;    // Включаем тактирование PA
	  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;	 //	Включаю тактирование РВ
	  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;    // Тактирование альтернативных функций GPIO
	  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;  // Тактирование модуля USART1
	  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   // Включить тактирование  TIM2

	  // Тактирование  GPIOA , TIM1, альтернативных функций порта
	  	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_TIM1EN | RCC_APB2ENR_AFIOEN;

	 //APB1
	  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;  //Вкл. тактирование USART2

	  RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;	 // ВКЛ. тактирование SPI2


	  // UART1
	  		// настройка вывода PA9 (TX1 UART1) на режим альтернативной функции с активным выходом
	  		// Биты CNF = 10, ,биты MODE = X1
	  		GPIOA->CRH |= GPIO_CRH_CNF9_1;
	  		GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
	  		GPIOA->CRH |= GPIO_CRH_MODE9_0;
	  		GPIOA->CRH |= GPIO_CRH_MODE9_1;

	  		// настройка вывода PA10 (RX1 UART1) на режим входа с подтягивающим резистором
	  		// Биты CNF = 10, ,биты MODE = 00, ODR = 1
	  		GPIOA->CRH &= (~GPIO_CRH_CNF10_0);
	  		GPIOA->CRH |= GPIO_CRH_CNF10_1;
	  		GPIOA->CRH &= (~(GPIO_CRH_MODE10));
	  		GPIOA->BSRR |= GPIO_ODR_ODR10;

	  // UART2
	  		// настройка вывода PA2 (TX1 UART2) на режим альтернативной функции с активным выходом
	  		// Биты CNF = 10, ,биты MODE = X1
	  		GPIOA->CRL |= GPIO_CRL_CNF2_1;
	  		GPIOA->CRL &= ~GPIO_CRL_CNF2_0;
	  		GPIOA->CRL |= GPIO_CRL_MODE2_0;
	  		GPIOA->CRL |= GPIO_CRL_MODE2_1;

	  		// настройка вывода PA3 (RX1 UART2) на режим входа с подтягивающим резистором
	  		// Биты CNF = 10, ,биты MODE = 00, ODR = 1
	  		GPIOA->CRL &= (~GPIO_CRL_CNF3_0);
	  		GPIOA->CRL |= GPIO_CRL_CNF3_1;
	  		GPIOA->CRL &= (~(GPIO_CRL_MODE3));
	  		GPIOA->BSRR |= GPIO_ODR_ODR3;

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


	  // Иницыализация таймера

	  //делитель
	  	TIM1->PSC = 72;
	  	//значение перезагрузки
	          TIM1->ARR = 1000;
	  	//коэф. заполнения
	  	TIM1->CCR4 = lite;
	  //	TIM1->CCR3 = lite;
	  //	TIM1->CCR2 = lite;
	  //	TIM1->CCR1 = lite;

	  	//настроим на выход канал 4, активный уровень низкий
	  	TIM1->CCER |= TIM_CCER_CC4E | TIM_CCER_CC4P;
	  	TIM1->CCMR2 &= ~TIM_CCMR2_OC4PE;
/*
	  	TIM1->CCER |= TIM_CCER_CC3E | TIM_CCER_CC3P;
	  	TIM1->CCMR2 &= ~TIM_CCMR2_OC3PE;

	  	TIM1->CCER |= TIM_CCER_CC2E | TIM_CCER_CC2P;
	  	TIM1->CCMR1 &= ~TIM_CCMR1_OC2PE;

	  	TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC1P;
	  	TIM1->CCMR1 &= ~TIM_CCMR1_OC1PE;
*/
	  	//разрешим использовать выводы таймера как выходы
	  	TIM1->BDTR |= TIM_BDTR_MOE;
	  	//PWM mode 1, прямой ШИМ 4 канал
	          TIM1->CCMR2 = TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;
	     //      TIM1->CCMR2 = TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1;

	       //    TIM1->CCMR1 = TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;
	       //    TIM1->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
	          //если надо настроить первый канал, это можно сделать так
	          //TIM1->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;

	           //считаем вверх
	  	TIM1->CR1 &= ~TIM_CR1_DIR;
	  	//выравнивание по фронту, Fast PWM
	  	TIM1->CR1 &= ~TIM_CR1_CMS;

	  	TIM1->CR1 &= ~TIM_CR1_URS;
	  	//включаем счётчик
	  	TIM1->CR1 |= TIM_CR1_CEN;
}

void delay(uint32_t time_delay)
		{
		    uint32_t i;
		    for(i = 0; i < time_delay; i++);
		}



int main(void)
{

    PortInit();

    while(1){
	GPIOC->ODR ^= GPIO_ODR_ODR13;

	delay(100000);

	TIM1->CCR4 = 400;
	GPIOC->ODR ^= GPIO_ODR_ODR13;

	delay(100000);

	TIM1->CCR4 = 600;
	GPIOC->ODR ^= GPIO_ODR_ODR13;
	delay(100000);

	TIM1->CCR4 = 800;
	GPIOC->ODR ^= GPIO_ODR_ODR13;
	delay(100000);

	TIM1->CCR4 = 950;
	GPIOC->ODR ^= GPIO_ODR_ODR13;

	delay(100000);

	TIM1->CCR4 = 100;

	/*
	    //TIM1->CR1 &= ~TIM_CR1_CEN;
	    TIM1->CCR4 = lite;
	    TIM1->EGR |= TIM_EGR_UG;
	    TIM1->CR1 &= ~TIM_CR1_URS;
	    //TIM1->CR1 |= TIM_CR1_CEN;
	    */



    }
return 0;
}
