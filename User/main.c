#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "touch_key.h"

#define BAUD_RATE 115200	  //д�����ʼ��ַ

int main (void)
{		
	// ��ʼ������
    RCC_Configuration(); 
	
	LED_Init();

	while(1)
	{
	    if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A)) {
		    GPIO_WriteBit(LEDPORT, LED1, (BitAction)(1));
		}
		if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_B)) {
			GPIO_WriteBit(LEDPORT, LED2, (BitAction)(1));
		}  
		if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_C)) {
			GPIO_WriteBit(LEDPORT, LED1 | LED2, (BitAction)(0));
		}  
		if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_D)) {
			GPIO_WriteBit(LEDPORT, LED1 | LED2, (BitAction)(1));
		}
	}
}

