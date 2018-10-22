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

#define MAX_BUF_LEN 65536


class UART{
public:
    DCB    dcb;
    Byte   read_buffer[MAX_BUF_LEN];
    HANDLE hComm;
    unsigned int port_id;
    void SelectComPort(std::vector<int> *);


    COMSTAT Comstat;

    bool SetupTimeout(DWORD ReadInterval,
                      DWORD ReadTotalMultiplier,
                      DWORD ReadTotalConstant,
                      DWORD WriteTotalMultiplier,
                      DWORD WriteTotalConstant);
    bool SetupDCB(DCB &config);
    OVERLAPPED OverLapped;

public:
    UART();
    ~UART();
    bool               is_opened;
    bool               open();
    bool               close();
    bool               setupdcb(DCB & conf);

    bool               write(Byte* szWriteBuffer, DWORD dwSend);
    bool               read(Byte *, unsigned int );
    bool               readbyte(Byte* RXBuff);

    virtual void       load_default(void);
    void                PrintDCB();
};

#endif // UART_H
