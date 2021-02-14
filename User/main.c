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
#include "oled0561.h"

#define BAUD_RATE 115200      //写入的起始地址

int main (void)
{
    u8 buffer[3];
    u8 a = 0, c = 0x01;
    delay_ms(100);


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

    LM75A_GetTemp(buffer);
    OLED0561_Init();

    // 设置亮度
    OLED_DISPLAY_LIT(100);

    // 显示全屏图片
    OLED_DISPLAY_PIC1();
    delay_ms(1000);

    OLED_DISPLAY_CLEAR();
    OLED_DISPLAY_8x16_BUFFER(0, "   LiuZhao   ");
    OLED_DISPLAY_8x16_BUFFER(6, "  Temp:");

    //汉字显示 刘朝电子
    OLED_DISPLAY_16x16(2, 2 * 16, 0);
    OLED_DISPLAY_16x16(2, 3 * 16, 1);
    OLED_DISPLAY_16x16(2, 4 * 16, 2);
    OLED_DISPLAY_16x16(2, 5 * 16, 3);
    while(1)
    {
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
        if(buffer[0]) {
            OLED_DISPLAY_8x16(6, 7 * 8, '-');
        }
        OLED_DISPLAY_8x16(6, 8 * 8, buffer[1] / 10 + 0x30);
        OLED_DISPLAY_8x16(6, 9 * 8, buffer[1] % 10 + 0x30);
        OLED_DISPLAY_8x16(6, 10 * 8, '.');
        OLED_DISPLAY_8x16(6, 11 * 8, buffer[2] / 10 + 0x30);
        OLED_DISPLAY_8x16(6, 12 * 8, buffer[2] % 10 + 0x30);
        OLED_DISPLAY_8x16(6, 13 * 8, 'C');
        delay_ms(200);
    }
}

