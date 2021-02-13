#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "touch_key.h" 
#include "usart.h"
#include "TM1640.h"
#include "rtc.h"
#include "encoder.h"

#define BAUD_RATE 115200      //写入的起始地址

int main (void)
{
    u8 a = 0, b = 0, c = 0x01;

    // 初始化配置
    RCC_Configuration();

    RTC_Config();
    ENCODER_Init();
    TM1640_Init();
    TM1640_display(0, a / 10);
    TM1640_display(1, a % 10);
    TM1640_display(2, 20);
    TM1640_display(3, 20);
    TM1640_display(4, 20);
    TM1640_display(5, 20);
    TM1640_display(6, 20);
    TM1640_display(7, 20);
    while(1)
    {
        // 读取旋转编码器值
        b = ENCODER_READ();
        if(b == 1) {
            a++;
            if(a > 99) {
                a = 0;
            }
        }
        if(b == 2) {
            if(a == 0) {
                a = 100;
            }
            a--;
        }
        if(b == 3) {
            a = 0;
        }
        if(b != 0) {
            TM1640_display(0, a / 10);
            TM1640_display(1, a % 10);
        }
    }
}

