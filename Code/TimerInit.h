
#include "stm32f1xx.h"


void TimerInit(void){

	  //делитель
	  	TIM1->PSC = 7200;
	  	//значение перезагрузки
		TIM1->ARR = 100;
		TIM1->SMCR &= ~ TIM_SMCR_SMS;
		TIM1->EGR = TIM_EGR_UG;
		TIM1->SR &= ~TIM_SR_UIF;        	// Сбрасываю флаг прерывания

		TIM1->CR1 |= TIM_CR1_ARPE; // Разрешаю работу TIM1 и сброс при достижении максимальнго значения
		TIM1->DIER |= TIM_DIER_UIE;             // разрешаю прерывание по обновлению (достижению)

		TIM1->CR1 &= ~TIM_CR1_DIR;              //считаем вверх

		TIM1->CR1 |= TIM_CR1_CEN;		//включаем счётчик


		NVIC_EnableIRQ(TIM1_UP_IRQn); 		 //Разрешаем обработку прерывания от таймера 2
		NVIC_SetPriority(TIM1_UP_IRQn, 1); 	 //Приоритет прерывания


		 // Иницыализацыи TIM2

		  	TIM2->PSC = 720;
		  	//значение перезагрузки
		    TIM2->ARR = 1000;
		  	//коэф. заполнения
		  	TIM2->CCR4 = 100;
		  	TIM2->CCR3 = 100;
		  	TIM2->CCR2 = 100;
		  	TIM2->CCR1 = 100;

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
		         TIM2->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_0;
		         TIM2->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_0;
		         TIM2->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_0;
		         TIM2->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0;

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
			  	TIM3->CCR4 = 100;
			  	TIM3->CCR3 = 100;
			  	TIM3->CCR2 = 100;
			  	TIM3->CCR1 = 100;

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
			         TIM3->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_0;
			         TIM3->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_0;
			         TIM3->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_0;
			         TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0;

			         //считаем вверх
				 TIM3->CR1 &= ~TIM_CR1_DIR;
				 //выравнивание по фронту, Fast PWM
				 TIM3->CR1 &= ~TIM_CR1_CMS;

				 TIM3->CR1 &= ~TIM_CR1_URS;
				 //включаем счётчик
				 TIM3->CR1 |= TIM_CR1_CEN;


				 // Иницыализацыи TIM4

				  	TIM4->PSC = 72;
				  	//значение перезагрузки
				         TIM4->ARR = 1000;
				  	//коэф. заполнения
				  	TIM4->CCR4 = 100;
				  	TIM4->CCR3 = 100;
				  	TIM4->CCR2 = 100;
				  	TIM4->CCR1 = 100;

				  	//настроим на выход канал 4, активный уровень низкий
				  	TIM4->CCER |= TIM_CCER_CC4E | TIM_CCER_CC4P;
				  	TIM4->CCMR2 &= ~TIM_CCMR2_OC4PE;

				  	TIM4->CCER |= TIM_CCER_CC3E | TIM_CCER_CC3P;
				  	TIM4->CCMR2 &= ~TIM_CCMR2_OC3PE;

				  	TIM4->CCER |= TIM_CCER_CC2E | TIM_CCER_CC2P;
				  	TIM4->CCMR1 &= ~TIM_CCMR1_OC2PE;

				  	TIM4->CCER |= TIM_CCER_CC1E | TIM_CCER_CC1P;
				  	TIM4->CCMR1 &= ~TIM_CCMR1_OC1PE;

				  	//разрешим использовать выводы таймера как выходы
				  	TIM4->BDTR |= TIM_BDTR_MOE;

				  	 //PWM mode 1, прямой ШИМ 4 канал
				         TIM4->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_0;
				         TIM4->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_0;
				         TIM4->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_0;
				         TIM4->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0;

				         //считаем вверх
					 TIM4->CR1 &= ~TIM_CR1_DIR;
					 //выравнивание по фронту, Fast PWM
					 TIM4->CR1 &= ~TIM_CR1_CMS;

					 TIM4->CR1 &= ~TIM_CR1_URS;
					 //включаем счётчик
					 TIM4->CR1 |= TIM_CR1_CEN;

}
