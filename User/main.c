#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"	
#include "led.h"  	
#include "key.h"     	
#include "flash.h"
#include "buzzer.h"
#include "usart.h"

#define FLASH_START_ADDR  0x0801f000	  //д�����ʼ��ַ
#define Baud_Rate  115200	  //д�����ʼ��ַ

int main (void)
{			 
	// ��������
	u8 lightDarkType;

	//���ں����Ƶ�ռ�ձ�
	u16 dutyCycle, i, a;

	// ��ʼ������
    RCC_Configuration();

	// ��ʼ��LED������
	LED_Init();

	// ��ʼ��KEY����
	KEY_Init();

	uart_init(Baud_Rate);

	BUZZER_Init();
	//BUZZER_BEEP1();
	MIDI_PLAY();

	//��ָ��ҳ�ĵ�ַ��FLASH
	a = FLASH_R(FLASH_START_ADDR);

	//ֱ����ֵ����������ֵд��LED��LED��GPIOB���PB0��PB1�ϣ�
	GPIO_Write(LEDPORT,a); 
	lightDarkType = 0;
    dutyCycle = 1;
	while(1)
	{
	    // USART_SendData(USART1 , 0x55);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
	    if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){ //�������ӿڵĵ�ƽ
            delay_ms(20); //��ʱȥ����
            if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){ //�������ӿڵĵ�ƽ
                GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0)); //LEDȡ��
                GPIO_WriteBit(LEDPORT,LED2,(BitAction)(0)); //LEDȡ��
            }
			BUZZER_BEEP1();
			delay_us(2000);
			BUZZER_BEEP1();
			while(!GPIO_ReadInputDataBit(KEYPORT,KEY1));
        }
		if(!GPIO_ReadInputDataBit(KEYPORT,KEY2))
		{
		    delay_ms(20); //��ʱȥ����
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

