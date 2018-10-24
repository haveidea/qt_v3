#define QT_NO_DEBUG_OUTPUT

#ifndef UART_H
#define UART_H
#include <myglobal.h>
#include <windows.h>
#include <commctrl.h>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <myglobal.h>
#include <vector>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#define MAX_BUF_LEN 65536

typedef struct
{
    int num;
    TCHAR name[5000];
}  uartport;
class UART{
public slots:
    void readData(void);
public:
    QSerialPort * serial;
    DCB    dcb;
    Byte   read_buffer[MAX_BUF_LEN];
    HANDLE hComm;
    void handleError(QSerialPort::SerialPortError );
    unsigned int port_id;
   // void SelectComPort(std::vector<QSerialPort> *);


    COMSTAT Comstat;

    OVERLAPPED OverLapped;


public:
    UART();
    ~UART();
    bool               is_opened;
    bool               open();
    bool               close();

    bool               write(Byte* szWriteBuffer, DWORD dwSend);

    virtual void       load_default(void);
};

#endif // UART_H
