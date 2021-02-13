#include "touch_key.h"

void TOUCH_KEY_Init(void){ //微动开关的接口初始化
	GPIO_InitTypeDef  GPIO_InitStructure; //定义GPIO的初始化枚举结构	
    GPIO_InitStructure.GPIO_Pin = TOUCH_KEY_A | TOUCH_KEY_B | TOUCH_KEY_C | TOUCH_KEY_D; //选择端口                       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //选择IO接口工作方式 //上拉电阻       
	GPIO_Init(TOUCH_KEYPORT,&GPIO_InitStructure);			
}

