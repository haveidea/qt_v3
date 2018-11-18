/***************************���յ��ӹ�����*************************************
  * @attention
  *
  * ʵ��ƽ̨:MINI  STM32 ������ 
  * 
  * 
  *
  *******************************************************************************/
  
#include "bsp_led.h"   

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED������ʱ��*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); 

		/*ѡ��Ҫ���Ƶ�GPIOB����*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIOB0*/
		GPIO_Init(GPIOB, &GPIO_InitStructure);		  

		/* �ر�led��	*/
		GPIO_SetBits(GPIOB, GPIO_Pin_9);
		
	
}

static void LED_Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}

/*----------------------------------------------------------------*/
void LED_Test(void)
{
  
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	 
 
	/* ����2��ʹ�ù̼������IO */
	while (1)
	{
		LED1( ON );			  // ��
		LED_Delay(0x0FFFFF);
		LED1( OFF );		  // ��
		LED_Delay(0x0FFFFF);
	}
}


/*********************************************END OF FILE**********************/
