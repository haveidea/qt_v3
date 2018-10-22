#include "myOven.h"
#include "QDebug"
#if 0
void myOven::load_oven(){
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
    dcb.fOutxCtsFlow = 0;   //CTS输出流控制
    dcb.fOutxDsrFlow = 0;   //DSR输出流控制
    dcb.fDtrControl = 0;  //DTR流控制类型
    dcb.fRtsControl = 1;  //RTS流控制
    dcb.fDsrSensitivity = 0;   //对DSR信号线不敏感
    dcb.fOutX = 0;   //XON/XOFF输出流控制
    dcb.fInX = 0;   //XON/XOFF输入流控制
    /* ---------- 容错机制 ------- */
    dcb.fErrorChar = 0;   //允许错误替换
    dcb.fBinary = 1;   //二进制模式，不检测EOF
    dcb.fNull = 0;   //允许剥离，去掉NULL字符
    dcb.fAbortOnError = 0;   //有错误时终止读写操作
    dcb.wReserved = 0;   //
    dcb.XonLim = 1;   //XON发送字符之前缓冲区中允许接收的最小字节数
    dcb.XoffLim = 1;   //XON发送字符之前缓冲区中允许的最小可用字节数
    dcb.XonChar = 0x13;   //发送和接受XON字符
    dcb.XoffChar = 0x19;   //发送和接受XOFF字符
    dcb.EvtChar = 0;   //接收到的事件字符
    port_id = 255;

}
#endif
myOven::myOven()
{
  //  this->load_oven();
    this->PrintDCB();
    qInfo("deault loaded");
}
//bool myOven::set_temp(float temp)
//{
//    qDebug()<<"TODO";

//    //open uart;
//    //if(this->hComm==NULL)
//      //  this->open();
//    // calcalate code according to temp value;
//    // char* code;
//    //write to uart
//    //this->write(code,2);
//    //close uart
//   // this->close();
//    return true;
//}
