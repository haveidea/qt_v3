#define QT_NO_DEBUG_OUTPUT

#ifndef AGENT_H
#define AGENT_H
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
#include <myMCUAgent.h>


#include <myglobal.h>

class myAgent: public QObject
{
    Q_OBJECT

public slots:
    void set_oven_cmd(int);
    void set_oven_temp(float);
    float  get_oven_temp();
    void get_oven_temp2(double&);
    void run_all_board(float , float , float , long int , long int , long int , int , int);
    void set_parameters_all_board(int);
    void check_parameters_all_board(int);
    void auto_check_temp_all_board(float , long int , int );
    void manual_check_temp_all_board(int);

//private:
//    QThread agent_thread;

signals:
    void refresh_oven_temp();

public:
    myAgent();
    ~myAgent();
    myOven      *oven_uart;
    myMCUAgent *mcu_uart_agent[4];
//    bool        set_temp(float );
    bool        testuart(Byte *);
    //void set_oven_temp(float);

    //float       get_oven_temp();
    unsigned short CRC16_MODBUS(void *pushMsg ,unsigned int pBufSize);
};

#endif // AGENT_H
