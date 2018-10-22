#include "myglobal.h"
#include "myAgent.h"
#include "myChip.h"

void myAgent::set_oven_cmd(int cmd)
{
    Byte a[8];
    if(cmd == 1){
        qInfo("agent set oven start");
        a[0] = 0x01;
        a[1] = 0x05;
        a[2] = 0x01;
        a[3] = 0x60;
        a[4] = 0xff;
        a[5] = 0x00;
        a[6] = 0x8d;
        a[7] = 0xd8;
    }
    else{
        qInfo("agent set oven stop");
        a[0] = 0x01;
        a[1] = 0x05;
        a[2] = 0x01;
        a[3] = 0x61;
        a[4] = 0xff;
        a[5] = 0x00;
        a[6] = 0xdc;
        a[7] = 0x18;
    }
    if(this->oven_uart->is_opened!=TRUE)
    {
        qInfo("oven uart is not open. set oven start/stop error");
    }
    else{
//        qInfo("a[0]: %02x",a[0]);
//        qInfo("a[1]: %02x",a[1]);
//        qInfo("a[2]: %02x",a[2]);
//        qInfo("a[3]: %02x",a[3]);
//        qInfo("a[4]: %02x",a[4]);
//        qInfo("a[5]: %02x",a[5]);
//        qInfo("a[6]: %02x",a[6]);
//        qInfo("a[7]: %02x",a[7]);
        this->oven_uart->write(a,8);
        qInfo("oven uart oven set oven start/stop send out");
    }
}

void myAgent::set_oven_temp(float f)
{
    Byte a[8];
    qInfo("agent set temp %f", f);
    if(f == 7.0){
        a[0] = 0x01;
        a[1] = 0x06;
        a[2] = 0x00;
        a[3] = 0x64;
        a[4] = 0x02;
        a[5] = 0xbc;
        a[6] = 0xc8;
        a[7] = 0xc4;
    }
    else if(f == 27.0){
        a[0] = 0x01;
        a[1] = 0x06;
        a[2] = 0x00;
        a[3] = 0x64;
        a[4] = 0x0a;
        a[5] = 0x8c;
        a[6] = 0xcf;
        a[7] = 0x10;

    }
    else if(f == 47.0){
        a[0] = 0x01;
        a[1] = 0x06;
        a[2] = 0x00;
        a[3] = 0x64;
        a[4] = 0x12;
        a[5] = 0x5c;
        a[6] = 0xc4;
        a[7] = 0x8c;
    }
    else {
        a[0] = 0x01;
        a[1] = 0x06;
        a[2] = 0x00;
        a[3] = 0x64;
        a[4] = ((short)(f*100))>>8;
        a[5] = ((short)(f*100))&0x00FF;
        a[6] = CRC16_MODBUS(a,6)>>8;
        a[7] = CRC16_MODBUS(a,6)&0xFF;
    }
    if(this->oven_uart->is_opened!=TRUE)
    {
        qInfo("oven uart is not open. set oven temp error");
    }
    else{
//        qInfo("a[0]: %02x",a[0]);
//        qInfo("a[1]: %02x",a[1]);
//        qInfo("a[2]: %02x",a[2]);
//        qInfo("a[3]: %02x",a[3]);
//        qInfo("a[4]: %02x",a[4]);
//        qInfo("a[5]: %02x",a[5]);
//        qInfo("a[6]: %02x",a[6]);
//        qInfo("a[7]: %02x",a[7]);

        this->oven_uart->write(a,8);
        qInfo("oven uart oven set temp send out");
        //qInfo("debug: %f",this->get_oven_temp());
    }

}

myAgent::myAgent()
{
//    this->moveToThread(&agent_thread);
//    agent_thread.start();

    this->mcu_uart_agent[0] = new(myMCUAgent);
    this->mcu_uart_agent[1] = new(myMCUAgent);
    this->mcu_uart_agent[2] = new(myMCUAgent);
    this->mcu_uart_agent[3] = new(myMCUAgent);

    this->oven_uart = new(myOven);
  //  this->oven_uart->load_oven();
}

myAgent::~myAgent()
{
//    agent_thread.terminate();
//    agent_thread.wait();
//    agent_thread.quit();
}

//bool myAgent::set_temp(float temp)
//{
//    bool result;
//    result = this->oven_uart->set_temp(temp);
//    emit refresh_oven_temp(); // for debug. not valid code
//    return result;

//}

float myAgent::get_oven_temp()
{
    //qDebug()<<"TODO";
    //Byte a[8],b[8];
    float result;

    Byte a[10],b[12];

    //a[0] = 0x01;
    //a[1] = 0x04;
    //a[2] = 0x00;
    //a[3] = 0x5e;
    //a[4] = 0x00;
    //a[5] = 0x01;
    //a[6] = CRC16_MODBUS(a,6)>>8;
    //a[7] = CRC16_MODBUS(a,6)&0xFF;


    a[0] = 0x01;
    a[1] = 0x04;
    a[2] = 0x00;
    a[3] = 0x5b;
    a[4] = 0x00;
    a[5] = 0x04;
    a[6] = 0x80;
    a[7] = 0x1a;

//    a[0] = 0x00;
//    a[1] = 0x0a;
//    a[2] = 0x6b;
//    a[3] = 0x11;
//    a[4] = 0x02;
//    a[5] = 0x00;
//    a[6] = 0x00;
//    a[7] = 0x00;
//    a[8] = 0xfe;
//    a[9] = 0xff;

    if(this->oven_uart->is_opened!=TRUE)
    {
        qInfo("oven uart is not open. get oven temp error");

//        this->oven_uart->write(a,8);
//        qInfo("oven uart oven get temp send out");

//        this->oven_uart->read(b,13);
//        qInfo("oven uart oven get temp");
    }
    else{
        //this->oven_uart->write(a,8);
        this->oven_uart->write(a,8);
        qInfo("oven uart oven get temp send out=====");

        this->oven_uart->read(b,13);
        qInfo("oven uart oven get temp");
        qInfo("I am here");

    }
qInfo("I am here1");
    if(this->oven_uart->is_opened!=TRUE)
    {
        qInfo("oven uart is not open. get oven temp error");
    }
    else{
        //this->oven_uart->read(b,8);
        //this->oven_uart->read(b,12);
        qInfo("oven uart oven get temp");
    }
    qInfo("I am here2");
    //result = (b[3]*256+b[4])/100;
    qInfo("b[0]: %02x",b[0]);
    qInfo("b[1]: %02x",b[1]);
    qInfo("b[2]: %02x",b[2]);
    qInfo("b[3]: %02x",b[3]);
    qInfo("b[4]: %02x",b[4]);
    qInfo("b[5]: %02x",b[5]);
    qInfo("b[6]: %02x",b[6]);
    qInfo("b[7]: %02x",b[7]);
    qInfo("b[8]: %02x",b[8]);
    qInfo("b[9]: %02x",b[9]);

    result = (b[8]*256+b[9])*175.72/65536-46.85;

    return result;
}


//void myAgent::get_oven_temp2(double &result)
//{
//    //qDebug()<<"TODO";
//    //Byte a[8],b[8];
//    //float result;

//    Byte a[10],b[12];

//    //a[0] = 0x01;
//    //a[1] = 0x04;
//    //a[2] = 0x00;
//    //a[3] = 0x5e;
//    //a[4] = 0x00;
//    //a[5] = 0x01;
//    //a[6] = CRC16_MODBUS(a,6)>>8;
//    //a[7] = CRC16_MODBUS(a,6)&0xFF;

//    a[0] = 0x00;
//    a[1] = 0x0a;
//    a[2] = 0x6b;
//    a[3] = 0x11;
//    a[4] = 0x02;
//    a[5] = 0x00;
//    a[6] = 0x00;
//    a[7] = 0x00;
//    a[8] = 0xfe;
//    a[9] = 0xff;

//    if(this->oven_uart->is_opened!=TRUE)
//    {
//        qInfo("oven uart is not open. get oven temp error");
//    }
//    else{
//        //this->oven_uart->write(a,8);
//        this->oven_uart->write(a,10);
//        qInfo("oven uart oven get temp send out");


//    }

//    if(this->oven_uart->is_opened!=TRUE)
//    {
//        qInfo("oven uart is not open. get oven temp error");
//    }
//    else{
//        this->oven_uart->read(b,12);
//        qInfo("oven uart oven get temp");
//    }
//    //result = (b[3]*256+b[4])/100;
//    qInfo("b[0]: %02x",b[0]);
//    qInfo("b[1]: %02x",b[1]);
//    qInfo("b[2]: %02x",b[2]);
//    qInfo("b[3]: %02x",b[3]);
//    qInfo("b[4]: %02x",b[4]);
//    qInfo("b[5]: %02x",b[5]);
//    qInfo("b[6]: %02x",b[6]);
//    qInfo("b[7]: %02x",b[7]);
//    qInfo("b[8]: %02x",b[8]);
//    qInfo("b[9]: %02x",b[9]);

//    result = (b[8]*256+b[9])*175.72/65536-46.85;

//    //return result;
//}

void myAgent::get_oven_temp2(double &result)
{

    //Byte a[8],b[8];

    Byte a[8],b[13];

    //a[0] = 0x01;
    //a[1] = 0x04;
    //a[2] = 0x00;
    //a[3] = 0x5e;
    //a[4] = 0x00;
    //a[5] = 0x01;
    //a[6] = CRC16_MODBUS(a,6)>>8;
    //a[7] = CRC16_MODBUS(a,6)&0xFF;

    this->oven_uart->PrintDCB();

    a[0] = 0x01;
    a[1] = 0x04;
    a[2] = 0x00;
    a[3] = 0x5b;
    a[4] = 0x00;
    a[5] = 0x04;
    a[6] = 0x80;
    a[7] = 0x1a;

//    a[0] = 0x00;
//    a[1] = 0x0a;
//    a[2] = 0x6b;
//    a[3] = 0x11;
//    a[4] = 0x02;
//    a[5] = 0x00;
//    a[6] = 0x00;
//    a[7] = 0x00;
//    a[8] = 0xfe;
//    a[9] = 0xff;

    if(this->oven_uart->is_opened!=TRUE)
    {
        qInfo("oven uart is not open. get oven temp error");

//        this->oven_uart->write(a,8);
//        qInfo("oven uart oven get temp send out");

//        this->oven_uart->read(b,13);
//        qInfo("oven uart oven get temp");
    }
    else{
        //this->oven_uart->write(a,8);
        this->oven_uart->write(a,8);
        qInfo("oven uart oven get temp send out===2222==");

        this->oven_uart->read(b,13);
        qInfo("oven uart oven get temp");
        qInfo("I am here");

    }
qInfo("I am here1");
    if(this->oven_uart->is_opened!=TRUE)
    {
        qInfo("oven uart is not open. get oven temp error");
    }
    else{
        //this->oven_uart->read(b,8);
        //this->oven_uart->read(b,12);
        qInfo("oven uart oven get temp");
    }
    qInfo("I am here2");
    //result = (b[3]*256+b[4])/100;
    qInfo("b[0]: %02x",b[0]);
    qInfo("b[1]: %02x",b[1]);
    qInfo("b[2]: %02x",b[2]);
    qInfo("b[3]: %02x",b[3]);
    qInfo("b[4]: %02x",b[4]);
    qInfo("b[5]: %02x",b[5]);
    qInfo("b[6]: %02x",b[6]);
    qInfo("b[7]: %02x",b[7]);
    qInfo("b[8]: %02x",b[8]);
    qInfo("b[9]: %02x",b[9]);

    result = (b[8]*256+b[9])*175.72/65536-46.85;


    //return result;
}


//void myAgent::run_all_board(float cal_hi, float cal_lo, float temp_check)
//{
//    for(int ii=0; ii<NUM_MOTHER_BOARDS; ii++) {
//        qInfo("\r\nMBoard %d setting parameters",ii+1);
//        mcu_uart_agent[ii]->set_parameters();
//    }


//    set_oven_cmd(1); //oven run
//    mcu_uart_agent[0]->sleep(2000);


//    set_oven_temp(cal_lo); //set oven temperature
//    qInfo("oven begin to go to %f", cal_lo);

//    //set_oven_temp(47.0); //set oven temperature
//    //qInfo("oven begin to go to 47.0");

//    QDateTime dateTime1 = QDateTime::currentDateTime();
//    qInfo() << dateTime1.toString("HH:mm:ss.zzz") << "\r\n";

//    qInfo("Wait 45min...");
//    //mcu_uart_agent[0]->sleep(2700000);  //wait 45min
//    mcu_uart_agent[0]->sleep(3000000);  //50min

//    //mcu_uart_agent[0]->sleep(600000);  //wait 10min

//    for(int ii=0; ii<NUM_MOTHER_BOARDS; ii++) {
//        qInfo("\r\nMBoard %d getting %f result",ii+1, cal_lo);
//        //mcu_uart_agent[ii]->run_once(7.0,1800000); //get 7.0 result, wait 30min
//        mcu_uart_agent[ii]->run_once(cal_lo);

//        //qInfo("MBoard %d getting 47.0 result",ii+1);
//        //mcu_uart_agent[ii]->run_once(7.0,1800000); //get 7.0 result, wait 30min
//        //mcu_uart_agent[ii]->run_once(47.0);
//    }


//    set_oven_temp(cal_hi); //set oven temperature
//    qInfo("oven begin to go to %f", cal_hi);
//    QDateTime dateTime2 = QDateTime::currentDateTime();
//    qInfo() << dateTime2.toString("HH:mm:ss.zzz") << "\r\n";

//    qInfo("Wait 45min...");
//    mcu_uart_agent[0]->sleep(2700000);  //wait 45min
//    //mcu_uart_agent[0]->sleep(1200000);  //wait 20min

//    for(int ii=0; ii<NUM_MOTHER_BOARDS; ii++) {
//        qInfo("\r\nMBoard %d getting %f result",ii+1,cal_hi);
//        //mcu_uart_agent[ii]->run_once(77.0,1800000); //get 77.0 result, wait 30min
//        mcu_uart_agent[ii]->run_once(cal_hi);
//    }

//    qInfo("\r\nBegin to set coeff...");
//    QDateTime dateTime3 = QDateTime::currentDateTime();
//    qInfo() << dateTime3.toString("HH:mm:ss.zzz") << "\r\n";

//    for(int ii=0; ii<NUM_MOTHER_BOARDS; ii++) {
//        qInfo("\r\nMBoard %d setting coeff",ii+1);
//        mcu_uart_agent[ii]->set_coeff();
//    }


//    set_oven_temp(temp_check); //set oven temperature
//    qInfo("oven begin to go to %f", temp_check);

//    //set_oven_temp(70.0); //set oven temperature
//    //qInfo("oven begin to go to 70.0");

//    QDateTime dateTime4 = QDateTime::currentDateTime();
//    qInfo() << dateTime4.toString("HH:mm:ss.zzz") << "\r\n";

//    qInfo("Wait 45min...");
//    mcu_uart_agent[0]->sleep(2700000);  //wait 45min
//    //mcu_uart_agent[0]->sleep(1200000);  //wait 20min

//    for(int ii=0; ii<NUM_MOTHER_BOARDS; ii++) {
//        qInfo("*************************************************************************************************");
//        qInfo("\r\nMBoard %d checking temp in %f\r\n",ii+1,temp_check);
//        qInfo("*************************************************************************************************");
//        //mcu_uart_agent[ii]->check_temp(47.0,1800000);
//        mcu_uart_agent[ii]->check_temp(temp_check);

//        //qInfo("MBoard %d checking temp in 70.0",ii+1);
//        //mcu_uart_agent[ii]->check_temp(47.0,1800000);
//        //mcu_uart_agent[ii]->check_temp(70.0);
//    }

//    qInfo("Temperature check done");
//    QDateTime dateTime5 = QDateTime::currentDateTime();
//    qInfo() << dateTime5.toString("HH:mm:ss.zzz") << "\r\n";

//    set_oven_cmd(0); //oven off

//    for(int ii=0; ii<NUM_MOTHER_BOARDS; ii++) {
//        mcu_uart_agent[ii]->run_all_done();
//    }

//}


void myAgent::run_all_board(float cal_hi, float cal_lo, float temp_check, long int time_hi_to_lo, long int time_lo_to_hi, long int time_check, int cali_serial, int mboard_num)
{
    for(int ii=0; ii<mboard_num; ii++) {
        qInfo("\r\nMBoard %d setting parameters",ii+1);
        mcu_uart_agent[ii]->set_parameters();
        qInfo("\r\nMBoard %d checking parameters",ii+1);
        mcu_uart_agent[ii]->check_parameters();
    }


    set_oven_cmd(1); //oven run
    mcu_uart_agent[0]->sleep(2000);


    if(cali_serial == 0) {  //low -> high
        set_oven_temp(cal_lo); //set oven temperature
        qInfo("oven begin to go to %f", cal_lo);

        QDateTime dateTime1 = QDateTime::currentDateTime();
        qInfo() << dateTime1.toString("HH:mm:ss.zzz") << "\r\n";

        qInfo("Wait %ld min for oven temp high to low...",(time_hi_to_lo/60000));
        mcu_uart_agent[0]->sleep(time_hi_to_lo);

        for(int ii=0; ii<mboard_num; ii++) {
            qInfo("\r\nMBoard %d getting %f result",ii+1, cal_lo);
            mcu_uart_agent[ii]->run_once(cal_lo);
        }


        set_oven_temp(cal_hi); //set oven temperature
        qInfo("oven begin to go to %f", cal_hi);
        QDateTime dateTime2 = QDateTime::currentDateTime();
        qInfo() << dateTime2.toString("HH:mm:ss.zzz") << "\r\n";

        qInfo("Wait %ld min for oven temp low to high...",(time_lo_to_hi/60000));
        mcu_uart_agent[0]->sleep(time_lo_to_hi);

        for(int ii=0; ii<mboard_num; ii++) {
            qInfo("\r\nMBoard %d getting %f result",ii+1,cal_hi);
            mcu_uart_agent[ii]->run_once(cal_hi);
        }
    }
    else {  //high -> low
        set_oven_temp(cal_hi); //set oven temperature
        qInfo("oven begin to go to %f", cal_hi);
        QDateTime dateTime2 = QDateTime::currentDateTime();
        qInfo() << dateTime2.toString("HH:mm:ss.zzz") << "\r\n";

        qInfo("Wait %ld min for oven temp low to high...",(time_lo_to_hi/60000));
        mcu_uart_agent[0]->sleep(time_lo_to_hi);

        for(int ii=0; ii<mboard_num; ii++) {
            qInfo("\r\nMBoard %d getting %f result",ii+1,cal_hi);
            mcu_uart_agent[ii]->run_once(cal_hi);
        }

        set_oven_temp(cal_lo); //set oven temperature
        qInfo("oven begin to go to %f", cal_lo);

        QDateTime dateTime1 = QDateTime::currentDateTime();
        qInfo() << dateTime1.toString("HH:mm:ss.zzz") << "\r\n";

        qInfo("Wait %ld min for oven temp high to low...",(time_hi_to_lo/60000));
        mcu_uart_agent[0]->sleep(time_hi_to_lo);

        for(int ii=0; ii<mboard_num; ii++) {
            qInfo("\r\nMBoard %d getting %f result",ii+1, cal_lo);
            mcu_uart_agent[ii]->run_once(cal_lo);
        }
    }

    qInfo("\r\nBegin to set coeff...");
    QDateTime dateTime3 = QDateTime::currentDateTime();
    qInfo() << dateTime3.toString("HH:mm:ss.zzz") << "\r\n";

    for(int ii=0; ii<mboard_num; ii++) {
        qInfo("\r\nMBoard %d setting coeff",ii+1);
        mcu_uart_agent[ii]->set_coeff();
    }


    set_oven_temp(temp_check); //set oven temperature
    qInfo("oven begin to go to %f", temp_check);

    QDateTime dateTime4 = QDateTime::currentDateTime();
    qInfo() << dateTime4.toString("HH:mm:ss.zzz") << "\r\n";

    qInfo("Wait %ld min to check point...",(time_check/60000));
    mcu_uart_agent[0]->sleep(time_check);

    for(int ii=0; ii<mboard_num; ii++) {
        qInfo("*************************************************************************************************");
        qInfo("\r\nMBoard %d checking temp in %f\r\n",ii+1,temp_check);
        qInfo("*************************************************************************************************");
        //mcu_uart_agent[ii]->check_temp(47.0,1800000);
        mcu_uart_agent[ii]->check_temp(temp_check);
    }

    qInfo("Temperature check done");
    QDateTime dateTime5 = QDateTime::currentDateTime();
    qInfo() << dateTime5.toString("HH:mm:ss.zzz") << "\r\n";

    set_oven_cmd(0); //oven off

    for(int ii=0; ii<mboard_num; ii++) {
        mcu_uart_agent[ii]->run_all_done();
    }

}



void myAgent::auto_check_temp_all_board(float temp_check, long int time_check, int mboard_num)
{
    set_oven_temp(temp_check); //set oven temperature
    qInfo("oven begin to go to check point %f", temp_check);

    QDateTime dateTime4 = QDateTime::currentDateTime();
    qInfo() << dateTime4.toString("HH:mm:ss.zzz") << "\r\n";

    qInfo("Wait %ld min to check point...",(time_check/60000));
    mcu_uart_agent[0]->sleep(time_check);

    for(int ii=0; ii<mboard_num; ii++) {
        qInfo("*************************************************************************************************");
        qInfo("\r\nMBoard %d checking temp in %f\r\n",ii+1,temp_check);
        qInfo("*************************************************************************************************");
        //mcu_uart_agent[ii]->check_temp(47.0,1800000);
        mcu_uart_agent[ii]->check_temp(temp_check);
    }

    qInfo("Temperature check done");
    QDateTime dateTime5 = QDateTime::currentDateTime();
    qInfo() << dateTime5.toString("HH:mm:ss.zzz") << "\r\n";

    set_oven_cmd(0); //oven off

    for(int ii=0; ii<mboard_num; ii++) {
        mcu_uart_agent[ii]->run_all_done();
    }

}


void myAgent::manual_check_temp_all_board(int mboard_num)
{

    for(int ii=0; ii<mboard_num; ii++) {
        qInfo("*************************************************************************************************");
        qInfo("\r\nMBoard %d checking temp \r\n",ii+1);
        qInfo("*************************************************************************************************");
        mcu_uart_agent[ii]->manual_check_temp_indoor();
    }

}


void myAgent::set_parameters_all_board(int mboard_num) {
    for(int ii=0; ii<mboard_num; ii++) {
        qInfo("\r\nMBoard %d setting parameters",ii+1);
        mcu_uart_agent[ii]->set_parameters();
    }
    qInfo("All Mother Boards' parameters set done!");
}

void myAgent::check_parameters_all_board(int mboard_num) {
    for(int ii=0; ii<mboard_num; ii++) {
        qInfo("\r\nMBoard %d checking parameters",ii+1);
        mcu_uart_agent[ii]->check_parameters();
    }
    qInfo("All Mother Boards' parameters check done!");
}


//void myAgent::run_all_board()
//{


//    for(int ii=0; ii<NUM_MOTHER_BOARDS; ii++) {
//        qInfo("****************************************************");
//        qInfo("\r\nMBoard %d checking temp in 47.0\r\n",ii+1);
//        qInfo("****************************************************");
//        qInfo("MBoard %d checking temp in 47.0",ii+1);
//        //mcu_uart_agent[ii]->check_temp(47.0,1800000);
//        mcu_uart_agent[ii]->check_temp(47.0);
//    }

//    qInfo("Temperature check done");
//    QDateTime dateTime5 = QDateTime::currentDateTime();
//    qInfo() << dateTime5.toString("HH:mm:ss.zzz") << "\r\n";

//    //set_oven_cmd(0); //oven off

//    for(int ii=0; ii<NUM_MOTHER_BOARDS; ii++) {
//        mcu_uart_agent[ii]->run_all_done();
//    }

//}


unsigned short myAgent::CRC16_MODBUS(void *pushMsg ,unsigned int pBufSize) {
    unsigned short wCRCin = 0xFFFF;
    unsigned short tmp, result;

    unsigned char *pushMsgg = (unsigned char *)pushMsg;

    while(pBufSize--) {
        wCRCin = *pushMsgg ^ wCRCin;

        for(int i=0; i<8; i++) {
            tmp = wCRCin & 0x0001;
            wCRCin = wCRCin >> 1;

            if(tmp)
                wCRCin = wCRCin ^ 0xa001;
        }
        pushMsgg++;
    }
    result = ((wCRCin & 0x00FF) << 8) | ((wCRCin & 0xFF00) >> 8);
    return result;
}
