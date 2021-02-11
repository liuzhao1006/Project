#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "buzzer.h"	
#include "usart.h"

#define BAUD_RATE 115200	  //写入的起始地址

int main (void)
{			
    u8 a;
	 
	// 初始化配置
    RCC_Configuration();

	LED_Init();

	KEY_Init();

	BUZZER_Init();

	uart_init(BAUD_RATE);

	while(1)
	{
        if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET) {
		    a = USART_ReceiveData(USART1);
			switch (a)
			{
			    case '0':
				    GPIO_WriteBit(LEDPORT, LED1, (BitAction)0);
					printf("%c: LED1 OFF", a);
				    break; 
			    case '1':
				    GPIO_WriteBit(LEDPORT, LED1, (BitAction)1);
					printf("%c: LED1 ON", a);
				    break; 
			    case '2':
				    BUZZER_BEEP1();
					printf("%c: BUZZER", a);
				    break;
				default:
				    
					break;
			}
		}

		// 按键控制
		if (!GPIO_ReadInputDataBit(KEYPORT, KEY1)) {
			delay_ms(20);
			if (!GPIO_ReadInputDataBit(KEYPORT, KEY1)) {
				while(!GPIO_ReadInputDataBit(KEYPORT, KEY1));
				printf("KEY1 ");
			}
		}

		if (!GPIO_ReadInputDataBit(KEYPORT, KEY2)) {
			delay_ms(20);
			if (!GPIO_ReadInputDataBit(KEYPORT, KEY2)) {
			    while (!GPIO_ReadInputDataBit(KEYPORT, KEY2));
				printf("KEY2 ");
			}
		}
	}
}

