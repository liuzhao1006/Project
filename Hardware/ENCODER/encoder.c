#include "encoder.h"

/**
 * ��ť������־��1Ϊ������
 */
u8 KUP;

u16 cou;

void ENCODER_Init(void)
{
    // ����GPIO�ĳ�ʼ��ö�ٽṹ
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
    
    //ѡ��˿ں�
    GPIO_InitStructure.GPIO_Pin = ENCODER_L | ENCODER_D;

    // ѡ��io�ӿڹ�����ʽ����������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(ENCODER_PORT_A, &GPIO_InitStructure);

    // ѡ��˿ں�
    GPIO_InitStructure.GPIO_Pin = ENCODER_R;

    // ѡ��io�ӿڹ�����ʽ����������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(ENCODER_PORT_B, &GPIO_InitStructure);
}

/**
 * �ӿڳ�ʼ��
 */
u8 ENCODER_READ(void)
{
    // ��Ű�����ֵ
    u8 a;
    u8 kt;
    a = 0;
    if(GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_L)) {
        // �ж���ť�Ƿ�������
        KUP = 0;
    }
    if(!GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_L) && KUP == 0) {
        // �ж��Ƿ���ת��ť��ͬʱ�ж��Ƿ�����ť����
        delay_us(100);

        // ����ť��һ�˵�ƽ״̬��¼
        kt = GPIO_ReadInputDataBit(ENCODER_PORT_B, ENCODER_R);
        delay_ms(3);

        // ȥ����
        if(!GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_L)) {
            // ����һ���ж��������ת
            if(kt == 0) {
                // ��ת
                a = 1;
            } else {
                // ��ת
                a = 2;
            }

            // ��ʼ�����жϼ�����
            cou = 0;
            while(!GPIO_ReadInputDataBit(ENCODER_PORT_A,ENCODER_L) && cou < 60000) {
                // �ȴ��ſ���ť��ͬʱ�ۼ��ж�����
                cou++;
                KUP = 1;
                delay_us(20);
            }
        }
    }

    // �ж���ť�Ƿ���
    if(!GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_D) && KUP == 0) {
        delay_ms(20);

        // ȥ����
        if(!GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_D)) {
            // �ڰ�������ʱ���ϰ�����״ֵ̬
            a = 3;
        }
    }
    return a;
}

