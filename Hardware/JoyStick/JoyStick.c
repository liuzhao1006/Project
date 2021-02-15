#include "JoyStick.h"

void JoyStick_Init(void){ //微动开关的接口初始化
    GPIO_InitTypeDef  GPIO_InitStructure; //定义GPIO的初始化枚举结构  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);       
    GPIO_InitStructure.GPIO_Pin = JoyStick_KEY; //选择端口号（0~15或all）                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //选择IO接口工作方式 //上拉电阻       
    GPIO_Init(JoyStickPORT,&GPIO_InitStructure);            
}


