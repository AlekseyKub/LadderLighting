#include "stm32f1xx.h"


#define SV(x) StepValue[x]

#define OUT1 TIM2->CCR1
#define OUT2 TIM2->CCR2
#define OUT3 TIM2->CCR3
#define OUT4 TIM2->CCR4
#define OUT5 TIM3->CCR1
#define OUT6 TIM3->CCR2
#define OUT7 TIM3->CCR3
#define OUT8 TIM3->CCR4
#define OUT9 TIM4->CCR4
#define OUT10 TIM4->CCR3
#define OUT11 TIM4->CCR2
#define OUT12 TIM4->CCR1

/*
#define SV2 StepValue[1]
#define SV3 StepValue[2]
#define SV4 StepValue[3]
#define SV5 StepValue[4]
#define SV6 StepValue[5]
#define SV7 StepValue[6]
#define SV8 StepValue[7]
#define SV9 StepValue[8]
#define SV10 StepValue[9]
#define SV11 StepValue[10]
#define SV12 StepValue[11]
*/

void StepSetDown(void);

void delay(uint32_t time_delay)
		{
		    uint32_t i;
		    for(i = 0; i < time_delay; i++);
		}
