#include "buzzer.h"
#include "delay.h"

void BUZZER_Init(void){ //蜂鸣器的接口初始化
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    GPIO_InitStructure.GPIO_Pin = BUZZER; //选择端口号                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //选择IO接口工作方式       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置IO接口速度（2/10/50MHz）    
	GPIO_Init(BUZZERPORT, &GPIO_InitStructure);	
	
	GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1)); //蜂鸣器接口输出高电平1		
}

void BUZZER_BEEP1(void){ //蜂鸣器响一声
	u16 i;
	for(i=0;i<200;i++){
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(0)); //蜂鸣器接口输出0
		delay_us(500); //延时		
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1)); //蜂鸣器接口输出高电平1
		delay_us(500); //延时		
	}
}

uc16 music1[78]={ //音乐1的数据表（奇数是音调，偶数是长度）
330,750,
440,375,
494,375,
523,750,
587,375,
659,375,
587,750,
494,375,
392,375,
440,1500,
330,750,
440,375,
494,375,
523,750,
587,375,
659,375,
587,750,
494,375,
392,375,
784,1500,
659,750,
698,375,
784,375,
880,750,
784,375,
698,375,
659,750,
587,750,
659,750,
523,375,
494,375,
440,750,
440,375,
494,375,
523,750,
523,750,
494,750,
392,750,
440,3000
};

void MIDI_PLAY(void){ //MIDI音乐
	u16 i,e;
	for(i=0;i<39;i++){
		for(e=0;e<music1[i*2]*music1[i*2+1]/1000;e++){
			GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(0)); //蜂鸣器接口输出0
			delay_us(500000/music1[i*2]); //延时		
			GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1)); //蜂鸣器接口输出高电平1
			delay_us(500000/music1[i*2]); //延时	
		}	
	}
}

