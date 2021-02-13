#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "touch_key.h"

#define BAUD_RATE 115200	  //д�����ʼ��ַ
#define KEYA_SPEED1 100       //������ʱ�䳤��
#define KEYA_SPEED2 10		  // ˫����ʱ�䳤��				   

int main (void)
{	
    u8 a = 0, b, c = 0;
		
	// ��ʼ������
    RCC_Configuration(); 
	
	LED_Init();

	TOUCH_KEY_Init();

	while(1)
	{
	    //��ⰴ���Ƿ���
	    if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A)) {
		    // ��ʱȥ����
			delay_ms(20);

			// �жϳ��̼�
			if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A)) {
			    // ѭ���жϳ�������ʱ��ת
				while ((!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A)) && c < KEYA_SPEED1) {
			        c++;
					// �����жϵļ�ʱ
					delay_ms(10);		
				}

				// ��������
				if (c >= KEYA_SPEED1) {
				    GPIO_WriteBit(LEDPORT, LED1, (BitAction)(1));
					while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A));
				} else {
				    // ��������
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

