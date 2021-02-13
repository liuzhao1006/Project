#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "touch_key.h"

#define BAUD_RATE 115200	  //写入的起始地址
#define KEYA_SPEED1 100       //长按的时间长度
#define KEYA_SPEED2 10		  // 双击的时间长度				   

int main (void)
{	
    u8 a = 0, b, c = 0;
		
	// 初始化配置
    RCC_Configuration(); 
	
	LED_Init();

	TOUCH_KEY_Init();

	while(1)
	{
	    //检测按键是否按下
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
					while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A));
				} else {
				    // 单击处理
					for (b = 0; b < KEYA_SPEED2; b++) {
						delay_ms(20);
						if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A)) {
							a = 1;
							GPIO_WriteBit(LEDPORT, LED2, (BitAction)(1));
							while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A));
						}
					}
					if (a == 0) {
						GPIO_WriteBit(LEDPORT, LED1 | LED2, (BitAction)(0));
					}
				}
				a = 0;
				c = 0;
			}
		}
	}
}

