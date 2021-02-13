#include "i2c.h"

/**
 * I2C�ӿڳ�ʼ��
 */
void I2C_GPIO_Init(void){
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);

    // ����I2C���� 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

    // ѡ��˿ں�
    GPIO_InitStructure.GPIO_Pin = I2C_SCL | I2C_SDA;

    // ѡ��IO�ӿڹ�����ʽ
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;

    // ����IO�ӿ��ٶȣ�2/10/50MHz��
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2CPORT, &GPIO_InitStructure);
}

/**
 * I2C��ʼ��
 */
void I2C_Configuration(void){
    I2C_InitTypeDef  I2C_InitStructure;
    
    // ������GPIO�ӿڵ�״̬
    I2C_GPIO_Init();
    
    // ����ΪI2Cģʽ
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    
    // ������ַ���ӻ������ô˵�ַ��
    I2C_InitStructure.I2C_OwnAddress1 = HostAddress;
    
    // ����Ӧ��
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    
    //7λ��ַģʽ
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    
    //�����ٶ�����
    I2C_InitStructure.I2C_ClockSpeed = BusSpeed;
    I2C_Init(I2C1,&I2C_InitStructure);
    
    // ����I2C
    I2C_Cmd(I2C1,ENABLE);
}

void I2C_SAND_BUFFER(u8 SlaveAddr,u8 WriteAddr,u8* pBuffer,u16 NumByteToWrite){
    // I2C�������ݴ���������ַ���Ĵ������ڲ���ַ��������
    // ������ʼλ
    I2C_GenerateSTART(I2C1,ENABLE);
    
    // ���EV5
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    
    // ����������ַ
    I2C_Send7bitAddress(I2C1,SlaveAddr,I2C_Direction_Transmitter);
    
    // ���EV6
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
    // �ڲ����ܵ�ַ
    I2C_SendData(I2C1,WriteAddr); 
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    // ��λ�Ĵ����ǿգ����ݼĴ����ѿգ�����EV8���������ݵ�DR��������¼�
    // ѭ����������
    while(NumByteToWrite--){
        // ��������
        I2C_SendData(I2C1,*pBuffer);
        
        // ����ָ����λ
        pBuffer++;
        
        // ���EV8
        while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    }
    
    // ����ֹͣ�ź�
    I2C_GenerateSTOP(I2C1,ENABLE);
}

/**
 * I2C����һ���ֽڣ��ӵ�ַ���ڲ���ַ�����ݣ�
 */
void I2C_SAND_BYTE(u8 SlaveAddr,u8 writeAddr,u8 pBuffer){
    // ���Ϳ�ʼ�ź�
    I2C_GenerateSTART(I2C1,ENABLE);
    
    // �ȴ����
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    
    // ���ʹ�������ַ��״̬��д�룩
    I2C_Send7bitAddress(I2C1,SlaveAddr, I2C_Direction_Transmitter);
    
    // �ȴ����
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
    // ���ʹ������ڲ��Ĵ�����ַ
    I2C_SendData(I2C1,writeAddr);
    
    // �ȴ����
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    // ����Ҫд�������
    I2C_SendData(I2C1,pBuffer);
    
    // �ȴ����
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    // ���ͽ����ź�
    I2C_GenerateSTOP(I2C1,ENABLE);
}

void I2C_READ_BUFFER(u8 SlaveAddr,u8 readAddr,u8* pBuffer,u16 NumByteToRead){
    // I2C��ȡ���ݴ���������ַ���Ĵ������ڲ���ַ��������
    while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
    
    // �����ź�
    I2C_GenerateSTART(I2C1,ENABLE);
    
    // ��� EV5
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    
    // д��������ַ
    I2C_Send7bitAddress(I2C1,SlaveAddr, I2C_Direction_Transmitter);
    
    // ��� EV6
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_Cmd(I2C1,ENABLE);
    
    // ���Ͷ��ĵ�ַ
    I2C_SendData(I2C1,readAddr);
    
    // ��� EV8
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    // �����ź�
    I2C_GenerateSTART(I2C1,ENABLE);
    
    // ��� EV5
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    
    // ��������ַ����������Ϊ��
    I2C_Send7bitAddress(I2C1,SlaveAddr,I2C_Direction_Receiver);
    
    // ���EV6
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    while(NumByteToRead){
        
        // ֻʣ�����һ������ʱ���� if ���
        if(NumByteToRead == 1){
            
            // �����һ������ʱ�ر�Ӧ��λ
            I2C_AcknowledgeConfig(I2C1,DISABLE);
            
            // ���һ������ʱʹ��ֹͣλ
            I2C_GenerateSTOP(I2C1,ENABLE);
        }
        
        // ��ȡ����
        if(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)){
            
            // ���ÿ⺯��������ȡ���� pBuffer
            *pBuffer = I2C_ReceiveData(I2C1);
            
            // ָ����λ
            pBuffer++;
            
            //�ֽ����� 1
            NumByteToRead--;
        }
    }
    I2C_AcknowledgeConfig(I2C1,ENABLE);
}

/**
 * I2C��ȡһ���ֽ�
 */
u8 I2C_READ_BYTE(u8 SlaveAddr,u8 readAddr){
    u8 a;
    while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
    I2C_GenerateSTART(I2C1,ENABLE);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1,SlaveAddr, I2C_Direction_Transmitter); 
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_Cmd(I2C1,ENABLE);
    I2C_SendData(I2C1,readAddr);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_GenerateSTART(I2C1,ENABLE);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1,SlaveAddr, I2C_Direction_Receiver);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    
    // �����һ������ʱ�ر�Ӧ��λ
    I2C_AcknowledgeConfig(I2C1,DISABLE);
    
    // ���һ������ʱʹ��ֹͣλ
    I2C_GenerateSTOP(I2C1,ENABLE);
    a = I2C_ReceiveData(I2C1);
    return a;
}

