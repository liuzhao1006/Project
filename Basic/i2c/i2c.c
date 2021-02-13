#include "i2c.h"

/**
 * I2C接口初始化
 */
void I2C_GPIO_Init(void){
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);

    // 启动I2C功能 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

    // 选择端口号
    GPIO_InitStructure.GPIO_Pin = I2C_SCL | I2C_SDA;

    // 选择IO接口工作方式
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;

    // 设置IO接口速度（2/10/50MHz）
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2CPORT, &GPIO_InitStructure);
}

/**
 * I2C初始化
 */
void I2C_Configuration(void){
    I2C_InitTypeDef  I2C_InitStructure;
    
    // 先设置GPIO接口的状态
    I2C_GPIO_Init();
    
    // 设置为I2C模式
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    
    // 主机地址（从机不得用此地址）
    I2C_InitStructure.I2C_OwnAddress1 = HostAddress;
    
    // 允许应答
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    
    //7位地址模式
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    
    //总线速度设置
    I2C_InitStructure.I2C_ClockSpeed = BusSpeed;
    I2C_Init(I2C1,&I2C_InitStructure);
    
    // 开启I2C
    I2C_Cmd(I2C1,ENABLE);
}

void I2C_SAND_BUFFER(u8 SlaveAddr,u8 WriteAddr,u8* pBuffer,u16 NumByteToWrite){
    // I2C发送数据串（器件地址，寄存器，内部地址，数量）
    // 产生起始位
    I2C_GenerateSTART(I2C1,ENABLE);
    
    // 清除EV5
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    
    // 发送器件地址
    I2C_Send7bitAddress(I2C1,SlaveAddr,I2C_Direction_Transmitter);
    
    // 清除EV6
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
    // 内部功能地址
    I2C_SendData(I2C1,WriteAddr); 
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    // 移位寄存器非空，数据寄存器已空，产生EV8，发送数据到DR既清除该事件
    // 循环发送数据
    while(NumByteToWrite--){
        // 发送数据
        I2C_SendData(I2C1,*pBuffer);
        
        // 数据指针移位
        pBuffer++;
        
        // 清除EV8
        while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    }
    
    // 产生停止信号
    I2C_GenerateSTOP(I2C1,ENABLE);
}

/**
 * I2C发送一个字节（从地址，内部地址，内容）
 */
void I2C_SAND_BYTE(u8 SlaveAddr,u8 writeAddr,u8 pBuffer){
    // 发送开始信号
    I2C_GenerateSTART(I2C1,ENABLE);
    
    // 等待完成
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    
    // 发送从器件地址及状态（写入）
    I2C_Send7bitAddress(I2C1,SlaveAddr, I2C_Direction_Transmitter);
    
    // 等待完成
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
    // 发送从器件内部寄存器地址
    I2C_SendData(I2C1,writeAddr);
    
    // 等待完成
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    // 发送要写入的内容
    I2C_SendData(I2C1,pBuffer);
    
    // 等待完成
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    // 发送结束信号
    I2C_GenerateSTOP(I2C1,ENABLE);
}

void I2C_READ_BUFFER(u8 SlaveAddr,u8 readAddr,u8* pBuffer,u16 NumByteToRead){
    // I2C读取数据串（器件地址，寄存器，内部地址，数量）
    while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
    
    // 开启信号
    I2C_GenerateSTART(I2C1,ENABLE);
    
    // 清除 EV5
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    
    // 写入器件地址
    I2C_Send7bitAddress(I2C1,SlaveAddr, I2C_Direction_Transmitter);
    
    // 清除 EV6
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_Cmd(I2C1,ENABLE);
    
    // 发送读的地址
    I2C_SendData(I2C1,readAddr);
    
    // 清除 EV8
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    // 开启信号
    I2C_GenerateSTART(I2C1,ENABLE);
    
    // 清除 EV5
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    
    // 将器件地址传出，主机为读
    I2C_Send7bitAddress(I2C1,SlaveAddr,I2C_Direction_Receiver);
    
    // 清除EV6
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    while(NumByteToRead){
        
        // 只剩下最后一个数据时进入 if 语句
        if(NumByteToRead == 1){
            
            // 最后有一个数据时关闭应答位
            I2C_AcknowledgeConfig(I2C1,DISABLE);
            
            // 最后一个数据时使能停止位
            I2C_GenerateSTOP(I2C1,ENABLE);
        }
        
        // 读取数据
        if(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)){
            
            // 调用库函数将数据取出到 pBuffer
            *pBuffer = I2C_ReceiveData(I2C1);
            
            // 指针移位
            pBuffer++;
            
            //字节数减 1
            NumByteToRead--;
        }
    }
    I2C_AcknowledgeConfig(I2C1,ENABLE);
}

/**
 * I2C读取一个字节
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
    
    // 最后有一个数据时关闭应答位
    I2C_AcknowledgeConfig(I2C1,DISABLE);
    
    // 最后一个数据时使能停止位
    I2C_GenerateSTOP(I2C1,ENABLE);
    a = I2C_ReceiveData(I2C1);
    return a;
}

