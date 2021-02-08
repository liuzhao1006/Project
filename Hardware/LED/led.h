#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#include "delay.h"

//#define LED1 PBout(0)// PB0
//#define LED2 PBout(1)// PB1	

//����IO�ӿ�
#define LEDPORT	GPIOB

//����IO�ӿ�
#define LED1	GPIO_Pin_0	

//����IO�ӿ�
#define LED2	GPIO_Pin_1

//���峣��ֵ
#define PARAMETER_ONE	10

//���峣��ֵ
#define PARAMETER_TWO	500	

//��ʼ��
void LED_Init(void);

// ������
void LED_Breathing_Lamp(u16 dutyCycle);

		 				    
#endif
