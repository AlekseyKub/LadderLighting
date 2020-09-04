#include "stm32f1xx.h"

//Настройка тактирования
void ClockInit(void)
{
  RCC->CR |= (1<<RCC_CR_HSEON_Pos);            //Запускаем генератор HSE
  while(RCC->CR & (1<<RCC_CR_HSERDY_Pos)){     //Дожидаемся включения
  }

  RCC->CFGR |= (0x07<<RCC_CFGR_PLLMULL_Pos)    //PLL множитель равен 9
            | (0x01<<RCC_CFGR_PLLSRC_Pos);     //Тактирование PLL от HSE

  RCC->CR |= (1<<RCC_CR_PLLON_Pos);            //Запускаем PLL
  while(RCC->CR & (1<<RCC_CR_PLLRDY_Pos)){     //Дожидаемся включения
  }

  FLASH->ACR |= (0x02<<FLASH_ACR_LATENCY_Pos); //Устанавливаем 2 цикла ожидания для Flash так как частота ядра у нас будет 48 MHz < SYSCLK <= 72 MHz

  RCC->CFGR |=(0x00<<RCC_CFGR_PPRE2_Pos)       //Делитель шины APB2 отключен
            | (0x04<<RCC_CFGR_PPRE1_Pos)       //Делитель нишы APB1 равен 2
            | (0x00<<RCC_CFGR_HPRE_Pos);       //Делитель AHB отключен


  RCC->CFGR |= (0x02<<RCC_CFGR_SW_Pos);        //Переключаемся на работу от PLL

  //Ждем, пока переключимся
  while((RCC->CFGR & RCC_CFGR_SWS_Msk) != (0x02<<RCC_CFGR_SWS_Pos))
  {
  }
  //отключаем внутренний RC-генератор
  //для экономии энергии
  RCC->CR &= ~(1<<RCC_CR_HSION_Pos);
}
