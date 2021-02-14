#include "relay.h"

/**
 * �̵����Ľӿڳ�ʼ��
 */
void RELAY_Init(void){
    GPIO_InitTypeDef  GPIO_InitStructure;

    // APB2����ʱ��ʹ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);

    //����AFIO��ӳ�书��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // ѡ��˿ںţ�0~15��all��
    GPIO_InitStructure.GPIO_Pin = RELAY1 | RELAY2;

    // ѡ��IO�ӿڹ�����ʽ
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    // ����IO�ӿ��ٶȣ�2/10/50MHz��
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RELAYPORT, &GPIO_InitStructure);

    // ���뽫����JTAG���ܲ�����GPIOʹ��
    // �ı�ָ���ܽŵ�ӳ��,��ȫ����JTAG+SW-DP
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);

    //��Ϊ�͵�ƽ��0�� ��ʼΪ�ؼ̵���
    GPIO_ResetBits(RELAYPORT,RELAY1 | RELAY2);
}

/**
 * �̵����Ŀ��Ƴ���c=0�̵����ſ���c=1�̵������ϣ�
 */
void RELAY_1(u8 c){
    // ͨ������ֵд��ӿ�
    GPIO_WriteBit(RELAYPORT,RELAY1,(BitAction)(c));
}

/**
 * �̵����Ŀ��Ƴ���c=0�̵����ſ���c=1�̵������ϣ�
 */
void RELAY_2(u8 c){
    // ͨ������ֵд��ӿ�
    GPIO_WriteBit(RELAYPORT,RELAY2,(BitAction)(c));
}

