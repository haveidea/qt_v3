/***************************浩普电子工作室*************************************
  * @attention
  *
  * 实验平台:MINI  STM32 开发板 
  * 
  * 
  *
  *******************************************************************************/
  
#include "bsp_led.h"   

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED的外设时钟*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); 

		/*选择要控制的GPIOB引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIOB0*/
		GPIO_Init(GPIOB, &GPIO_InitStructure);		  

		/* 关闭led灯	*/
		GPIO_SetBits(GPIOB, GPIO_Pin_9);
		
	
}

static void LED_Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}

/*----------------------------------------------------------------*/
void LED_Test(void)
{
  
	/* LED 端口初始化 */
	LED_GPIO_Config();	 
 
	/* 方法2，使用固件库控制IO */
	while (1)
	{
		LED1( ON );			  // 亮
		LED_Delay(0x0FFFFF);
		LED1( OFF );		  // 灭
		LED_Delay(0x0FFFFF);
	}
}


/*********************************************END OF FILE**********************/
