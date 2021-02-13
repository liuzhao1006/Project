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
	u8 bya;	
	// ��ʼ������
    RCC_Configuration();
	
    RTC_Config(); 
	
	LED_Init();

	KEY_Init();

	BUZZER_Init();

	USART1_Init(BAUD_RATE);

	USART1_RX_STA=0xC000;

	while(1)
	{
	    // �����־λ��0XC000��ʾ�յ����ݴ�����ɣ����Դ���
        if(USART1_RX_STA&0xC000){ //�����־λ��0xC000��ʾ�յ����ݴ���ɣ����Դ���
			if((USART1_RX_STA&0x3FFF)==0){ //�����Ļس�������ʾһ�λ�ӭ��
				if(RTC_Get()==0){ //����ʱ��ֵ��ͬʱ�жϷ���ֵ�ǲ���0����0ʱ��ȡ��ֵ�Ǵ���ġ�
					printf(" ���ҿ�����STM32ʵʱʱ�Ӳ��Գ���   \r\n");
					printf(" ����ʵʱʱ�䣺%d-%d-%d %d:%d:%d  ",ryear,rmon,rday,rhour,rmin,rsec);//��ʾ����ʱ��
					if(rweek==0)printf("������   \r\n");//rweekֵΪ0ʱ��ʾ������
					if(rweek==1)printf("����һ   \r\n");
					if(rweek==2)printf("���ڶ�   \r\n");
					if(rweek==3)printf("������   \r\n");
					if(rweek==4)printf("������   \r\n");
					if(rweek==5)printf("������   \r\n");
					if(rweek==6)printf("������   \r\n");
					printf(" �����س�������ʱ�䡣������ĸC��ʼ��ʱ�� \r\n");
					printf(" ����������ʱ�䣬��ʽ20170806120000�����س���ȷ���� \r\n");
				}else{
					printf("��ȡʧ�ܣ�\r\n");
				}
			}else if((USART1_RX_STA&0x3FFF)==1){ //�ж������ǲ���2��
				if(USART1_RX_BUF[0]=='c' || USART1_RX_BUF[0]=='C'){
					RTC_First_Config(); //��������c��C����ʼ��ʱ��
					BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);//������ɺ���󱸼Ĵ�����д�����ַ�0xA5A5
					printf("��ʼ���ɹ���      \r\n");//��ʾ��ʼ���ɹ�
				}else{
					printf("ָ�����          \r\n"); //��ʾָ�����
				} 
			}else if((USART1_RX_STA&0x3FFF)==14){ //�ж������ǲ���14��
				//�������ն˷����������ݻ��㲢д��RTC
				ryear = (USART1_RX_BUF[0]-0x30)*1000+(USART1_RX_BUF[1]-0x30)*100+(USART1_RX_BUF[2]-0x30)*10+USART1_RX_BUF[3]-0x30;
				rmon = (USART1_RX_BUF[4]-0x30)*10+USART1_RX_BUF[5]-0x30;//���ڷ��������ַ�����0x30����ܵõ�ʮ����0~9������
				rday = (USART1_RX_BUF[6]-0x30)*10+USART1_RX_BUF[7]-0x30;
				rhour = (USART1_RX_BUF[8]-0x30)*10+USART1_RX_BUF[9]-0x30;
				rmin = (USART1_RX_BUF[10]-0x30)*10+USART1_RX_BUF[11]-0x30;
				rsec = (USART1_RX_BUF[12]-0x30)*10+USART1_RX_BUF[13]-0x30;
				bya=RTC_Set(ryear,rmon,rday,rhour,rmin,rsec); //������д��RTC�������ĳ���
				if(bya==0)printf("д��ɹ���      \r\n");//��ʾд��ɹ� 
				else printf("д��ʧ�ܣ�       \r\n"); //��ʾд��ʧ��
			}
			USART1_RX_STA=0; //���������ݱ�־λ��0
		} 
		if (RTC_Get() == 0) {
			GPIO_WriteBit(LEDPORT,LED1,(BitAction)(rsec%2)); //LED1�ӿ�
			GPIO_WriteBit(LEDPORT,LED2,(BitAction)(rmin%2)); //LED2�ӿ�
		}
	}
}

