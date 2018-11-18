///////////////////////// ///////////////
// Minyuan MY18B20 Final Test Software 2
//              Version 0.55
// Author    DS. Li, B. Zhao, S. Wang, YL. Zhai
//         
//      Copyright    2018/4/2
//
// Release Note
//
////////////////////////////////////////


#include <stdio.h>
#include <math.h> 
#include <string.h>
#include <stdlib.h>   	//ZYL
#include "bsp_DS18B20.h"
#include "stm32f10x_tim.h"
#include "stm32f10x.h"
#include "misc.h"

#include "bsp_iic.h"

// FreeRTOS head file, add here.
//#include "FreeRTOS.h"
//#include "task.h"
//#include "queue.h"
//#include "list.h"
//#include "portable.h"
//#include "FreeRTOSConfig.h"

//#define  DWT_CYCCNT  *(volatile unsigned int *)0xE0001004
//#define  DWT_CR      *(volatile unsigned int *)0xE0001000
//#define  DEM_CR      *(volatile unsigned int *)0xE000EDFC
//#define  DBGMCU_CR   *(volatile unsigned int *)0xE0042004

//#define  DEM_CR_TRCENA               (1 << 24)
//#define  DWT_CR_CYCCNTENA            (1 <<  0)


//#define  timerINTERRUPT_FREQUENCY    20000
// 
//#define  timerHIGHEST_PRIORITY       1
// 
// 
//volatile uint32_t ulHighFrequencyTimerTicks = 0UL;


//void Delay_us(uint32_t _ulDelayTime)
//{
//  uint32_t tCnt, tDelayCnt;
//	uint32_t tStart;
//		
//	tStart = DWT_CYCCNT;                                     /* initial count value */
//	tCnt = 0;
//	tDelayCnt = _ulDelayTime * (SystemCoreClock / 1000000);	 /* num of ticks need */ 		      

//	while(tCnt < tDelayCnt)
//	{
//		tCnt = DWT_CYCCNT - tStart; /* in this procedure, if recount of 32-bit counter happends first time, it still can be count correctly */	
//	}
//}





/*
 * STATE: MUX_18B20_OUT_GPIO_Config
 * DESCRIP: MUX_18B20_OUT's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_18B20_OUT_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open DUT_DQ_OUT_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(MUX_18B20_OUT_CLK, ENABLE); 

	/*select DUT_DQ_OUT_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = MUX_18B20_OUT_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial DUT_DQ_OUT_PORT*/
  	GPIO_Init(MUX_18B20_OUT_PORT, &GPIO_InitStructure);
	
		GPIO_SetBits(MUX_18B20_OUT_PORT, MUX_18B20_OUT_PIN);	 
}


/*
 * STATE: STRONG_PULLUP_GPIO_Config
 * DESCRIP: STRONG_PULLUP's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void STRONG_PULLUP_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open STRONG_PULLUP_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(STRONG_PULLUP_CLK, ENABLE); 

	/*select STRONG_PULLUP_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = STRONG_PULLUP_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial STRONG_PULLUP_PORT*/
  	GPIO_Init(STRONG_PULLUP_PORT, &GPIO_InitStructure);
	
		GPIO_SetBits(STRONG_PULLUP_PORT, STRONG_PULLUP_PIN);	 
}





/*
 * STATE: MUX_S3_GPIO_Config
 * DESCRIP: MUX_S3's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_S3_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S3_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(MUX_S3_CLK, ENABLE); 

	/*select MUX_S3_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = MUX_S3_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S3_PORT*/
  	GPIO_Init(MUX_S3_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(MUX_S3_PORT, MUX_S3_PIN);	 
}

/*
 * STATE: MUX_S2_GPIO_Config
 * DESCRIP: MUX_S2's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_S2_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S2_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(MUX_S2_CLK, ENABLE); 

	/*select MUX_S2_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = MUX_S2_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S2_PORT*/
  	GPIO_Init(MUX_S2_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(MUX_S2_PORT, MUX_S2_PIN);	 
}

/*
 * STATE: MUX_S1_GPIO_Config
 * DESCRIP: MUX_S1's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_S1_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S1_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(MUX_S1_CLK, ENABLE); 

	/*select MUX_S1_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = MUX_S1_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S1_PORT*/
  	GPIO_Init(MUX_S1_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(MUX_S1_PORT, MUX_S1_PIN);	 
}

/*
 * STATE: MUX_S0_GPIO_Config
 * DESCRIP: MUX_S0's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_S0_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(MUX_S0_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = MUX_S0_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(MUX_S0_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(MUX_S0_PORT, MUX_S0_PIN);	 
}

static void P0_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(P0_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = P0_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(P0_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(P0_PORT, P0_PIN);	 
}

static void P1_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(P1_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = P1_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(P1_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(P1_PORT, P1_PIN);	 
}

static void P2_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(P2_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = P2_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(P2_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(P2_PORT, P2_PIN);	 
}




static void SUB_E1_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(SUB_E1_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = SUB_E1_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(SUB_E1_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(SUB_E1_PORT, SUB_E1_PIN);	 
}

static void SUB_E2_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(SUB_E2_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = SUB_E2_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(SUB_E2_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(SUB_E2_PORT, SUB_E2_PIN);	 
}

static void SUB_E3_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(SUB_E3_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = SUB_E3_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(SUB_E2_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(SUB_E2_PORT, SUB_E2_PIN);	 
}

static void SUB_E4_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(SUB_E4_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = SUB_E4_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(SUB_E4_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(SUB_E4_PORT, SUB_E4_PIN);	 
}

static void SUB_E5_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(SUB_E5_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = SUB_E5_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(SUB_E5_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(SUB_E5_PORT, SUB_E5_PIN);	 
}

static void SUB_E6_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(SUB_E6_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = SUB_E6_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(SUB_E6_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(SUB_E6_PORT, SUB_E6_PIN);	 
}

static void SUB_E7_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(SUB_E7_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = SUB_E7_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(SUB_E7_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(SUB_E7_PORT, SUB_E7_PIN);	 
}

static void SUB_E8_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(SUB_E8_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = SUB_E8_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(SUB_E8_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(SUB_E8_PORT, SUB_E8_PIN);	 
}

static void SUB_E9_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(SUB_E9_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = SUB_E9_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(SUB_E9_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(SUB_E9_PORT, SUB_E9_PIN);	 
}

static void SUB_E10_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(SUB_E2_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = SUB_E10_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(SUB_E10_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(SUB_E10_PORT, SUB_E10_PIN);	 
}

static void SUB_E11_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(SUB_E11_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = SUB_E11_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(SUB_E11_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(SUB_E2_PORT, SUB_E11_PIN);	 
}

static void SUB_E12_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(SUB_E12_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = SUB_E12_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(SUB_E12_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(SUB_E12_PORT, SUB_E12_PIN);	 
}

static void SUB_E13_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(SUB_E13_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = SUB_E13_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(SUB_E13_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(SUB_E13_PORT, SUB_E13_PIN);	 
}

static void SUB_E14_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(SUB_E14_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = SUB_E14_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(SUB_E14_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(SUB_E14_PORT, SUB_E14_PIN);	 
}


static void SUB_E15_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(SUB_E15_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = SUB_E15_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(SUB_E15_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(SUB_E15_PORT, SUB_E15_PIN);	 
}


static void SUB_E16_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(SUB_E16_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = SUB_E16_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(SUB_E16_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(SUB_E16_PORT, SUB_E16_PIN);	 
}


static void M0_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(M0_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = M0_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(M0_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(M0_PORT, M0_PIN);	 
}

static void M1_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(M1_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = M1_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(M1_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(M1_PORT, M1_PIN);	 
}

static void M2_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(M2_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = M2_PIN;	  /// changed

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(M2_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(M2_PORT, M2_PIN);	 
}



void GPIO_Config(void)
{
		MUX_18B20_OUT_GPIO_Config();
		STRONG_PULLUP_GPIO_Config();

  	P0_GPIO_Config();
	  P1_GPIO_Config();
	  P2_GPIO_Config();
		
		MUX_S0_GPIO_Config();
		MUX_S1_GPIO_Config();
		MUX_S2_GPIO_Config();
		MUX_S3_GPIO_Config();
		
		SUB_E1_GPIO_Config();
		SUB_E2_GPIO_Config();
		SUB_E3_GPIO_Config();
		SUB_E4_GPIO_Config();
		SUB_E5_GPIO_Config();
		SUB_E6_GPIO_Config();
		SUB_E7_GPIO_Config();
		SUB_E8_GPIO_Config();
		SUB_E9_GPIO_Config();
		SUB_E10_GPIO_Config();
		SUB_E11_GPIO_Config();
    SUB_E12_GPIO_Config();
		SUB_E13_GPIO_Config();
		SUB_E14_GPIO_Config();
    SUB_E15_GPIO_Config();
		SUB_E16_GPIO_Config();


    M0_GPIO_Config();
		M1_GPIO_Config();
		M2_GPIO_Config();
		
	//  LED_GPIO_Config();/* LED initial£¬ not needed */

}


static void MUX_18B20_OUT_Mode_IPU(void)
{
 	  GPIO_InitTypeDef GPIO_InitStructure;

	  /*select DUT_DQ_OUT_PORT pin to control*/	
	  GPIO_InitStructure.GPIO_Pin = MUX_18B20_OUT_PIN;

	  /*set pin mode to input pull up mode*/ 
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	

	  /*initial DUT_DQ_OUT_PORT*/
	  GPIO_Init(MUX_18B20_OUT_PORT, &GPIO_InitStructure);
}



/*
 * STATE: MUX_18B20_OUT_Mode_Out_PP
 * DESCRIP: set MUX_18B20_OUT-DATA pin to be output mode
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_18B20_OUT_Mode_Out_PP(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;

	 	/*select MUX_18B20_OUT_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = MUX_18B20_OUT_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */    
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*initial MUX_18B20_OUT_PORT*/
  	GPIO_Init(MUX_18B20_OUT_PORT, &GPIO_InitStructure);
}








/*
 * master send reset pulse to slave
 */
static void MUX_18B20_OUT_Rst(void)
{
	/*set pin mode to push-pull out mode*/
	MUX_18B20_OUT_Mode_Out_PP();
//		Delay_us(11750);
  Delay_us(3);
	
	MUX_18B20_OUT_DATA_OUT(LOW);
	/* master drive bus low at least 480us */
	Delay_us(480);

	MUX_18B20_OUT_Mode_IPU();
	/* master release bus */
//	MUX_18B20_OUT_DATA_OUT(HIGH);
	
	/*once slave receive reset signal, it will send presence pulse to master after 15~60us*/
	Delay_us(15);
}



/*
 * master send reset pulse to slave
 */
static void DQ_Rst(uint8_t type)
{
		switch(type) {
//			case DUT_DQ_OUT:
//				DUT_DQ_OUT_Rst();
//				break;
			case MUX_18B20_OUT:
				MUX_18B20_OUT_Rst();
				break;
//			case TOTAL_DQ_OUT:
//				TOTAL_DQ_OUT_Rst();
//				break;
			default:
				MUX_18B20_OUT_Rst();
				break;
		}
}






/*
 * check presence pulse
 * 0: success
 * 1: failure
 */
static uint8_t MUX_18B20_OUT_Presence(void)
{
	uint8_t pulse_time = 0;
	
	/*set pin mode to input pull up mode*/
	MUX_18B20_OUT_Mode_IPU();
	Delay_us(3);
	
	/* wait for presence pulse, 60~240us low level signal
	 * if presence pulse does not come, then timeout; once slave receive reset signal, it will send presence pulse to master after 15~60us
	 */
	while( MUX_18B20_OUT_DATA_IN() && pulse_time<100 )
	{
		pulse_time++;
		Delay_us(1);
	}	
	/* after 100us, presence pulse does not come*/
	if( pulse_time >=100 )
		return 1;
	else
		pulse_time = 0;
	
	/* presence pulse comes and not sustain over 240us */
	while( !MUX_18B20_OUT_DATA_IN() && pulse_time<240 )
	{
		pulse_time++;
		Delay_us(1);
	}	
	if( pulse_time >=240 )
		return 1;
	else
		return 0;
}



/*
 * check presence pulse
 * 0: success
 * 1: failure
 */
static uint8_t DQ_Presence(uint8_t type)
{
		
		if (type== MUX_18B20_OUT)
				return MUX_18B20_OUT_Presence();
	else
		{ printf(" \n mismatch type \n" );
			return MUX_18B20_OUT_Presence();
	}		
}	





/*
 * MUX_18B20_OUT read one bit
 */
static uint8_t MUX_18B20_OUT_Read_Bit(void)
{
	uint8_t dat;
	
	/* time slot of read 1 and read 0 need to be over 60us */	

	
	MUX_18B20_OUT_Mode_Out_PP();
	Delay_us(3);
	/* master drive bus low >1us <15us*/
	MUX_18B20_OUT_DATA_OUT(LOW);
	Delay_us(2);
	
	/* set pin to inputmode, release bus, then pull up by pull-up resistor*/
	MUX_18B20_OUT_Mode_IPU();
	Delay_us(7);
	
	if( MUX_18B20_OUT_DATA_IN() == SET )
		dat = 1;
	else
		dat = 0;
	
	/* based on Time Slot Timing Diagram */
	Delay_us(60);
	
	return dat;
}



/*
 * DQ read one bit
 */
static uint8_t DQ_Read_Bit(uint8_t type)
{
//	if (type== MUX_18B20_OUT)
				return MUX_18B20_OUT_Read_Bit();
//	else
//		{ printf(" \n mismatch type \n" );
//			return MUX_18B20_OUT_Read_Bit();
//	}		
}


uint8_t MUX_18B20_OUT_Read2Bit(void)  
{    
		uint8_t i, j, dat;	
	  dat = 0;
	
		for(i=0; i<2; i++) 
		{
			j = MUX_18B20_OUT_Read_Bit();		
			dat = (dat) | (j<<i);
		}
	
		return dat;
}

uint8_t DQ_Read2Bit(uint8_t type)  
{    
		uint8_t i, j, dat;	
	  dat = 0;
	
		for(i=0; i<2; i++) 
		{
			j = DQ_Read_Bit(type);	
		
			dat = (dat) | (j<<i);
		}
	
		return dat;
}



/*
 * MUX_18B20_OUT read one byte, LSB first
 */
uint8_t MUX_18B20_OUT_Read_Byte(void)
{
	uint8_t i, j, dat = 0;	
	
	for(i=0; i<8; i++) 
	{
		j = MUX_18B20_OUT_Read_Bit();		
		dat = (dat) | (j<<i);
	}
	
	return dat;
}

/*
 * DQ read one byte, LSB first   
 */
uint8_t DQ_Read_Byte(uint8_t type)
{
	uint8_t i, j, dat = 0;	
	
	
	for(i=0; i<8; i++) 
	{
		j = DQ_Read_Bit(type);		
		//	printf("\r %d \n",j);
		dat = (dat) | (j<<i);

	}

	//printf("\r data: %d \n",dat);
	return dat;
}



void MUX_18B20_OUT_Write_Bit(uint8_t bit)  
{  
		uint8_t testb;
		MUX_18B20_OUT_Mode_Out_PP();
	  Delay_us(5);
		testb = bit&0x01;	
		/* time slot of write 1 and read 0 need to be over 60us */
		if (testb)
		{			
			MUX_18B20_OUT_DATA_OUT(LOW);
			/* 1us < this delay < 15us */
			Delay_us(6);
			//Delay_us(rand() % 12 + 2);
			
			MUX_18B20_OUT_DATA_OUT(HIGH);
			Delay_us(60);
		}		
		else
		{			
			MUX_18B20_OUT_DATA_OUT(LOW);
			/* 60us < Tx 0 < 120us */
			Delay_us(70);
			//Delay_us(rand() % 58 + 61);
			
			MUX_18B20_OUT_DATA_OUT(HIGH);			
			/* 1us < Trec < infinity*/
			Delay_us(10);
			//Delay_us(rand() % 6 + 2);
		}	  
}



void DQ_Write_Bit(uint8_t bit, uint8_t type)  
{  
		switch(type) {
//			case DUT_DQ_OUT:
//				DUT_DQ_OUT_Write_Bit(bit);
//				break;
			case MUX_18B20_OUT:
				MUX_18B20_OUT_Write_Bit(bit);
				break;
//			case TOTAL_DQ_OUT:
//				TOTAL_DQ_OUT_Write_Bit(bit);
//				break;
			default:
				MUX_18B20_OUT_Write_Bit(bit);
				break;
		}	  
}


/*
 * MUX_18B20_OUT write one byte, LSB first
 */
void MUX_18B20_OUT_Write_Byte(uint8_t dat)
{
	uint8_t i, testb;
	MUX_18B20_OUT_Mode_Out_PP();
	Delay_us(5);
	
	for( i=0; i<8; i++ )
	{
		testb = dat&0x01;
		dat = dat>>1;		
		/* time slot of write 1 and read 0 need to be over 60us */
		if (testb)
		{			
			MUX_18B20_OUT_DATA_OUT(LOW);
			/* 1us < this delay < 15us */
			Delay_us(5);
			
			MUX_18B20_OUT_DATA_OUT(HIGH);
			Delay_us(70);
		}		
		else
		{			
			MUX_18B20_OUT_DATA_OUT(LOW);
			/* 60us < Tx 0 < 120us */
			Delay_us(70);
			
			MUX_18B20_OUT_DATA_OUT(HIGH);			
			/* 1us < Trec < ÎÞÇî´ó*/
			Delay_us(10);
		}
	}
}


/*
 * DQ write one byte, LSB first
 */
void DQ_Write_Byte(uint8_t dat, uint8_t type)
{
		//switch(type) //{
//			case DUT_DQ_OUT:
//				DUT_DQ_OUT_Write_Byte(dat);
//				break;
	//		case MUX_18B20_OUT:
				MUX_18B20_OUT_Write_Byte(dat);
	//			break;
//			case TOTAL_DQ_OUT:
//				TOTAL_DQ_OUT_Write_Byte(dat);
//				break;
	//		default:
//				MUX_18B20_OUT_Write_Byte(dat);
//				break;
		//}
}




/*
 * MY18B20
 * when 12-bit resolution ratio, 5 sign bits£¬7 integer bits, 4 decimal bits
 *
 *         |---------integer----------|-----decimal resolution ratio 1/(2^4)=0.0625----|
 * LSB  | 2^3 | 2^2 | 2^1 | 2^0 | 2^(-1) | 2^(-2) | 2^(-3) | 2^(-4) |
 *
 *
 *         |-----sign bit: 0->positive  1->negative-------|-----------integer-----------|
 * MSB  |  s  |  s  |  s  |  s  |    s   |   2^6  |   2^5  |   2^4  |
 *
 * 
 * temperature = sign bit + integer + decimal*0.0625
 */



float MUX_DQ_OUT_Get_Temp(void)
{
	uint8_t tpmsb, tplsb;
	short s_tem;
	float f_tem;
	
	MUX_18B20_OUT_Rst();	   
	MUX_18B20_OUT_Presence();	 
	MUX_18B20_OUT_Write_Byte(SKIP_ROM);				
	MUX_18B20_OUT_Write_Byte(CONVERT_T);				
	
	
	Delay_us(8000);
//	do{
//		done = DUT_DQ_OUT_Read_Bit();
//	}while(done != 1);
	
	
	MUX_18B20_OUT_Rst();	   
	MUX_18B20_OUT_Presence();	 
	MUX_18B20_OUT_Write_Byte(SKIP_ROM);						
  MUX_18B20_OUT_Write_Byte(READ_SCRATCHPAD);				
	
	tplsb = MUX_18B20_OUT_Read_Byte();		 
	tpmsb = MUX_18B20_OUT_Read_Byte(); 
	
	//for(i=0; i<8; i++) {
     //serial[i] = DQ_Read_Byte(type); 
		 //printf("\r\n Temp byte HI : %2x\r\n",tpmsb);
		 //printf("\r\n Temp byte LO : %2x\r\n",tplsb);
	//}
	
	s_tem = tpmsb<<8;
	s_tem = s_tem | tplsb;
	
	s_tem = s_tem & 4095;
	
	if( (s_tem & 2048) == 2048 )	{
		s_tem = (s_tem^4095) & 4095;
		f_tem = -1*(s_tem+1) * 0.0625;
	}	/* negative */
			
	else
		f_tem = s_tem * 0.0625;
	
	return f_tem; 	
}



void MUX_18B20_OUT_Read_Temperaure_Skip(uint8_t *temp, float *temp_trans , uint8_t index) 
{
		short s_tem;
	
		MUX_18B20_OUT_Rst();	   
		MUX_18B20_OUT_Presence();	 
		MUX_18B20_OUT_Write_Byte(SKIP_ROM);				
		MUX_18B20_OUT_Write_Byte(CONVERT_T);
		
		Delay_us(6000);
	
	  MUX_18B20_OUT_Rst();	   
		MUX_18B20_OUT_Presence();	 
		MUX_18B20_OUT_Write_Byte(SKIP_ROM);
	  MUX_18B20_OUT_Write_Byte(READ_SCRATCHPAD);

		temp[0] = MUX_18B20_OUT_Read_Byte();
		temp[1] = MUX_18B20_OUT_Read_Byte();
		
		s_tem = temp[1]<<8;
		s_tem = s_tem | temp[0];
	
		s_tem = s_tem & 4095;
	
		if( (s_tem & 2048) == 2048 )	{
			s_tem = (s_tem^4095) & 4095;
			temp_trans[index] = -1*(s_tem+1) * 0.0625;
		}	/* negative */	
		else
			temp_trans[index] = s_tem * 0.0625;
		
}


void MUX_18B20_OUT_Read_Temperaure_Skip_7(uint8_t *temp, float *temp_trans, uint8_t index) 
{
		short s_tem;
	
	  MUX_18B20_OUT_Rst();	   
		MUX_18B20_OUT_Presence();	 
		MUX_18B20_OUT_Write_Byte(SKIP_ROM);				
		MUX_18B20_OUT_Write_Byte(CONVERT_T);
		
		Delay_us(6000);  //For V1 Chip
	
	  MUX_18B20_OUT_Rst();	   
		MUX_18B20_OUT_Presence();	 
		MUX_18B20_OUT_Write_Byte(SKIP_ROM);
	  MUX_18B20_OUT_Write_Byte(READ_SCRATCHPAD);

		temp[0] = MUX_18B20_OUT_Read_Byte();
		temp[1] = MUX_18B20_OUT_Read_Byte();
		
		s_tem = temp[1]<<8;
		s_tem = s_tem | temp[0];
	
		s_tem = s_tem & 4095;
	
		if( (s_tem & 2048) == 2048 )	{
			s_tem = (s_tem^4095) & 4095;
			temp_trans[index] = -1*(s_tem+1) * 0.0625;
		}	/* negative */	
		else
		temp_trans[index] = s_tem * 0.0625;
		
}

void MUX_18B20_OUT_Read_Temperaure_Ori(uint8_t *temp, uint16_t *temp_trans, uint8_t index) 
{
		short s_tem;
	
	  MUX_18B20_OUT_Rst();	   
		MUX_18B20_OUT_Presence();	 
		MUX_18B20_OUT_Write_Byte(SKIP_ROM);				
		MUX_18B20_OUT_Write_Byte(CONVERT_T);
		
		Delay_us(16000);  //For V2 Chip
	
	  MUX_18B20_OUT_Rst();	   
		MUX_18B20_OUT_Presence();	 
		MUX_18B20_OUT_Write_Byte(SKIP_ROM);
	  MUX_18B20_OUT_Write_Byte(READ_SCRATCHPAD);

		temp[0] = MUX_18B20_OUT_Read_Byte();
		temp[1] = MUX_18B20_OUT_Read_Byte();
		
		s_tem = temp[1]<<8;
		s_tem = s_tem | temp[0];

		temp_trans[index] = s_tem;
		
}


void MUX_18B20_OUT_Convert_Temperaure(void) 
{

	  MUX_18B20_OUT_Rst();	   
		MUX_18B20_OUT_Presence();	 
		MUX_18B20_OUT_Write_Byte(SKIP_ROM);				
		MUX_18B20_OUT_Write_Byte(CONVERT_T);
		
		Delay_us(6000);  //For V1 Chip
		
}




uint8_t DQ_SearchROM(uint8_t (*pID)[8],uint8_t Num, uint8_t type)  
{   
    unsigned char k,l = 0,ConflictBit,m,n;  
    unsigned char BUFFER[MAXNUM_SWITCH_18B20_OUT] = {0};  
    unsigned char ss[64]= {0};
		unsigned char s = 0;  
    uint8_t num = 0;      
	 
			for(m=0; m<80; m++)  
        {    
            for(n=0; n<8; n++)  
            {   
		pID[m][n] = 0;
						}
					}
				
		do  
    {  
        DQ_Rst(type);
				DQ_Presence(type);
        DQ_Write_Byte(SEARCH_ROM, type);	   
			     
				for(m=0; m<8; m++)  
        {    
            for(n=0; n<8; n++)  
            {  
                k = DQ_Read2Bit(type);		//read two bits
							
								k = k&0x03;  
                s = s>>1;  
                
								if(k == 0x02)							//0000 0010, if get data of 0
                {             
                    DQ_Write_Bit(0, type);  //write 0, let devices of 0 on bus response
                    ss[(m*8+n)]=0;
									 // printf("SEARCH_ROM: byte: %d bit %d, hit 0\r\n",m, n);
                }  
                else if(k == 0x01)				//0000 0001, if get data of 1
                {  
                    s = s|0x80;  
                    DQ_Write_Bit(1, type);  //write 1, let devices of 1 on bus response   
                    ss[(m*8+n)] = 1;  
									 // printf("SEARCH_ROM: byte: %d bit %d, hit 1\r\n",m, n);
                }  
                else if(k == 0x00)  //if get 00, then there is confliction, needs to check  
                {                
                    ConflictBit = m*8+n+1;                   
                    
										if(ConflictBit > BUFFER[l])  //if conflict bit greater than top of stack, then write 0   
                    {                         
                        DQ_Write_Bit(0, type);  
                        ss[(m*8+n)] = 0;                                                
                        BUFFER[++l] = ConflictBit;                         
											 // printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch 0\r\n",m, n);
                    }  
                    else if(ConflictBit < BUFFER[l])  //if conflict bit less than top of stack, then write previous data
                    {  
                        s = s|((ss[(m*8+n)]&0x01)<<7);  
                        DQ_Write_Bit(ss[(m*8+n)], type);  
											 // printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch %d\r\n",m, n,ss[(m*8+n)]);
                    }  
                    else if(ConflictBit == BUFFER[l])  //if conflict bit equal to top of stack, then write 1
                    {  
                        s = s|0x80;  
                        DQ_Write_Bit(1, type);  
                        ss[(m*8+n)] = 1;  
                        l = l-1;  
											  //printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch 1\r\n",m, n);
                    }  
                }  
                else  //if get 0x03(0000 0011), then there's no device on bus
                {  
									  printf("SEARCH_ROM: byte: %d bit %d, got 0x03, device not exist\r\n",m,n);
                    return num;  //search finish, return number of devices
                }
            }  
            pID[num][m] = s;
						s = 0;
        }  
        num = num+1;
    }  
    while(BUFFER[l] != 0&&(num < MAXNUM_SWITCH_18B20_OUT));   
      
    return num;     //return number of devices
}


uint8_t DQ_Alarm_SearchROM(uint8_t (*pID)[8],uint8_t Num, uint8_t type)  
{   
    unsigned char k,l = 0,ConflictBit,m,n;  
    unsigned char BUFFER[MAXNUM_SWITCH_18B20_OUT] = {0};  
    unsigned char ss[64];
		unsigned char s = 0;  
    uint8_t num = 0;      
	  
		do  
    {  
        DQ_Rst(type);
				DQ_Presence(type);
        DQ_Write_Byte(ALARM_SEARCH, type);	   
			     
				for(m=0; m<8; m++)  
        {    
            for(n=0; n<8; n++)  
            {  
                k = DQ_Read2Bit(type);		//read two bits
							
								k = k&0x03;  
                s = s>>1;  
                
								if(k == 0x02)							//0000 0010, if get data of 0
                {             
                    DQ_Write_Bit(0, type);  //write 0, let devices of 0 on bus response
                    ss[(m*8+n)]=0;
									  //printf("SEARCH_ROM: byte: %d bit %d, hit 0\r\n",m, n);
                }  
                else if(k == 0x01)				//0000 0001, if get data of 1
                {  
                    s = s|0x80;  
                    DQ_Write_Bit(1, type);  //write 1, let devices of 1 on bus response   
                    ss[(m*8+n)] = 1;  
									  //printf("SEARCH_ROM: byte: %d bit %d, hit 1\r\n",m, n);
                }  
                else if(k == 0x00)  //if get 00, then there is confliction, needs to check  
                {                
                    ConflictBit = m*8+n+1;                   
                    
										if(ConflictBit > BUFFER[l])  //if conflict bit greater than top of stack, then write 0   
                    {                         
                        DQ_Write_Bit(0, type);  
                        ss[(m*8+n)] = 0;                                                
                        BUFFER[++l] = ConflictBit;                         
											  //printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch 0\r\n",m, n);
                    }  
                    else if(ConflictBit < BUFFER[l])  //if conflict bit less than top of stack, then write previous data
                    {  
                        s = s|((ss[(m*8+n)]&0x01)<<7);  
                        DQ_Write_Bit(ss[(m*8+n)], type);  
											  //printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch %d\r\n",m, n,ss[(m*8+n)]);
                    }  
                    else if(ConflictBit == BUFFER[l])  //if conflict bit equal to top of stack, then write 1
                    {  
                        s = s|0x80;  
                        DQ_Write_Bit(1, type);  
                        ss[(m*8+n)] = 1;  
                        l = l-1;  
											  //printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch 1\r\n",m, n);
                    }  
                }  
                else  //if get 0x03(0000 0011), then there's no device on bus
                {  
									  printf("SEARCH_ROM: byte: %d bit %d, got 0x03, device not exist\r\n",m,n);
                    return num;  //search finish, return number of devices
                }
            }  
            pID[num][m] = s;
						s = 0;
        }  
        num = num+1;
    }  
    while(BUFFER[l] != 0&&(num < MAXNUM_SWITCH_18B20_OUT));   
      
    return num;     //return number of devices
}


void DQ_Read_Scrpad(uint8_t *serial, uint8_t type)  
{
  uint8_t i;
  DQ_Rst(type);
  DQ_Presence(type);
  DQ_Write_Byte(SKIP_ROM, type); 
  DQ_Write_Byte(READ_SCRATCHPAD, type); 
  
	for(i=0; i<9; i++) {
     serial[i] = DQ_Read_Byte(type); 
		 //printf("\r\n Scratchpad byte %d : %2x\r\n",i, serial[i]);
		//printf("%.2x ",serial[i]);
	}

	//for(i=0; i<9; i++) {
     //serial[i] = DQ_Read_Byte(type); 
		 
	//}

}

void DQ_Read_Scrpad_Ext(uint8_t *serial, uint8_t type)  
{
  uint8_t i;
  DQ_Rst(type);
  DQ_Presence(type);
  DQ_Write_Byte(SKIP_ROM, type); 
  DQ_Write_Byte(READ_SCRATCHPAD_EXT, type); 
  
	for(i=0; i<6; i++) {
     serial[i] = DQ_Read_Byte(type); 
		 printf("\r\n Scratchpad Extend byte %d : %2x\r\n",i, serial[i]);
	}	
}

void DQ_Read_User_Ext(uint8_t *serial, uint8_t type)  
{
  uint8_t i;
  DQ_Rst(type);
  DQ_Presence(type);
  DQ_Write_Byte(SKIP_ROM, type); 
  DQ_Write_Byte(READ_USER_EXT, type); 
  
	for(i=0; i<5; i++) {
     serial[i] = DQ_Read_Byte(type); 
		 printf("\r\n User Extend byte %d : %2x\r\n",i, serial[i]);
	}	
}

void DQ_Read_Rom_Code(uint8_t *serial, uint8_t type)  
{
  uint8_t i;

  DQ_Rst(type);
  DQ_Presence(type);
	DQ_Write_Byte(READ_ROM, type); 
  
	for(i=0; i<8; i++) {                                 //Dongsheng
     serial[i] = DQ_Read_Byte(type);     
	//	printf("\r Loop %d \n",i);
		 //printf("\r\n ROM byte %d : %2x\r\n",i, serial[i]);
		//printf("%2x",serial[i]);
	}	
	
	//for(i=0; i<8; i++) {
     //serial[i] = DQ_Read_Byte(type); 
		 //printf("\r\n ROM byte %d : %2x\r\n",i, serial[i]);
	//}

}



void DQ_Write_Test(uint8_t data, uint8_t type)  
{

  DQ_Rst(type);
  DQ_Presence(type);
  DQ_Write_Byte(data, type); 
	
}

void DQ_Read_Parameters(uint8_t *serial, uint8_t type)  
{
  uint8_t i;
  DQ_Rst(type);
  DQ_Presence(type);
  DQ_Write_Byte(SKIP_ROM, type); 
  DQ_Write_Byte(READ_PARAMETERS, type); 
  
	for(i=0; i<8; i++) {
     serial[i] = DQ_Read_Byte(type); 
		 //printf("\r\n Parameter byte %d : %2x\r\n",i, serial[i]);
		//printf("%2x",serial[i]);
	}	
}

void DQ_Check_Power_Supply(uint8_t type)
{
		char mode;
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(READ_POWER_SUPPLY, type);
	
		mode = DQ_Read_Bit(type);
		
		printf("\r\nPower Supply mode is: %d\r\n", mode);
}

void DQ_Recall_EE(uint8_t type)
{
		
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(RECALL_E2, type); 
	  Delay_us(3000);
	
}


void DQ_Recall_PAGE0_RES(uint8_t type)
{
		
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(RECALL_PAGE0_RES, type); 
	  Delay_us(3000);
	
}


void DQ_Recall_PAGE1(uint8_t type)
{
		
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
	//	Delay_us(10);
    DQ_Write_Byte(RECALL_PAGE1, type); 	
	
		Delay_us(3000);
}



void DQ_Copy_PAGE0(uint8_t type)  
{    
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(COPY_PAGE0, type); 
		
		Delay_us(30000);
}


void DQ_Copy_PAGE1(uint8_t type)  
{    
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(COPY_PAGE1, type);
		
		Delay_us(35000);
}



void DQ_Write_Scratchpad(uint8_t TH,uint8_t TL,uint8_t CFG, uint8_t type)  
{  
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(WRITE_SCRATCHPAD, type); 
		DQ_Write_Byte(TH, type); 
		DQ_Write_Byte(TL, type); 
		DQ_Write_Byte(CFG, type);		      
}

void DQ_Write_User(uint8_t UDF0,uint8_t UDF1,uint8_t UDF2, uint8_t type)  
{  
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(WRITE_USER, type); 
		DQ_Write_Byte(UDF0, type); 
		DQ_Write_Byte(UDF1, type); 
		DQ_Write_Byte(UDF2, type);		      
}

void DQ_Write_Scratchpad_Ext(uint8_t ANA_CONF,uint8_t TTHRES_HI,uint8_t TTHRES_LO, uint8_t ADC_COEFF_EXT0,uint8_t ADC_COEFF_EXT1,uint8_t ADC_COEFF_EXT2, uint8_t type)  
{  
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(WRITE_SCRATCHPAD_EXT, type); 
		DQ_Write_Byte(ANA_CONF, type); 
		DQ_Write_Byte(TTHRES_HI, type); 
		DQ_Write_Byte(TTHRES_LO, type);
		DQ_Write_Byte(ADC_COEFF_EXT0, type); 
		DQ_Write_Byte(ADC_COEFF_EXT1, type); 
		DQ_Write_Byte(ADC_COEFF_EXT2, type);	
}

void DQ_Write_User_Ext(uint8_t UDF_EXT0,uint8_t UDF_EXT1,uint8_t UDF_EXT2,uint8_t UDF_EXT3,uint8_t UDF_EXT4, uint8_t type)  
{  
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(WRITE_USER_EXT, type); 
		DQ_Write_Byte(UDF_EXT0, type); 
		DQ_Write_Byte(UDF_EXT1, type); 
		DQ_Write_Byte(UDF_EXT2, type);
		DQ_Write_Byte(UDF_EXT3, type); 
		DQ_Write_Byte(UDF_EXT4, type);	
}

void DQ_Write_Parameters(uint8_t ADC_COEFF0,uint8_t ADC_COEFF1,uint8_t ADC_COEFF2,uint8_t ADC_CONF0,uint8_t ADC_CONF1,uint8_t ANA_CAL0,uint8_t ANA_CAL1,uint8_t TTRIM, uint8_t type)  
{  
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);
		DQ_Write_Byte(WRITE_PARAMETERS, type);   
		DQ_Write_Byte(ADC_COEFF0, type); 
		DQ_Write_Byte(ADC_COEFF1, type); 
		DQ_Write_Byte(ADC_COEFF2, type);
		DQ_Write_Byte(ADC_CONF0, type); 
		DQ_Write_Byte(ADC_CONF1, type); 
		DQ_Write_Byte(ANA_CAL0, type);
		DQ_Write_Byte(ANA_CAL1, type); 
		DQ_Write_Byte(TTRIM, type); 
}

void Array_Setup_ROM(uint8_t *ROM, uint8_t type)  
{  
		uint8_t i;
		
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SETUP_ROM, type);   
		
		for(i=0; i<8; i++)
			DQ_Write_Byte(ROM[i], type);

		DQ_Copy_PAGE1(type);
}

void Array_Setup_AB(uint8_t *AB, uint8_t type)  
{  
		uint8_t i;
		
		DQ_Rst(MUX_18B20_OUT);
		DQ_Presence(MUX_18B20_OUT);
		DQ_Write_Byte(SKIP_ROM, MUX_18B20_OUT);  
		DQ_Write_Byte(WRITE_SCRATCHPAD_EXT, MUX_18B20_OUT); 
		DQ_Write_Byte(0x11, MUX_18B20_OUT); 

		Delay_us(1000);
	
	  DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);
	  DQ_Write_Byte(WRITE_PARAMETERS, type);   
		
		for(i=0; i<4; i++)
			DQ_Write_Byte(AB[i], type);
	  
	  DQ_Write_Byte(0x20, type);

		DQ_Copy_PAGE1(type);
}





/********************************CP tasks*******************************************************************************/








/*****************************************FT Tasks******************************************************************************************/
void MUX1_EN(void) {
		M0_DATA_OUT(0);
		M1_DATA_OUT(0);
		M2_DATA_OUT(0);
}

void MUX2_EN(void) {
		M0_DATA_OUT(1);
		M1_DATA_OUT(0);
		M2_DATA_OUT(0);
}

void MUX3_EN(void) {
		M0_DATA_OUT(0);
		M1_DATA_OUT(1);
		M2_DATA_OUT(0);
}

void MUX4_EN(void) {
		M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(0);
}

void MUX5_EN(void) {
		M0_DATA_OUT(0);
		M1_DATA_OUT(0);
		M2_DATA_OUT(1);
}
void MUX6_EN(void) {
		M0_DATA_OUT(1);
		M1_DATA_OUT(0);
		M2_DATA_OUT(1);
}
void MUX7_EN(void) {
		M0_DATA_OUT(0);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
}

void MUX_DIS(void) {
		M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
}

void MUX_Channel_SEL(uint8_t ch) {
		switch(ch) {
					case 0:
						MUX_S0_DATA_OUT(0);
						MUX_S1_DATA_OUT(0);
						MUX_S2_DATA_OUT(0);
						MUX_S3_DATA_OUT(0);
						break;
					case 1:
						MUX_S0_DATA_OUT(1);
						MUX_S1_DATA_OUT(0);
						MUX_S2_DATA_OUT(0);
						MUX_S3_DATA_OUT(0);
						break;
					case 2:
						MUX_S0_DATA_OUT(0);
						MUX_S1_DATA_OUT(1);
						MUX_S2_DATA_OUT(0);
						MUX_S3_DATA_OUT(0);
						break;
					case 3:
						MUX_S0_DATA_OUT(1);
						MUX_S1_DATA_OUT(1);
						MUX_S2_DATA_OUT(0);
						MUX_S3_DATA_OUT(0);
						break;
					case 4:
						MUX_S0_DATA_OUT(0);
						MUX_S1_DATA_OUT(0);
						MUX_S2_DATA_OUT(1);
						MUX_S3_DATA_OUT(0);
						break;
					case 5:
						MUX_S0_DATA_OUT(1);
						MUX_S1_DATA_OUT(0);
						MUX_S2_DATA_OUT(1);
						MUX_S3_DATA_OUT(0);
						break;
					case 6:
						MUX_S0_DATA_OUT(0);
						MUX_S1_DATA_OUT(1);
						MUX_S2_DATA_OUT(1);
						MUX_S3_DATA_OUT(0);
						break;
					case 7:
						MUX_S0_DATA_OUT(1);
						MUX_S1_DATA_OUT(1);
						MUX_S2_DATA_OUT(1);
						MUX_S3_DATA_OUT(0);
						break;
					case 8:
						MUX_S0_DATA_OUT(0);
						MUX_S1_DATA_OUT(0);
						MUX_S2_DATA_OUT(0);
						MUX_S3_DATA_OUT(1);
						break;
					case 9:
						MUX_S0_DATA_OUT(1);
						MUX_S1_DATA_OUT(0);
						MUX_S2_DATA_OUT(0);
						MUX_S3_DATA_OUT(1);
						break;
					case 10:
						MUX_S0_DATA_OUT(0);
						MUX_S1_DATA_OUT(1);
						MUX_S2_DATA_OUT(0);
						MUX_S3_DATA_OUT(1);
						break;
					case 11:
						MUX_S0_DATA_OUT(1);
						MUX_S1_DATA_OUT(1);
						MUX_S2_DATA_OUT(0);
						MUX_S3_DATA_OUT(1);
						break;
					case 12:
						MUX_S0_DATA_OUT(0);
						MUX_S1_DATA_OUT(0);
						MUX_S2_DATA_OUT(1);
						MUX_S3_DATA_OUT(1);
						break;
					case 13:
						MUX_S0_DATA_OUT(1);
						MUX_S1_DATA_OUT(0);
						MUX_S2_DATA_OUT(1);
						MUX_S3_DATA_OUT(1);
						break;
					case 14:
						MUX_S0_DATA_OUT(0);
						MUX_S1_DATA_OUT(1);
						MUX_S2_DATA_OUT(1);
						MUX_S3_DATA_OUT(1);
						break;
					case 15:
						MUX_S0_DATA_OUT(1);
						MUX_S1_DATA_OUT(1);
						MUX_S2_DATA_OUT(1);
						MUX_S3_DATA_OUT(1);
						break;
					default:
						MUX_S0_DATA_OUT(0);
						MUX_S1_DATA_OUT(0);
						MUX_S2_DATA_OUT(0);
						MUX_S3_DATA_OUT(0);
						break;
		}
}



void Board_SEL(uint8_t ch) {
		switch(ch) {
					case 0:
						SUB_E1_DATA_OUT(1);
						SUB_E2_DATA_OUT(0);
						SUB_E3_DATA_OUT(0);
						SUB_E4_DATA_OUT(0);
						SUB_E5_DATA_OUT(0);
						SUB_E6_DATA_OUT(0);
						SUB_E7_DATA_OUT(0);
						SUB_E8_DATA_OUT(0);
						SUB_E9_DATA_OUT(0);
						SUB_E10_DATA_OUT(0);
						SUB_E11_DATA_OUT(0);
						SUB_E12_DATA_OUT(0);
						SUB_E13_DATA_OUT(0);
						SUB_E14_DATA_OUT(0);
						SUB_E15_DATA_OUT(0);
						SUB_E16_DATA_OUT(0);
						break;
					case 1:
						SUB_E1_DATA_OUT(0);
						SUB_E2_DATA_OUT(1);
						SUB_E3_DATA_OUT(0);
						SUB_E4_DATA_OUT(0);
						SUB_E5_DATA_OUT(0);
						SUB_E6_DATA_OUT(0);
						SUB_E7_DATA_OUT(0);
						SUB_E8_DATA_OUT(0);
						SUB_E9_DATA_OUT(0);
						SUB_E10_DATA_OUT(0);
						SUB_E11_DATA_OUT(0);
						SUB_E12_DATA_OUT(0);
						SUB_E13_DATA_OUT(0);
						SUB_E14_DATA_OUT(0);
						SUB_E15_DATA_OUT(0);
						SUB_E16_DATA_OUT(0);
					break;
					case 2:
						SUB_E1_DATA_OUT(0);
						SUB_E2_DATA_OUT(0);
						SUB_E3_DATA_OUT(1);
						SUB_E4_DATA_OUT(0);
						SUB_E5_DATA_OUT(0);
						SUB_E6_DATA_OUT(0);
						SUB_E7_DATA_OUT(0);
						SUB_E8_DATA_OUT(0);
						SUB_E9_DATA_OUT(0);
						SUB_E10_DATA_OUT(0);
						SUB_E11_DATA_OUT(0);
						SUB_E12_DATA_OUT(0);
						SUB_E13_DATA_OUT(0);
						SUB_E14_DATA_OUT(0);
						SUB_E15_DATA_OUT(0);
						SUB_E16_DATA_OUT(0);
						break;
					case 3:
						SUB_E1_DATA_OUT(0);
						SUB_E2_DATA_OUT(0);
						SUB_E3_DATA_OUT(0);
						SUB_E4_DATA_OUT(1);
						SUB_E5_DATA_OUT(0);
						SUB_E6_DATA_OUT(0);
						SUB_E7_DATA_OUT(0);
						SUB_E8_DATA_OUT(0);
						SUB_E9_DATA_OUT(0);
						SUB_E10_DATA_OUT(0);
						SUB_E11_DATA_OUT(0);
						SUB_E12_DATA_OUT(0);
						SUB_E13_DATA_OUT(0);
						SUB_E14_DATA_OUT(0);
						SUB_E15_DATA_OUT(0);
						SUB_E16_DATA_OUT(0);
						break;
					case 4:
						SUB_E1_DATA_OUT(0);
						SUB_E2_DATA_OUT(0);
						SUB_E3_DATA_OUT(0);
						SUB_E4_DATA_OUT(0);
						SUB_E5_DATA_OUT(1);
						SUB_E6_DATA_OUT(0);
						SUB_E7_DATA_OUT(0);
						SUB_E8_DATA_OUT(0);
						SUB_E9_DATA_OUT(0);
						SUB_E10_DATA_OUT(0);
						SUB_E11_DATA_OUT(0);
						SUB_E12_DATA_OUT(0);
						SUB_E13_DATA_OUT(0);
						SUB_E14_DATA_OUT(0);
						SUB_E15_DATA_OUT(0);
						SUB_E16_DATA_OUT(0);
						break;
					case 5:
						SUB_E1_DATA_OUT(0);
						SUB_E2_DATA_OUT(0);
						SUB_E3_DATA_OUT(0);
						SUB_E4_DATA_OUT(0);
						SUB_E5_DATA_OUT(0);
						SUB_E6_DATA_OUT(1);
						SUB_E7_DATA_OUT(0);
						SUB_E8_DATA_OUT(0);
						SUB_E9_DATA_OUT(0);
						SUB_E10_DATA_OUT(0);
						SUB_E11_DATA_OUT(0);
						SUB_E12_DATA_OUT(0);
						SUB_E13_DATA_OUT(0);
						SUB_E14_DATA_OUT(0);
						SUB_E15_DATA_OUT(0);
						SUB_E16_DATA_OUT(0);
						break;
					case 6:
						SUB_E1_DATA_OUT(0);
						SUB_E2_DATA_OUT(0);
						SUB_E3_DATA_OUT(0);
						SUB_E4_DATA_OUT(0);
						SUB_E5_DATA_OUT(0);
						SUB_E6_DATA_OUT(0);
						SUB_E7_DATA_OUT(1);
						SUB_E8_DATA_OUT(0);
						SUB_E9_DATA_OUT(0);
						SUB_E10_DATA_OUT(0);
						SUB_E11_DATA_OUT(0);
						SUB_E12_DATA_OUT(0);
						SUB_E13_DATA_OUT(0);
						SUB_E14_DATA_OUT(0);
						SUB_E15_DATA_OUT(0);
						SUB_E16_DATA_OUT(0);
						break;
					case 7:
						SUB_E1_DATA_OUT(0);
						SUB_E2_DATA_OUT(0);
						SUB_E3_DATA_OUT(0);
						SUB_E4_DATA_OUT(0);
						SUB_E5_DATA_OUT(0);
						SUB_E6_DATA_OUT(0);
						SUB_E7_DATA_OUT(0);
						SUB_E8_DATA_OUT(1);
						SUB_E9_DATA_OUT(0);
						SUB_E10_DATA_OUT(0);
						SUB_E11_DATA_OUT(0);
						SUB_E12_DATA_OUT(0);
						SUB_E13_DATA_OUT(0);
						SUB_E14_DATA_OUT(0);
						SUB_E15_DATA_OUT(0);
						SUB_E16_DATA_OUT(0);
						break;
					case 8:
						SUB_E1_DATA_OUT(0);
						SUB_E2_DATA_OUT(0);
						SUB_E3_DATA_OUT(0);
						SUB_E4_DATA_OUT(0);
						SUB_E5_DATA_OUT(0);
						SUB_E6_DATA_OUT(0);
						SUB_E7_DATA_OUT(0);
						SUB_E8_DATA_OUT(0);
						SUB_E9_DATA_OUT(1);
						SUB_E10_DATA_OUT(0);
						SUB_E11_DATA_OUT(0);
						SUB_E12_DATA_OUT(0);
						SUB_E13_DATA_OUT(0);
						SUB_E14_DATA_OUT(0);
						SUB_E15_DATA_OUT(0);
						SUB_E16_DATA_OUT(0);
						break;
					case 9:
						SUB_E1_DATA_OUT(0);
						SUB_E2_DATA_OUT(0);
						SUB_E3_DATA_OUT(0);
						SUB_E4_DATA_OUT(0);
						SUB_E5_DATA_OUT(0);
						SUB_E6_DATA_OUT(0);
						SUB_E7_DATA_OUT(0);
						SUB_E8_DATA_OUT(0);
						SUB_E9_DATA_OUT(0);
						SUB_E10_DATA_OUT(1);
						SUB_E11_DATA_OUT(0);
						SUB_E12_DATA_OUT(0);
						SUB_E13_DATA_OUT(0);
						SUB_E14_DATA_OUT(0);
						SUB_E15_DATA_OUT(0);
						SUB_E16_DATA_OUT(0);
						break;
					case 10:
						SUB_E1_DATA_OUT(0);
						SUB_E2_DATA_OUT(0);
						SUB_E3_DATA_OUT(0);
						SUB_E4_DATA_OUT(0);
						SUB_E5_DATA_OUT(0);
						SUB_E6_DATA_OUT(0);
						SUB_E7_DATA_OUT(0);
						SUB_E8_DATA_OUT(0);
						SUB_E9_DATA_OUT(0);
						SUB_E10_DATA_OUT(0);
						SUB_E11_DATA_OUT(1);
						SUB_E12_DATA_OUT(0);
						SUB_E13_DATA_OUT(0);
						SUB_E14_DATA_OUT(0);
						SUB_E15_DATA_OUT(0);
						SUB_E16_DATA_OUT(0);
						break;
					case 11:
						SUB_E1_DATA_OUT(0);
						SUB_E2_DATA_OUT(0);
						SUB_E3_DATA_OUT(0);
						SUB_E4_DATA_OUT(0);
						SUB_E5_DATA_OUT(0);
						SUB_E6_DATA_OUT(0);
						SUB_E7_DATA_OUT(0);
						SUB_E8_DATA_OUT(0);
						SUB_E9_DATA_OUT(0);
						SUB_E10_DATA_OUT(0);
						SUB_E11_DATA_OUT(0);
						SUB_E12_DATA_OUT(1);
						SUB_E13_DATA_OUT(0);
						SUB_E14_DATA_OUT(0);
						SUB_E15_DATA_OUT(0);
						SUB_E16_DATA_OUT(0);
						break;
					case 12:
						SUB_E1_DATA_OUT(0);
						SUB_E2_DATA_OUT(0);
						SUB_E3_DATA_OUT(0);
						SUB_E4_DATA_OUT(0);
						SUB_E5_DATA_OUT(0);
						SUB_E6_DATA_OUT(0);
						SUB_E7_DATA_OUT(0);
						SUB_E8_DATA_OUT(0);
						SUB_E9_DATA_OUT(0);
						SUB_E10_DATA_OUT(0);
						SUB_E11_DATA_OUT(0);
						SUB_E12_DATA_OUT(0);
						SUB_E13_DATA_OUT(1);
						SUB_E14_DATA_OUT(0);
						SUB_E15_DATA_OUT(0);
						SUB_E16_DATA_OUT(0);
						break;
					case 13:
						SUB_E1_DATA_OUT(0);
						SUB_E2_DATA_OUT(0);
						SUB_E3_DATA_OUT(0);
						SUB_E4_DATA_OUT(0);
						SUB_E5_DATA_OUT(0);
						SUB_E6_DATA_OUT(0);
						SUB_E7_DATA_OUT(0);
						SUB_E8_DATA_OUT(0);
						SUB_E9_DATA_OUT(0);
						SUB_E10_DATA_OUT(0);
						SUB_E11_DATA_OUT(0);
						SUB_E12_DATA_OUT(0);
						SUB_E13_DATA_OUT(0);
						SUB_E14_DATA_OUT(1);
						SUB_E15_DATA_OUT(0);
						SUB_E16_DATA_OUT(0);
						break;
					case 14:
						SUB_E1_DATA_OUT(0);
						SUB_E2_DATA_OUT(0);
						SUB_E3_DATA_OUT(0);
						SUB_E4_DATA_OUT(0);
						SUB_E5_DATA_OUT(0);
						SUB_E6_DATA_OUT(0);
						SUB_E7_DATA_OUT(0);
						SUB_E8_DATA_OUT(0);
						SUB_E9_DATA_OUT(0);
						SUB_E10_DATA_OUT(0);
						SUB_E11_DATA_OUT(0);
						SUB_E12_DATA_OUT(0);
						SUB_E13_DATA_OUT(0);
						SUB_E14_DATA_OUT(0);
						SUB_E15_DATA_OUT(1);
						SUB_E16_DATA_OUT(0);
						break;
					case 15:
						SUB_E1_DATA_OUT(0);
						SUB_E2_DATA_OUT(0);
						SUB_E3_DATA_OUT(0);
						SUB_E4_DATA_OUT(0);
						SUB_E5_DATA_OUT(0);
						SUB_E6_DATA_OUT(0);
						SUB_E7_DATA_OUT(0);
						SUB_E8_DATA_OUT(0);
						SUB_E9_DATA_OUT(0);
						SUB_E10_DATA_OUT(0);
						SUB_E11_DATA_OUT(0);
						SUB_E12_DATA_OUT(0);
						SUB_E13_DATA_OUT(0);
						SUB_E14_DATA_OUT(0);
						SUB_E15_DATA_OUT(0);
						SUB_E16_DATA_OUT(1);
						break;
					default:
						SUB_E1_DATA_OUT(1);
						SUB_E2_DATA_OUT(0);
						SUB_E3_DATA_OUT(0);
						SUB_E4_DATA_OUT(0);
						SUB_E5_DATA_OUT(0);
						SUB_E6_DATA_OUT(0);
						SUB_E7_DATA_OUT(0);
						SUB_E8_DATA_OUT(0);
						SUB_E9_DATA_OUT(0);
						SUB_E10_DATA_OUT(0);
						SUB_E11_DATA_OUT(0);
						SUB_E12_DATA_OUT(0);
						SUB_E13_DATA_OUT(0);
						SUB_E14_DATA_OUT(0);
						SUB_E15_DATA_OUT(0);
						SUB_E16_DATA_OUT(0);
						break;
		}
}

void line_en(uint8_t row, uint8_t index) {
		switch(row) {
			case 0:
				if(index == 0) {
					MUX1_EN();
					Delay_us(100);
					MUX_Channel_SEL(0);
				}
				else if(index == 1) {
					MUX1_EN();
					Delay_us(100);
					MUX_Channel_SEL(1);
				}
				else if(index == 2) {
					MUX1_EN();
					Delay_us(100);
					MUX_Channel_SEL(2);
				}
				else if(index == 3) {
					MUX1_EN();
					Delay_us(100);
					MUX_Channel_SEL(3);
				}
				else if(index == 4) {
					MUX1_EN();
					Delay_us(100);
					MUX_Channel_SEL(4);
				}
				else if(index == 5) {
					MUX1_EN();
					Delay_us(100);
					MUX_Channel_SEL(5);
				}
				else if(index == 6) {
					MUX1_EN();
					Delay_us(100);
					MUX_Channel_SEL(6);
				}
				else if(index == 7) {
					MUX1_EN();
					Delay_us(100);
					MUX_Channel_SEL(7);
				}
				else if(index == 8) {
					MUX1_EN();
					Delay_us(100);
					MUX_Channel_SEL(8);
				}
				else if(index == 9) {
					MUX1_EN();
					Delay_us(100);
					MUX_Channel_SEL(9);
				}
				else {
					MUX_DIS();
				}
				break;
			case 1:
				if(index == 0) {
					MUX1_EN();
					Delay_us(100);
					MUX_Channel_SEL(10);
				}
				else if(index == 1) {
					MUX1_EN();
					Delay_us(100);
					MUX_Channel_SEL(11);
				}
				else if(index == 2) {
					MUX1_EN();
					Delay_us(100);
					MUX_Channel_SEL(12);
				}
				else if(index == 3) {
					MUX1_EN();
					Delay_us(100);
					MUX_Channel_SEL(13);
				}
				else if(index == 4) {
					MUX1_EN();
					Delay_us(100);
					MUX_Channel_SEL(14);
				}
				else if(index == 5) {
					MUX1_EN();
					Delay_us(100);
					MUX_Channel_SEL(15);
				}
				else if(index == 6) {
					MUX2_EN();
					Delay_us(100);
					MUX_Channel_SEL(0);
				}
				else if(index == 7) {
					MUX2_EN();
					Delay_us(100);
					MUX_Channel_SEL(1);
				}
				else if(index == 8) {
					MUX2_EN();
					Delay_us(100);
					MUX_Channel_SEL(2);
				}
				else if(index == 9) {
					MUX2_EN();
					Delay_us(100);
					MUX_Channel_SEL(3);
				}
				else {
					MUX_DIS();
				}
				break;
			case 2:
				if(index == 0) {
					MUX2_EN();
					Delay_us(100);
					MUX_Channel_SEL(4);
				}
				else if(index == 1) {
					MUX2_EN();
					Delay_us(100);
					MUX_Channel_SEL(5);
				}
				else if(index == 2) {
					MUX2_EN();
					Delay_us(100);
					MUX_Channel_SEL(6);
				}
				else if(index == 3) {
					MUX2_EN();
					Delay_us(100);
					MUX_Channel_SEL(7);
				}
				else if(index == 4) {
					MUX2_EN();
					Delay_us(100);
					MUX_Channel_SEL(8);
				}
				else if(index == 5) {
					MUX2_EN();
					Delay_us(100);
					MUX_Channel_SEL(9);
				}
				else if(index == 6) {
					MUX2_EN();
					Delay_us(100);
					MUX_Channel_SEL(10);
				}
				else if(index == 7) {
					MUX2_EN();
					Delay_us(100);
					MUX_Channel_SEL(11);
				}
				else if(index == 8) {
					MUX2_EN();
					Delay_us(100);
					MUX_Channel_SEL(12);
				}
				else if(index == 9) {
					MUX2_EN();
					Delay_us(100);
					MUX_Channel_SEL(13);
				}
				else {
					MUX_DIS();
				}
				break;
			case 3:
				if(index == 0) {
					MUX2_EN();
					Delay_us(100);
					MUX_Channel_SEL(14);
				}
				else if(index == 1) {
					MUX2_EN();
					Delay_us(100);
					MUX_Channel_SEL(15);
				}
				else if(index == 2) {
					MUX3_EN();
					Delay_us(100);
					MUX_Channel_SEL(0);
				}
				else if(index == 3) {
					MUX3_EN();
					Delay_us(100);
					MUX_Channel_SEL(1);
				}
				else if(index == 4) {
					MUX3_EN();
					Delay_us(100);
					MUX_Channel_SEL(2);
				}
				else if(index == 5) {
					MUX3_EN();
					Delay_us(100);
					MUX_Channel_SEL(3);	
				}
				else if(index == 6) {
					MUX3_EN();
					Delay_us(100);
					MUX_Channel_SEL(4);
				}
				else if(index == 7) {
					MUX3_EN();
					Delay_us(100);
					MUX_Channel_SEL(5);
				}
				else if(index == 8) {
					MUX3_EN();
					Delay_us(100);
					MUX_Channel_SEL(6);
				}
				else if(index == 9) {
					MUX3_EN();
					Delay_us(100);
					MUX_Channel_SEL(7);
				}
				else {
					MUX_DIS();
				}
				break;
			case 4:
				if(index == 0) {
					MUX3_EN();
					Delay_us(100);
					MUX_Channel_SEL(8);
				}
				else if(index == 1) {
					MUX3_EN();
					Delay_us(100);
					MUX_Channel_SEL(9);
				}
				else if(index == 2) {
					MUX3_EN();
					Delay_us(100);
					MUX_Channel_SEL(10);
				}
				else if(index == 3) {
					MUX3_EN();
					Delay_us(100);
					MUX_Channel_SEL(11);
				}
				else if(index == 4) {
					MUX3_EN();
					Delay_us(100);
					MUX_Channel_SEL(12);
				}
				else if(index == 5) {
					MUX3_EN();
					Delay_us(100);
					MUX_Channel_SEL(13);
				}
				else if(index == 6) {
					MUX3_EN();
					Delay_us(100);
					MUX_Channel_SEL(14);
				}
				else if(index == 7) {
					MUX3_EN();
					Delay_us(100);
					MUX_Channel_SEL(15);
				}
				else if(index == 8) {
					MUX4_EN();
					Delay_us(100);
					MUX_Channel_SEL(0);
				}
				else if(index == 9) {
					MUX4_EN();
					Delay_us(100);
					MUX_Channel_SEL(1);
				}
				else {
					MUX_DIS();
				}
				break;
			case 5:
				if(index == 0) {
					MUX4_EN();
					Delay_us(100);
					MUX_Channel_SEL(2);
				}
				else if(index == 1) {
					MUX4_EN();
					Delay_us(100);
					MUX_Channel_SEL(3);
				}
				else if(index == 2) {
					MUX4_EN();
					Delay_us(100);
					MUX_Channel_SEL(4);
				}
				else if(index == 3) {
					MUX4_EN();
					Delay_us(100);
					MUX_Channel_SEL(5);
				}
				else if(index == 4) {
					MUX4_EN();
					Delay_us(100);
					MUX_Channel_SEL(6);
				}
				else if(index == 5) {
					MUX4_EN();
					Delay_us(100);
					MUX_Channel_SEL(7);
				}
				else if(index == 6) {
					MUX4_EN();
					Delay_us(100);
					MUX_Channel_SEL(8);
				}
				else if(index == 7) {
					MUX4_EN();
					Delay_us(100);
					MUX_Channel_SEL(9);
				}
				else if(index == 8) {
					MUX4_EN();
					Delay_us(100);
					MUX_Channel_SEL(10);
				}
				else if(index == 9) {
					MUX4_EN();
					Delay_us(100);
					MUX_Channel_SEL(11);
				}
				else {
					MUX_DIS();
				}
				break;
			case 6:
				if(index == 0) {
					MUX4_EN();
					Delay_us(100);
					MUX_Channel_SEL(12);
				}
				else if(index == 1) {
					MUX4_EN();
					Delay_us(100);
					MUX_Channel_SEL(13);
				}
				else if(index == 2) {
					MUX4_EN();
					Delay_us(100);
					MUX_Channel_SEL(14);
				}
				else if(index == 3) {
					MUX4_EN();
					Delay_us(100);
					MUX_Channel_SEL(15);
				}
				else if(index == 4) {
					MUX5_EN();
					Delay_us(100);
					MUX_Channel_SEL(0);
				}
				else if(index == 5) {
					MUX5_EN();
					Delay_us(100);
					MUX_Channel_SEL(1);
				}
				else if(index == 6) {
					MUX5_EN();
					Delay_us(100);
					MUX_Channel_SEL(2);
				}
				else if(index == 7) {
					MUX5_EN();
					Delay_us(100);
					MUX_Channel_SEL(3);
				}
				else if(index == 8) {
					MUX5_EN();
					Delay_us(100);
					MUX_Channel_SEL(4);
				}
				else if(index == 9) {
					MUX5_EN();
					Delay_us(100);
					MUX_Channel_SEL(5);
				}
				else {
					MUX_DIS();
				}
				break;
			case 7:
				if(index == 0) {
					MUX5_EN();
					Delay_us(100);
					MUX_Channel_SEL(6);
				}
				else if(index == 1) {
					MUX5_EN();
					Delay_us(100);
					MUX_Channel_SEL(7);
				}
				else if(index == 2) {
					MUX5_EN();
					Delay_us(100);
					MUX_Channel_SEL(8);
				}
				else if(index == 3) {
					MUX5_EN();
					Delay_us(100);
					MUX_Channel_SEL(9);
				}
				else if(index == 4) {
					MUX5_EN();
					Delay_us(100);
					MUX_Channel_SEL(10);
				}
				else if(index == 5) {
					MUX5_EN();
					Delay_us(100);
					MUX_Channel_SEL(11);
				}
				else if(index == 6) {
					MUX5_EN();
					Delay_us(100);
					MUX_Channel_SEL(12);
				}
				else if(index == 7) {
					MUX5_EN();
					Delay_us(100);
					MUX_Channel_SEL(13);
				}
				else if(index == 8) {
					MUX5_EN();
					Delay_us(100);
					MUX_Channel_SEL(14);
				}
				else if(index == 9) {
					MUX5_EN();
					Delay_us(100);
					MUX_Channel_SEL(15);
				}
				else {
					MUX_DIS();
				}
				break;
			case 8:
				if(index == 0) {
					MUX6_EN();
					Delay_us(100);
					MUX_Channel_SEL(0);
				}
				else if(index == 1) {
					MUX6_EN();
					Delay_us(100);
					MUX_Channel_SEL(1);
				}
				else if(index == 2) {
					MUX6_EN();
					Delay_us(100);
					MUX_Channel_SEL(2);
				}
				else if(index == 3) {
					MUX6_EN();
					Delay_us(100);
					MUX_Channel_SEL(3);
				}
				else if(index == 4) {
					MUX6_EN();
					Delay_us(100);
					MUX_Channel_SEL(4);
				}
				else if(index == 5) {
					MUX6_EN();
					Delay_us(100);
					MUX_Channel_SEL(5);
				}
				else if(index == 6) {
					MUX6_EN();
					Delay_us(100);
					MUX_Channel_SEL(6);
				}
				else if(index == 7) {
					MUX6_EN();
					Delay_us(100);
					MUX_Channel_SEL(7);
				}	
				else if(index == 8) {
					MUX6_EN();
					Delay_us(100);
					MUX_Channel_SEL(8);
				}
				else if(index == 9) {
					MUX6_EN();
					Delay_us(100);
					MUX_Channel_SEL(9);
				}
				else {
					MUX_DIS();
				}
				break;
			case 9:
				if(index == 0) {
					MUX6_EN();
					Delay_us(100);
					MUX_Channel_SEL(10);
				}
				else if(index == 1) {
					MUX6_EN();
					Delay_us(100);
					MUX_Channel_SEL(11);
				}
				else if(index == 2) {
					MUX6_EN();
					Delay_us(100);
					MUX_Channel_SEL(12);
				}
				else if(index == 3) {
					MUX6_EN();
					Delay_us(100);
					MUX_Channel_SEL(13);
				}
				else if(index == 4) {
					MUX6_EN();
					Delay_us(100);
					MUX_Channel_SEL(14);
				}
				else if(index == 5) {
					MUX6_EN();
					Delay_us(100);
					MUX_Channel_SEL(15);
				}
				else if(index == 6) {
					MUX7_EN();
					Delay_us(100);
					MUX_Channel_SEL(0);
				}
				else if(index == 7) {
					MUX7_EN();
					Delay_us(100);
					MUX_Channel_SEL(1);
				}
				else if(index == 8) {
					MUX7_EN();
					Delay_us(100);
					MUX_Channel_SEL(2);
				}
				else if(index == 9) {
					MUX7_EN();
					Delay_us(100);
					MUX_Channel_SEL(3);
				}
				else {
					MUX_DIS();
				}
				break;
			default:
					MUX_DIS();
				break;
		}
}




int Array_ROM_Read(uint8_t (*pID)[8])
//int Array_ROM_Read(uint8_t **pID) 
{
		uint8_t i;
	  int jj=0;
	int good_ic=0;
		
	
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		for(i=0; i<100; i++) 
	{
			if(i<16)
				MUX1_EN();
			else if(i>=16&&i<32)
				MUX2_EN();
			else if(i>=32&&i<48)
				MUX3_EN();
			else if(i>=48&&i<64)
				MUX4_EN();
			else if(i>=64&&i<80)
				MUX5_EN();
			else if(i>=80&&i<96)
				MUX6_EN();
			else if(i>=96&&i<100)
				MUX7_EN();
			
			Delay_us(100);
			
			MUX_Channel_SEL(i%16);
			
			Delay_us(100);
		
		
			printf("\r\nNo.%d MY18B20 ROM ID: ", i+1);
     DQ_Recall_PAGE1(MUX_18B20_OUT);
//			Delay_us(10);
			DQ_Read_Rom_Code(pID[i], MUX_18B20_OUT);	
			
	
			
	if (( pID[i][0] != 0x28||pID[i][3] !=0x43|| pID[i][4] !=0x98))
		
		{
		printf("  Wrong ROM ID Found!! ---- %d", i+1); 
		jj=jj+1;
		}
		
	else
		
	good_ic=good_ic+1;
	
	}
	
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
    Delay_us(100);
	
	
  printf(" \r\n  Total %d wrong ICs!\n",jj);
	return good_ic;
}


void Array_PARA_Get(uint8_t (*pID)[8]) 
{
		uint8_t i;
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(1000);
	
		for(i=0; i<100; i++) 
	  {
			if(i<16)
				MUX1_EN();
			else if(i>=16&&i<32)
				MUX2_EN();
			else if(i>=32&&i<48)
				MUX3_EN();
			else if(i>=48&&i<64)
				MUX4_EN();
			else if(i>=64&&i<80)
				MUX5_EN();
			else if(i>=80&&i<96)
				MUX6_EN();
			else if(i>=96&&i<100)
				MUX7_EN();
			
			Delay_us(1000);
			MUX_Channel_SEL(i%16);
			Delay_us(1000);
      DQ_Recall_PAGE1(MUX_18B20_OUT);
			DQ_Read_Parameters(pID[i], MUX_18B20_OUT);			
	  }
	
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
    Delay_us(1000);  
}



void Array_ROM_Get(uint8_t (*pID)[8]) 
{
		uint8_t i;
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(1000);
	
		for(i=0; i<100; i++) 
	  {
			if(i<16)
				MUX1_EN();
			else if(i>=16&&i<32)
				MUX2_EN();
			else if(i>=32&&i<48)
				MUX3_EN();
			else if(i>=48&&i<64)
				MUX4_EN();
			else if(i>=64&&i<80)
				MUX5_EN();
			else if(i>=80&&i<96)
				MUX6_EN();
			else if(i>=96&&i<100)
				MUX7_EN();
			
			Delay_us(1000);
			MUX_Channel_SEL(i%16);
			Delay_us(1000);
      DQ_Recall_PAGE1(MUX_18B20_OUT);
			DQ_Read_Rom_Code(pID[i], MUX_18B20_OUT);		
	  }
	
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
    Delay_us(1000);  
}

void Array_ROM_Get_Row(uint8_t (*pID)[8], uint8_t row) 
{
		uint8_t i;
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		for(i=0; i<10; i++) 
	  {
			line_en(row, i);
			Delay_us(100);
      DQ_Recall_PAGE1(MUX_18B20_OUT);
			DQ_Read_Rom_Code(pID[i], MUX_18B20_OUT);		
	  }
	
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
    Delay_us(100);  
}

void Array_ROM_Get_Col(uint8_t (*pID)[8], uint8_t col) 
{
		uint8_t i;
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		for(i=0; i<10; i++) 
	  {
			line_en(i, col);
			Delay_us(100);
      DQ_Recall_PAGE1(MUX_18B20_OUT);
			DQ_Read_Rom_Code(pID[i], MUX_18B20_OUT);		
	  }
	
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
    Delay_us(100);  
}

void Array_ROM_Get_Chip(uint8_t (*pID)[8], uint8_t row, uint8_t col) 
{
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
		Delay_us(100);
	
		line_en(row, col);
		Delay_us(100);
    DQ_Recall_PAGE1(MUX_18B20_OUT);
		DQ_Read_Rom_Code(pID[0], MUX_18B20_OUT);		
	  
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
    Delay_us(100);  
}

void Array_Coeff_Set(uint8_t (*pID)[3]) 
{
		uint8_t i;
		uint8_t serial[8];
	
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		for(i=0; i<100; i++) 
	  {
			if(i<16)
				MUX1_EN();
			else if(i>=16&&i<32)
				MUX2_EN();
			else if(i>=32&&i<48)
				MUX3_EN();
			else if(i>=48&&i<64)
				MUX4_EN();
			else if(i>=64&&i<80)
				MUX5_EN();
			else if(i>=80&&i<96)
				MUX6_EN();
			else if(i>=96&&i<100)
				MUX7_EN();
			
			Delay_us(100);
			MUX_Channel_SEL(i%16);
			Delay_us(100);
      
			DQ_Read_Parameters(serial, MUX_18B20_OUT);
			
			DQ_Rst(MUX_18B20_OUT);
			DQ_Presence(MUX_18B20_OUT);
			DQ_Write_Byte(SKIP_ROM, MUX_18B20_OUT);
			DQ_Write_Byte(WRITE_PARAMETERS, MUX_18B20_OUT); 
			DQ_Write_Byte(serial[0], MUX_18B20_OUT);
			DQ_Write_Byte(serial[1], MUX_18B20_OUT);
			DQ_Write_Byte(serial[2], MUX_18B20_OUT);
			DQ_Write_Byte(pID[i][0], MUX_18B20_OUT); 
			DQ_Write_Byte(pID[i][1], MUX_18B20_OUT); 
			DQ_Write_Byte(pID[i][2], MUX_18B20_OUT);
			DQ_Write_Byte(serial[6], MUX_18B20_OUT);
			DQ_Write_Byte(serial[7], MUX_18B20_OUT);
			
			Delay_us(100);
			DQ_Copy_PAGE1(MUX_18B20_OUT);
	  }
	
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
    Delay_us(100);  
}

void Array_Coeff_Set_Row(uint8_t (*pID)[3], uint8_t row) 
{
		uint8_t i;
		uint8_t serial[8];
	
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		for(i=0; i<10; i++) 
	  {
			line_en(row, i);
			Delay_us(100);
      
			DQ_Read_Parameters(serial, MUX_18B20_OUT);
			
			DQ_Rst(MUX_18B20_OUT);
			DQ_Presence(MUX_18B20_OUT);
			DQ_Write_Byte(SKIP_ROM, MUX_18B20_OUT);
			DQ_Write_Byte(WRITE_PARAMETERS, MUX_18B20_OUT);   
			DQ_Write_Byte(pID[i][0], MUX_18B20_OUT); 
			DQ_Write_Byte(pID[i][1], MUX_18B20_OUT); 
			DQ_Write_Byte(pID[i][2], MUX_18B20_OUT);
			DQ_Write_Byte(0x00, MUX_18B20_OUT); 
			//DQ_Write_Byte(0x00, MUX_18B20_OUT);
			DQ_Copy_PAGE1(MUX_18B20_OUT);		
	  }
	
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
    Delay_us(100);  
}

void Array_Coeff_Set_Col(uint8_t (*pID)[3], uint8_t col) 
{
		uint8_t i;
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		for(i=0; i<10; i++) 
	  {
			line_en(i, col);
			Delay_us(100);
      DQ_Rst(MUX_18B20_OUT);
			DQ_Presence(MUX_18B20_OUT);
			DQ_Write_Byte(SKIP_ROM, MUX_18B20_OUT);
			DQ_Write_Byte(WRITE_PARAMETERS, MUX_18B20_OUT);   
			DQ_Write_Byte(pID[i][0], MUX_18B20_OUT); 
			DQ_Write_Byte(pID[i][1], MUX_18B20_OUT); 
			DQ_Write_Byte(pID[i][2], MUX_18B20_OUT);
			DQ_Write_Byte(0x00, MUX_18B20_OUT); 
			//DQ_Write_Byte(0x00, MUX_18B20_OUT);
			DQ_Copy_PAGE1(MUX_18B20_OUT);		
	  }
	
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
    Delay_us(100);  
}

void Array_Coeff_Set_Chip(uint8_t (*pID)[3], uint8_t row, uint8_t col) 
{
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		line_en(row, col);
		Delay_us(100);
    DQ_Rst(MUX_18B20_OUT);
		DQ_Presence(MUX_18B20_OUT);
		DQ_Write_Byte(SKIP_ROM, MUX_18B20_OUT);
		DQ_Write_Byte(WRITE_PARAMETERS, MUX_18B20_OUT);   
		DQ_Write_Byte(pID[0][0], MUX_18B20_OUT); 
		DQ_Write_Byte(pID[0][1], MUX_18B20_OUT); 
		DQ_Write_Byte(pID[0][2], MUX_18B20_OUT);
		DQ_Write_Byte(0x00, MUX_18B20_OUT); 
		//DQ_Write_Byte(0x00, MUX_18B20_OUT);
		DQ_Copy_PAGE1(MUX_18B20_OUT);		
	  
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
    Delay_us(100);  
}

void Array_Temp_Read_MUX(uint8_t *Temp, float *Temp_trans, float *array) 
{
		uint8_t i, j;
		float sum; 
		
		Delay_us(100);
	  M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		for(i=0; i<100; i++) 
		{
			if(i<16)
				MUX1_EN();
			else if(i>=16&&i<32)
				MUX2_EN();
			else if(i>=32&&i<48)
				MUX3_EN();
			else if(i>=48&&i<64)
				MUX4_EN();
			else if(i>=64&&i<80)
				MUX5_EN();
			else if(i>=80&&i<96)
				MUX6_EN();
			else if(i>=96&&i<100)
				MUX7_EN();
			
			Delay_us(100);
			
			MUX_Channel_SEL(i%16);
			Delay_us(100);
			sum = 0;
			
			for(j=0; j<3; j++) 
				{                //measure three times
				MUX_18B20_OUT_Read_Temperaure_Skip_7(Temp,array, j);
			  sum = sum + array[j];	
				
				}
	  	Temp_trans[i]= sum/3;	 	
			
			}			
}


void Array_Temp_Read_MUX_Ori(uint8_t *Temp, uint16_t *Temp_trans, uint16_t *array) 
{
		uint8_t i;
		//float sum; 
		
		Delay_us(100);
	  M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		for(i=0; i<100; i++) 
		{
			if(i<16)
				MUX1_EN();
			else if(i>=16&&i<32)
				MUX2_EN();
			else if(i>=32&&i<48)
				MUX3_EN();
			else if(i>=48&&i<64)
				MUX4_EN();
			else if(i>=64&&i<80)
				MUX5_EN();
			else if(i>=80&&i<96)
				MUX6_EN();
			else if(i>=96&&i<100)
				MUX7_EN();
			
			Delay_us(100);
			
			MUX_Channel_SEL(i%16);
			Delay_us(100);
			
			MUX_18B20_OUT_Read_Temperaure_Ori(Temp,array, 0);	
			Temp_trans[i] = array[0];
		}			
}

void Array_Temp_Read_MUX_Ori_Row(uint8_t *Temp, uint16_t *Temp_trans, uint16_t *array, uint8_t row) 
{
		uint8_t i;
		//float sum; 
		
		Delay_us(100);
	  M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		for(i=0; i<10; i++) 
		{
			line_en(row, i);
			Delay_us(100);
			
			MUX_18B20_OUT_Read_Temperaure_Ori(Temp,array, 0);	
			Temp_trans[i] = array[0];
		}			
}

void Array_Temp_Read_MUX_Ori_Col(uint8_t *Temp, uint16_t *Temp_trans, uint16_t *array, uint8_t col) 
{
		uint8_t i;
		//float sum; 
		
		Delay_us(100);
	  M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		for(i=0; i<10; i++) 
		{
			line_en(i, col);
			Delay_us(100);
			
			MUX_18B20_OUT_Read_Temperaure_Ori(Temp,array, 0);	
			Temp_trans[i] = array[0];
		}			
}

void Array_Temp_Read_MUX_Ori_Chip(uint8_t *Temp, uint16_t *Temp_trans, uint16_t *array, uint8_t row, uint8_t col) 
{
		
		Delay_us(100);
	  M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
		line_en(row, col);
		Delay_us(100);
		MUX_18B20_OUT_Read_Temperaure_Ori(Temp,array, 0);	
		Temp_trans[0] = array[0];
					
}


void Array_Convert_Temp_MUX(void) 
{
		uint8_t i;
		
		Delay_us(100);
	  M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		for(i=0; i<100; i++) 
		{
			if(i<16)
				MUX1_EN();
			else if(i>=16&&i<32)
				MUX2_EN();
			else if(i>=32&&i<48)
				MUX3_EN();
			else if(i>=48&&i<64)
				MUX4_EN();
			else if(i>=64&&i<80)
				MUX5_EN();
			else if(i>=80&&i<96)
				MUX6_EN();
			else if(i>=96&&i<100)
				MUX7_EN();
			
			Delay_us(100);
			
			MUX_Channel_SEL(i%16);
			Delay_us(100);
			MUX_18B20_OUT_Convert_Temperaure();	
		}			
}

void Array_Convert_Temp_MUX_Row(uint8_t row) 
{
		uint8_t i;
		
		Delay_us(100);
	  M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		for(i=0; i<10; i++) 
		{
			line_en(row, i);
			Delay_us(100);
			MUX_18B20_OUT_Convert_Temperaure();	
		}			
}

void Array_Convert_Temp_MUX_Col(uint8_t col) 
{
		uint8_t i;
		
		Delay_us(100);
	  M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		for(i=0; i<10; i++) 
		{
			line_en(i, col);
			Delay_us(100);
			MUX_18B20_OUT_Convert_Temperaure();	
		}			
}

void Array_Convert_Temp_MUX_Chip(uint8_t row, uint8_t col) 
{
		Delay_us(100);
	  M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
		line_en(row, col);
		Delay_us(100);
		MUX_18B20_OUT_Convert_Temperaure();	
			
}




void Array_Scratchpad_Read(uint8_t (*pID)[9])
//void Array_Scratchpad_Read(uint8_t **pID) 
{
		uint8_t i;
	
	  //int jj=0; 
    //int wrong_ic[100];
	
	
		Delay_us(1000);
	  M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(1000);
	
		for(i=0; i<100; i++) 
		{
			if(i<16)
				MUX1_EN();
			else if(i>=16&&i<32)
				MUX2_EN();
			else if(i>=32&&i<48)
				MUX3_EN();
			else if(i>=48&&i<64)
				MUX4_EN();
			else if(i>=64&&i<80)
				MUX5_EN();
			else if(i>=80&&i<96)
				MUX6_EN();
			else if(i>=96&&i<100)
				MUX7_EN();
		Delay_us(1000);
			
			MUX_Channel_SEL(i%16);
			
			DQ_Recall_EE(MUX_18B20_OUT);
			DQ_Recall_PAGE0_RES(MUX_18B20_OUT);
			DQ_Read_Scrpad(pID[i], MUX_18B20_OUT);				 
			
		}
    M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
         		
}




void Array_Set_Parameters(void)  // Set default values 
{
		uint8_t i;
	  uint8_t serial[8], temp=0;
	  
		Delay_us(100);
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(1000);
	
		for(i=0; i<100; i++) 
	  {
			if(i<16)
				MUX1_EN();
			else if(i>=16&&i<32)
				MUX2_EN();
			else if(i>=32&&i<48)
				MUX3_EN();
			else if(i>=48&&i<64)
				MUX4_EN();
			else if(i>=64&&i<80)
				MUX5_EN();
			else if(i>=80&&i<96)
				MUX6_EN();
			else if(i>=96&&i<100)
				MUX7_EN();
			
			Delay_us(1000);
			
			MUX_Channel_SEL(i%16);
			
			Delay_us(1000);
		
		  DQ_Rst(MUX_18B20_OUT);
			DQ_Presence(MUX_18B20_OUT);
			DQ_Write_Byte(SKIP_ROM, MUX_18B20_OUT);  
			DQ_Write_Byte(WRITE_SCRATCHPAD, MUX_18B20_OUT); 
			DQ_Write_Byte(0x64, MUX_18B20_OUT);  // Alarm Threshold Hi to 100
			DQ_Write_Byte(0x05, MUX_18B20_OUT);  // Alarm Threshold Low to 5
			DQ_Write_Byte(0x7f, MUX_18B20_OUT);  // 12-bit ADC
			
			Delay_us(1000);
			
			DQ_Rst(MUX_18B20_OUT);
			DQ_Presence(MUX_18B20_OUT);
			DQ_Write_Byte(SKIP_ROM, MUX_18B20_OUT);  
			DQ_Write_Byte(WRITE_USER, MUX_18B20_OUT);   
			DQ_Write_Byte(0x00, MUX_18B20_OUT);    // Set user space to 00/00/FF as default value
			DQ_Write_Byte(0x00, MUX_18B20_OUT);
			DQ_Write_Byte(0xff, MUX_18B20_OUT);
			
			DQ_Copy_PAGE0(MUX_18B20_OUT);
			
//			DQ_Rst(MUX_18B20_OUT);
//			DQ_Presence(MUX_18B20_OUT);
//			DQ_Write_Byte(SKIP_ROM, MUX_18B20_OUT);
//			DQ_Write_Byte(WRITE_PARAMETERS, MUX_18B20_OUT);   
//			DQ_Write_Byte(0x00, MUX_18B20_OUT); 
//			DQ_Write_Byte(0x00, MUX_18B20_OUT); 
//			DQ_Write_Byte(0x00, MUX_18B20_OUT);
//			DQ_Write_Byte(0x01, MUX_18B20_OUT); 
//			DQ_Write_Byte(0x00, MUX_18B20_OUT);
			
			DQ_Read_Parameters(serial, MUX_18B20_OUT);
			temp = serial[6] & 0x7f;
			
			DQ_Write_Parameters(0x02,0x00,0x81,0x00,0x00,0x00,temp,0x1c,MUX_18B20_OUT);
			
			DQ_Copy_PAGE1(MUX_18B20_OUT);
   
	  }
	
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
    Delay_us(1000);
	
}

void Array_Set_Parameters_Row(uint8_t row)  // Set default values 
{
		uint8_t i;
	  uint8_t serial[8];
	  
		Delay_us(100);
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		for(i=0; i<10; i++) 
	  {
			line_en(row, i);
			
			Delay_us(100);
		
		  DQ_Rst(MUX_18B20_OUT);
			DQ_Presence(MUX_18B20_OUT);
			DQ_Write_Byte(SKIP_ROM, MUX_18B20_OUT);  
			DQ_Write_Byte(WRITE_SCRATCHPAD, MUX_18B20_OUT); 
			DQ_Write_Byte(0x64, MUX_18B20_OUT);  // Alarm Threshold Hi to 100
			DQ_Write_Byte(0x05, MUX_18B20_OUT);  // Alarm Threshold Low to 5
			DQ_Write_Byte(0x7f, MUX_18B20_OUT);  // 12-bit ADC
			
			DQ_Rst(MUX_18B20_OUT);
			DQ_Presence(MUX_18B20_OUT);
			DQ_Write_Byte(SKIP_ROM, MUX_18B20_OUT);  
			DQ_Write_Byte(WRITE_USER, MUX_18B20_OUT);   
			DQ_Write_Byte(0x00, MUX_18B20_OUT);    // Set user space to 00/00/FF as default value
			DQ_Write_Byte(0x00, MUX_18B20_OUT);
			DQ_Write_Byte(0xff, MUX_18B20_OUT);
			
			DQ_Copy_PAGE0(MUX_18B20_OUT);
			
//			DQ_Rst(MUX_18B20_OUT);
//			DQ_Presence(MUX_18B20_OUT);
//			DQ_Write_Byte(SKIP_ROM, MUX_18B20_OUT);
//			DQ_Write_Byte(WRITE_PARAMETERS, MUX_18B20_OUT);   
//			DQ_Write_Byte(0x00, MUX_18B20_OUT); 
//			DQ_Write_Byte(0x00, MUX_18B20_OUT); 
//			DQ_Write_Byte(0x00, MUX_18B20_OUT);
//			DQ_Write_Byte(0x01, MUX_18B20_OUT); 
//			DQ_Write_Byte(0x00, MUX_18B20_OUT);
			
			DQ_Read_Parameters(serial, MUX_18B20_OUT);
			DQ_Write_Parameters(0x00,0x00,0x00,0x00,0x00,serial[5],serial[6],0x00,MUX_18B20_OUT);
			
			DQ_Copy_PAGE1(MUX_18B20_OUT);
   
	  }
	
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
    Delay_us(100);
	
}


void Array_Set_Parameters_Col(uint8_t col)  // Set default values 
{
		uint8_t i;
	  uint8_t serial[8];
	  
		Delay_us(100);
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		for(i=0; i<10; i++) 
	  {
			line_en(i, col);
			
			Delay_us(100);
		
		  DQ_Rst(MUX_18B20_OUT);
			DQ_Presence(MUX_18B20_OUT);
			DQ_Write_Byte(SKIP_ROM, MUX_18B20_OUT);  
			DQ_Write_Byte(WRITE_SCRATCHPAD, MUX_18B20_OUT); 
			DQ_Write_Byte(0x64, MUX_18B20_OUT);  // Alarm Threshold Hi to 100
			DQ_Write_Byte(0x05, MUX_18B20_OUT);  // Alarm Threshold Low to 5
			DQ_Write_Byte(0x7f, MUX_18B20_OUT);  // 12-bit ADC
			
			DQ_Rst(MUX_18B20_OUT);
			DQ_Presence(MUX_18B20_OUT);
			DQ_Write_Byte(SKIP_ROM, MUX_18B20_OUT);  
			DQ_Write_Byte(WRITE_USER, MUX_18B20_OUT);   
			DQ_Write_Byte(0x00, MUX_18B20_OUT);    // Set user space to 00/00/FF as default value
			DQ_Write_Byte(0x00, MUX_18B20_OUT);
			DQ_Write_Byte(0xff, MUX_18B20_OUT);
			
			DQ_Copy_PAGE0(MUX_18B20_OUT);
			
//			DQ_Rst(MUX_18B20_OUT);
//			DQ_Presence(MUX_18B20_OUT);
//			DQ_Write_Byte(SKIP_ROM, MUX_18B20_OUT);
//			DQ_Write_Byte(WRITE_PARAMETERS, MUX_18B20_OUT);   
//			DQ_Write_Byte(0x00, MUX_18B20_OUT); 
//			DQ_Write_Byte(0x00, MUX_18B20_OUT); 
//			DQ_Write_Byte(0x00, MUX_18B20_OUT);
//			DQ_Write_Byte(0x01, MUX_18B20_OUT); 
//			DQ_Write_Byte(0x00, MUX_18B20_OUT);
			
			DQ_Read_Parameters(serial, MUX_18B20_OUT);
			DQ_Write_Parameters(0x00,0x00,0x00,0x00,0x00,serial[5],serial[6],0x00,MUX_18B20_OUT);
			
			DQ_Copy_PAGE1(MUX_18B20_OUT);
   
	  }
	
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
    Delay_us(100);
	
}

void Array_Set_Parameters_Chip(uint8_t row, uint8_t col)  // Set default values 
{
		//uint8_t i;
	  uint8_t serial[8];
	  
		Delay_us(100);
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		
			line_en(row, col);
			
			Delay_us(100);
		
		  DQ_Rst(MUX_18B20_OUT);
			DQ_Presence(MUX_18B20_OUT);
			DQ_Write_Byte(SKIP_ROM, MUX_18B20_OUT);  
			DQ_Write_Byte(WRITE_SCRATCHPAD, MUX_18B20_OUT); 
			DQ_Write_Byte(0x64, MUX_18B20_OUT);  // Alarm Threshold Hi to 100
			DQ_Write_Byte(0x05, MUX_18B20_OUT);  // Alarm Threshold Low to 5
			DQ_Write_Byte(0x7f, MUX_18B20_OUT);  // 12-bit ADC
			
			DQ_Rst(MUX_18B20_OUT);
			DQ_Presence(MUX_18B20_OUT);
			DQ_Write_Byte(SKIP_ROM, MUX_18B20_OUT);  
			DQ_Write_Byte(WRITE_USER, MUX_18B20_OUT);   
			DQ_Write_Byte(0x00, MUX_18B20_OUT);    // Set user space to 00/00/FF as default value
			DQ_Write_Byte(0x00, MUX_18B20_OUT);
			DQ_Write_Byte(0xff, MUX_18B20_OUT);
			
			DQ_Copy_PAGE0(MUX_18B20_OUT);
			
//			DQ_Rst(MUX_18B20_OUT);
//			DQ_Presence(MUX_18B20_OUT);
//			DQ_Write_Byte(SKIP_ROM, MUX_18B20_OUT);
//			DQ_Write_Byte(WRITE_PARAMETERS, MUX_18B20_OUT);   
//			DQ_Write_Byte(0x00, MUX_18B20_OUT); 
//			DQ_Write_Byte(0x00, MUX_18B20_OUT); 
//			DQ_Write_Byte(0x00, MUX_18B20_OUT);
//			DQ_Write_Byte(0x01, MUX_18B20_OUT); 
//			DQ_Write_Byte(0x00, MUX_18B20_OUT);
			
			DQ_Read_Parameters(serial, MUX_18B20_OUT);
			DQ_Write_Parameters(0x00,0x00,0x00,0x00,0x00,serial[5],serial[6],0x00,MUX_18B20_OUT);
			
			DQ_Copy_PAGE1(MUX_18B20_OUT);
   
	  
	
  	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
    Delay_us(100);
	
}




void Print_Temp(uint8_t (*Temp)[2], float (*Temp_trans)[2],int num, int delta, float temp_ref)
{
		int i, j;
	  int jj=0;
	  int wrong_ic[100];
		
		printf("\r\n");
	
		for(i=0; i<num; i++) 
		{
				printf("Channel %d: ", i+1);
			
				for(j=1; j>=0; j--) {
					printf("%2x", Temp[i][j]);
				}
				printf("\r\nTranslated Temp: %.4f", (Temp_trans[i][0]-delta));
				
				//printf("\r\ncheck: %.4f", abs(Temp_trans[i][0]-delta-temp_ref));
				
				if((Temp_trans[i][0]-delta-temp_ref) >= 1 || (Temp_trans[i][0]-delta-temp_ref) <= -1) {
						printf("   ERROR!!!\r\n");
					   jj=jj+1;
					 wrong_ic[jj]=i+1;  
				}
				printf("\r\n");
		}			
		
		printf (" \n Total  %d failed ICs, they are: ",jj);
			    for(i=1; i<=jj; i++) 
		     printf("   No:%d",wrong_ic[i]);
}





void Print_Check_Temp( float *Temp_trans,int num)
{
		int i;
	
		printf("\r\n");
	
		for(i=0; i<num; i++) 
		{
			printf("Channel %d: ", i+1);
			
			printf("\r Translated Temp: %.4f", Temp_trans[i]);
				
			printf("\r\n");
		}			
			
}




void Print_ROM_ID(uint8_t (*pID)[8], int num)
{
		int i, j;
		
		printf("\r\n");
	
		for(i=0; i<num; i++) 
		{
				printf("Channel %d: ", i);
			
				for(j=0; j<8; j++)
					printf("%2x", pID[i][j]);
			  
				printf("\r\n");
		}			
}

uint8_t CRC8_Cal(uint8_t *serial, uint8_t length) {
	uint8_t result = 0x00;
	uint8_t pDataBuf;
	uint8_t i;
	
	while(length--) {
		pDataBuf = *serial++;
		
		for(i=0;i<8;i++) {
			if((result^(pDataBuf))&0x01) {
				result ^= 0x18;
				result >>= 1;
				result |= 0x80;
			}
			else {
				result >>= 1;
			}
			pDataBuf >>= 1;
		}
			
	}
	return result;
}

void ROM_Code_Cal(uint8_t (*pID)[8], int pair) 
	{
		uint16_t count, i, j, k;
		
		for(count=0; count<pair; count++) {
			for(i=0; i<256; i++) {
				pID[i+(count*256)][7] = CRC8_Cal(pID[i+(count*256)],7);
				
				printf("\nROM code[%d]: ", (i+(count*256)));
				for(j=0; j<8; j++) {
					printf("%2x",pID[i+(count*256)][j]);
				}
				
				for(k=0;k<8;k++) {
					pID[i+(count*256)+1][k] = pID[i+(count*256)][k];
				}
				pID[i+(count*256)+1][4]++;
			}
			pID[256+(count*256)][4] = 0x00;
			pID[256+(count*256)][3] = count + 1;
		}

}

void Write_ROM_Code(uint8_t *serial, uint8_t type) {
		uint8_t i;
		
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SETUP_ROM, type);   
		
		for(i=0; i<8; i++)
			DQ_Write_Byte(serial[i], type); 
}







void ROM_redo(uint8_t (*pID)[8])
{
		
	  
	  uint16_t  i;
	  //static uint8_t count = 0;
	 	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(1000);
	
		for(i=0; i<100; i++) 
		{
					if(i<16)
						MUX1_EN();
					else if(i>=16&&i<32)
						MUX2_EN();
					else if(i>=32&&i<48)
						MUX3_EN();
					else if(i>=48&&i<64)
						MUX4_EN();
					else if(i>=64&&i<80)
						MUX5_EN();
					else if(i>=80&&i<96)
						MUX6_EN();
					else if(i>=96&&i<100)
						MUX7_EN();
			    Delay_us(1000);
					MUX_Channel_SEL(i%16);
				  Delay_us(1000);
					DQ_Recall_PAGE1(MUX_18B20_OUT);
			
					DQ_Read_Rom_Code(pID[i], MUX_18B20_OUT);	

				  if (( pID[i][0] != 0x28 ) || ( pID[i][3] == 0x77 ) || ( pID[i][4] == 0x91 ) || /*( pID[i][5] == 0x01 ) ||*/ ( pID[i][6] == 0x02 ))
				  {
						pID[i][0]=0x28;
					  pID[i][3]=0x77;
						pID[i][4]=0x91;
						//pID[i][5]=0x01;
						pID[i][6]=0x02;
						pID[i][7] = CRC8_Cal(pID[i],7);
			
						DQ_Rst(MUX_18B20_OUT);
					  DQ_Presence(MUX_18B20_OUT);
						DQ_Write_Byte(SETUP_ROM, MUX_18B20_OUT);   
						DQ_Write_Byte(pID[i][0], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][1], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][2], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][3], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][4], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][5], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][6], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][7], MUX_18B20_OUT); 
						
						DQ_Copy_PAGE1(MUX_18B20_OUT);	
				}
	 }
}


void ROM_redo_ROW(uint8_t (*pID)[8], uint8_t row)
{
		
	  uint16_t  i;
	 	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		for(i=0; i<10; i++) 
		{
				line_en(row, i);
				Delay_us(100);
				DQ_Recall_PAGE1(MUX_18B20_OUT);
				DQ_Read_Rom_Code(pID[i], MUX_18B20_OUT);	

				//if (( pID[i][0] == 0x28  ) && ( pID[i][7] == 0xFF ))
				//{
						pID[i][0]=0x28;
					  pID[i][3]=0x77;
						pID[i][4]=0x91;
						pID[i][5]=0x01;
						pID[i][6]=0x02;
						pID[i][7] = CRC8_Cal(pID[i],7);
				
						DQ_Rst(MUX_18B20_OUT);
						DQ_Presence(MUX_18B20_OUT);
						DQ_Write_Byte(SETUP_ROM, MUX_18B20_OUT);   
						DQ_Write_Byte(pID[i][0], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][1], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][2], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][3], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][4], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][5], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][6], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][7], MUX_18B20_OUT); 
						
						DQ_Copy_PAGE1(MUX_18B20_OUT);	
				//}
		
	 }
}


void ROM_redo_COL(uint8_t (*pID)[8], uint8_t col)
{
		
	  uint16_t  i;
	 	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
	
		Delay_us(100);
	
		for(i=0; i<10; i++) 
		{
				line_en(i, col);
				Delay_us(100);
				DQ_Recall_PAGE1(MUX_18B20_OUT);
			
				DQ_Read_Rom_Code(pID[i], MUX_18B20_OUT);	

				//if (( pID[i][0] == 0x28  ) && ( pID[i][7] == 0xFF ))
				//{
						pID[i][0]=0x28;
					  pID[i][3]=0x77;
						pID[i][4]=0x91;
						pID[i][5]=0x01;
						pID[i][6]=0x02;
						pID[i][7] = CRC8_Cal(pID[i],7);
					
						DQ_Rst(MUX_18B20_OUT);
						DQ_Presence(MUX_18B20_OUT);
						DQ_Write_Byte(SETUP_ROM, MUX_18B20_OUT);   
						DQ_Write_Byte(pID[i][0], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][1], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][2], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][3], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][4], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][5], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][6], MUX_18B20_OUT); 
						DQ_Write_Byte(pID[i][7], MUX_18B20_OUT); 
						
						DQ_Copy_PAGE1(MUX_18B20_OUT);	
				//}
		
	 }
}

void ROM_redo_CHIP(uint8_t (*pID)[8], uint8_t row, uint8_t col)
{
	 	M0_DATA_OUT(1);
		M1_DATA_OUT(1);
		M2_DATA_OUT(1);
		Delay_us(100);
		
		line_en(row, col);
		Delay_us(100);
		DQ_Recall_PAGE1(MUX_18B20_OUT);
		DQ_Read_Rom_Code(pID[0], MUX_18B20_OUT);	

		//if (( pID[0][0] == 0x28  ) && ( pID[0][7] == 0xFF ))
		//{
			pID[0][0]=0x28;
			pID[0][3]=0x77;
			pID[0][4]=0x91;
			pID[0][5]=0x01;
			pID[0][6]=0x02;
		  pID[0][7] = CRC8_Cal(pID[0],7);

			DQ_Rst(MUX_18B20_OUT);
			DQ_Presence(MUX_18B20_OUT);
			DQ_Write_Byte(SETUP_ROM, MUX_18B20_OUT);   
			DQ_Write_Byte(pID[0][0], MUX_18B20_OUT); 
			DQ_Write_Byte(pID[0][1], MUX_18B20_OUT); 
			DQ_Write_Byte(pID[0][2], MUX_18B20_OUT); 
			DQ_Write_Byte(pID[0][3], MUX_18B20_OUT); 
			DQ_Write_Byte(pID[0][4], MUX_18B20_OUT); 
			DQ_Write_Byte(pID[0][5], MUX_18B20_OUT); 
			DQ_Write_Byte(pID[0][6], MUX_18B20_OUT); 
			DQ_Write_Byte(pID[0][7], MUX_18B20_OUT); 
						
			DQ_Copy_PAGE1(MUX_18B20_OUT);
					
		//}
}

/*************************************END OF FILE******************************/
