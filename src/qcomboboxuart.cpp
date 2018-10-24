#include "QComboBoxUart.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

/////////////////baudrate
void QComboBox_uart_baudrate::setvalue()
{
    qInfo("baudrate index selected is %d",currentIndex());
    switch(currentIndex()){
    case 0: uart->serial->setBaudRate(115200);break;
    case 1: uart->serial->setBaudRate(38400) ;break;
    case 2: uart->serial->setBaudRate(19200) ;break;
    case 3: uart->serial->setBaudRate(9600)  ;break;
    case 4: uart->serial->setBaudRate(4800)  ;break;
    case 5: uart->serial->setBaudRate(2400)  ;break;
    case 6: uart->serial->setBaudRate(1200)  ;break;
    case 7: uart->serial->setBaudRate(300)   ;break;
    default: uart->serial->setBaudRate(9600) ;break;
    }
    qInfo("baudrate index selected is end");
}

void QComboBox_uart_baudrate::config()
{
    this->addItem(QString());
    this->addItem(QString());
    this->addItem(QString());
    this->addItem(QString());
    this->addItem(QString());
    this->addItem(QString());
    this->addItem(QString());
    this->addItem(QString());
    this->addItem(QString());
    this->setGeometry(QRect(70, 80, 70, 25));

    baud2index_map [115200] = 0;
    baud2index_map [38400]  = 1;
    baud2index_map [19200]  = 2;
    baud2index_map [9600]   = 3;
    baud2index_map [4800]   = 4;
    baud2index_map [2400]   = 5;
    baud2index_map [1200]   = 6;
    baud2index_map [300]    = 7;

    std::map<DWORD,int>::iterator it;
    for(it = baud2index_map.begin(); it != baud2index_map.end(); it++) {
        index2baud_map[it->second] = it->first;
    }
    this->setItemText(0, QApplication::translate("MainWindow", "115200", nullptr));
    this->setItemText(1, QApplication::translate("MainWindow", "38400", nullptr));
    this->setItemText(2, QApplication::translate("MainWindow", "19200", nullptr));
    this->setItemText(3, QApplication::translate("MainWindow", "9600", nullptr));
    this->setItemText(4, QApplication::translate("MainWindow", "4800", nullptr));
    this->setItemText(5, QApplication::translate("MainWindow", "2400", nullptr));
    this->setItemText(6, QApplication::translate("MainWindow", "1200", nullptr));
    this->setItemText(7, QApplication::translate("MainWindow", "300", nullptr));
    this->setItemText(8, QApplication::translate("MainWindow", "NA", nullptr));
}

QComboBox_uart_baudrate::QComboBox_uart_baudrate(QWidget *parent):QComboBox(parent){
    config();
}

void QComboBox_uart_baudrate::bind_uart(UART * uart){
    this->uart = uart;
}

//////////////////////stopbits
void QComboBox_uart_stopbits::setvalue()
{
    switch(currentIndex()){
        case 0:     uart->serial->setStopBits(QSerialPort::StopBits::OneStop);break;
        case 1:     uart->serial->setStopBits(QSerialPort::StopBits::OneAndHalfStop);break;
        case 2:     uart->serial->setStopBits(QSerialPort::StopBits::TwoStop);break;
        default:    uart->serial->setStopBits(QSerialPort::StopBits::OneStop);break;
    }
}

void QComboBox_uart_stopbits::config()
{
    this->addItem(QString());
    this->addItem(QString());
    this->addItem(QString());

    this->setGeometry(QRect(70, 80, 70, 25));

    this->setItemText(0, QApplication::translate("MainWindow", "1", nullptr));
    this->setItemText(1, QApplication::translate("MainWindow", "1.5", nullptr));
    this->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));

}

QComboBox_uart_stopbits::QComboBox_uart_stopbits(QWidget *parent):QComboBox(parent){
    config();
}

void QComboBox_uart_stopbits::bind_uart(UART * uart){
    this->uart = uart;
 //   refresh();
}

void QComboBox_uart_port::setvalue()
{
    QString qs = this->currentText();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if(qs.startsWith(info.portName()) && qs.endsWith(info.serialNumber())){
                 uart->serial->setPort(info);
        }
    }
}

void QComboBox_uart_port::config()
{

    this->clear();
    int ii = 0;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QString qs;
        qs = info.portName() + " " + info.serialNumber();
        this->addItem(qs);
        this->setItemText(ii, QApplication::translate("MainWindow", qs.toLocal8Bit().data(), nullptr));
        ii++;
    }
}

QComboBox_uart_port::QComboBox_uart_port(QWidget *parent):QComboBox(parent){
    index = 0;

    this->addItem(QString());
    this->setItemText(index, QApplication::translate("MainWindow", "NA" , nullptr));
    this->config();
}

void QComboBox_uart_port::bind_uart(UART * uart){
    this->uart = uart;
}

void QComboBox_uart_parity::setvalue()
{
    qInfo("parity index selected is %d",currentIndex());

    switch(currentIndex()){
        case 0: this->uart->serial->setParity(QSerialPort::Parity::NoParity);break;
        case 1: this->uart->serial->setParity(QSerialPort::Parity::OddParity);break;
        case 2: this->uart->serial->setParity(QSerialPort::Parity::EvenParity);break;
        case 3: this->uart->serial->setParity(QSerialPort::Parity::MarkParity);break;
        case 4: this->uart->serial->setParity(QSerialPort::Parity::SpaceParity);break;
    }
    qInfo("parity index selected end");

}

void QComboBox_uart_parity::config()
{
    this->addItem(QString());
    this->addItem(QString());
    this->addItem(QString());
    this->addItem(QString());
    this->addItem(QString());
    this->setGeometry(QRect(70, 80, 70, 25));

    baud2index_map ["NONE"] = 0;
    baud2index_map ["ODD"]  = 1;
    baud2index_map ["EVEN"] = 2;
    baud2index_map ["MARK"] = 3;
    baud2index_map ["SPACE"]= 4;

    std::map<string,int>::iterator it;
    for(it = baud2index_map.begin(); it != baud2index_map.end(); it++) {
        index2baud_map[it->second] = it->first;
    }
    this->setItemText(0, QApplication::translate("MainWindow", "NONE", nullptr));
    this->setItemText(1, QApplication::translate("MainWindow", "ODD", nullptr));
    this->setItemText(2, QApplication::translate("MainWindow", "EVEN", nullptr));
    this->setItemText(3, QApplication::translate("MainWindow", "MARK", nullptr));
    this->setItemText(4, QApplication::translate("MainWindow", "SPACE", nullptr));
}

QComboBox_uart_parity::QComboBox_uart_parity(QWidget *parent):QComboBox(parent){
    config();
}

void QComboBox_uart_parity::bind_uart(UART * uart){
    this->uart = uart;
}


void QComboBox_uart_flowcontrol::setvalue()
{
//    enum FlowControl {
//        NoFlowControl,
//        HardwareControl,
//        SoftwareControl,
//        UnknownFlowControl = -1
    switch(currentIndex()){
    case 0:  uart->serial->setFlowControl(QSerialPort::FlowControl::NoFlowControl);break;
    case 1:  uart->serial->setFlowControl(QSerialPort::FlowControl::HardwareControl);break;
    case 2:  uart->serial->setFlowControl(QSerialPort::FlowControl::SoftwareControl);break;
    default: uart->serial->setFlowControl(QSerialPort::FlowControl::NoFlowControl);break;
    }
}

void QComboBox_uart_flowcontrol::config()
{
    this->addItem(QString());
    this->addItem(QString());
    this->addItem(QString());
    this->setGeometry(QRect(70, 80, 70, 25));

    baud2index_map ["None"]      = 0;
    baud2index_map ["Hardware"]  = 1;
    baud2index_map ["Xon/Xoff"]  = 2;

    std::map<string,int>::iterator it;
    for(it = baud2index_map.begin(); it != baud2index_map.end(); it++) {
        index2baud_map[it->second] = it->first;
    }

    this->setItemText(0, QApplication::translate("MainWindow", "None", nullptr));
    this->setItemText(1, QApplication::translate("MainWindow", "Hardware", nullptr));
    this->setItemText(2, QApplication::translate("MainWindow", "Xon/Xoff", nullptr));

}

QComboBox_uart_flowcontrol::QComboBox_uart_flowcontrol(QWidget *parent):QComboBox(parent){
    config();
}

void QComboBox_uart_flowcontrol::bind_uart(UART * uart){
    this->uart = uart;
 //   refresh();
}

void QComboBox_uart_data::setvalue()
{
    switch(currentIndex()){
    case 0:     uart->serial->setDataBits(QSerialPort::DataBits::Data8);break;
    case 1:     uart->serial->setDataBits(QSerialPort::DataBits::Data7);break;
    case 2:     uart->serial->setDataBits(QSerialPort::DataBits::Data6);break;
    case 3:    uart->serial->setDataBits(QSerialPort::DataBits::Data5);break;
    default:    uart->serial->setDataBits(QSerialPort::DataBits::Data8);break;
    }
}

void QComboBox_uart_data::config()
{
    this->addItem(QString());
    this->addItem(QString());
    this->addItem(QString());
    this->addItem(QString());
    this->setGeometry(QRect(70, 80, 70, 25));

    baud2index_map [8] = 0;
    baud2index_map [7]  = 1;
    baud2index_map [6]  = 2;
    baud2index_map [5]   = 3;

    std::map<Byte,int>::iterator it;
    for(it = baud2index_map.begin(); it != baud2index_map.end(); it++) {
        index2baud_map[it->second] = it->first;
    }
    this->setItemText(0, QApplication::translate("MainWindow", "8", nullptr));
    this->setItemText(1, QApplication::translate("MainWindow", "7", nullptr));
    this->setItemText(2, QApplication::translate("MainWindow", "6", nullptr));
    this->setItemText(3, QApplication::translate("MainWindow", "5", nullptr));
}

QComboBox_uart_data::QComboBox_uart_data(QWidget *parent):QComboBox(parent){
    config();
}

void QComboBox_uart_data::bind_uart(UART * uart){
    this->uart = uart;
//    refresh();
}
