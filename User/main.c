#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"	
#include "usart.h"

#define BAUD_RATE 115200	  //д�����ʼ��ַ

int main (void)
{			
    u8 a;
	 
	// ��ʼ������
    RCC_Configuration();

	uart_init(BAUD_RATE);

	while(1)
	{
        if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
		{
		    a = USART_ReceiveData(USART1);
			printf("%c", a);
		}
	}
}

