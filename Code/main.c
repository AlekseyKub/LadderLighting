#include "main.h"
#include "stm32f1xx.h"
#include "stm32f103xb.h"
#include "RCCinit.h"
#include "TimerInit.h"


char DownOn = 0;    	// флаг нижнего датчика
char UpOn = 0;		// флаг верхнего датчика
char Resetlite = 0;	// Флаг обновления яркости ступенек
char AllLiteOn = 0;   // Флаг включения всех ступенек

int DelayOff = 0;	// Переменная для отсчета задержек

char OffStatus = 0; 	// Статус как выключать ступеньки
char Status = 0;		// статус работы контроллера  0-ожидание саботки 1-сраб. ниж. дат. 2-сраб. вехн. дат. 3-сработали оба датчика 4-задержка на выключение
				// 5-выключение вверх 6-выключение вниз 7-выключение одновременно
int SpeedLite = 10;        	// Скорость зажигания
int SmoothnessLite = 200;	// Плавность зажигания
int Step = 12;			// Количество ступенек
int MaxLite = 300;		// Максимальная яркость
int MaxLiteDuti = 50;		// Дежурная яркость

int StepValue[12];		// Хранение значения яркости ступенек

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

/*
	   GPIOB->CRH &= ~(GPIO_CRH_MODE15 | GPIO_CRH_CNF15);
	   //MODE: вход, оставляем в нуле
	   //CNF: вход с pull-up / pull-down
	   GPIOB->CRH |= (0x00 << GPIO_CRH_MODE15_Pos) | (0x02 << GPIO_CRH_CNF15_Pos);
	   GPIOB->ODR |= (1<<15); //Включаем подтяжку вверх

	   GPIOB->CRH &= ~(GPIO_CRH_MODE14 | GPIO_CRH_CNF14);
	   GPIOB->CRH |= (0x00 << GPIO_CRH_MODE14_Pos) | (0x02 << GPIO_CRH_CNF14_Pos);
	   GPIOB->ODR |= (1<<14);
*/
	   GPIOB->CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5);
	   //MODE: вход, оставляем в нуле
	   //CNF: вход с pull-up / pull-down
	   GPIOB->CRL |= (0x00 << GPIO_CRL_MODE5_Pos) | (0x02 << GPIO_CRL_CNF5_Pos);
	   GPIOB->ODR |= (1<<5); //Включаем подтяжку вверх

	   GPIOB->CRL &= ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4);
	   //MODE: вход, оставляем в нуле
	   //CNF: вход с pull-up / pull-down
	   GPIOB->CRL |= (0x00 << GPIO_CRL_MODE4_Pos) | (0x02 << GPIO_CRL_CNF4_Pos);
	   GPIOB->ODR |= (1<<4); //Включаем подтяжку вверх

}

// перевод ступенек в дежурный режим
void StandbyMode (void){
	int a = 1;
	while (a <= 12){
		SV(a) = 0;
		a++;
	}

	SV(1) = MaxLiteDuti;
	SV(Step) = MaxLiteDuti;
	Resetlite = 1;
}

// проверка на включение всех ступенек
void AllLite(void){
	if (SV(5) == 100){
		Status = 4;
		DownOn = 0;
		UpOn = 0;
	}
}

void TIM1_UP_IRQHandler(void){
        //GPIOC->ODR ^= GPIO_ODR_ODR13;
    	TIM1->CNT = 0;

    	switch (Status){

    	case 1:
    		StepSetDown();
    		AllLite();
    		break;

    	case 2:
    		StepSetUp();
    		AllLite();
    		break;

    	case 3:
    		StepSetDown();
    		StepSetUp();
    		AllLite();
    		break;

    	case 4:// десь надо сделатьь задержку
    		StandbyMode();
    		GPIOC->ODR |= GPIO_ODR_ODR13;

    		break;

    	case 5:
    		break;
    	case 6:
    		break;
    	case 7:
    		break;
    	}

    	TIM1->SR &= ~TIM_SR_UIF;        	// Сбрасываю флаг прерывания
}

// Функция Включения ступенек снизу вверх
void StepSetDown(void){
	if ((Status == 1) || (Status == 3)){
	int x = 1;		// переменная подсчета ступенек вверх

	if (SV(x) <= MaxLite){	// если первая ступенька еще не доконца включилась увеличиваем яркость
	    SV(x) += SpeedLite;
	}

	for (x = 1 ; x <=Step ; x++ ){						// проходимся по всем ступенькам для зажигания следующей не дожидаясь максимума предыдущей
		if ((SV(x-1) >= SmoothnessLite) && (SV(x) < MaxLite)){     	// (условие выполнится только для одной ступеньки)
			SV(x) += SpeedLite;
		}
	}

	}
	Resetlite = 1;

}

// Функция включения ступенек сверху вниз
void StepSetUp(void){
    if((Status == 2) || (Status == 3)){
    int y = Step;

    if (SV(y) <= MaxLite){
	SV(y) += SpeedLite;
    }

    for (y = Step ; y >= 0 ; y-- ){			// проходимся по всем ступенькам для зажигания следующей не дожидаясь максимума предыдущей
    		if ((SV(y + 1) >= SmoothnessLite) && (SV(y) < MaxLite)){     // (условие выполнится только для одной ступеньки)
    			SV(y) += SpeedLite;
    		}
    }
    Resetlite = 1;
    }
}



int main(void)
{
    ClockInit();
    PortInit();
    TimerInit();
    GPIOC->ODR ^= GPIO_ODR_ODR13;


    StandbyMode();
    Resetlite = 1;
    __enable_irq ();  // разрешить прерывания if((GPIOB->IDR & (1<<15)) == 1)

    while(1){

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



    	if(GPIOB->IDR & (1<<5)){
    		DownOn = 1;
    		}


    	if(GPIOB->IDR & (1<<4)){
    		UpOn = 1 ;
    		}


    if (DownOn == 1){			// Если сработал нижний датчик, переводим контроллер в режим 1
	    if (Status != 4){
    	Status = 1;
	}
    }

	if (UpOn == 1){				// Если сработал верний датчик, переводим контроллер в режим 2
	    if (Status != 4){
		Status = 2;
	}
	}

	if ((DownOn == 1) && (UpOn == 1)){	// Если сработали два датчика переводим в режим 3
	    if (Status != 4){
		Status = 3;
	}
	}



    }
return 0;
}

