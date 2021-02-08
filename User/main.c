#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"	
#include "led.h"  	
#include "key.h"     	
#include "flash.h"
#include "buzzer.h"

#define FLASH_START_ADDR  0x0801f000	  //写入的起始地址


int main (void)
{			 
	// 亮暗类型
	u8 lightDarkType;

	//调节呼吸灯的占空比
	u16 dutyCycle, i, a;

	// 初始化配置
    RCC_Configuration();

	// 初始化LED灯驱动
	LED_Init();

	// 初始化KEY驱动
	KEY_Init();

	BUZZER_Init();
	BUZZER_BEEP1();

	//从指定页的地址读FLASH
	a = FLASH_R(FLASH_START_ADDR);

	//直接数值操作将变量值写入LED（LED在GPIOB组的PB0和PB1上）
	GPIO_Write(LEDPORT,a); 
	lightDarkType = 0;
    dutyCycle = 1;
	while(1)
	{
	    if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){ //读按键接口的电平
            delay_ms(20); //延时去抖动
            if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){ //读按键接口的电平
                GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0)); //LED取反
                GPIO_WriteBit(LEDPORT,LED2,(BitAction)(0)); //LED取反
            }
			BUZZER_BEEP1();
			delay_us(2000);
			BUZZER_BEEP1();
			while(!GPIO_ReadInputDataBit(KEYPORT,KEY1));
        }
		if(!GPIO_ReadInputDataBit(KEYPORT,KEY2))
		{
		    delay_ms(20); //延时去抖动
			BUZZER_BEEP1();
		}
		if (lightDarkType == 0)
		{
		    for (i = 0; i < 10; i++)
		    {
		        LED_Breathing_Lamp(dutyCycle);
		    }
		    dutyCycle++;
		    if (dutyCycle == 500)
		    {
		        lightDarkType = 1;    
		    }
		 }
		 if (lightDarkType == 1)
		 {
		     for (i = 0; i < 10; i++)
		     {
		         LED_Breathing_Lamp(dutyCycle);
		     }
		     dutyCycle--;
		     if (dutyCycle == 1)
		     {
		         lightDarkType = 0;    
		     }
		 }
	}
}

