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
	  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;	 //Включаю тактирование РВ
	  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;    // Тактирование альтернативных функций GPIO
	  //RCC->APB2ENR |= RCC_APB2ENR_USART1EN;  // Тактирование модуля USART1
	  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   // Включить тактирование  TIM2

	  // Тактирование  GPIOA , TIM1, альтернативных функций порта
	  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_TIM1EN | RCC_APB2ENR_AFIOEN;
	  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN |RCC_APB1ENR_TIM3EN;


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



	  // Иницыализация таймера TIM1

	  //делитель
	  	TIM1->PSC = 72;
	  	//значение перезагрузки
	         TIM1->ARR = 1000;
	  	//коэф. заполнения
	  	TIM1->CCR4 = lite;
	  	TIM1->CCR3 = 100;
	  	TIM1->CCR2 = lite;
	  	TIM1->CCR1 = lite;

	  	//настроим на выход канал 4, активный уровень низкий
	  	TIM1->CCER |= TIM_CCER_CC4E | TIM_CCER_CC4P;
	  	TIM1->CCMR2 &= ~TIM_CCMR2_OC4PE;

	  	TIM1->CCER |= TIM_CCER_CC3E | TIM_CCER_CC3P;
	  	TIM1->CCMR2 &= ~TIM_CCMR2_OC3PE;

	  	TIM1->CCER |= TIM_CCER_CC2E | TIM_CCER_CC2P;
	  	TIM1->CCMR1 &= ~TIM_CCMR1_OC2PE;

	  	TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC1P;
	  	TIM1->CCMR1 &= ~TIM_CCMR1_OC1PE;

	  	//разрешим использовать выводы таймера как выходы
	  	TIM1->BDTR |= TIM_BDTR_MOE;

	  	 //PWM mode 1, прямой ШИМ 4 канал
	         TIM1->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;
	         TIM1->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1;
	         TIM1->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;
	         TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;

	         //считаем вверх
		 TIM1->CR1 &= ~TIM_CR1_DIR;
		 //выравнивание по фронту, Fast PWM
		 TIM1->CR1 &= ~TIM_CR1_CMS;

		 TIM1->CR1 &= ~TIM_CR1_URS;
		 //включаем счётчик
		 TIM1->CR1 |= TIM_CR1_CEN;


		 // Иницыализацыи TIM2

		  	TIM2->PSC = 72;
		  	//значение перезагрузки
		         TIM2->ARR = 1000;
		  	//коэф. заполнения
		  	TIM2->CCR4 = lite;
		  	TIM2->CCR3 = 100;
		  	TIM2->CCR2 = lite;
		  	TIM2->CCR1 = lite;

		  	//настроим на выход канал 4, активный уровень низкий
		  	TIM2->CCER |= TIM_CCER_CC4E | TIM_CCER_CC4P;
		  	TIM2->CCMR2 &= ~TIM_CCMR2_OC4PE;

		  	TIM2->CCER |= TIM_CCER_CC3E | TIM_CCER_CC3P;
		  	TIM2->CCMR2 &= ~TIM_CCMR2_OC3PE;

		  	TIM2->CCER |= TIM_CCER_CC2E | TIM_CCER_CC2P;
		  	TIM2->CCMR1 &= ~TIM_CCMR1_OC2PE;

		  	TIM2->CCER |= TIM_CCER_CC1E | TIM_CCER_CC1P;
		  	TIM2->CCMR1 &= ~TIM_CCMR1_OC1PE;

		  	//разрешим использовать выводы таймера как выходы
		  	TIM2->BDTR |= TIM_BDTR_MOE;

		  	 //PWM mode 1, прямой ШИМ 4 канал
		         TIM2->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;
		         TIM2->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1;
		         TIM2->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;
		         TIM2->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;

		         //считаем вверх
			 TIM2->CR1 &= ~TIM_CR1_DIR;
			 //выравнивание по фронту, Fast PWM
			 TIM2->CR1 &= ~TIM_CR1_CMS;

			 TIM2->CR1 &= ~TIM_CR1_URS;
			 //включаем счётчик
			 TIM2->CR1 |= TIM_CR1_CEN;




			 // Иницыализацыи TIM3

			  	TIM3->PSC = 72;
			  	//значение перезагрузки
			         TIM3->ARR = 1000;
			  	//коэф. заполнения
			  	TIM3->CCR4 = lite;
			  	TIM3->CCR3 = 100;
			  	TIM3->CCR2 = lite;
			  	TIM3->CCR1 = lite;

			  	//настроим на выход канал 4, активный уровень низкий
			  	TIM3->CCER |= TIM_CCER_CC4E | TIM_CCER_CC4P;
			  	TIM3->CCMR2 &= ~TIM_CCMR2_OC4PE;

			  	TIM3->CCER |= TIM_CCER_CC3E | TIM_CCER_CC3P;
			  	TIM3->CCMR2 &= ~TIM_CCMR2_OC3PE;

			  	TIM3->CCER |= TIM_CCER_CC2E | TIM_CCER_CC2P;
			  	TIM3->CCMR1 &= ~TIM_CCMR1_OC2PE;

			  	TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC1P;
			  	TIM3->CCMR1 &= ~TIM_CCMR1_OC1PE;

			  	//разрешим использовать выводы таймера как выходы
			  	TIM3->BDTR |= TIM_BDTR_MOE;

			  	 //PWM mode 1, прямой ШИМ 4 канал
			         TIM3->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;
			         TIM3->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1;
			         TIM3->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;
			         TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;

			         //считаем вверх
				 TIM3->CR1 &= ~TIM_CR1_DIR;
				 //выравнивание по фронту, Fast PWM
				 TIM3->CR1 &= ~TIM_CR1_CMS;

				 TIM3->CR1 &= ~TIM_CR1_URS;
				 //включаем счётчик
				 TIM3->CR1 |= TIM_CR1_CEN;




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
	TIM1->CCR3 = 600;
	TIM1->CCR2 = 600;
	TIM1->CCR1 = 600;
	TIM2->CCR4 = 600;
	TIM2->CCR3 = 600;
	TIM2->CCR2 = 600;
	TIM2->CCR1 = 600;
	TIM3->CCR4 = 600;
	TIM3->CCR3 = 600;
	TIM3->CCR2 = 600;
	TIM3->CCR1 = 600;
	GPIOC->ODR ^= GPIO_ODR_ODR13;

	delay(100000);

	TIM1->CCR4 = 600;
	TIM1->CCR3 = 800;
	TIM1->CCR2 = 800;
	TIM1->CCR1 = 800;
	TIM2->CCR4 = 800;
	TIM2->CCR3 = 800;
	TIM2->CCR2 = 800;
	TIM2->CCR1 = 800;
	TIM3->CCR4 = 800;
	TIM3->CCR3 = 800;
	TIM3->CCR2 = 800;
	TIM3->CCR1 = 800;

	GPIOC->ODR ^= GPIO_ODR_ODR13;
	delay(100000);

	TIM1->CCR4 = 800;
	TIM1->CCR3 = 950;
	TIM1->CCR2 = 950;
	TIM1->CCR1 = 950;
	TIM2->CCR4 = 900;
	TIM2->CCR3 = 900;
	TIM2->CCR2 = 900;
	TIM2->CCR1 = 900;
	TIM3->CCR4 = 900;
	TIM3->CCR3 = 900;
	TIM3->CCR2 = 900;
	TIM3->CCR1 = 900;
	GPIOC->ODR ^= GPIO_ODR_ODR13;
	delay(100000);

	TIM1->CCR4 = 950;
	TIM1->CCR3 = 100;
	TIM1->CCR2 = 100;
	TIM1->CCR1 = 100;
	TIM2->CCR4 = 100;
	TIM2->CCR3 = 100;
	TIM2->CCR2 = 100;
	TIM2->CCR1 = 100;
	TIM3->CCR4 = 100;
	TIM3->CCR3 = 100;
	TIM3->CCR2 = 100;
	TIM3->CCR1 = 100;
	GPIOC->ODR ^= GPIO_ODR_ODR13;

	delay(100000);

	TIM1->CCR4 = 100;
	TIM1->CCR3 = 400;
	TIM1->CCR2 = 400;
	TIM1->CCR1 = 400;
	TIM2->CCR4 = 400;
	TIM2->CCR3 = 400;
	TIM2->CCR2 = 400;
	TIM2->CCR1 = 400;
	TIM3->CCR4 = 400;
	TIM3->CCR3 = 400;
	TIM3->CCR2 = 400;
	TIM3->CCR1 = 400;

    }
return 0;
}
