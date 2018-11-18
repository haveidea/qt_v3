/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

#include "bsp_led.h"
#include "bsp_usart1.h"
#include "misc.h"

//uint8_t BOARD_INDEX, ROW_INDEX, COL_INDEX;
//uint8_t BOARD_COMMAND=0, ROW_COMMAND=0, COL_COMMAND=0, CHIP_COMMAND=0;
//int PACKAGE_LEN;
//uint8_t coeff_buff[300];

int ii=0;
uint8_t buffer[512] = {0};

extern void TimingDelay_Decrement(void);
extern MY18B20_QTCMD STATE;

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
   if (CoreDebug->DHCSR & 1) {  //check C_DEBUGEN == 1 -> Debugger Connected  
      __breakpoint(0);  // halt program execution here         
  }	
	while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TimingDelay_Decrement();	
}

void USART1_IRQHandler(void)
{ 
	//uint8_t i=0, j=0;
	//uint8_t i;
	//uint8_t buffer[310] = {0};
	uint8_t Clear = Clear;
//	
//	uint8_t pack_len_low = 0;
//	uint16_t pack_len_high = 0;
//	uint8_t command_pre = 0;
//	uint8_t command_base_low = 0;
//	uint16_t command_base_high = 0;
//	uint8_t board_idx = 0;
//	uint8_t row_idx = 0;
//			volatile int jj;

//	uint8_t col_idx = 0;
//	uint8_t eof = 0;
//	uint8_t crc = 0;
//	
//	uint16_t pack_len = 0;
//	uint16_t command_base = 0;
	
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//  {	
//    /* Read one byte from the receive data register */
//		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//		i = USART1 -> DR;		
// }
//	
//	if(i == 0x55)
//		printf("B");
	
#if 1
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    /* Read one byte from the receive data register */
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		buffer[ii++] = USART1 -> DR;
  }	
	else if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		Clear = USART1 -> SR;
		Clear = USART1 -> DR;
	}
	
	//printf("i'm here");
	//printf("\r\nii: %d",ii);

	if(ii >= 2 && (ii==((buffer[0]<<8)|buffer[1]))) {
			STATE = Package_Received;
//		pack_len_high = buffer[0];
//		pack_len_low = buffer[1];
//		pack_len = (pack_len_high << 8) | pack_len_low;
//		
//		command_pre = buffer[2];
//		command_base_high = buffer[3];
//		command_base_low = buffer[4];
//		board_idx = buffer[5];
//		row_idx = buffer[6];
//		col_idx = buffer[7];
//		eof = buffer[pack_len-2];
//		crc = buffer[pack_len-1];
//		
//		
//		//pack_len = (pack_len_high << 8) | pack_len_low;
//    command_base = (command_base_high << 8) | command_base_low;
//		
//		PACKAGE_LEN = pack_len;
//		BOARD_INDEX = board_idx;
//	  ROW_INDEX = row_idx;
//	  COL_INDEX = col_idx;
//		
//		if(command_pre == Sel_all) {
//			if(command_base == ow_do_convert) {STATE = Convert_Temperature_all;}
//			else if(command_base == ow_get_temp_ref) {STATE = Get_Temperature_Ref_all;}
//			else if(command_base == ow_set_parameters) {STATE = Set_Parameters_all;}
//		}
//		else if(command_pre == Sel_board) {
//			if(command_base == ow_do_convert) {STATE = Convert_Temperature_board;}
//			else if(command_base == ow_get_temp) {STATE = Get_Temperature_board;}
//			else if(command_base == ow_get_temp_ref) {STATE = Get_Temperature_Ref_board;}
//			else if(command_base == ow_set_parameters) {STATE = Set_Parameters_board;}
//			else if(command_base == ow_get_rom) {STATE = Get_ROM_board;}
//			else if(command_base == ow_set_coeff) {STATE = Set_Coeff_board;}
//			else if(command_base == ow_get_para) {STATE = Get_PARA_board;}
//			else if(command_base == ow_get_scrpad) {STATE = Get_SCRPAD_board;}
//		}
//		else if(command_pre == Sel_row) {
//			if(command_base == ow_do_convert) {STATE = Convert_Temperature_row;}
//			else if(command_base == ow_get_temp) {STATE = Get_Temperature_row;}
//			else if(command_base == ow_set_parameters) {STATE = Set_Parameters_row;}
//			else if(command_base == ow_get_rom) {STATE = Get_ROM_row;}
//			else if(command_base == ow_set_coeff) {STATE = Set_Coeff_row;}
//		}
//		else if(command_pre == Sel_col) {
//			if(command_base == ow_do_convert) {STATE = Convert_Temperature_col;}
//			else if(command_base == ow_get_temp) {STATE = Get_Temperature_col;}
//			else if(command_base == ow_set_parameters) {STATE = Set_Parameters_col;}
//			else if(command_base == ow_get_rom) {STATE = Get_ROM_col;}
//			else if(command_base == ow_set_coeff) {STATE = Set_Coeff_col;}
//		}
//		else if(command_pre == Sel_chip) {
//			if(command_base == ow_do_convert) {STATE = Convert_Temperature_chip;}
//			else if(command_base == ow_get_temp) {STATE = Get_Temperature_chip;}
//			else if(command_base == ow_set_parameters) {STATE = Set_Parameters_chip;}
//			else if(command_base == ow_get_rom) {STATE = Get_ROM_chip;}
//			else if(command_base == ow_set_coeff) {STATE = Set_Coeff_chip;}
//		}

		
//		printf("length: %d", ((buffer[0]<<8)|buffer[1]));
//		printf("STATE: %d\r\n", STATE);
//		printf("\r\npack_len_low: %02x\r\n", pack_len_low);
//		printf("\r\npack_len_high: %02x\r\n", pack_len_high);
//		printf("\r\ncommand_pre: %02x\r\n", command_pre);
//		printf("\r\ncommand_base_low: %02x\r\n", command_base_low);
//		printf("\r\ncommand_base_high: %02x\r\n", command_base_high);
//		printf("\r\nboard_idx: %02x\r\n", board_idx);
//		printf("\r\nrow_idx: %02x\r\n", row_idx);
//		printf("\r\ncol_idx: %02x\r\n", col_idx);
//		printf("\r\neof: %02x\r\n", eof);
//		printf("\r\ncrc: %02x\r\n", crc);
    ii = 0;
 }
 #endif
}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
