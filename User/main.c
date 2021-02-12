#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "buzzer.h"	
#include "usart.h"	 	
#include "rtc.h"

#define BAUD_RATE 115200	  //写入的起始地址

int main (void)
{			
	// 初始化配置
    RCC_Configuration();

	LED_Init();

	KEY_Init();

	BUZZER_Init();

	USART1_Init(BAUD_RATE);

	USART1_RX_STA=0xC000;

	while(1)
	{
        
		if(USART1_RX_STA&0xC000){ //如果标志位是0xC000表示收到数据串完成，可以处理。
			if((USART1_RX_STA&0x3FFF)==0){ //单独的回车键再显示一次欢迎词
				printf("\033[1;47;33m\r\n"); //设置颜色（参考超级终端使用）
				printf(" 1y--开LED1灯      1n--关LED1灯 \r\n");
				printf(" 2y--开LED2灯      2n--关LED2灯 \r\n");
				printf(" 请输入控制指令，按回车键执行！ \033[0m\r\n");
			}else if((USART1_RX_STA&0x3FFF)==2 && USART1_RX_BUF[0]=='1' && USART1_RX_BUF[1]=='y'){ //判断数据是不是2个，第一个数据是不是“1”，第二个是不是“y”
				GPIO_SetBits(LEDPORT,LED1); //LED灯都为高电平（1）
				printf("1y -- LED1灯已经点亮！\r\n");
			}else if((USART1_RX_STA&0x3FFF)==2 && USART1_RX_BUF[0]=='1' && USART1_RX_BUF[1]=='n'){
				GPIO_ResetBits(LEDPORT,LED1); ////LED灯都为低电平（0）
				printf("1n -- LED1灯已经熄灭！\r\n");
			}else if((USART1_RX_STA&0x3FFF)==2 && USART1_RX_BUF[0]=='2' && USART1_RX_BUF[1]=='y'){
				GPIO_SetBits(LEDPORT,LED2); //LED灯都为高电平（1）
				printf("2y -- LED2灯已经点亮！\r\n");
			}else if((USART1_RX_STA&0x3FFF)==2 && USART1_RX_BUF[0]=='2' && USART1_RX_BUF[1]=='n'){
				GPIO_ResetBits(LEDPORT,LED2); ////LED灯都为低电平（0）
				printf("2n -- LED2灯已经熄灭！\r\n");
			}else{ //如果以上都不是，即是错误的指令。
				printf("指令错误！\r\n"); 
			}
			USART1_RX_STA=0; //将串口数据标志位清0
		}
		if (RTC_Get() == 0) {
			GPIO_WriteBit(LEDPORT,LED1,(BitAction)(rsec%2)); //LED1接口
			GPIO_WriteBit(LEDPORT,LED2,(BitAction)(rmin%2)); //LED2接口
		}
	}
}

