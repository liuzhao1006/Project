#ifndef __LM75A_H
#define __LM75A_H    
#include "sys.h"
#include "i2c.h"

/**
 * 器件地址
 */
#define LM75A_ADD 0x9E

/**
 * 读温度
 */
void LM75A_GetTemp(u8 *Tempbuffer);

/**
 * 掉电模式
 */
void LM75A_POWERDOWN(void);

#endif

