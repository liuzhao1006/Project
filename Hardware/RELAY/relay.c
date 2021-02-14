#include "relay.h"

/**
 * 继电器的接口初始化
 */
void RELAY_Init(void){
    GPIO_InitTypeDef  GPIO_InitStructure;

    // APB2外设时钟使能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);

    //启动AFIO重映射功能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // 选择端口号（0~15或all）
    GPIO_InitStructure.GPIO_Pin = RELAY1 | RELAY2;

    // 选择IO接口工作方式
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    // 设置IO接口速度（2/10/50MHz）
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RELAYPORT, &GPIO_InitStructure);

    // 必须将禁用JTAG功能才能做GPIO使用
    // 改变指定管脚的映射,完全禁用JTAG+SW-DP
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);

    //都为低电平（0） 初始为关继电器
    GPIO_ResetBits(RELAYPORT,RELAY1 | RELAY2);
}

/**
 * 继电器的控制程序（c=0继电器放开，c=1继电器吸合）
 */
void RELAY_1(u8 c){
    // 通过参数值写入接口
    GPIO_WriteBit(RELAYPORT,RELAY1,(BitAction)(c));
}

/**
 * 继电器的控制程序（c=0继电器放开，c=1继电器吸合）
 */
void RELAY_2(u8 c){
    // 通过参数值写入接口
    GPIO_WriteBit(RELAYPORT,RELAY2,(BitAction)(c));
}

