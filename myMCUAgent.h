#define QT_NO_DEBUG_OUTPUT

#ifndef MYMCUAGENT_H
#define MYMCUAGENT_H
#include "UART.h"
#include "myChipMap.h"
#include <QObject>
#include <myMCU.h>
#include <myOven.h>

#include "MathBiCubic.h"
#include "MathLeastSquare.h"
#include<iostream>
#include<fstream>
#include <QThread>
#include <myglobal.h>
#include <QTimer>
#include <QApplication>
#include <QTime>


typedef enum{
    all          =  0, // 单纯发送convertT指令（含6ms dealy）
    board_sel    =  1,
    row_sel      =  2,
    col_sel      =  3,
    individule   =  4
}UartSelype;

typedef enum{
    ow_doconvert      =  0x1100, // 单纯发送convertT指令（含6ms dealy）
    ow_gettemp        =  0x1101, //读取当前温度值（含convertT指令，返回原始16-bit读值 (MSB先行)）
    ow_gettemp_ref    =  0x1102, //读取Si7051温度值（返回原始16-bit读值 (MSB先行)）
    ow_writeparameters=  0x1200, //功能为设置ROM code的crc和初始化相应scratchpad value，无需payload
    ow_getromcode     =  0x1201, //读取ROM code （payload中ROM code为MSB先行）
    ow_setcoeff       =  0x1300,  //设置校准参数，发送计算好的3-byte coeff到MCU，低字节先行(对应芯片scratchpad中adc_coeff由低到高次序)
    ow_getpara        =  0x1400,
    ow_getscrpad      =  0x1401
}UartCmdType;


class myMCUAgent: public QObject
{

    Q_OBJECT
public:
    myMCUAgent();
    myMCU       *mcu_uart;
    myChipMap   map;



    //void run_once( float temp, long int wait_msec);
    void sleep(long int msec);
    //void  execute_cmd_check_stable(float temp_set);
    void set_parameters();
    void check_parameters();
    void set_coeff();
    //void check_temp(float temp_set, long int wait_msec);
    void check_temp(float temp_set);
    void manual_check_temp_indoor();
    void get_ref(float temp_set);

signals:
    void run_all_done();     //customize signal
    void s_errorbox(QString);
    void get_oven_temp2(double&);
    void set_oven_temp(float );
    void set_oven_cmd(int);

public slots:
    void run_all();
    //void run_once( float temp, long int wait_msec);
    void run_once( float temp);

    void execute_uart_cmd(int sel, int cmd, int boardx, int boardy,int row,int col,Byte* payload, int payload_len);

private:
    ~myMCUAgent();
    QTimer *timer;
    float*** fKnow = NULL;
    float*** fRet = NULL;
    void update_map( Byte * buffer, unsigned int len);
    bool parsing_response(Byte * response, int selAll);
    float convert_reftemp(Byte temp[2]);
    float convert_temp(Byte temp[2]);
    void update_temp_plan();
    void calc_coeff(int boardx, int boardy,int row,int col);


    bool pack_cmd(int sel, int cmd, int board, int row,int col,Byte* payload, int payload_len, Byte *&char_cmd, int* send_len);

    void  execute_cmd_check_stable(float temp_set);
    void  execute_temp_check();
    bool parsing_response_getref(Byte * response_a, vector<float> &vec);
    bool parsing_response_checktemp(Byte * response_a, vector<vector<float> >& vv, int count, int &right_count);

    void execute_getref_cmd(int sel, int cmd, int boardx, int boardy,int row,int col,Byte* payload, int payload_len, float temp_set);
    bool parsing_response_for_getref(Byte * response_a, float temp_set);

    bool parsing_response_getref_new(Byte * response_a, vector<float> &vec, vector<float> &ref_vec, int count, float temp_set, int mboard_y, int mboard_x);

    void execute_uart_cmd_new(int sel, int cmd, int boardx, int boardy,int row,int col,Byte* payload, int payload_len, float temp_set);
    bool parsing_response_new(Byte * response_a, int selAll, int count, vector<vector<float>> &vv, vector<float> &v, vector<float> &ref_vec, float temp_set, bool ready);

};

#endif // MYMCUAGENT_H
