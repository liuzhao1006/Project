#include "encoder.h"

/**
 * 旋钮锁死标志（1为锁死）
 */
u8 KUP;

u16 cou;

void ENCODER_Init(void)
{
    // 定义GPIO的初始化枚举结构
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
    
    //选择端口号
    GPIO_InitStructure.GPIO_Pin = ENCODER_L | ENCODER_D;

    // 选择io接口工作方式，上拉电阻
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(ENCODER_PORT_A, &GPIO_InitStructure);

    // 选择端口号
    GPIO_InitStructure.GPIO_Pin = ENCODER_R;

    // 选择io接口工作方式，上拉电阻
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(ENCODER_PORT_B, &GPIO_InitStructure);
}

/**
 * 接口初始化
 */
u8 ENCODER_READ(void)
{
    // 存放按键的值
    u8 a;
    u8 kt;
    a = 0;
    if(GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_L)) {
        // 判断旋钮是否解除锁死
        KUP = 0;
    }
    if(!GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_L) && KUP == 0) {
        // 判断是否旋转旋钮，同时判断是否有旋钮锁死
        delay_us(100);

        // 把旋钮另一端电平状态记录
        kt = GPIO_ReadInputDataBit(ENCODER_PORT_B, ENCODER_R);
        delay_ms(3);

        // 去抖动
        if(!GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_L)) {
            // 用另一端判断左或右旋转
            if(kt == 0) {
                // 右转
                a = 1;
            } else {
                // 左转
                a = 2;
            }

            // 初始锁死判断计数器
            cou = 0;
            while(!GPIO_ReadInputDataBit(ENCODER_PORT_A,ENCODER_L) && cou < 60000) {
                // 等待放开旋钮，同时累加判断锁死
                cou++;
                KUP = 1;
                delay_us(20);
            }
        }
    }

    // 判断旋钮是否按下
    if(!GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_D) && KUP == 0) {
        delay_ms(20);

        // 去抖动
        if(!GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_D)) {
            // 在按键按下时加上按键的状态值
            a = 3;
        }
    }
    return a;
}

