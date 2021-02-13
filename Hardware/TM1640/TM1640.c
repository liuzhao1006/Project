#include "TM1640.h"
#include "delay.h"

/**
 * �궨�壬ͨ�����ʣ�Ĭ��Ϊ1���粻��ͨ�ſɼӴ���ֵ��
 */
#define DEL 1

/**
 * ��ַģʽ������
 * �궨�� �̶���ַģʽ
 */
#define TM1640MEDO_ADD 0X44

/**
 * ��ʾ����������
 * �궨�� ����
 */
#define TM1640MEDO_DISPLAY 0X8C

/**
 * �궨�� ���ȹ�
 */
#define TM1640MEDO_DISPLAY_OFF 0X80

/**
 * ͨ��ʱ�� ��ʼ������GPIO���������Ͳ㣩
 */
void TM1640_start()
{
    // �ӿ�����ߵ�ƽ1
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_DIN, (BitAction)(1));
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_SCLK, (BitAction)(1));
    delay_us(DEL);
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_DIN, (BitAction)(0));
    delay_us(DEL);
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_SCLK, (BitAction)(0));
    delay_us(DEL);
}

/**
 * ͨѶʱ�� ����������GPIO���������Ͳ㣩
 */
void TM1640_stop()
{
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_DIN, (BitAction)(0));
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_SCLK, (BitAction)(1));
    delay_us(DEL);
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_DIN, (BitAction)(1));
    delay_us(DEL);
}

/**
 * д���ݣ��Ͳ㣩
 */
void TM1640_write(u8 data)
{
    u8 i;
    u8 aa;
    aa = data;
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_DIN, (BitAction)(0));
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_SCLK, (BitAction)(0));
    for(i = 0; i < 8; i++) {
        GPIO_WriteBit(TM1640_GPIOPORT, TM1640_SCLK, (BitAction)(0));
        delay_us(DEL);
        if(aa & 0x01) {
            GPIO_WriteBit(TM1640_GPIOPORT, TM1640_DIN, (BitAction)(1));
            delay_us(DEL);
        } else {
            GPIO_WriteBit(TM1640_GPIOPORT, TM1640_DIN, (BitAction)(0));
            delay_us(DEL);
        }
        GPIO_WriteBit(TM1640_GPIOPORT, TM1640_SCLK, (BitAction)(1));
        delay_us(DEL);
        aa = aa >> 1;
    }
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_DIN, (BitAction)(0));
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_SCLK, (BitAction)(0));
}

void TM1640_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);
    GPIO_InitStructure.GPIO_Pin = TM1640_DIN | TM1640_SCLK;

    // ѡ��˿ںţ�0~15 ���� all��
    // ѡ��IO�ӿڹ�����ʽ
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    // ����IO�ӿ��ٶȣ�2/10/50MHz��
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TM1640_GPIOPORT, &GPIO_InitStructure);

    // �ӿ�����ߵ�ƽ1
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_DIN, (BitAction)(1));

    // �ӿ�����ߵ�ƽ1
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_SCLK, (BitAction)(1));

    TM1640_start();

    // �������ݣ�0X40, 0X44�ֱ��Ӧ��ַ�Զ���һ�͹̶���ַģʽ
    TM1640_write(TM1640MEDO_ADD);
    TM1640_stop();
    TM1640_start();
    TM1640_write(TM1640MEDO_DISPLAY);
    TM1640_stop();
}

/**
 * �̶���ַģʽ����ʾ���8��LED����
 */
void TM1640_led(u8 data)
{
    TM1640_start();

    // ����ʾ���ݶ�Ӧ�ĵ�ַ
    TM1640_write(TM1640_LEDPORT);

    // ��1byte��ʾ����
    TM1640_write(data);
    TM1640_stop();
}

/**
 * �̶���ַģʽ����ʾ���
 */
void TM1640_display(u8 address,u8 data)
{
    const u8 buffer[21] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F,
        0X6F, 0XBF, 0X86, 0XDB, 0XCF, 0XE6, 0XED, 0XFD, 0X87, 0XFF, 0XEF, 0X00};
    TM1640_start();

    // ����ʾ���ݶ�Ӧ�ĵ�ַ
    TM1640_write(0XC0 + address);

    // ��1byte��ʾ����
    TM1640_write(buffer[data]);
    TM1640_stop();
}

/**
 * ��ַ�Զ���һģʽ����ʾ���
 */
void TM1640_display_add(u8 address,u8 data)
{
    u8 i;
    const u8 buffer[21] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F,
        0X6F, 0XBF, 0X86, 0XDB, 0XCF, 0XE6, 0XED, 0XFD, 0X87, 0XFF, 0XEF, 0X00};
    TM1640_start();

    // ����ʾ���ݶ�Ӧ�ĵ�ַ
    TM1640_write(0XC0 + address);
    for(i = 0; i < 16; i++) {
        TM1640_write(buffer[data]);
    }
    TM1640_stop();
}

