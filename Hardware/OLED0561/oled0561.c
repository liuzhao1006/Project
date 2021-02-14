#include "oled0561.h"
#include "ASCII_8x16.h"
#include "CHS_16x16.h"
#include "PIC1.h"

/**
 * OLED������ʾ��ʼ��
 */
void OLED0561_Init (void){
    // OLED����ʾ
    OLED_DISPLAY_OFF();

    // �����Ļ����
    OLED_DISPLAY_CLEAR();

    // OLED����ʼֵ���ò�����ʾ
    OLED_DISPLAY_ON();

}

/**
 * OLED����ʼֵ���ò�����ʾ
 */
void OLED_DISPLAY_ON (void){
    u8 buf[28]={
    0xae,//0xae:����ʾ��0xaf:����ʾ
    0x00,0x10,//��ʼ��ַ��˫�ֽڣ�       
    0xd5,0x80,//��ʾʱ��Ƶ�ʣ�
    0xa8,0x3f,//�����ʣ�
    0xd3,0x00,//��ʾƫ�ƣ�
    0XB0,//д��ҳλ�ã�0xB0~7��
    0x40,//��ʾ��ʼ��
    0x8d,0x14,//VCC��Դ
    0xa1,//���ö�����ӳ�䣿
    0xc8,//COM�����ʽ��
    0xda,0x12,//COM�����ʽ��
    0x81,0xff,//�Աȶȣ�ָ�0x81�����ݣ�0~255��255��ߣ�
    0xd9,0xf1,//������ڣ�
    0xdb,0x30,//VCC��ѹ���
    0x20,0x00,//ˮƽѰַ����
    0xa4,//0xa4:������ʾ��0xa5:�������
    0xa6,//0xa6:������ʾ��0xa7:��ɫ��ʾ
    0xaf//0xae:����ʾ��0xaf:����ʾ
    }; //
    I2C_SAND_BUFFER(OLED0561_ADD,COM,buf,28);
}

/**
 * OLED������ʾ
 */
void OLED_DISPLAY_OFF (void){
    u8 buf[3]={
        0xae,//0xae:����ʾ��0xaf:����ʾ
        0x8d,0x10,//VCC��Դ
    };
    I2C_SAND_BUFFER(OLED0561_ADD,COM,buf,3);
}

/**
 * OLED���������ã�0~255��
 */
void OLED_DISPLAY_LIT (u8 x){
    I2C_SAND_BYTE(OLED0561_ADD,COM,0x81);

    // ����ֵ
    I2C_SAND_BYTE(OLED0561_ADD,COM,x);
}

/**
 * ��������
 */
void OLED_DISPLAY_CLEAR(void){
    u8 j,t;

    // ������ʼҳ��ַΪ0xB0
    for(t=0xB0;t<0xB8;t++){
        // ҳ��ַ����0xB0��0xB7��
        I2C_SAND_BYTE(OLED0561_ADD,COM,t);

        // ��ʼ�е�ַ�ĸ�4λ
        I2C_SAND_BYTE(OLED0561_ADD,COM,0x10);

        // ��ʼ�е�ַ�ĵ�4λ
        I2C_SAND_BYTE(OLED0561_ADD,COM,0x00);

        // ��ҳ�������
        for(j=0;j<132;j++){
            I2C_SAND_BYTE(OLED0561_ADD,DAT,0x00);
        }
    }
}

/**
 * ��ʾӢ��������8*16��ASCII��
 * ȡģ��СΪ16*16��ȡģ��ʽΪ�������Ҵ��ϵ��¡�������8���¸�λ��
 *
 * @param x ��ʾ���ֵ�ҳ���꣨��0��7�����˴������޸ģ�
 * @param y ��ʾ���ֵ������꣨��0��63��
 * @param w Ҫ��ʾ���ֵı��
 */
void OLED_DISPLAY_8x16(u8 x, u8 y, u16 w){
    u8 j,t,c=0;

    // ��OLED������������оƬ�Ǵ�0x02����Ϊ��������һ�У�����Ҫ����ƫ����
    y=y+2;
    for(t=0;t<2;t++){
        // ҳ��ַ����0xB0��0xB7��
        I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+x);

        // ��ʼ�е�ַ�ĸ�4λ
        I2C_SAND_BYTE(OLED0561_ADD,COM,y/16+0x10);

        // ��ʼ�е�ַ�ĵ�4λ
        I2C_SAND_BYTE(OLED0561_ADD,COM,y%16);

        // ��ҳ�������
        for(j=0;j<8;j++){
            // Ϊ�˺�ASII���ӦҪ��512
            I2C_SAND_BYTE(OLED0561_ADD,DAT,ASCII_8x16[(w*16)+c-512]);

            //ҳ��ַ��1
            c++;
        }
        x++;
    }
}

/**
 * ��LCM����һ���ַ���,����64�ַ�֮�ڡ�
 * Ӧ�ã�OLED_DISPLAY_8_16_BUFFER(0," LiuZhao Studio"); 
 */
void OLED_DISPLAY_8x16_BUFFER(u8 row,u8 *str){
    u8 r=0;
    while(*str != '\0'){
        OLED_DISPLAY_8x16(row,r*8,*str++);
        r++;
    }
}

/**
 * ��ʾ����16*16
 * ȡģ��СΪ16*16��ȡģ��ʽΪ�������Ҵ��ϵ��¡�������8���¸�λ��
 * @param x ��ʾ���ֵ�ҳ���꣨��0xB0��0xB7��
 * @param y ��ʾ���ֵ������꣨��0��63��
 * @param w Ҫ��ʾ���ֵı��
 */
void OLED_DISPLAY_16x16(u8 x, u8 y, u16 w){
    u8 j,t,c=0;
    for(t=0;t<2;t++){
    // ҳ��ַ����0xB0��0xB7��
        I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+x);

        // ��ʼ�е�ַ�ĸ�4λ
        I2C_SAND_BYTE(OLED0561_ADD,COM,y/16+0x10);

        //��ʼ�е�ַ�ĵ�4λ
        I2C_SAND_BYTE(OLED0561_ADD,COM,y%16);

        //��ҳ�������
        for(j=0;j<16;j++){
            I2C_SAND_BYTE(OLED0561_ADD,DAT,GB_16[(w*32)+c]);

            //ҳ��ַ��1
            c++;
        }
        x++;
    }

    //����ʾ 
    I2C_SAND_BYTE(OLED0561_ADD,COM,0xAF);
}

/**
 * ��ʾȫ��ͼƬ
 */
void OLED_DISPLAY_PIC1(void) {
    u8 m,i;
    for(m=0;m<8;m++) {
        I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+m);

        // ��ʼ�е�ַ�ĸ�4λ
        I2C_SAND_BYTE(OLED0561_ADD,COM,0x10);

        // ��ʼ�е�ַ�ĵ�4λ
        I2C_SAND_BYTE(OLED0561_ADD,COM,0x02);

        // ����128��ͼƬ��ʾ����
        for(i=0;i<128;i++){
            I2C_SAND_BYTE(OLED0561_ADD,DAT,PIC1[i+m*128]);
        }
    }
}

