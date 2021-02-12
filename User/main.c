#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "buzzer.h"	
#include "usart.h"	 	
#include "rtc.h"

#define BAUD_RATE 115200	  //д�����ʼ��ַ

int main (void)
{			
	// ��ʼ������
    RCC_Configuration();

	LED_Init();

	KEY_Init();

	BUZZER_Init();

	USART1_Init(BAUD_RATE);

	USART1_RX_STA=0xC000;

	while(1)
	{
        
		if(USART1_RX_STA&0xC000){ //�����־λ��0xC000��ʾ�յ����ݴ���ɣ����Դ���
			if((USART1_RX_STA&0x3FFF)==0){ //�����Ļس�������ʾһ�λ�ӭ��
				printf("\033[1;47;33m\r\n"); //������ɫ���ο������ն�ʹ�ã�
				printf(" 1y--��LED1��      1n--��LED1�� \r\n");
				printf(" 2y--��LED2��      2n--��LED2�� \r\n");
				printf(" ���������ָ����س���ִ�У� \033[0m\r\n");
			}else if((USART1_RX_STA&0x3FFF)==2 && USART1_RX_BUF[0]=='1' && USART1_RX_BUF[1]=='y'){ //�ж������ǲ���2������һ�������ǲ��ǡ�1�����ڶ����ǲ��ǡ�y��
				GPIO_SetBits(LEDPORT,LED1); //LED�ƶ�Ϊ�ߵ�ƽ��1��
				printf("1y -- LED1���Ѿ�������\r\n");
			}else if((USART1_RX_STA&0x3FFF)==2 && USART1_RX_BUF[0]=='1' && USART1_RX_BUF[1]=='n'){
				GPIO_ResetBits(LEDPORT,LED1); ////LED�ƶ�Ϊ�͵�ƽ��0��
				printf("1n -- LED1���Ѿ�Ϩ��\r\n");
			}else if((USART1_RX_STA&0x3FFF)==2 && USART1_RX_BUF[0]=='2' && USART1_RX_BUF[1]=='y'){
				GPIO_SetBits(LEDPORT,LED2); //LED�ƶ�Ϊ�ߵ�ƽ��1��
				printf("2y -- LED2���Ѿ�������\r\n");
			}else if((USART1_RX_STA&0x3FFF)==2 && USART1_RX_BUF[0]=='2' && USART1_RX_BUF[1]=='n'){
				GPIO_ResetBits(LEDPORT,LED2); ////LED�ƶ�Ϊ�͵�ƽ��0��
				printf("2n -- LED2���Ѿ�Ϩ��\r\n");
			}else{ //������϶����ǣ����Ǵ����ָ�
				printf("ָ�����\r\n"); 
			}
			USART1_RX_STA=0; //���������ݱ�־λ��0
		}
		if (RTC_Get() == 0) {
			GPIO_WriteBit(LEDPORT,LED1,(BitAction)(rsec%2)); //LED1�ӿ�
			GPIO_WriteBit(LEDPORT,LED2,(BitAction)(rmin%2)); //LED2�ӿ�
		}
	}
}

