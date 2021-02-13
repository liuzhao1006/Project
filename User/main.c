#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "touch_key.h" 
#include "usart.h"
#include "TM1640.h"
#include "rtc.h"
#include "encoder.h"
#include "lm75a.h"

#define BAUD_RATE 115200      //写入的起始地址

int main (void)
{
    u8 buffer[3];
    u8 a = 0, b = 0, c = 0x01;

    // 初始化配置
    RCC_Configuration();
    I2C_Configuration();

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

        // 读取LM75A的温度数据
        LM75A_GetTemp(buffer);
        TM1640_display(2, buffer[1] / 10);
        TM1640_display(3, buffer[1] % 10 + 10);
        TM1640_display(4, buffer[2] / 10);
        TM1640_display(5, buffer[2] % 10);
        TM1640_led(c);
        c <<= 1;
        if(c == 0x00) {
            c = 0x01;
        }
        delay_ms(150);
    }
}

