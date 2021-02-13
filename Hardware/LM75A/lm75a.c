#include "lm75a.h"

/**
 * 读出LM75A的温度值（-55~125摄氏度）
 * 温度正负号（0正1负），温度整数，温度小数（点后2位）依次放入*Tempbuffer（十进制）
 */
void LM75A_GetTemp(u8 *Tempbuffer){   
    // 温度值储存
    u8 buf[2];    
    u8 t=0,a=0;   

    // 读出温度值（器件地址，子地址，数据储存器，字节数）
    I2C_READ_BUFFER(LM75A_ADD,0x00,buf,2); 
    
    // 处理温度整数部分，0~125度
    t = buf[0]; 

    // 温度值为正值
    *Tempbuffer = 0; 
    
    // 判断温度是否是负（MSB表示温度符号）
    if(t & 0x80){ 
        //温度值为负值
        *Tempbuffer = 1; 
        
        // 计算补码（原码取反后加1）
        t = ~t; t++; 
    }

    // 从高到低按位加入温度积加值（0~125）
    if(t & 0x01){ a=a+1; } 
    if(t & 0x02){ a=a+2; }
    if(t & 0x04){ a=a+4; }
    if(t & 0x08){ a=a+8; }
    if(t & 0x10){ a=a+16; }
    if(t & 0x20){ a=a+32; }
    if(t & 0x40){ a=a+64; }
    Tempbuffer++;
    *Tempbuffer = a;
    a = 0;

    // 处理小数部分，取0.125精度的前2位（12、25、37、50、62、75、87）
    t = buf[1]; 
    if(t & 0x20){ a=a+12; }
    if(t & 0x40){ a=a+25; }
    if(t & 0x80){ a=a+50; }
    Tempbuffer++;
    *Tempbuffer = a;   
}

/**
 * LM75进入掉电模式，再次调用LM75A_GetTemp();即可正常工作
 * 建议只在需要低功耗情况下使用
 */
void LM75A_POWERDOWN(void){
    I2C_SAND_BYTE(LM75A_ADD,0x01,1);
}

