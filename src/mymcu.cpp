#include "myMCU.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

void myMCU::load_default(){
    serial->setBaudRate(QSerialPort::Baud115200);       //设置波特率为115200
    serial->setParity(QSerialPort::NoParity);           //校验位设置为0
    serial->setStopBits(QSerialPort::OneStop);          //停止位设置为1
    serial->setFlowControl(QSerialPort::NoFlowControl); //设置为无流控制
    serial->setDataBits(QSerialPort::Data8);            //设置数据位8
}

myMCU::myMCU()
{
}
