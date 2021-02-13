#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "touch_key.h" 
#include "usart.h"

#define BAUD_RATE 115200      //写入的起始地址
#define KEYA_SPEED1 100       //长按的时间长度
#define KEYA_SPEED2 10        // 双击的时间长度

int main (void)
{
    //用于滑动加减计数	
    u16 k=1000;

    //用于滑动加减计数
    u8 a = 0, b, c = 0;

    // 滑动结束的标志
    u8 s = 0;

    // 初始化配置
    RCC_Configuration(); 

    LED_Init();

    USART1_Init(BAUD_RATE);

    TOUCH_KEY_Init();

    while(1)
    {
        //检测A按键是否按下
        if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A)) {
            // 延时去抖动
            delay_ms(20);

            // 判断长短贱
            if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A)) {
                // 循环判断长按，到时跳转
                while ((!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A)) && c < KEYA_SPEED1) {
                    c++;
                    // 长按判断的计时
                    delay_ms(10);
                }

                // 长按处理
                if (c >= KEYA_SPEED1) {
                    GPIO_WriteBit(LEDPORT, LED1, (BitAction)(1));
                    printf("A键长按 \r\n");
                    while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A));
                } else {
                    if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_B)) {
                        k++;
                        printf("A键右划 %d \r\n", k);
                        a = 1;
                        s = 1;
                    }
                    if (a == 0) {
                        // 单击处理
                        for (b = 0; b < KEYA_SPEED2; b++) {
                            delay_ms(20);
                            if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A)) {
                                a = 1;
                                printf("A键双击 \r\n");
                                GPIO_WriteBit(LEDPORT, LED2, (BitAction)(1));
                                while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A));
                            }
                        }
                        if (a == 0) {
                            if (s == 1) {
                                s = 0;
                            } else {
                                GPIO_WriteBit(LEDPORT, LED1 | LED2, (BitAction)(0));
                                printf("A键单击 \r\n");
                            }
                        }
                    }
                }
            }

            // 参数清零
            a = 0;
            c = 0;
        }

        //检测B按键是否按下
        if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_B)) {
            // 延时去抖动
            delay_ms(20);

            // 判断长短贱
            if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_B)) {
                // 循环判断长按，到时跳转
                while ((!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_B)) && c < KEYA_SPEED1) {
                    c++;
                    // 长按判断的计时
                    delay_ms(10);
                }

                // 长按处理
                if (c >= KEYA_SPEED1) {
                    GPIO_WriteBit(LEDPORT, LED1, (BitAction)(1));
                    printf("B键长按 \r\n");
                    while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_B));
                } else {
                    if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_C)) {
                        k++;
                        printf("B键右划 %d \r\n", k);
                        a = 1;
                        s = 1;
                    }
                    if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A)) {
                        k--;
                        printf("B键左划 %d \r\n", k);
                        a = 1;
                        s = 1;
                    }
                    if (a == 0) {
                        // 单击处理
                        for (b = 0; b < KEYA_SPEED2; b++) {
                            delay_ms(20);
                            if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_B)) {
                                a = 1;
                                printf("B键双击 \r\n");
                                GPIO_WriteBit(LEDPORT, LED2, (BitAction)(1));
                                while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_B));
                            }
                        }
                        if (a == 0) {
                            if (s == 1) {
                                s = 0;
                            } else {
                                GPIO_WriteBit(LEDPORT, LED1 | LED2, (BitAction)(0));
                                printf("B键单击 \r\n");
                            }
                        }
                    }
                }
            }

            // 参数清零
            a = 0;
            c = 0;
        }

        //检测C按键是否按下
        if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_C)) {
            // 延时去抖动
            delay_ms(20);

            // 判断长短贱
            if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_C)) {
                // 循环判断长按，到时跳转
                while ((!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_C)) && c < KEYA_SPEED1) {
                    c++;
                    // 长按判断的计时
                    delay_ms(10);
                }

                // 长按处理
                if (c >= KEYA_SPEED1) {
                    GPIO_WriteBit(LEDPORT, LED1, (BitAction)(1));
                    printf("C键长按 \r\n");
                    while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_C));
                } else {
                    if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_D)) {
                        k++;
                        printf("C键右划 %d \r\n", k);
                        a = 1;
                        s = 1;
                    }
                    if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_B)) {
                        k--;
                        printf("C键左划 %d \r\n", k);
                        a = 1;
                        s = 1;
                    }
                    if (a == 0) {
                        // 单击处理
                        for (b = 0; b < KEYA_SPEED2; b++) {
                            delay_ms(20);
                            if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_C)) {
                                a = 1;
                                printf("C键双击 \r\n");
                                GPIO_WriteBit(LEDPORT, LED2, (BitAction)(1));
                                while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_C));
                            }
                        }
                        if (a == 0) {
                            if (s == 1) {
                                s = 0;
                            } else {
                                GPIO_WriteBit(LEDPORT, LED1 | LED2, (BitAction)(0));
                                printf("C键单击 \r\n");
                            }
                        }
                    }
                }
            }

            // 参数清零
            a = 0;
            c = 0;
        }

        //检测A按键是否按下
        if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_D)) {
            // 延时去抖动
            delay_ms(20);

            // 判断长短贱
            if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_D)) {
                // 循环判断长按，到时跳转
                while ((!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_D)) && c < KEYA_SPEED1) {
                    c++;
                    // 长按判断的计时
                    delay_ms(10);
                }

                // 长按处理
                if (c >= KEYA_SPEED1) {
                    GPIO_WriteBit(LEDPORT, LED1, (BitAction)(1));
                    printf("D键长按 \r\n");
                    while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_D));
                } else {
                    if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_C)) {
                        k--;
                        printf("D键左划 %d \r\n", k);
                        a = 1;
                        s = 1;
                    }
                    if (a == 0) {
                        // 单击处理
                        for (b = 0; b < KEYA_SPEED2; b++) {
                            delay_ms(20);
                            if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_D)) {
                                a = 1;
                                printf("D键双击 \r\n");
                                GPIO_WriteBit(LEDPORT, LED2, (BitAction)(1));
                                while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_D));
                            }
                        }
                        if (a == 0) {
                            if (s == 1) {
                                s = 0;
                            } else {
                                GPIO_WriteBit(LEDPORT, LED1 | LED2, (BitAction)(0));
                                printf("D键单击 \r\n");
                            }
                        }
                    }
                }
            }

            // 参数清零
            a = 0;
            c = 0;
        }
    }
}

