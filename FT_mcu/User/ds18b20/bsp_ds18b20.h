#ifndef __DS18B20_H
#define	__DS18B20_H

#include "stm32f10x.h"
#include "bsp_SysTick.h"

#define HIGH  1
#define LOW   0
////////////////////////////////////////////////////////////
#define SUB_E1_CLK     RCC_APB2Periph_GPIOA
#define SUB_E1_PIN     GPIO_Pin_1                 
#define SUB_E1_PORT		 GPIOA 

#define STRONG_PULLUP_CLK     RCC_APB2Periph_GPIOA
#define STRONG_PULLUP_PIN     GPIO_Pin_2                
#define STRONG_PULLUP_PORT		GPIOA 

#define SUB_E2_CLK     RCC_APB2Periph_GPIOA
#define SUB_E2_PIN     GPIO_Pin_3                 
#define SUB_E2_PORT		 GPIOA 

#define SUB_E3_CLK     RCC_APB2Periph_GPIOA
#define SUB_E3_PIN     GPIO_Pin_4                 
#define SUB_E3_PORT		 GPIOA 

#define SUB_E4_CLK     RCC_APB2Periph_GPIOA
#define SUB_E4_PIN     GPIO_Pin_5                 
#define SUB_E4_PORT		 GPIOA 

#define SUB_E5_CLK     RCC_APB2Periph_GPIOA
#define SUB_E5_PIN     GPIO_Pin_6                 
#define SUB_E5_PORT		 GPIOA

#define SUB_E11_CLK     RCC_APB2Periph_GPIOA
#define SUB_E11_PIN     GPIO_Pin_7                 
#define SUB_E11_PORT		 GPIOA

#define SUB_E6_CLK     RCC_APB2Periph_GPIOA
#define SUB_E6_PIN     GPIO_Pin_8                 
#define SUB_E6_PORT		 GPIOA

#define SUB_E7_CLK     RCC_APB2Periph_GPIOA
#define SUB_E7_PIN     GPIO_Pin_11                 
#define SUB_E7_PORT		 GPIOA

#define SUB_E8_CLK     RCC_APB2Periph_GPIOA
#define SUB_E8_PIN     GPIO_Pin_12                 
#define SUB_E8_PORT		 GPIOA

#define P0_CLK     RCC_APB2Periph_GPIOB
#define P0_PIN     GPIO_Pin_5                 
#define P0_PORT		 GPIOB

#define P1_CLK     RCC_APB2Periph_GPIOB
#define P1_PIN     GPIO_Pin_6                 
#define P1_PORT		 GPIOB

#define P2_CLK     RCC_APB2Periph_GPIOB
#define P2_PIN     GPIO_Pin_7                 
#define P2_PORT		 GPIOB

#define SCL_7051_CLK     RCC_APB2Periph_GPIOB
#define SCL_7051_PIN     GPIO_Pin_10                 
#define SCL_7051_PORT		 GPIOB

#define SDA_7051_CLK     RCC_APB2Periph_GPIOB
#define SDA_7051_PIN     GPIO_Pin_11                 
#define SDA_7051_PORT		 GPIOB

#define MUX_S3_CLK     RCC_APB2Periph_GPIOB
#define MUX_S3_PIN     GPIO_Pin_12                 
#define MUX_S3_PORT		 GPIOB

#define MUX_S2_CLK     RCC_APB2Periph_GPIOB
#define MUX_S2_PIN     GPIO_Pin_13                 
#define MUX_S2_PORT		 GPIOB

#define MUX_S1_CLK        RCC_APB2Periph_GPIOB
#define MUX_S1_PIN        GPIO_Pin_14                 
#define MUX_S1_PORT		    GPIOB

#define MUX_S0_CLK        RCC_APB2Periph_GPIOB
#define MUX_S0_PIN        GPIO_Pin_15                 
#define MUX_S0_PORT		    GPIOB

#define DQ_REF_IN_CLK      RCC_APB2Periph_GPIOC
#define DQ_REF_IN_PIN      GPIO_Pin_0                 
#define DQ_REF_IN_PORT		 GPIOC

#define MUX_18B20_OUT_CLK     RCC_APB2Periph_GPIOC
#define MUX_18B20_OUT_PIN     GPIO_Pin_1                 
#define MUX_18B20_OUT_PORT		 GPIOC

#define SUB_E9_CLK        RCC_APB2Periph_GPIOC
#define SUB_E9_PIN        GPIO_Pin_2                 
#define SUB_E9_PORT		    GPIOC

#define SUB_E10_CLK      RCC_APB2Periph_GPIOC
#define SUB_E10_PIN      GPIO_Pin_3                 
#define SUB_E10_PORT		 GPIOC

#define SUB_E12_CLK      RCC_APB2Periph_GPIOC
#define SUB_E12_PIN      GPIO_Pin_4                 
#define SUB_E12_PORT		 GPIOC

#define SUB_E13_CLK      RCC_APB2Periph_GPIOC
#define SUB_E13_PIN      GPIO_Pin_5                 
#define SUB_E13_PORT		  GPIOC

#define SUB_E14_CLK     RCC_APB2Periph_GPIOC
#define SUB_E14_PIN     GPIO_Pin_7                 
#define SUB_E14_PORT		 GPIOC

#define SUB_E15_CLK     RCC_APB2Periph_GPIOC
#define SUB_E15_PIN     GPIO_Pin_8                 
#define SUB_E15_PORT		 GPIOC

#define SUB_E16_CLK     RCC_APB2Periph_GPIOC
#define SUB_E16_PIN     GPIO_Pin_9                 
#define SUB_E16_PORT		 GPIOC

#define M0_CLK          RCC_APB2Periph_GPIOC
#define M0_PIN          GPIO_Pin_10                 
#define M0_PORT		      GPIOC

#define M1_CLK          RCC_APB2Periph_GPIOC
#define M1_PIN          GPIO_Pin_11                 
#define M1_PORT		      GPIOC
 
#define M2_CLK          RCC_APB2Periph_GPIOC
#define M2_PIN          GPIO_Pin_12                 
#define M2_PORT		      GPIOC

///////////////////////////////////////////////////////////

//output 1 or 0
#define SUB_E1_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_1);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_1)

#define STRONG_PULLUP_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_2);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_2)

#define SUB_E2_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_3);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_3)

#define SUB_E3_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_4);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_4)
					
#define SUB_E4_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_5)

#define SUB_E5_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_6);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_6)

#define SUB_E11_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_7);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_7)
					
#define SUB_E6_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_8);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_8)
					
#define SUB_E7_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_11);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_11)

#define SUB_E8_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_12);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_12)


	#define P0_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_5)
#define P1_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_6);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define P2_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_7);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define SCL_7051_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_10);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_10)
#define SDA_7051_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_11);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_11)
#define MUX_S3_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_12);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_12)

#define MUX_S2_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_13)

#define MUX_S1_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_14);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_14)

#define MUX_S0_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_15);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_15)

#define DQ_REF_IN_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_0);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_0)

#define MUX_18B20_OUT_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_1);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_1)
					
#define SUB_E9_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_2);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_2)

#define SUB_E10_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_3);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_3)
					
#define SUB_E12_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_4);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_4)

#define SUB_E13_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_5)

#define SUB_E14_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_7);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_7)
#define SUB_E15_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_8);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_8)
#define SUB_E16_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_9);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_9)
#define M0_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_10);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_10)
#define M1_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_11);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_11)
#define M2_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_12);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_12)
////////////////////////////////////////////////////////////////////

#define  SUB_E1_DATA_IN()	   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)

#define  STRONG_PULLUP_DATA_IN()	   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)
#define  SUB_E2_DATA_IN()	   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)

#define  SUB_E3_DATA_IN()	     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)
#define  SUB_E4_DATA_IN()	     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
#define  SUB_E5_DATA_IN()	     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
#define  SUB_E11_DATA_IN()	     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)
#define  SUB_E6_DATA_IN()	     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define  SUB_E7_DATA_IN()	     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)
#define  SUB_E8_DATA_IN()	     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)

#define  P0_DATA_IN()	     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define  P1_DATA_IN()	     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define  P2_DATA_IN()	     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)					
#define  SCL_7051_DATA_IN()	     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)
#define  SDA_7051_DATA_IN()	     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)
#define  S3_DATA_IN()	     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)
#define  S2_DATA_IN()	     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)
#define  S1_DATA_IN()	     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)
#define  S0_DATA_IN()	     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)
//#define  A05_DQ_OUT_DATA_IN()	   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)					


#define  DQ_REF_IN_DATA_IN()	     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)
#define  MUX_18B20_OUT_DATA_IN()	     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)
#define  SUB_E9_DATA_IN()	     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)					
#define  SUB_E10_DATA_IN()	     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)					
#define  SUB_E12_DATA_IN()	     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)					
#define  SUB_E13_DATA_IN()	     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)					
#define  SUB_E14_DATA_IN()	     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)					
#define  SUB_E15_DATA_IN()	     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)					
#define  SUB_E16_DATA_IN()	     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)					
#define  M0_DATA_IN()	     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10)					
#define  M1_DATA_IN()	     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)					
#define  M2_DATA_IN()	     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)					

#define MAXNUM_IN1 8
//#define MAXNUM_IN2 8
#define MAXNUM_SWITCH_18B20_OUT 80
#define MAXNUM_MUX_18B20_OUT 100
#define BOARD_NUM 12

//#define MAXNUM_IN4 8

#define IN1_TEST 0
//#define IN2_TEST 0
#define IN3_TEST 1
//#define IN4_TEST 0					

					
typedef enum   
{  
    SETUP_ROM           =   0xa6,
	  SEARCH_ROM          =   0xf0,     
    READ_ROM            =   0x33,   
    MATCH_ROM           =   0x55,   
    SKIP_ROM            =   0xcc,   
    ALARM_SEARCH        =   0xec,    
    CONVERT_T           =   0x44,   
    WRITE_SCRATCHPAD    =   0x4e,   
    READ_SCRATCHPAD     =   0xbe,   
    WRITE_SCRATCHPAD_EXT =   0x88,   
    READ_SCRATCHPAD_EXT  =   0xee,
	  WRITE_USER_EXT      =   0x77,   
    READ_USER_EXT       =   0xdd,
	  WRITE_PARAMETERS    =   0xab,   
    READ_PARAMETERS     =   0x8b,
		WRITE_USER          =   0x66,
		COPY_PAGE0          =   0x48,     
    COPY_PAGE1          =   0x4d,
		RECALL_E2           =   0xb8,
    RECALL_PAGE0_RES    =   0xbb,
    RECALL_PAGE1        =   0xba,	
    READ_POWER_SUPPLY   =   0xb4,    
} QIANTANG_CMD;		

typedef enum   
{  
    DUT_DQ_OUT           =   0x01,
	  MUX_18B20_OUT        =   0x02,     
    //A05_DQ_OUT           =   0x03,   
    TOTAL_DQ_OUT         =   0x04,       
} DQ_TYPE;
					

void GPIO_Config(void);

//void bsp_DelayUS(uint32_t _ulDelayTime);

//uint8_t DS18B20_IN1_Init(void);
//uint8_t DS18B20_IN2_Init(void);
uint8_t DS18B20_IN3_Init(void);
uint8_t DUT_DQ_OUT_Init(void);
//float DS18B20_IN1_Get_Temp(void);
//float DS18B20_IN2_Get_Temp(void);
float DS18B20_IN3_Get_Temp(void);
float DUT_DQ_OUT_Get_Temp(void);

uint8_t DQ_Read2Bit(uint8_t type);
void DQ_Write_Bit(uint8_t bit, uint8_t type);
void DQ_Read_Rom_Code(uint8_t *serial, uint8_t type);


void DQ_Read_Scrpad(uint8_t *serial, uint8_t type);
void DQ_Read_Scrpad_Ext(uint8_t *serial, uint8_t type);
void DQ_Read_User_Ext(uint8_t *serial, uint8_t type);
void DQ_Read_Parameters(uint8_t *serial, uint8_t type);

void DQ_Setup_ROM(uint8_t ROM0,uint8_t ROM1,uint8_t ROM2,uint8_t ROM3,uint8_t ROM4,uint8_t ROM5,uint8_t ROM6,uint8_t ROM7, uint8_t type);

uint8_t DQ_SearchROM(uint8_t (*pID)[8],uint8_t Num, uint8_t type);
uint8_t DQ_Alarm_SearchROM(uint8_t (*pID)[8],uint8_t Num, uint8_t type);

void DQ_Recall_EE(uint8_t type);
void DQ_Recall_PAGE0_RES(uint8_t type);
void DQ_Recall_PAGE1(uint8_t type);

void DQ_Copy_PAGE0(uint8_t type);
void DQ_Copy_PAGE1(uint8_t type);



void DQ_Write_Scratchpad(uint8_t TH,uint8_t TL,uint8_t CFG, uint8_t type);
void DQ_Write_User(uint8_t UDF0,uint8_t UDF1,uint8_t UDF2, uint8_t type);
void DQ_Write_Scratchpad_Ext(uint8_t ANA_CONF,uint8_t TTHRES_HI,uint8_t TTHRES_LO, uint8_t ADC_COEFF_EXT0,uint8_t ADC_COEFF_EXT1,uint8_t ADC_COEFF_EXT2, uint8_t type);
void DQ_Write_User_Ext(uint8_t UDF_EXT0,uint8_t UDF_EXT1,uint8_t UDF_EXT2,uint8_t UDF_EXT3,uint8_t UDF_EXT4, uint8_t type);
void DQ_Write_Parameters(uint8_t ADC_COEFF0,uint8_t ADC_COEFF1,uint8_t ADC_COEFF2,uint8_t ADC_CONF0,uint8_t ADC_CONF1,uint8_t ANA_CAL0,uint8_t ANA_CAL1,uint8_t TTRIM, uint8_t type);



void MUX_18B20_OUT_Read_Temperaure_Match(uint8_t *rom, uint8_t temp_lo, uint8_t temp_hi);
float MUX_DQ_OUT_Get_Temp(void);
//void Timer3_Init(u16 arr,u16 psc);

void bsp_DelayUS(uint32_t _ulDelayTime);

void ROM_redo(uint8_t (*pID)[8]);
void ROM_redo_ROW(uint8_t (*pID)[8], uint8_t row);
void ROM_redo_COL(uint8_t (*pID)[8], uint8_t col);
void ROM_redo_CHIP(uint8_t (*pID)[8], uint8_t row, uint8_t col);



void Send_Convert_Temp(void);
int Array_ROM_Read(uint8_t (*pID)[8]);
//int Array_ROM_Read(uint8_t **pID);
void Array_ROM_Get(uint8_t (*pID)[8]);
void Array_ROM_Get_Row(uint8_t (*pID)[8], uint8_t row);
void Array_ROM_Get_Col(uint8_t (*pID)[8], uint8_t col);
void Array_ROM_Get_Chip(uint8_t (*pID)[8], uint8_t row, uint8_t col);

void Array_ROM_Write(uint8_t (*pID)[8]);
void Array_PARA_Read(uint8_t (*pID)[8]);
void Array_Para_Write(uint8_t (*pID)[8]);

void Array_Temp_Read_Switch(uint8_t (*pID)[8], uint8_t (*Temp)[2]);

void MUX_18B20_OUT_Setup_ROM(uint8_t ROM0,uint8_t ROM1,uint8_t ROM2,uint8_t ROM3,uint8_t ROM4,uint8_t ROM5,uint8_t ROM6,uint8_t ROM7);

void Print_ROM_ID(uint8_t (*pID)[8], int num); 

void DQ_Write_Test(uint8_t data, uint8_t type);

void MUX_18B20_OUT_Read_Temperaure_Match_v2(uint8_t *rom, uint8_t *temp);

//void Array_Temp_Read_v2(uint8_t (*pID)[8], uint8_t (*Temp)[2]);

void Print_Temp(uint8_t (*Temp)[2], float (*Temp_trans)[2],int num, int delta, float temp_ref);


void Print_Check_Temp( float *Temp_trans,int num);
	
void MUX_18B20_OUT_Read_Temperaure_Skip(uint8_t *temp, float *temp_trans, uint8_t index);

float SWITCH_18B20_OUT_Get_Temp(void);

void Send_Convert(void);

float DUT_DQ_OUT_Get_Temp_14bit(void);

uint8_t CRC8_Cal(uint8_t *serial, uint8_t length);

void ROM_Code_Cal(uint8_t (*pID)[8], int pair);

void Write_ROM_Code(uint8_t *serial, uint8_t type);

void DQ_Check_Power_Supply(uint8_t type);

void Send_Convert_Temp_MUX(uint8_t type);

void Array_Send_Convert_Temp(void);

//void Temp_Calibre(float *temp_cal, uint32_t *temp_cal_res, float *temperature_7051);
void Temp_Calibre(float *temp_cal, float *temperature_7051);

void Array_AB_Calibre_MUX(float (*Temp_Cal)[2], float *temperature_7051);
//void Array_AB_Calibre_MUX(float **Temp_Cal, float *temperature_7051);

void Array_Temp_Read_MUX(uint8_t *Temp,float *Temp_trans, float *array);

void Array_Temp_Read_MUX_Ori(uint8_t *Temp, uint16_t *Temp_trans, uint16_t *array);
void Array_Temp_Read_MUX_Ori_Row(uint8_t *Temp, uint16_t *Temp_trans, uint16_t *array, uint8_t row);
void Array_Temp_Read_MUX_Ori_Col(uint8_t *Temp, uint16_t *Temp_trans, uint16_t *array, uint8_t col);
void Array_Temp_Read_MUX_Ori_Chip(uint8_t *Temp, uint16_t *Temp_trans, uint16_t *array, uint8_t row, uint8_t col);

void Array_Convert_Temp_MUX(void);
void Array_Convert_Temp_MUX_Row(uint8_t row);
void Array_Convert_Temp_MUX_Col(uint8_t col);
void Array_Convert_Temp_MUX_Chip(uint8_t row, uint8_t col);



//void Array_Set_Page0(void);
void Array_Set_Parameters(void);
void Array_Set_Parameters_Row(uint8_t row);
void Array_Set_Parameters_Col(uint8_t col);
void Array_Set_Parameters_Chip(uint8_t row, uint8_t col);

void Array_Coeff_Set(uint8_t (*pID)[3]);
void Array_Coeff_Set_Row(uint8_t (*pID)[3], uint8_t row);
void Array_Coeff_Set_Col(uint8_t (*pID)[3], uint8_t col);
void Array_Coeff_Set_Chip(uint8_t (*pID)[3], uint8_t row, uint8_t col);

void Array_Reset_Para(void);

void Array_PARA_Get(uint8_t (*pID)[8]);



void Array_Scratchpad_Ext_Read(uint8_t (*pID)[6]);

void Array_Scratchpad_Read(uint8_t (*pID)[9]);
//void Array_Scratchpad_Read(uint8_t **pID);

#endif /* __DS18B20_IN1_H */







