#define QT_NO_DEBUG_OUTPUT

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

void UART::PrintDCB()
{

    qInfo("dcb.DCBlength %d", dcb.DCBlength);
    qInfo("dcb.BaudRate  %d",dcb.BaudRate  );
    qInfo("dcb.Parity %d", dcb.Parity);
    qInfo("dcb.fParity %d", dcb.fParity);
    qInfo("dcb.StopBits %d", dcb.StopBits);
    qInfo("dcb.ByteSize %d",dcb.ByteSize );
    qInfo("dcb.fOutxCtsFlow %d",dcb.fOutxCtsFlow );
    qInfo("dcb.fOutxDsrFlow  %d",dcb.fOutxDsrFlow  );
    qInfo("dcb.fDtrControl %d", dcb.fDtrControl );
    qInfo("dcb.fDsrSensitivity %d",dcb.fDsrSensitivity );
    qInfo("dcb.fRtsControl %d", dcb.fRtsControl );
    qInfo("dcb.fOutX  %d", dcb.fOutX );
    qInfo("dcb.fInX %d",dcb.fInX );
    /* ---------- 容错机制 ------- */
    qInfo("dcb.fErrorChar %d", dcb.fErrorChar);
    qInfo("dcb.fBinary %d", dcb.fBinary);
    qInfo("dcb.fNull %d", dcb.fNull);
    qInfo("dcb.fAbortOnError %d", dcb.fAbortOnError);
    qInfo("dcb.wReserved %d", dcb.wReserved);
    qInfo("dcb.XonLim %d",dcb.XonLim );
    qInfo("dcb.XoffLim %d", dcb.XoffLim);
    qInfo("dcb.XonChar%d", dcb.XonChar);
    qInfo("dcb.XoffChar %d", dcb.XoffChar);
    qInfo("dcb.EvtChar %d",dcb.EvtChar );

}

void UART::SelectComPort(std::vector<int> * vec_valid_ports)
{
    for (int jj = 0; jj < 5; jj++)
    {

    }
    TCHAR lpTargetPath[5000]; // buffer to store the path of the COMPORTS
    DWORD test;
    bool gotPort=false; // in case the port is not found

    for(int i=0; i<255; i++) // checking ports from COM0 to COM255
    {
        CString str;
        str.Format(_T("%d"),i);
        CString ComName=CString("COM") + CString(str); // converting to COM0, COM1, COM2

        test = QueryDosDevice(ComName, (LPWSTR)lpTargetPath, 5000);

        // Test the return value and error if any
        if(test!=0) //QueryDosDevice returns zero if it didn't find an object
        {
            //m_MyPort.AddString((CString)ComName); // add to the ComboBox
            gotPort=1; // found port
            //      qDebug(" Active Ports Found %d",i); // to display error message incase no ports found
            vec_valid_ports->push_back(i);
        }
        if(::GetLastError()==ERROR_INSUFFICIENT_BUFFER)
        {
            lpTargetPath[10000]; // in case the buffer got filled, increase size of the buffer.
            continue;
        }
    }

    if(!gotPort) // if not port
        qDebug("No Active Ports Found"); // to display error message incase no ports found

}


void UART::load_default(){

//    dcb.DCBlength = sizeof(dcb);  //DCB块大小
//    dcb.BaudRate = 115200;  //波特率
//    dcb.Parity = 0;//NOPARITY;    //奇偶校验0-4：分别表示不校验、奇校验，偶校验、标号、空格
//    dcb.fParity = 0;   //不允许奇偶校验
//    dcb.StopBits = 0;//ONESTOPBIT;   //停止位, 0,1,2->1,1.5,2
//    dcb.ByteSize = 8;   //数据位，以字节表示4-8
//    dcb.fOutxCtsFlow = 0;   //CTS输出流控制
//    dcb.fOutxDsrFlow = 0;   //DSR输出流控制
//    dcb.fDtrControl = DTR_CONTROL_DISABLE;  //DTR流控制类型
//    dcb.fDsrSensitivity = 0;   //对DSR信号线不敏感
//    dcb.fRtsControl = RTS_CONTROL_DISABLE;  //RTS流控制
//    dcb.fOutX = 0;   //XON/XOFF输出流控制
//    dcb.fInX = 0;   //XON/XOFF输入流控制
//    /* ---------- 容错机制 ------- */
//    dcb.fErrorChar = 0;   //允许错误替换
//    dcb.fBinary = 1;   //二进制模式，不检测EOF
//    dcb.fNull = 0;   //允许剥离，去掉NULL字符
//    dcb.fAbortOnError = 0;   //有错误时终止读写操作
//    dcb.wReserved = 0;   //
//    dcb.XonLim = 1;   //XON发送字符之前缓冲区中允许接收的最小字节数
//    dcb.XoffLim = 1;   //XON发送字符之前缓冲区中允许的最小可用字节数
//    dcb.XonChar = 0x13;   //发送和接受XON字符
//    dcb.XoffChar = 0x19;   //发送和接受XOFF字符
//    dcb.EvtChar = 0;   //接收到的事件字符
    //    // DTR Control Flow Values.
    //    //
    //    #define DTR_CONTROL_DISABLE    0x00
    //    #define DTR_CONTROL_ENABLE     0x01
    //    #define DTR_CONTROL_HANDSHAKE  0x02

    //    //
    //    // RTS Control Flow Values
    //    //
    //    #define RTS_CONTROL_DISABLE    0x00
    //    #define RTS_CONTROL_ENABLE     0x01
    //    #define RTS_CONTROL_HANDSHAKE  0x02
    //    #define RTS_CONTROL_TOGGLE     0x03

    dcb.DCBlength = sizeof(dcb);  //DCB块大小
    dcb.BaudRate = 9600;  //波特率
    dcb.Parity = 0;//NOPARITY;    //奇偶校验0-4：分别表示不校验、奇校验，偶校验、标号、空格
    dcb.fParity = 0;   //不允许奇偶校验
    dcb.StopBits = 2;//ONESTOPBIT;   //停止位 0,1,2->1,1.5,2
    dcb.ByteSize = 8;   //数据位，以字节表示4-8

    dcb.fOutxCtsFlow = 1;   //CTS输出流控制
    dcb.fOutxDsrFlow = 1;   //DSR输出流控制
    dcb.fRtsControl = 3;  //RTS流控制
    dcb.fDtrControl = 1;  //DTR流控制类型
    dcb.fDsrSensitivity = 1;   //对DSR信号线不敏感

    /* ---------- 容错机制 ------- */
    dcb.fOutX = 0;   //XON/XOFF输出流控制
    dcb.fInX = 0;   //XON/XOFF输入流控制
    dcb.fErrorChar = 0;   //允许错误替换
    dcb.fBinary = 1;   //二进制模式，不检测EOF
    dcb.fNull = 1;   //允许剥离，去掉NULL字符
    dcb.fAbortOnError = 0;   //有错误时终止读写操作
    dcb.wReserved = 0;   //
    dcb.XonLim = 1;   //XON发送字符之前缓冲区中允许接收的最小字节数
    dcb.XoffLim = 1;   //XON发送字符之前缓冲区中允许的最小可用字节数
    dcb.XonChar = 0x13;   //发送和接受XON字符
    dcb.XoffChar = 0x19;   //发送和接受XOFF字符
    dcb.EvtChar = 0;   //接收到的事件字符
    port_id = 255;
}


UART::UART()
{
    hComm = NULL;
    is_opened = false;
    /* ---------- 串口设置 ------- */
    load_default();

}
UART::~UART()
{
    this->close();
}


bool UART::open()
{
    //HANDLE hComm;
    qInfo("Open UART");
    this->PrintDCB();
    if (!((hComm == INVALID_HANDLE_VALUE)||(hComm == nullptr)))
    {
        qDebug("Uart already opened");
        is_opened = true;
        return true;
    }

    //    std::wstring someText( L"hello world!" );
    //    SetDlgItemTextW( hwnd, result_EDIT, someText.c_str() );
    //    wstring to_wstring (int val);
    //    wstring to_wstring (long val);
    //    wstring to_wstring (long long val);
    //    wstring to_wstring (unsigned val);
    //    wstring to_wstring (unsigned long val);
    //    wstring to_wstring (unsigned long long val);
    //    wstring to_wstring (float val);
    //    wstring to_wstring (double val);
    //    wstring to_wstring (long double val);
    //    std::wstring pi = L"pi is " + std::to_wstring(3.1415926);
    //     std::wstring perfect = std::to_wstring(1+2+4+7+14) + L" is a perfect number";
    //     std::wcout << pi << L'\n';
    //     std::wcout << perfect << L'\n';
    qInfo("open uart with port_id %d",port_id);
    if(port_id == -1)
    {
        qInfo("port id invalid, open uart failed port_id is %d",port_id);
        is_opened = false;
        return false;
    }

#if TEST
    //is_opened = true;

    //return true;
#endif
    //std::wstring COM_STR = L"COM"+std::to_wstring(port_id);

    //QString b;
    //b=QString::number(port_id);
    //std::wstring COM_STR = L"COM"+b.toStdWString();
    std::wstring COM_STR = _T("\\\\.\\COM"+std::to_wstring(port_id));

    //QString qStr;
    //qStr= QString::fromStdWString(COM_STR);

    //qStr.toStdString().c_str();
    //hComm = CreateFile(L"COM7",  //指定串口
    //hComm = CreateFile(L"\\\\.\\COM77",  //指定串口
       hComm = CreateFile(COM_STR.c_str(),  //指定串口

                       GENERIC_READ | GENERIC_WRITE,  //允许读写
                       0,  //以独占方式打开
                       0,  //无安全属性
                       OPEN_EXISTING,  //通讯设备已存在
                       0,  //同步I/O
                       // FILE_ATTRIBUTE_NORMAL,  // normal file
                       //    FILE_FLAG_OVERLAPPED, // OVERLAP mode
                       0);   //不指定模式
    qInfo("Get immediate hComm handleer value 0x%x", hComm);

    if ((hComm == INVALID_HANDLE_VALUE)||(hComm == nullptr))
    {
        CloseHandle(hComm);
        qInfo("uart open error");
        is_opened = false;
        return FALSE;
    }
    else{
        qInfo("uart open success");
        is_opened = true;

        DWORD ReadIntervalTimeout=1000;
        DWORD ReadTotalMultiplier=3000;
        DWORD ReadTotalConstant=3000;
        DWORD WriteTotalMultiplier=5000;
        DWORD WriteTotalConstant=20000;

        SetupTimeout(ReadIntervalTimeout,
                     ReadTotalMultiplier,
                     ReadTotalConstant,
                     WriteTotalMultiplier,
                     WriteTotalConstant);

        return TRUE;
    }
}

bool UART::close()
{
    if (!(hComm == INVALID_HANDLE_VALUE)||(hComm == nullptr)){

        qDebug("hComm valid now closing");
        CloseHandle(hComm);
    }
    else{
        qDebug("hComm not valid.uart closed");
    }
    hComm = INVALID_HANDLE_VALUE;
    is_opened = false;
    return true;
}

bool UART::write(Byte* szWriteBuffer, DWORD dwSend)
{
    bool bWrite = TRUE;
    bool bResult = TRUE;
    DWORD BytesSent = 0;
    HANDLE hWriteEvent=NULL;
    ResetEvent(hWriteEvent);
    //this->close();

    qDebug("dwSend  %d", dwSend);

    if ((hComm == INVALID_HANDLE_VALUE)||(hComm == nullptr)){
        this->open();
        qDebug("hComm handleer value 0x%x", hComm);
        qDebug("String is %s, len is %d", szWriteBuffer,dwSend);
    }
    else{
        if (bWrite)
        {
            //     OverLapped.Offset = 0;
            //     OverLapped.OffsetHigh = 0;
            if((hComm == INVALID_HANDLE_VALUE)||(hComm == nullptr)){
                qDebug("hComm handleer value 0x%x", hComm);

                qDebug("Device not opened");
                //    qDebug("String is %s, len is %d", szWriteBuffer,dwSend);
                return false;
            }
            //qInfo("BytesSent value 0x%x", BytesSent);

            //qInfo("hComm handleer value 0x%x", hComm);
            for (int ii = 0; ii < dwSend; ii++)
            {
                //qInfo("to send %x", szWriteBuffer[ii]);
            }
            bResult = WriteFile(hComm,          //通信设备句柄，CreateFile()返回值得到
                                szWriteBuffer,  //指向写入数据缓冲区
                                dwSend,         //设置要写的字节数
                                &BytesSent,
                                //   &OverLapped);   //指向异步I/O数据

                                NULL);   // no overlap
            //
            if (!bResult)
            {
                DWORD dwError = GetLastError();
                switch (dwError)
                {
                case ERROR_IO_PENDING:
                    BytesSent = 0;
                    bWrite = FALSE;
                    break;
                default: qDebug("Write operation wrong,Error code 0x%x ", dwError);
                    break;
                }
                // return FALSE;
            }
        }
        if (!bWrite)
        {
            bWrite = TRUE;
            bResult = GetOverlappedResult(hComm,
                                          &OverLapped,
                                          &BytesSent,
                                          TRUE);
            if (!bResult)
            {
                qDebug( "GetOverlappedResults() in WriteFile()");
                return FALSE;

            }
        }
        if (BytesSent != dwSend)
        {
            qDebug("WARNING: WriteFile() error.. Bytes Sent:%d; Message Length:%d ",BytesSent,strlen((const char*)szWriteBuffer));
            return FALSE;
        }
        qDebug("Write correct ");
    }

    return TRUE;
}

bool UART::read(Byte * RXBuff, unsigned int len)
{

    //    this->close();
    //    this->open();
    if(hComm == nullptr){
        qInfo("Error: Device not opened, hComm handleer value 0x%x", hComm);
        return false;
    }
    qInfo("current handler is %d\n", hComm);
    for (int i = 0; i < len; i++){
        RXBuff[i] = 0x0;
    }
    bool bRead = TRUE;
    bool bResult = TRUE;
    DWORD dwError = 0;
    DWORD BytesRead = 0;
    DWORD total = 0;
    uint try_cnt;
    uint threshold = 1;
    try_cnt=0;
   while((total<len) && (try_cnt <=threshold))
//    while(1)
    {
        bResult = ClearCommError(hComm, &dwError, &Comstat);
        //if (Comstat.cbInQue == 0)
        //continue;
        if (bRead)
        {
           // qInfo("I am here 1");
            bResult = ReadFile(hComm,  //通信设备（此处为串口）句柄，由CreateFile()返回值得到
                               &RXBuff[total],  //指向接收缓冲区
                               1,  //指明要从串口中读取的字节数
                               &BytesRead,   //
                               NULL);
            //   &OverLapped);  //OVERLAPPED结构
            dwError =  GetLastError();
          //  qInfo("current dwError is %d",dwError);

            if(BytesRead != 0){
                qInfo("*********************");
                qInfo("Bytes read :%d,cur RXBuff: %02x, bResult is : %d\n",BytesRead, RXBuff[total], bResult);
                break;
            }
            total +=BytesRead;

            //if(BytesRead!= 0) exit(0);
            //    qDebug("I am here 2");
            if (dwError == ERROR_IO_PENDING)
            {
                bResult = GetOverlappedResult(hComm,
                                              &OverLapped,
                                              &BytesRead,
                                              TRUE);

            }
        }
        if(BytesRead == 0){
            try_cnt ++;
        }
        //qInfo("total %d,len %d", total, len);
    }
    if(try_cnt >= threshold)
    {
        qInfo("read time out");
        return false;
    }
    qInfo("read try cnt is %d", try_cnt);

    for (unsigned int ii = 0; ii < len; ii ++)
        qInfo("read byte 0x%02x",RXBuff[ii]);
    return true;
}

bool UART::readbyte(Byte* RXBuff)
{
    //    this->close();
    //    this->open();
    if(hComm == nullptr){
        qDebug("Error: Device not opened, hComm handleer value 0x%x", hComm);
        return false;
    }

    bool bRead = TRUE;
    bool bResult = TRUE;
    DWORD dwError = 0;
    DWORD BytesRead = 0;
    DWORD total = 0;
    do
    {
        //   qDebug("I am here 0");
        bResult = ClearCommError(hComm, &dwError, &Comstat);
        //if (Comstat.cbInQue == 0)
        //continue;
        if (bRead)
        {
            //   qDebug("I am here 1");
            bResult = ReadFile(hComm,  //通信设备（此处为串口）句柄，由CreateFile()返回值得到
                               RXBuff,  //指向接收缓冲区
                               1,  //指明要从串口中读取的字节数
                               &BytesRead,   //
                               &OverLapped);  //OVERLAPPED结构
            dwError =  GetLastError();
            total +=BytesRead;
            qDebug("Bytes read :%d,cur RXBuff: %02x, bResult is : %d\n",BytesRead, *RXBuff, bResult);
            //if(BytesRead!= 0) exit(0);
            //   qDebug("I am here 2");
            if (dwError == ERROR_IO_PENDING)
            {
                bResult = GetOverlappedResult(hComm,
                                              &OverLapped,
                                              &BytesRead,
                                              TRUE);
                qInfo("ERROR_IO_PENDING detected");

            }
        }
    }while(total<1);

    qDebug("read byte 0x%02x",*RXBuff);
    return true;
}


bool UART::setupdcb(DCB & conf)
{

    this->dcb=conf;
    if (!GetCommState(hComm, &dcb)) {
        return FALSE;
    }

    if (!SetCommState(hComm, &dcb))
        return FALSE;
    else
        return TRUE;
}

bool UART::SetupTimeout(DWORD ReadIntervalTimeout, DWORD ReadTotalMultiplier,
                        DWORD ReadTotalConstant, DWORD WriteTotalMultiplier, DWORD WriteTotalConstant)
{
    COMMTIMEOUTS time;
    time.ReadIntervalTimeout = ReadIntervalTimeout;   //读时间超时
    time.ReadTotalTimeoutConstant = ReadTotalConstant;  //读时间常量
    time.ReadTotalTimeoutMultiplier = ReadTotalMultiplier;  //读时间系数
    time.WriteTotalTimeoutConstant = WriteTotalConstant;  //写时间常量
    time.WriteTotalTimeoutMultiplier = WriteTotalMultiplier;  //写时间系数
    if (!SetCommTimeouts(hComm, &time))
        return FALSE;
    else
        return TRUE;
}
