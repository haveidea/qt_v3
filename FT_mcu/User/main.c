#include <stdio.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "bsp_usart1.h"
#include "bsp_DS18B20.h"
#include "bsp_iic.h"

#include "stm32f10x_rtc.h"
#include "misc.h"



uint8_t ID_Buff[100][8]= {0};
uint8_t PARA_Buff[100][8]= {0};
uint8_t SCRPAD_Buff[100][9]= {0};

uint16_t TEMP_TRANS_Buff_now[100];

uint8_t TEMP_Buff[2];


uint16_t array[10];

MY18B20_QTCMD STATE;
uint8_t BOARD_INDEX, ROW_INDEX, COL_INDEX;
int PACKAGE_LEN;
extern uint8_t buffer[512];


extern void MUX_Channel_SEL(uint8_t i);
extern void Board_SEL(uint8_t ch);

uint8_t ROM_Buff[100][8] = {0x28,0x00,0x00,0x00,0x00,0xee,0xff,0xff};
uint8_t COEFF_Buff[100][3];


void NVIC_Configuration(void)
{    
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


/**
  * @brief  main function
  * @param  N/A  
  * @retval N/A
  */
int main(void)
{ 
	
  int i=0, j=0, b=1;    //board number
	volatile int jj;
	
	unsigned short test;
	
	
	uint8_t 	pack_len_low 			= 0;
	uint16_t 	pack_len_high 		= 0;
	uint8_t 	command_pre 			= 0;
	uint8_t 	command_base_low 	= 0;
	uint16_t 	command_base_high = 0;
	uint8_t 	board_idx 				= 0;
	uint8_t 	row_idx 					= 0;	

	uint8_t col_idx 			= 0;
	uint8_t eof 					= 0;
	uint8_t crc 					= 0;
	
	uint16_t pack_len 		= 0;
	uint16_t command_base = 0;
	
  STATE = InvalidCMD;
	
	SysTick_Init();/* configure SysTick */ 	
	
	
	USART1_Config();
  
	NVIC_Configuration();//USART1 receive interruption configure	
	
	GPIO_Config();
	Board_SEL(0);
	
	I2C2_Init();
	//I2C1_Init();

	STRONG_PULLUP_DATA_OUT(1);
	
	//For 5V Test case
	P2_DATA_OUT(1);
	Delay_us(10000);
	
	for (test  = 0x000; test <= 0xfff; test++)
	{
		//if((((~test+1) |2048 ) & 0xfff) != ((((test^0xfff)+1) |2048 ) & 0xfff))
		{
			printf("\r\nInfo, test %d, code 1 :0x%04x, code 2:0x%04x\r\n",test,(((~test+1) |2048 ) & 0xfff),((((test^0xfff)+1) |2048 ) & 0xfff));
		}
	}

		
	for(;;)	  
	{	
    //printf("\r*********Please Enter Command(Hex)*********\r\n");
		switch(STATE) {
			case Package_Received:
				pack_len_high 		= buffer[0];
				pack_len_low 			= buffer[1];
				pack_len 					= (pack_len_high << 8) | pack_len_low;
				
				command_pre 			= buffer[2];
				command_base_high = buffer[3];
				command_base_low 	= buffer[4];
				board_idx 				= buffer[5];
				row_idx 					= buffer[6];
				col_idx 					= buffer[7];
				eof 							= buffer[pack_len-2];
				crc 							= buffer[pack_len-1];	
				
				command_base 			= (command_base_high << 8) | command_base_low;
				
				PACKAGE_LEN 			= pack_len;
				BOARD_INDEX 			= board_idx;
				ROW_INDEX 				= row_idx;
				COL_INDEX 				= col_idx;
				
				if(command_pre == Sel_all) {
					if(command_base      == ow_do_convert) 			{STATE = Convert_Temperature_all;}
					else if(command_base == ow_get_temp_ref) 		{STATE = Get_Temperature_Ref_all;}
					else if(command_base == ow_set_parameters)	{STATE = Set_Parameters_all;}
					else 																				{STATE = InvalidCMD;}
				}
				else if(command_pre == Sel_board) {
					if(command_base      == ow_do_convert) 			{STATE = Convert_Temperature_board;}
					else if(command_base == ow_get_temp)  	 		{STATE = Get_Temperature_board;}
					else if(command_base == ow_get_temp_ref) 		{STATE = Get_Temperature_Ref_board;}
					else if(command_base == ow_set_parameters) 	{STATE = Set_Parameters_board;}
					else if(command_base == ow_get_rom) 				{STATE = Get_ROM_board;}
					else if(command_base == ow_set_coeff) 			{STATE = Set_Coeff_board;}
					else if(command_base == ow_get_para) 				{STATE = Get_PARA_board;}
					else if(command_base == ow_get_scrpad) 			{STATE = Get_SCRPAD_board;}
					else 																				{STATE = InvalidCMD;}
				}
			 else if(command_pre == Sel_chip) {
					if(command_base == ow_do_convert) 					{STATE = Convert_Temperature_chip;}
					else if(command_base == ow_get_temp) 				{STATE = Get_Temperature_chip;}
					else if(command_base == ow_set_parameters) 	{STATE = Set_Parameters_chip;}
					else if(command_base == ow_get_rom) 				{STATE = Get_ROM_chip;}
					else if(command_base == ow_set_coeff) 			{STATE = Set_Coeff_chip;}
					else 																				{STATE = InvalidCMD;}
				}
				else {
					STATE = InvalidCMD;
				}
				break;
		 
			case Convert_Temperature_all: //Convert temperature , all
				 for(b=1; b<=BOARD_NUM; b++)
				 {
						Board_SEL(b-1);
					  Array_Convert_Temp_MUX();  
			   }
				 printf("%c", (PACKAGE_LEN+1) >> 8);
			   printf("%c", (PACKAGE_LEN+1) & 0xff);
			   
				 for(i=2; i<8; i++){
						printf("%c", buffer[i]);
				 }
				 printf("%c",0x01);
				 printf("%c", eof);
				 printf("%c", crc);
					
					//printf("\r\n Go back to main manu: 00\r\n");
					//printf("********************************************\r\n\n");
					STATE = InvalidCMD;	 
				break;
		   
			case Get_Temperature_Ref_all: //Get temperature ref, all
				 //printf("%02x", buffer[0]);
				 //printf("%02x", buffer[1]+BOARD_NUM);
			   //printf("%04x", (PACKAGE_LEN+BOARD_NUM*2));
					
				 printf("%c", (PACKAGE_LEN+2*BOARD_NUM) >> 8);
			   printf("%c", (PACKAGE_LEN+2*BOARD_NUM) & 0xff);
				
				 for(i=2; i<8; i++)
						printf("%c", buffer[i]);
			
			   for(b=1; b<=BOARD_NUM; b++)
				 {
						Board_SEL(b-1);
						//ref_7051[b-1] = Return_7051_Data();
					  if(Return_7051_Data() == 0x0000) {
							Delay_us(1200000);
							printf("%c", Return_7051_Data() >> 8);
							printf("%c", Return_7051_Data() & 0xff);
						}
						else {
							printf("%c", Return_7051_Data() >> 8);
							printf("%c", Return_7051_Data() & 0xff);
						}
					 //printf("%04x", Return_7051_Data());
					  //Delay_us(1200000);
						Delay_us(2000);
			   }
				 printf("%c", eof);
				 printf("%c", crc); 
					
					//printf("\r\n Go back to main manu: 00\r\n");
					//printf("********************************************\r\n\n");
					STATE = InvalidCMD;
					 
				break;	
			 
			 case Set_Parameters_all:  //Set parameters, all
					//printf("\r\n Writing Parameter ALL channel\r\n");
							
					for (b=1; b<=BOARD_NUM; b++)
		      { 
						//printf("\r\n ReadRom of Sub Board #: %d\r\n",b);
			 	    Delay_us(1000);
				    Board_SEL(b-1);
				  	ROM_redo(ROM_Buff);
						
						//Array_Set_Page0();
						Array_Set_Parameters();
		      }
					
					printf("%c", (PACKAGE_LEN+1) >> 8);
			    printf("%c", (PACKAGE_LEN+1) & 0xff);
			    for(i=2; i<8; i++)
						 printf("%c", buffer[i]);
				  printf("%c",0x01);
				  printf("%c", eof);
				  printf("%c", crc);
					
					//printf("\r\n Go back to main manu: 00\r\n");
					//printf("********************************************\r\n\n");
					STATE = InvalidCMD;
				 break;
				 
			 case Convert_Temperature_board: //Convert temperature, board
					Board_SEL(BOARD_INDEX);
					Array_Convert_Temp_MUX();  
					
			    printf("%c", (PACKAGE_LEN+1) >> 8);
			    printf("%c", (PACKAGE_LEN+1) & 0xff);
			    for(i=2; i<8; i++)
						printf("%c", buffer[i]);
				  printf("%c",0x01);
				  printf("%c", eof);
				  printf("%c", crc);
					//printf("\r\n Go back to main manu: 00\r\n");
					//printf("********************************************\r\n\n");
					STATE = InvalidCMD;	 
				break;
			 
			 case Get_Temperature_board: //Get temperature, board
					Board_SEL(BOARD_INDEX);
					Array_Temp_Read_MUX_Ori(TEMP_Buff, TEMP_TRANS_Buff_now, array);  
					
			    printf("%c", (PACKAGE_LEN+200) >> 8);
			    printf("%c", (PACKAGE_LEN+200) & 0xff);
			    for(i=2; i<8; i++)
						printf("%c", buffer[i]);
					
			    for(i=0; i<100; i++) {
						printf("%c", TEMP_TRANS_Buff_now[i] >> 8);
			      printf("%c", TEMP_TRANS_Buff_now[i] & 0xff);
						//printf("%04x", TEMP_TRANS_Buff_now[i]);
					}
				  
					printf("%c", eof);
				  printf("%c", crc);
					//printf("\r\n Go back to main manu: 00\r\n");
					//printf("********************************************\r\n\n");
					STATE = InvalidCMD;	 
				break;
					
			 case Get_Temperature_Ref_board: //Get temperature ref, board
					Board_SEL(BOARD_INDEX);
					//ref_7051[b-1] = Return_7051_Data();
			 
					printf("%c", (PACKAGE_LEN+2) >> 8);
			    printf("%c", (PACKAGE_LEN+2) & 0xff);
			    for(i=2; i<8; i++)
						printf("%c", buffer[i]);
			    
			    if(Return_7051_Data() == 0x0000) {
						Delay_us(1200000);
						printf("%c", Return_7051_Data() >> 8);
						printf("%c", Return_7051_Data() & 0xff);
					}
					else {
						printf("%c", Return_7051_Data() >> 8);
						printf("%c", Return_7051_Data() & 0xff);
					}
			    
			    printf("%c", eof);
				  printf("%c", crc);
					//printf("\r\n Go back to main manu: 00\r\n");
					//printf("********************************************\r\n\n");
					STATE = InvalidCMD;	 
				break;
			 
			 case Set_Parameters_board:  //Set parameters, board
					//printf("\r\n Setting board %d .\r\n",b);
					Board_SEL(BOARD_INDEX);
					//ROM_redo(ROM_Buff);
					Array_Set_Parameters();
				  
			    printf("%c", (PACKAGE_LEN+1) >> 8);
			    printf("%c", (PACKAGE_LEN+1) & 0xff);
			    for(i=2; i<8; i++)
						 printf("%c", buffer[i]);
				  printf("%c",0x01);
				  printf("%c", eof);
				  printf("%c", crc);
					//printf("\r\n Parameters set done.\r\n");
					//printf("\r\n Go back to main manu: 00\r\n");
					//printf("********************************************\r\n\n");
					STATE = InvalidCMD;
				break;
			 
			 case Get_ROM_board: //Get ROM, board
					Board_SEL(BOARD_INDEX);
					Array_ROM_Get(ID_Buff);  
					
			    printf("%c", (PACKAGE_LEN+800) >> 8);
			    printf("%c", (PACKAGE_LEN+800) & 0xff);
			    for(i=2; i<8; i++)
						printf("%c", buffer[i]);
			 
					for(i=0; i<100; i++) {
						for(j=0; j<8; j++)
							printf("%c", ID_Buff[i][j]);
					}
			    
					printf("%c", eof);
				  printf("%c", crc);
					//printf("\r\n Go back to main manu: 00\r\n");
					//printf("********************************************\r\n\n");
					STATE = InvalidCMD;	 
				break;
					
			 case Set_Coeff_board: //Set coeff, board
				  Board_SEL(BOARD_INDEX);
					j = 8;
			    for(i=0; i<100; i++) {
						COEFF_Buff[i][0] = buffer[j++];
						COEFF_Buff[i][1] = buffer[j++];
						COEFF_Buff[i][2] = buffer[j++];
					}		
					Array_Coeff_Set(COEFF_Buff);
			    j = 0;
					
					printf("%c", 0x00);
					printf("%c", 0x0b);
			    for(i=2; i<8; i++)
						printf("%c", buffer[i]);
				  printf("%c",0x01);
				  
					//printf("%c", (PACKAGE_LEN) >> 8);
			    //printf("%c", (PACKAGE_LEN) & 0xff);
					//for(i=2; i<8; i++)
						//printf("%c", buffer[i]);
			 
					//for(i=0; i<300; i++) {
						//printf("%c", buffer[i]);
					//}
					//printf("%c",0x01);
					
					printf("%c", eof);
				  printf("%c", crc);
					//printf("\r\n Go back to main manu: 00\r\n");
					//printf("********************************************\r\n\n");
					STATE = InvalidCMD;	 
				break;
				
			 case Get_PARA_board: //Get Parameter, board
					Board_SEL(BOARD_INDEX);
					Array_PARA_Get(PARA_Buff);  
					
			    printf("%c", (PACKAGE_LEN+800) >> 8);
			    printf("%c", (PACKAGE_LEN+800) & 0xff);
			    for(i=2; i<8; i++)
						printf("%c", buffer[i]);
			 
					for(i=0; i<100; i++) {
						for(j=0; j<8; j++)
							printf("%c", PARA_Buff[i][j]);
					}
			    
					printf("%c", eof);
				  printf("%c", crc);
					//printf("\r\n Go back to main manu: 00\r\n");
					//printf("********************************************\r\n\n");
					STATE = InvalidCMD;	 
				break;	
			 
			 case Get_SCRPAD_board: //Get Scratchpad, board
					Board_SEL(BOARD_INDEX);
					Array_Scratchpad_Read(SCRPAD_Buff);  
					
			    printf("%c", (PACKAGE_LEN+900) >> 8);
			    printf("%c", (PACKAGE_LEN+900) & 0xff);
			    for(i=2; i<8; i++)
						printf("%c", buffer[i]);
			 
					for(i=0; i<100; i++) {
						for(j=0; j<9; j++)
							printf("%c", SCRPAD_Buff[i][j]);
					}
			    
					printf("%c", eof);
				  printf("%c", crc);
					//printf("\r\n Go back to main manu: 00\r\n");
					//printf("********************************************\r\n\n");
					STATE = InvalidCMD;	 
				break;		
				 
			 case Convert_Temperature_chip:	//Convert temperature, chip
					Board_SEL(BOARD_INDEX);
					Array_Convert_Temp_MUX_Chip(ROW_INDEX, COL_INDEX);
					
			    printf("%c", (PACKAGE_LEN+1) >> 8);
			    printf("%c", (PACKAGE_LEN+1) & 0xff);
			    for(i=2; i<8; i++)
						printf("%c", buffer[i]);
				  printf("%c",0x01);
				  printf("%c", eof);
				  printf("%c", crc);
					//printf("\r\n Parameters set done.\r\n");
					//printf("\r\n Go back to main manu: 00\r\n");
					//printf("********************************************\r\n\n");
					STATE = InvalidCMD;
				break;
			 
			 case Get_Temperature_chip:	//Get temperature, chip
					Board_SEL(BOARD_INDEX);
					Array_Temp_Read_MUX_Ori_Chip(TEMP_Buff, TEMP_TRANS_Buff_now, array, ROW_INDEX, COL_INDEX);  
					
					printf("%c", (PACKAGE_LEN+2) >> 8);
			    printf("%c", (PACKAGE_LEN+2) & 0xff);
			    for(i=2; i<8; i++)
						printf("%c", buffer[i]);
			    
			    printf("%c", TEMP_TRANS_Buff_now[0] >> 8);
			    printf("%c", TEMP_TRANS_Buff_now[0] & 0xff);
			    //printf("%04x", TEMP_TRANS_Buff_now[0]);
				  
			    printf("%c", eof);
				  printf("%c", crc);
					//printf("\r\n Parameters set done.\r\n");
					//printf("\r\n Go back to main manu: 00\r\n");
					//printf("********************************************\r\n\n");
					STATE = InvalidCMD;
				break;
			 
			 case Set_Parameters_chip:	//Set parameters, chip
					//printf("\r\n Setting board %d .\r\n",b);
					Board_SEL(BOARD_INDEX);
					ROM_redo_CHIP(ROM_Buff, ROW_INDEX, COL_INDEX);
					Array_Set_Parameters_Chip(ROW_INDEX, COL_INDEX);
				
					printf("%c", (PACKAGE_LEN+1) >> 8);
			    printf("%c", (PACKAGE_LEN+1) & 0xff);
			    for(i=2; i<8; i++)
						 printf("%c", buffer[i]);
				  printf("%c",0x01);
				  printf("%c", eof);
				  printf("%c", crc);
			    //printf("\r\n Parameters set done.\r\n");
					//printf("\r\n Go back to main manu: 00\r\n");
					//printf("********************************************\r\n\n");
					STATE = InvalidCMD;
				break;
			 
			 case Get_ROM_chip: //Get ROM, chip
					Board_SEL(BOARD_INDEX);
					Array_ROM_Get_Chip(ID_Buff, ROW_INDEX, COL_INDEX);  
					
					printf("%c", (PACKAGE_LEN+8) >> 8);
			    printf("%c", (PACKAGE_LEN+8) & 0xff);
			    for(i=2; i<8; i++)
						printf("%c", buffer[i]);
			 
			    for(j=0; j<8; j++)
						printf("%c", ID_Buff[0][j]);
					
					printf("%c", eof);
				  printf("%c", crc);
					//printf("\r\n Go back to main manu: 00\r\n");
					//printf("********************************************\r\n\n");
					STATE = InvalidCMD;	 
				break;
					
			 case Set_Coeff_chip: //Set coeff, chip
				  Board_SEL(BOARD_INDEX);
					j = 8;
			    COEFF_Buff[i][0] = buffer[j++];
					COEFF_Buff[i][1] = buffer[j++];
					COEFF_Buff[i][2] = buffer[j++];
							
					Array_Coeff_Set_Chip(COEFF_Buff, ROW_INDEX, COL_INDEX);
			    j = 0;
					
					printf("%c", 0x00);
					printf("%c", 0x0b);
			    for(i=2; i<8; i++){
						printf("%c", buffer[i]);
					}
				  printf("%c",0x01);
				  printf("%c", eof);
				  printf("%c", crc);
					STATE = InvalidCMD;	 
				break;

				default:
						 
				break;
		} //switch

	}//for(;;)
}
