#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "touch_key.h" 
#include "usart.h"
#include "TM1640.h"
#include "rtc.h"

#define BAUD_RATE 115200      //写入的起始地址

int main (void)
{
    u8 c = 0x01;

    // 初始化配置
    RCC_Configuration();

    RTC_Config();
    TM1640_Init();

    while(1)
    {
        if(RTC_Get() == 0) {
            TM1640_display(0, rday / 10);
            TM1640_display(1, rday % 10 + 10);
            TM1640_display(2, rhour / 10);
            TM1640_display(3, rhour % 10 + 10);
            TM1640_display(4, rmin / 10);
            TM1640_display(5, rmin % 10 + 10);
            TM1640_display(6, rsec / 10);
            TM1640_display(7, rsec % 10 + 10);
            TM1640_led(c);
            c <<= 1;
            if(c == 0x00) {
                c = 0x01;
            }
            delay_ms(125);
        }
    }
}

