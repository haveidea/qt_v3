/*******************************************************************************/
  
#include "bsp_iic.h"
#include "stm32f10x_i2c.h"

#include "bsp_DS18B20.h"

uint8_t I2c_Buf[3] = "AB0"; //�¶ȴ��

//*****************************************************  
// IIC2��ʼ����������ʼ��STM32Ӳ���Դ���IIC1  
//                 IIC1_SCL��ӦGPIO.B6  
//                 IIC1_SDA��ӦGPIO.B7  
//*****************************************************  


float Return_7051_Tmp(void)
{
	//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //��������Ƿ�æ ���ǿ� SCL ��SDA�Ƿ�Ϊ �� 
	//uint8_t i;
	float temperature;
	uint16_t temp[2];
	int timeout_counter = 0;

	
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY) && timeout_counter < si7051_read_timeout){timeout_counter++;}; //��������Ƿ�æ ���ǿ� SCL ��SDA�Ƿ�Ϊ �� 
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return -50.0; 
	}
	timeout_counter = 0;
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);  //����1�ֽ�1Ӧ��ģʽ
	
	I2C_GenerateSTART(I2C2, ENABLE);  // ������ʼλ 
	

	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) && timeout_counter < si7051_read_timeout){timeout_counter++;}; //EV5,��ģʽ
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return -50.0; 
	}
	timeout_counter = 0;
	
	I2C_Send7bitAddress(I2C2, 0x80, I2C_Direction_Transmitter);  //����������ַ(д) ����ĵ�ַ�������ֲ��ϵõ��ģ�Ҫ����һλ��//0x40->0x80, ��ַ��7bit���������ں��������ǰ�油0��8bit�� 
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) && timeout_counter < si7051_read_timeout){timeout_counter++;};
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return -50.0; 
	}
	timeout_counter = 0;																														 
	
	//while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) && timeout_counter < si7051_read_timeout){timeout_counter++;};
	//timeout_counter = 0;
	
	I2C_SendData(I2C2, 0xe3);  //����Measure Temperature Command
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) && timeout_counter < si7051_read_timeout){timeout_counter++;}; //�����ѷ���
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return -50.0; 
	}
	timeout_counter = 0;
	
	I2C_GenerateSTART(I2C2, ENABLE);  //��ʼλ
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) && timeout_counter < si7051_read_timeout){timeout_counter++;};
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return -50.0; 
	}
	timeout_counter = 0;
	
	I2C_Send7bitAddress(I2C2, 0x80, I2C_Direction_Receiver);  //����������ַ(��)
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) && timeout_counter < si7051_read_timeout){timeout_counter++;};
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return -50.0; 
	}
	timeout_counter = 0;
	
	//��Temperature Register
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED) && timeout_counter < si7051_read_timeout){timeout_counter++;}; /* EV7 */ 
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return -50.0; 
	}
	timeout_counter = 0;
	
	temp[0]= I2C_ReceiveData(I2C2);
	//printf("temp[0]: %2x", temp[0]);
	temp[0] = temp[0] << 8;
	
	
	
	I2C_AcknowledgeConfig(I2C2, DISABLE); //���һλ��Ҫ�ر�Ӧ��� 
	I2C_GenerateSTOP(I2C2, ENABLE); //����ֹͣλ
	
	/*
	�� Ϊ�����յ����һ���ֽں����һ��NACK���壬�ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)�������ACKλ�� 
	�� Ϊ�˲���һ��ֹͣ/����ʼ��������������ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)����STOP/STARTλ�� 
	�� ֻ����һ���ֽ�ʱ���պ���EV6֮��(EV6_1ʱ�����ADDR֮��)Ҫ�ر�Ӧ���ֹͣ�����Ĳ���λ��
	*/
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED) && timeout_counter < si7051_read_timeout){timeout_counter++;}; /* EV7 */ 
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return -50.0; 
	}
	timeout_counter = 0;
	
	temp[1]= I2C_ReceiveData(I2C2);
	
	temperature = (temp[0]+temp[1])*175.72/65536-46.85;
	
	
	//return temperature;
	//for(i=0; i<2; i++)
	//printf("\r\n Si7051: %.2f \r\n", temperature);
	

	//Decrement the read bytes counter 
	
	//I2C_AcknowledgeConfig(I2C2, ENABLE);  //�ٴ�����Ӧ��ģʽ
	I2C_AcknowledgeConfig(I2C2, DISABLE); //���һλ��Ҫ�ر�Ӧ��� 
	I2C_GenerateSTOP(I2C2, ENABLE); //����ֹͣλ
	
	return temperature;
}

uint16_t Return_7051_Data(void)
{
	//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //��������Ƿ�æ ���ǿ� SCL ��SDA�Ƿ�Ϊ �� 
	uint8_t i, id[8];
	//float temperature;
	uint16_t temp[2];
	//I2C_AcknowledgePolling(I2C2,0x80);
	int timeout_counter = 0;
		
	/*************************************************************************************************************/
	I2C_AcknowledgeConfig(I2C2, ENABLE);  //����1�ֽ�1Ӧ��ģʽ
	
	I2C_GenerateSTART(I2C2, ENABLE);  // ������ʼλ 
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) && timeout_counter < si7051_read_timeout){timeout_counter++;}; //EV5,��ģʽ
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return 0x0000; 
	}
	timeout_counter = 0;
	
	I2C_Send7bitAddress(I2C2, 0x80, I2C_Direction_Transmitter);  //����������ַ(д)
	
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) && timeout_counter < si7051_read_timeout){timeout_counter++;};
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return 0x0000; 
	}
	timeout_counter = 0;
	
	//I2C_SendData(I2C1, 0xe3);  //����Measure Temperature Command
	//while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
	I2C_SendData(I2C2, 0xfc);
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) && timeout_counter < si7051_read_timeout){timeout_counter++;}; //�����ѷ���
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return 0x0000; 
	}
	timeout_counter = 0;
	
	I2C_SendData(I2C2, 0xc9);
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) && timeout_counter < si7051_read_timeout){timeout_counter++;}; //�����ѷ���
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return 0x0000; 
	}
	timeout_counter = 0;
	
	I2C_GenerateSTART(I2C2, ENABLE);  //��ʼλ
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) && timeout_counter < si7051_read_timeout){timeout_counter++;};
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return 0x0000; 
	}
	timeout_counter = 0;
	
	I2C_Send7bitAddress(I2C2, 0x80, I2C_Direction_Receiver);  //����������ַ(��)
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) && timeout_counter < si7051_read_timeout){timeout_counter++;};
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return 0x0000; 
	}
	timeout_counter = 0;
	
	//��ID Register
	for(i=0; i<8; i++) {
		while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED) && timeout_counter < si7051_read_timeout){timeout_counter++;}; /* EV7 */ 
		if (timeout_counter == si7051_read_timeout)
		{
			I2C2_Init();
			return 0x0000; 
		}
		timeout_counter = 0;
		
		id[i]= I2C_ReceiveData(I2C2);
	}
	
	//for(i=0; i<8; i++)
		//printf("id[%d]: %2x", i, id[i]);
	
	I2C_AcknowledgeConfig(I2C2, DISABLE); //���һλ��Ҫ�ر�Ӧ��� 
	I2C_GenerateSTOP(I2C2, ENABLE); //����ֹͣλ
	
	/*
	�� Ϊ�����յ����һ���ֽں����һ��NACK���壬�ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)�������ACKλ�� 
	�� Ϊ�˲���һ��ֹͣ/����ʼ��������������ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)����STOP/STARTλ�� 
	�� ֻ����һ���ֽ�ʱ���պ���EV6֮��(EV6_1ʱ�����ADDR֮��)Ҫ�ر�Ӧ���ֹͣ�����Ĳ���λ��
	*/
	
	//while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); //EV7  
	//temp[1]= I2C_ReceiveData(I2C1);
	
	//printf("temp[1]: %2x", temp[1]);
	
	//Decrement the read bytes counter 
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);  //�ٴ�����Ӧ��ģʽ
	
	
	/*************************************************************************************************************/
	
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY) && timeout_counter < si7051_read_timeout){timeout_counter++;}; //��������Ƿ�æ ���ǿ� SCL ��SDA�Ƿ�Ϊ �� 
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return 0x0000; 
	}
	timeout_counter = 0;
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);  //����1�ֽ�1Ӧ��ģʽ
	
	I2C_GenerateSTART(I2C2, ENABLE);  // ������ʼλ 
	

	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) && timeout_counter < si7051_read_timeout){timeout_counter++;}; //EV5,��ģʽ
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return 0x0000; 
	}
	timeout_counter = 0;
	
	I2C_Send7bitAddress(I2C2, 0x80, I2C_Direction_Transmitter);  //����������ַ(д) ����ĵ�ַ�������ֲ��ϵõ��ģ�Ҫ����һλ��//0x40->0x80, ��ַ��7bit���������ں��������ǰ�油0��8bit�� 
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) && timeout_counter < si7051_read_timeout){timeout_counter++;};
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return 0x0000; 
	}
	timeout_counter = 0;																														 
	
	//while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) && timeout_counter < si7051_read_timeout){timeout_counter++;};
	//timeout_counter = 0;
	
	I2C_SendData(I2C2, 0xe3);  //����Measure Temperature Command
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) && timeout_counter < si7051_read_timeout){timeout_counter++;}; //�����ѷ���
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return 0x0000; 
	}
	timeout_counter = 0;
	
	//Delay_us(1200000);  //wait 1.2s after measure temperature cmd send
	Delay_us(100000);
	
	I2C_GenerateSTART(I2C2, ENABLE);  //��ʼλ repeated start
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) && timeout_counter < si7051_read_timeout){timeout_counter++;};
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return 0x0000; 
	}
	timeout_counter = 0;
	
	I2C_Send7bitAddress(I2C2, 0x80, I2C_Direction_Receiver);  //����������ַ(��)
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) && timeout_counter < si7051_read_timeout){timeout_counter++;};
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return 0x0000; 
	}
	timeout_counter = 0;
	
	//��Temperature Register
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED) && timeout_counter < si7051_read_timeout){timeout_counter++;}; /* EV7 */ 
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return 0x0000; 
	}
	timeout_counter = 0;
	
	temp[0]= I2C_ReceiveData(I2C2);
	//printf("temp[0]: %2x", temp[0]);
	temp[0] = temp[0] << 8;
	
	
	
	I2C_AcknowledgeConfig(I2C2, DISABLE); //���һλ��Ҫ�ر�Ӧ��� 
	I2C_GenerateSTOP(I2C2, ENABLE); //����ֹͣλ
	
	/*
	�� Ϊ�����յ����һ���ֽں����һ��NACK���壬�ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)�������ACKλ�� 
	�� Ϊ�˲���һ��ֹͣ/����ʼ��������������ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)����STOP/STARTλ�� 
	�� ֻ����һ���ֽ�ʱ���պ���EV6֮��(EV6_1ʱ�����ADDR֮��)Ҫ�ر�Ӧ���ֹͣ�����Ĳ���λ��
	*/
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED) && timeout_counter < si7051_read_timeout){timeout_counter++;}; /* EV7 */ 
	if (timeout_counter == si7051_read_timeout)
	{
		I2C2_Init();
		return 0x0000; 
	}
	timeout_counter = 0;
	
	temp[1]= I2C_ReceiveData(I2C2);
	
	//temperature = (temp[0]+temp[1])*175.72/65536-46.85;
	
	
	//return temperature;
	//for(i=0; i<2; i++)
	//printf("\r\n Si7051: %.2f \r\n", temperature);
	

	//Decrement the read bytes counter 
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);  //�ٴ�����Ӧ��ģʽ
	
	
	return (temp[0]+temp[1]);
}




void I2C1_Read_Tmp_7(uint16_t *temp, float *temperature)
{
	//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //��������Ƿ�æ ���ǿ� SCL ��SDA�Ƿ�Ϊ �� 
	//uint8_t i;
	//float temperature;
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //����1�ֽ�1Ӧ��ģʽ
	
	I2C_GenerateSTART(I2C1, ENABLE);  // ������ʼλ 
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,��ģʽ
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Transmitter);  //����������ַ(д) ����ĵ�ַ�������ֲ��ϵõ��ģ�Ҫ����һλ��
																															 //0x40->0x80, ��ַ��7bit���������ں��������ǰ�油0��8bit�� 
	
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C1, 0xe3);  //����Measure Temperature Command
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
	
	I2C_GenerateSTART(I2C1, ENABLE);  //��ʼλ
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Receiver);  //����������ַ(��)
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	//��Temperature Register
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[0]= I2C_ReceiveData(I2C1);
	//printf("temp[0]: %2x", temp[0]);
	temp[0] = temp[0] << 8;
	
	
	
	I2C_AcknowledgeConfig(I2C1, DISABLE); //���һλ��Ҫ�ر�Ӧ��� 
	I2C_GenerateSTOP(I2C1, ENABLE); //����ֹͣλ
	
	/*
	�� Ϊ�����յ����һ���ֽں����һ��NACK���壬�ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)�������ACKλ�� 
	�� Ϊ�˲���һ��ֹͣ/����ʼ��������������ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)����STOP/STARTλ�� 
	�� ֻ����һ���ֽ�ʱ���պ���EV6֮��(EV6_1ʱ�����ADDR֮��)Ҫ�ر�Ӧ���ֹͣ�����Ĳ���λ��
	*/
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[1]= I2C_ReceiveData(I2C1);
	
	temperature[0] = (temp[0]+temp[1])*175.72/65536-46.85;
	
	//for(i=0; i<2; i++)
	printf("\r\n Si7051: %.2f \r\n", temperature[0]);
	
	//Decrement the read bytes counter 
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //�ٴ�����Ӧ��ģʽ
}

void I2C1_Read_Tmp_47(uint16_t *temp, float *temperature)
{
	//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //��������Ƿ�æ ���ǿ� SCL ��SDA�Ƿ�Ϊ �� 
	//uint8_t i;
	//float temperature;
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //����1�ֽ�1Ӧ��ģʽ
	
	I2C_GenerateSTART(I2C1, ENABLE);  // ������ʼλ 
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,��ģʽ
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Transmitter);  //����������ַ(д) ����ĵ�ַ�������ֲ��ϵõ��ģ�Ҫ����һλ��
																															 //0x40->0x80, ��ַ��7bit���������ں��������ǰ�油0��8bit�� 
	
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C1, 0xe3);  //����Measure Temperature Command
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
	
	I2C_GenerateSTART(I2C1, ENABLE);  //��ʼλ
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Receiver);  //����������ַ(��)
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	//��Temperature Register
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[0]= I2C_ReceiveData(I2C1);
	//printf("temp[0]: %2x", temp[0]);
	temp[0] = temp[0] << 8;
	
	
	
	I2C_AcknowledgeConfig(I2C1, DISABLE); //���һλ��Ҫ�ر�Ӧ��� 
	I2C_GenerateSTOP(I2C1, ENABLE); //����ֹͣλ
	
	/*
	�� Ϊ�����յ����һ���ֽں����һ��NACK���壬�ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)�������ACKλ�� 
	�� Ϊ�˲���һ��ֹͣ/����ʼ��������������ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)����STOP/STARTλ�� 
	�� ֻ����һ���ֽ�ʱ���պ���EV6֮��(EV6_1ʱ�����ADDR֮��)Ҫ�ر�Ӧ���ֹͣ�����Ĳ���λ��
	*/
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[1]= I2C_ReceiveData(I2C1);
	
	temperature[1] = (temp[0]+temp[1])*175.72/65536-46.85;
	
	//for(i=0; i<2; i++)
	printf("\r\n Si7051: %.2f \r\n", temperature[1]);
	
	//Decrement the read bytes counter 
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //�ٴ�����Ӧ��ģʽ
}


void I2C1_7051_Test(uint8_t *temp)
{
	//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //��������Ƿ�æ ���ǿ� SCL ��SDA�Ƿ�Ϊ �� 
	uint8_t i;
	
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //����1�ֽ�1Ӧ��ģʽ
	
	I2C_GenerateSTART(I2C1, ENABLE);  // ������ʼλ 
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,��ģʽ
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Transmitter);  //����������ַ(д)
	
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	//I2C_SendData(I2C1, 0xe3);  //����Measure Temperature Command
	//while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
	I2C_SendData(I2C1, 0xfc);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
	I2C_SendData(I2C1, 0xc9);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
	
	I2C_GenerateSTART(I2C1, ENABLE);  //��ʼλ
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Receiver);  //����������ַ(��)
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	//��Temperature Register
	for(i=0; i<8; i++) {
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
		temp[i]= I2C_ReceiveData(I2C1);
	}
	
	for(i=0; i<8; i++)
		printf("temp[%d]: %2x", i, temp[i]);
	
	I2C_AcknowledgeConfig(I2C1, DISABLE); //���һλ��Ҫ�ر�Ӧ��� 
	I2C_GenerateSTOP(I2C1, ENABLE); //����ֹͣλ
	
	/*
	�� Ϊ�����յ����һ���ֽں����һ��NACK���壬�ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)�������ACKλ�� 
	�� Ϊ�˲���һ��ֹͣ/����ʼ��������������ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)����STOP/STARTλ�� 
	�� ֻ����һ���ֽ�ʱ���պ���EV6֮��(EV6_1ʱ�����ADDR֮��)Ҫ�ر�Ӧ���ֹͣ�����Ĳ���λ��
	*/
	
	//while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); //EV7  
	//temp[1]= I2C_ReceiveData(I2C1);
	
	//printf("temp[1]: %2x", temp[1]);
	
	//Decrement the read bytes counter 
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //�ٴ�����Ӧ��ģʽ
} 



//*****************************************************  
// IIC2��ʼ����������ʼ��STM32Ӳ���Դ���IIC2  
//                 IIC2_SCL��ӦGPIO.B10  
//                 IIC2_SDA��ӦGPIO.B11  
//*****************************************************  
void I2C2_Init(void)  
{  
    /*GPIO��IIC��ʼ���ṹ��*/  
    GPIO_InitTypeDef GPIO_InitStructure;  
    I2C_InitTypeDef I2C_InitStructure;  
      
    /*GPIO��IICʱ��ʹ��*/  
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );     //GPIOBʱ��ʹ��  
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C2, ENABLE );      //IIC2ʱ��ʹ��  
  
    /*��ʼ��GPIO*/  
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;   //��ʼ��GPIO.B10(IIC2_SCL)��GPIO.B11(IIC2_SDA)  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           //�������ٶ�50Hz  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;             //�������ģʽΪ���ù��ܿ�©���  
    GPIO_Init( GPIOB, &GPIO_InitStructure );                    //����GPIO��ʼ���ṹ���ʼ��GPIOB  
      
    /*��ʼ��IIC2*/  
    I2C_DeInit(I2C2);
		I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;                  //����ΪIICģʽ  
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;          //����IIC��ռ�ձȣ��͵�ƽ���Ըߵ�ƽֵΪ2  
    I2C_InitStructure.I2C_OwnAddress1 = 0x0A;                   //STM32�����ַ, ������������  
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;                 //ʹ��ACK�ź�  
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;   //ָ��7λ��ַ  
    I2C_InitStructure.I2C_ClockSpeed = 100000;                  //ʱ��Ƶ�ʣ�����С�ڵ���400KHz  
      
    I2C_Cmd( I2C2, ENABLE );                                    //ʹ��IIC2  
    I2C_Init(I2C2, &I2C_InitStructure);                       //����IIC��ʼ���ṹ���ʼ��IIC2  
      
    /*����һ�ֽ�һӦ��ģʽ*/  
    I2C_AcknowledgeConfig( I2C2, ENABLE );                      //ʹ��IIC2Ӧ��״̬    
}
 

/************************************************************************************
**static void I2C_AcknowledgePolling(I2C_TypeDef *I2Cx,unsigned char I2C_Addr)
**�ȴ���ȡI2C����Ȩ

************************************************************************************/
static void I2C_AcknowledgePolling(I2C_TypeDef *I2Cx,unsigned char I2C_Addr)
{ 
    do{ 
				I2C_GenerateSTART(I2Cx,ENABLE);
        I2C_ReadRegister(I2Cx,I2C_Register_SR1);//���ADDRλ
				I2C_ReadRegister(I2Cx,I2C_Register_SR2);//
        I2C_Send7bitAddress(I2Cx,I2C_Addr,I2C_Direction_Transmitter);
				Delay_us(10);								//���͵�ַ�󣬲��������յ�ACK������ʱ�ȴ�
		
    }while(!(I2C_ReadRegister(I2Cx,I2C_Register_SR1)&0x0002)); 
 
    I2C_ClearFlag(I2Cx,I2C_FLAG_AF);
} 




/*********************************************END OF FILE**********************/
