#ifndef __RELAY_H
#define __RELAY_H
#include "sys.h"

/**
 * ����IO�ӿ�
 */
#define RELAYPORT GPIOA

/**
 * ����IO�ӿ�
 */
#define RELAY1 GPIO_Pin_14

/**
 * ����IO�ӿ�
 */
#define RELAY2 GPIO_Pin_13

/**
 * �̵�����ʼ��
 */
void RELAY_Init(void);

/**
 * �̵�������1
 */
void RELAY_1(u8 c);

/**
 * �̵�������2
 */
void RELAY_2(u8 c);

#endif
