#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "touch_key.h" 
#include "usart.h"

#define BAUD_RATE 115200      //д�����ʼ��ַ
#define KEYA_SPEED1 100       //������ʱ�䳤��
#define KEYA_SPEED2 10        // ˫����ʱ�䳤��

int main (void)
{
    //���ڻ����Ӽ�����	
    u16 k=1000;

    //���ڻ����Ӽ�����
    u8 a = 0, b, c = 0;

    // ���������ı�־
    u8 s = 0;

    // ��ʼ������
    RCC_Configuration(); 

    LED_Init();

    USART1_Init(BAUD_RATE);

    TOUCH_KEY_Init();

    while(1)
    {
        //���A�����Ƿ���
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
                    printf("A������ \r\n");
                    while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A));
                } else {
                    if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_B)) {
                        k++;
                        printf("A���һ� %d \r\n", k);
                        a = 1;
                        s = 1;
                    }
                    if (a == 0) {
                        // ��������
                        for (b = 0; b < KEYA_SPEED2; b++) {
                            delay_ms(20);
                            if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A)) {
                                a = 1;
                                printf("A��˫�� \r\n");
                                GPIO_WriteBit(LEDPORT, LED2, (BitAction)(1));
                                while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A));
                            }
                        }
                        if (a == 0) {
                            if (s == 1) {
                                s = 0;
                            } else {
                                GPIO_WriteBit(LEDPORT, LED1 | LED2, (BitAction)(0));
                                printf("A������ \r\n");
                            }
                        }
                    }
                }
            }

            // ��������
            a = 0;
            c = 0;
        }

        //���B�����Ƿ���
        if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_B)) {
            // ��ʱȥ����
            delay_ms(20);

            // �жϳ��̼�
            if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_B)) {
                // ѭ���жϳ�������ʱ��ת
                while ((!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_B)) && c < KEYA_SPEED1) {
                    c++;
                    // �����жϵļ�ʱ
                    delay_ms(10);
                }

                // ��������
                if (c >= KEYA_SPEED1) {
                    GPIO_WriteBit(LEDPORT, LED1, (BitAction)(1));
                    printf("B������ \r\n");
                    while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_B));
                } else {
                    if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_C)) {
                        k++;
                        printf("B���һ� %d \r\n", k);
                        a = 1;
                        s = 1;
                    }
                    if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_A)) {
                        k--;
                        printf("B���� %d \r\n", k);
                        a = 1;
                        s = 1;
                    }
                    if (a == 0) {
                        // ��������
                        for (b = 0; b < KEYA_SPEED2; b++) {
                            delay_ms(20);
                            if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_B)) {
                                a = 1;
                                printf("B��˫�� \r\n");
                                GPIO_WriteBit(LEDPORT, LED2, (BitAction)(1));
                                while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_B));
                            }
                        }
                        if (a == 0) {
                            if (s == 1) {
                                s = 0;
                            } else {
                                GPIO_WriteBit(LEDPORT, LED1 | LED2, (BitAction)(0));
                                printf("B������ \r\n");
                            }
                        }
                    }
                }
            }

            // ��������
            a = 0;
            c = 0;
        }

        //���C�����Ƿ���
        if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_C)) {
            // ��ʱȥ����
            delay_ms(20);

            // �жϳ��̼�
            if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_C)) {
                // ѭ���жϳ�������ʱ��ת
                while ((!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_C)) && c < KEYA_SPEED1) {
                    c++;
                    // �����жϵļ�ʱ
                    delay_ms(10);
                }

                // ��������
                if (c >= KEYA_SPEED1) {
                    GPIO_WriteBit(LEDPORT, LED1, (BitAction)(1));
                    printf("C������ \r\n");
                    while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_C));
                } else {
                    if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_D)) {
                        k++;
                        printf("C���һ� %d \r\n", k);
                        a = 1;
                        s = 1;
                    }
                    if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_B)) {
                        k--;
                        printf("C���� %d \r\n", k);
                        a = 1;
                        s = 1;
                    }
                    if (a == 0) {
                        // ��������
                        for (b = 0; b < KEYA_SPEED2; b++) {
                            delay_ms(20);
                            if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_C)) {
                                a = 1;
                                printf("C��˫�� \r\n");
                                GPIO_WriteBit(LEDPORT, LED2, (BitAction)(1));
                                while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_C));
                            }
                        }
                        if (a == 0) {
                            if (s == 1) {
                                s = 0;
                            } else {
                                GPIO_WriteBit(LEDPORT, LED1 | LED2, (BitAction)(0));
                                printf("C������ \r\n");
                            }
                        }
                    }
                }
            }

            // ��������
            a = 0;
            c = 0;
        }

        //���A�����Ƿ���
        if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_D)) {
            // ��ʱȥ����
            delay_ms(20);

            // �жϳ��̼�
            if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_D)) {
                // ѭ���жϳ�������ʱ��ת
                while ((!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_D)) && c < KEYA_SPEED1) {
                    c++;
                    // �����жϵļ�ʱ
                    delay_ms(10);
                }

                // ��������
                if (c >= KEYA_SPEED1) {
                    GPIO_WriteBit(LEDPORT, LED1, (BitAction)(1));
                    printf("D������ \r\n");
                    while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_D));
                } else {
                    if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_C)) {
                        k--;
                        printf("D���� %d \r\n", k);
                        a = 1;
                        s = 1;
                    }
                    if (a == 0) {
                        // ��������
                        for (b = 0; b < KEYA_SPEED2; b++) {
                            delay_ms(20);
                            if (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_D)) {
                                a = 1;
                                printf("D��˫�� \r\n");
                                GPIO_WriteBit(LEDPORT, LED2, (BitAction)(1));
                                while (!GPIO_ReadInputDataBit(TOUCH_KEYPORT, TOUCH_KEY_D));
                            }
                        }
                        if (a == 0) {
                            if (s == 1) {
                                s = 0;
                            } else {
                                GPIO_WriteBit(LEDPORT, LED1 | LED2, (BitAction)(0));
                                printf("D������ \r\n");
                            }
                        }
                    }
                }
            }

            // ��������
            a = 0;
            c = 0;
        }
    }
}

