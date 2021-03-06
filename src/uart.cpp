#define QT_NO_DEBUG_OUTPUT
#include <QGroupUartConfig.h>
// COM Port.cpp : Defines the entry point for the application.
#include "UART.h"
#include <commctrl.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <QKeyEvent>
#include <cstring>
#include <atlstr.h>


void UART::load_default(){

}


void UART::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
       qInfo("Uart Error, now close");
        if (serial->isOpen())
               serial->close();
    }
}


UART::UART()
{
    serial = new QSerialPort;
    is_opened = false;
}

UART::~UART()
{
    this->close();
}

bool UART::open()
{
    qInfo("baudraete is %d", serial->baudRate());
     if(serial->open(QIODevice::ReadWrite))
     {
         qInfo("Uart Open successful");
         this->is_opened = TRUE;

         return TRUE;
     }
     else{
         this->is_opened = FALSE;

         qInfo("Uart Open error");
         return FALSE;
     }

}

bool UART::close()
{
    if (serial->isOpen())
             serial->close();
    this->is_opened = serial->isOpen();
    if(this->is_opened){
        qInfo("Uart close fail");
        return FALSE;
    }
    else{
        qInfo("Uart close successful");
        return TRUE;
    }
}

bool UART::write(Byte* szWriteBuffer, DWORD dwSend)
{


    const   char*   p   =   (const   char*)(char*)szWriteBuffer;
    serial->write(p,dwSend);
    return TRUE;
}
