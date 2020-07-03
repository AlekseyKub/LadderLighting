#include "main.h"
#include "stm32f1xx.h"
#include "stm32f103xb.h"

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


	  GPIOC->CRH |= GPIO_CRH_MODE13_1;      // выход максимально 50mhz
	  GPIOC->CRH |= GPIO_CRH_MODE13_0;

	  GPIOC->CRH &=~ GPIO_CRH_CNF13_1;		// настройка на выход порта С13
	  GPIOC->CRH &=~ GPIO_CRH_CNF13_0;

	  GPIOA->CRH |= GPIO_CRH_MODE11_1;      // выход максимально 50mhz
	  GPIOA->CRH |= GPIO_CRH_MODE11_0;

	  GPIOA->CRH &=~ GPIO_CRH_CNF11_1;		// настройка на выход порта С13
	  GPIOA->CRH &=~ GPIO_CRH_CNF11_0;


}




int main(void)
{
   // ClockInit();
   // PortInit();

    while(1){
	GPIOC->ODR &=~ GPIO_ODR_ODR13;
    }
return 0;
}
