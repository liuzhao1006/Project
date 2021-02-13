#ifndef __ENCODER_H
#define __ENCODER_H
#include "sys.h"
#include "delay.h"

/**
 * ����IO�ӿ���
 */
#define ENCODER_PORT_A GPIOA

/**
 * ����IO�ӿ�
 */
#define ENCODER_L GPIO_Pin_6

/**
 * ����IO�ӿ�
 */
#define ENCODER_D GPIO_Pin_7

/**
 * ����IO�ӿ���
 */
#define ENCODER_PORT_B GPIOB

/**
 * ����IO�ӿ�
 */
#define ENCODER_R GPIO_Pin_2

void ENCODER_Init(void);

u8 ENCODER_READ(void);

#endif

