#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x.h"
#include "misc.h"

int main(void)
{
	ledInit();
	buttonInit();

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_Init(&NVIC_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);

	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStructure);

    while(1)
    {
    }
}

void EXTI0_IRQHandler(void){
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) != 0){
		turnOnLed();
	}
	else{
		turnOffLed();
	}
}

void turnOnLed(){
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}

void turnOffLed(){
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

void blink()
{
	for(int i = 0; i < 1000000; i++);
	GPIOC->ODR ^= GPIO_Pin_13;
	for(int i = 0; i < 1000000; i++);
	GPIOC->ODR ^= GPIO_Pin_13;
}

void ledInit(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_LedInit;
	GPIO_LedInit.GPIO_Pin = GPIO_Pin_13;
	GPIO_LedInit.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_LedInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_LedInit);
}

void buttonInit(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_ButtonInit;
	GPIO_ButtonInit.GPIO_Pin = GPIO_Pin_0;
	GPIO_ButtonInit.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_ButtonInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_ButtonInit);
}
