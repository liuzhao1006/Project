#include "oled0561.h"
#include "ASCII_8x16.h"
#include "CHS_16x16.h"
#include "PIC1.h"

/**
 * OLED屏开显示初始化
 */
void OLED0561_Init (void){
    // OLED关显示
    OLED_DISPLAY_OFF();

    // 清空屏幕内容
    OLED_DISPLAY_CLEAR();

    // OLED屏初始值设置并开显示
    OLED_DISPLAY_ON();

}

/**
 * OLED屏初始值设置并开显示
 */
void OLED_DISPLAY_ON (void){
    u8 buf[28]={
    0xae,//0xae:关显示，0xaf:开显示
    0x00,0x10,//开始地址（双字节）       
    0xd5,0x80,//显示时钟频率？
    0xa8,0x3f,//复用率？
    0xd3,0x00,//显示偏移？
    0XB0,//写入页位置（0xB0~7）
    0x40,//显示开始线
    0x8d,0x14,//VCC电源
    0xa1,//设置段重新映射？
    0xc8,//COM输出方式？
    0xda,0x12,//COM输出方式？
    0x81,0xff,//对比度，指令：0x81，数据：0~255（255最高）
    0xd9,0xf1,//充电周期？
    0xdb,0x30,//VCC电压输出
    0x20,0x00,//水平寻址设置
    0xa4,//0xa4:正常显示，0xa5:整体点亮
    0xa6,//0xa6:正常显示，0xa7:反色显示
    0xaf//0xae:关显示，0xaf:开显示
    }; //
    I2C_SAND_BUFFER(OLED0561_ADD,COM,buf,28);
}

/**
 * OLED屏关显示
 */
void OLED_DISPLAY_OFF (void){
    u8 buf[3]={
        0xae,//0xae:关显示，0xaf:开显示
        0x8d,0x10,//VCC电源
    };
    I2C_SAND_BUFFER(OLED0561_ADD,COM,buf,3);
}

/**
 * OLED屏亮度设置（0~255）
 */
void OLED_DISPLAY_LIT (u8 x){
    I2C_SAND_BYTE(OLED0561_ADD,COM,0x81);

    // 亮度值
    I2C_SAND_BYTE(OLED0561_ADD,COM,x);
}

/**
 * 清屏操作
 */
void OLED_DISPLAY_CLEAR(void){
    u8 j,t;

    // 设置起始页地址为0xB0
    for(t=0xB0;t<0xB8;t++){
        // 页地址（从0xB0到0xB7）
        I2C_SAND_BYTE(OLED0561_ADD,COM,t);

        // 起始列地址的高4位
        I2C_SAND_BYTE(OLED0561_ADD,COM,0x10);

        // 起始列地址的低4位
        I2C_SAND_BYTE(OLED0561_ADD,COM,0x00);

        // 整页内容填充
        for(j=0;j<132;j++){
            I2C_SAND_BYTE(OLED0561_ADD,DAT,0x00);
        }
    }
}

/**
 * 显示英文与数字8*16的ASCII码
 * 取模大小为16*16，取模方式为“从左到右从上到下”“纵向8点下高位”
 *
 * @param x 显示汉字的页坐标（从0到7）（此处不可修改）
 * @param y 显示汉字的列坐标（从0到63）
 * @param w 要显示汉字的编号
 */
void OLED_DISPLAY_8x16(u8 x, u8 y, u16 w){
    u8 j,t,c=0;

    // 因OLED屏的内置驱动芯片是从0x02列作为屏上最左一列，所以要加上偏移量
    y=y+2;
    for(t=0;t<2;t++){
        // 页地址（从0xB0到0xB7）
        I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+x);

        // 起始列地址的高4位
        I2C_SAND_BYTE(OLED0561_ADD,COM,y/16+0x10);

        // 起始列地址的低4位
        I2C_SAND_BYTE(OLED0561_ADD,COM,y%16);

        // 整页内容填充
        for(j=0;j<8;j++){
            // 为了和ASII表对应要减512
            I2C_SAND_BYTE(OLED0561_ADD,DAT,ASCII_8x16[(w*16)+c-512]);

            //页地址加1
            c++;
        }
        x++;
    }
}

/**
 * 向LCM发送一个字符串,长度64字符之内。
 * 应用：OLED_DISPLAY_8_16_BUFFER(0," LiuZhao Studio"); 
 */
void OLED_DISPLAY_8x16_BUFFER(u8 row,u8 *str){
    u8 r=0;
    while(*str != '\0'){
        OLED_DISPLAY_8x16(row,r*8,*str++);
        r++;
    }
}

/**
 * 显示汉字16*16
 * 取模大小为16*16，取模方式为“从左到右从上到下”“纵向8点下高位”
 * @param x 显示汉字的页坐标（从0xB0到0xB7）
 * @param y 显示汉字的列坐标（从0到63）
 * @param w 要显示汉字的编号
 */
void OLED_DISPLAY_16x16(u8 x, u8 y, u16 w){
    u8 j,t,c=0;
    for(t=0;t<2;t++){
    // 页地址（从0xB0到0xB7）
        I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+x);

        // 起始列地址的高4位
        I2C_SAND_BYTE(OLED0561_ADD,COM,y/16+0x10);

        //起始列地址的低4位
        I2C_SAND_BYTE(OLED0561_ADD,COM,y%16);

        //整页内容填充
        for(j=0;j<16;j++){
            I2C_SAND_BYTE(OLED0561_ADD,DAT,GB_16[(w*32)+c]);

            //页地址加1
            c++;
        }
        x++;
    }

    //开显示 
    I2C_SAND_BYTE(OLED0561_ADD,COM,0xAF);
}

/**
 * 显示全屏图片
 */
void OLED_DISPLAY_PIC1(void) {
    u8 m,i;
    for(m=0;m<8;m++) {
        I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+m);

        // 起始列地址的高4位
        I2C_SAND_BYTE(OLED0561_ADD,COM,0x10);

        // 起始列地址的低4位
        I2C_SAND_BYTE(OLED0561_ADD,COM,0x02);

        // 送入128次图片显示内容
        for(i=0;i<128;i++){
            I2C_SAND_BYTE(OLED0561_ADD,DAT,PIC1[i+m*128]);
        }
    }
}

