#include "touch_key.h"

void TOUCH_KEY_Init(void){ // ΢�����صĽӿڳ�ʼ��
	GPIO_InitTypeDef  GPIO_InitStructure; // ����GPIO�ĳ�ʼ��ö��	
    GPIO_InitStructure.GPIO_Pin = TOUCH_KEY_A | TOUCH_KEY_B | TOUCH_KEY_C | TOUCH_KEY_D; // ѡ��˿�                      
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ѡ��IO�ӿڹ�����ʽ����������   
	GPIO_Init(TOUCH_KEYPORT,&GPIO_InitStructure);			
}

