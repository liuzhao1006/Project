
#include "led.h"

 /**
  *	LED灯的接口初始化
  */
void LED_Init(void)
{ 
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);       

	 //选择端口号（0~15或all）
    GPIO_InitStructure.GPIO_Pin = LED1 | LED2; 
	
	 //选择IO接口工作方式                         
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    
	
	 //设置IO接口速度（2/10/50MHz） 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
	GPIO_Init(LEDPORT, &GPIO_InitStructure);			
}

/**
 * 点亮LED呼吸灯
 *
 * @param dutyCycle 延时时间
 */
void LED_Breathing_Lamp(u16 dutyCycle)
{
		    
	//LED1接口输出高电平1
	GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));
	GPIO_WriteBit(LEDPORT,LED2,(BitAction)(0));
	
	// 延时 
	delay_us(dutyCycle);

	// LED1接口输出低电平0
	GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0));
	GPIO_WriteBit(LEDPORT,LED2,(BitAction)(1));

	// 延时
	delay_us(PARAMETER_TWO + 1 - dutyCycle);
}

