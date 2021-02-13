#include "TM1640.h"
#include "delay.h"

/**
 * 宏定义，通信速率（默认为1，如不能通信可加大数值）
 */
#define DEL 1

/**
 * 地址模式的设置
 * 宏定义 固定地址模式
 */
#define TM1640MEDO_ADD 0X44

/**
 * 显示连读的设置
 * 宏定义 亮度
 */
#define TM1640MEDO_DISPLAY 0X8C

/**
 * 宏定义 亮度关
 */
#define TM1640MEDO_DISPLAY_OFF 0X80

/**
 * 通信时序 起始（基础GPIO操作）（低层）
 */
void TM1640_start()
{
    // 接口输出高电平1
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_DIN, (BitAction)(1));
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_SCLK, (BitAction)(1));
    delay_us(DEL);
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_DIN, (BitAction)(0));
    delay_us(DEL);
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_SCLK, (BitAction)(0));
    delay_us(DEL);
}

/**
 * 通讯时序 结束（基础GPIO操作）（低层）
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
 * 写数据（低层）
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

    // 选择端口号（0~15 或者 all）
    // 选择IO接口工作方式
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    // 设置IO接口速度（2/10/50MHz）
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TM1640_GPIOPORT, &GPIO_InitStructure);

    // 接口输出高电平1
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_DIN, (BitAction)(1));

    // 接口输出高电平1
    GPIO_WriteBit(TM1640_GPIOPORT, TM1640_SCLK, (BitAction)(1));

    TM1640_start();

    // 设置数据，0X40, 0X44分别对应地址自动加一和固定地址模式
    TM1640_write(TM1640MEDO_ADD);
    TM1640_stop();
    TM1640_start();
    TM1640_write(TM1640MEDO_DISPLAY);
    TM1640_stop();
}

/**
 * 固定地址模式的显示输出8个LED控制
 */
void TM1640_led(u8 data)
{
    TM1640_start();

    // 传显示数据对应的地址
    TM1640_write(TM1640_LEDPORT);

    // 传1byte显示数据
    TM1640_write(data);
    TM1640_stop();
}

/**
 * 固定地址模式的显示输出
 */
void TM1640_display(u8 address,u8 data)
{
    const u8 buffer[21] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F,
        0X6F, 0XBF, 0X86, 0XDB, 0XCF, 0XE6, 0XED, 0XFD, 0X87, 0XFF, 0XEF, 0X00};
    TM1640_start();

    // 传显示数据对应的地址
    TM1640_write(0XC0 + address);

    // 传1byte显示数据
    TM1640_write(buffer[data]);
    TM1640_stop();
}

/**
 * 地址自动加一模式的显示输出
 */
void TM1640_display_add(u8 address,u8 data)
{
    u8 i;
    const u8 buffer[21] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F,
        0X6F, 0XBF, 0X86, 0XDB, 0XCF, 0XE6, 0XED, 0XFD, 0X87, 0XFF, 0XEF, 0X00};
    TM1640_start();

    // 传显示数据对应的地址
    TM1640_write(0XC0 + address);
    for(i = 0; i < 16; i++) {
        TM1640_write(buffer[data]);
    }
    TM1640_stop();
}

