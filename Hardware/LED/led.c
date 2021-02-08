
#include "led.h"

 /**
  *	LED�ƵĽӿڳ�ʼ��
  */
void LED_Init(void)
{ 
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);       

	 //ѡ��˿ںţ�0~15��all��
    GPIO_InitStructure.GPIO_Pin = LED1 | LED2; 
	
	 //ѡ��IO�ӿڹ�����ʽ                         
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    
	
	 //����IO�ӿ��ٶȣ�2/10/50MHz�� 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
	GPIO_Init(LEDPORT, &GPIO_InitStructure);			
}

/**
 * ����LED������
 *
 * @param dutyCycle ��ʱʱ��
 */
void LED_Breathing_Lamp(u16 dutyCycle)
{
		    
	//LED1�ӿ�����ߵ�ƽ1
	GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));
	GPIO_WriteBit(LEDPORT,LED2,(BitAction)(0));
	
	// ��ʱ 
	delay_us(dutyCycle);

	// LED1�ӿ�����͵�ƽ0
	GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0));
	GPIO_WriteBit(LEDPORT,LED2,(BitAction)(1));

	// ��ʱ
	delay_us(PARAMETER_TWO + 1 - dutyCycle);
}

