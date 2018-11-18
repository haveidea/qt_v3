#ifndef __IIC_H
#define	__IIC_H

#define si7051_read_timeout  10000

 

#include "stm32f10x.h"
#include <stdio.h>


void I2C1_Init(void);
void I2C2_Init(void);

void I2C2_Read_Tmp(uint16_t *temp, uint8_t index);
void I2C2_Init_Tmp(uint8_t index);

void I2C1_Read_Tmp(uint16_t *temp);

void I2C1_7051_Test(uint8_t *temp);

void I2C1_Read_Tmp_7(uint16_t *temp, float *temperature);

void I2C1_Read_Tmp_47(uint16_t *temp, float *temperature);

float Return_7051_Tmp(void);

uint16_t Return_7051_Data(void);

static void I2C_AcknowledgePolling(I2C_TypeDef *I2Cx,unsigned char I2C_Addr);

#endif /* __IIC_H */
