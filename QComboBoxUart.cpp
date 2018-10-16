#include "QComboBox_uart_baudrate.h"


void QComboBox_uart_baudrate::refresh()
{

    std::map <DWORD,int>::iterator it;
    if(uart==nullptr){
        qDebug()<<"uart is not binding, cannot fresh uart baudrate setting, ignore";
    }
    else{
   //     uart->load_default();
        if((it = baud2index_map.find(uart->dcb.BaudRate))!=baud2index_map.end())
            setCurrentIndex(it->second);
        else
            setCurrentIndex(0);
    }
}

void QComboBox_uart_baudrate::setvalue()
{
    switch(currentIndex()){
    case 0: uart->dcb.BaudRate = 115200;break;
    case 1: uart->dcb.BaudRate = 38400;break;
    case 2: uart->dcb.BaudRate = 19200;break;
    case 3: uart->dcb.BaudRate = 9600;break;
    case 4: uart->dcb.BaudRate = 4800;break;
    case 5: uart->dcb.BaudRate = 2400;break;
    case 6: uart->dcb.BaudRate = 1200;break;
    case 7: uart->dcb.BaudRate = 300;break;
    default: uart->dcb.BaudRate = 9600;break;
    }
}

QComboBox_uart_baudrate::QComboBox_uart_baudrate():QComboBox()
{
    config();
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
    refresh();
}

#include "QComboBox_uart_stopbits.h"


void QComboBox_uart_stopbits::refresh()
{

    if(uart==nullptr){
        qDebug()<<"uart is not binding, cannot fresh uart uart_stopbits setting, ignore";
    }
    else{
        //     qDebug()<<"refresh uart";
     //   uart->load_default();
        setCurrentIndex(uart->dcb.StopBits);
    }
}

void QComboBox_uart_stopbits::setvalue()
{
    uart->dcb.StopBits= currentIndex() ;
}

QComboBox_uart_stopbits::QComboBox_uart_stopbits():QComboBox()
{
    config();
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
    refresh();
}



#include "QComboBox_uart_port.h"


void QComboBox_uart_port::refresh()
{
    setCurrentIndex(0);
    index = 1;
 //   qDebug("remove %d items", this->count()-1);
    for (int ii = this->count()-1; ii>=1;ii--)
    {
        this->removeItem(ii);
    }
  //  qDebug("current items num is  %d items", this->count());


    vec_valid_ports.clear();
    this->uart->SelectComPort(&vec_valid_ports);

    //for(std::vector<int>::iterator it = vec_valid_ports.begin() ; it != vec_valid_ports.end(); ++it)
 //   qDebug("add %d items", vec_valid_ports.size());

    for (unsigned it=0; it<vec_valid_ports.size(); it++)
    {
        //addvalidport(vec_valid_ports[it]);
        std::stringstream buffer;
        buffer<<vec_valid_ports[it];
        std::string str = buffer.str();
        QString qstr = QString::fromStdString(str);

    //    qDebug("I am here with port id %d,index %d,size:%d",vec_valid_ports[it],index,this->size());
        this->addItem((QString(qstr)));

       // this->setItemText(index, QApplication::translate("MainWindow", str.c_str() , nullptr));

        index++;
      //  qDebug("new  %d items added", this->count()-1);

    }

}

void QComboBox_uart_port::setvalue()
{
    QString qs = this->currentText();
    int i;
    //    QStringRef subString = qs.midRef(4,qs.size());
    //    int i = subString.toInt();
    if(qs == "NA")
        i = -1;
    else
        i = qs.toInt();

    qDebug("set uart port to com%d",i);
    uart->port_id=i;
}

QComboBox_uart_port::QComboBox_uart_port():QComboBox()
{
    index = 0;
    this->addItem(QString());
    this->setItemText(index, QApplication::translate("MainWindow", "NA" , nullptr));
}

//void QComboBox_uart_port::config()
//{

//}

QComboBox_uart_port::QComboBox_uart_port(QWidget *parent):QComboBox(parent){
    index = 0;

    this->addItem(QString());
    this->setItemText(index, QApplication::translate("MainWindow", "NA" , nullptr));
}

void QComboBox_uart_port::bind_uart(UART * uart){
    this->uart = uart;
    refresh();
}

void QComboBox_uart_port::addvalidport(int i)
{

}



#include "QComboBox_uart_parity.h"


void QComboBox_uart_parity::refresh()
{

    if(uart==nullptr){
        qDebug()<<"uart is not binding, cannot fresh uart uart_parity setting, ignore";
    }
    else{
        if((uart->dcb.Parity) <=4)
            setCurrentIndex(uart->dcb.Parity);
        else
            setCurrentIndex(0);
    }
}

void QComboBox_uart_parity::setvalue()
{
    uart->dcb.Parity = currentIndex();
}

QComboBox_uart_parity::QComboBox_uart_parity():QComboBox()
{
    config();
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
    refresh();
}



#include "QComboBox_uart_flowcontrol.h"


void QComboBox_uart_flowcontrol::refresh()
{

    std::map <string,int>::iterator it;
    if(uart==nullptr){
        qDebug()<<"uart is not binding, cannot fresh uart uart_flowcontrol setting, ignore";
    }
    else{
     //   uart->load_default();
        string search_string;


    if((uart->dcb.fOutX == 0) & (uart->dcb.fInX == 0)) search_string = "None";
    else if((uart->dcb.fOutX == 1) & (uart->dcb.fInX == 1)) search_string = "Xon/Xoff";
        else search_string = "None";
        if((it = baud2index_map.find(search_string))!=baud2index_map.end())
            setCurrentIndex(it->second);
        else
            setCurrentIndex(0);
    }
}

void QComboBox_uart_flowcontrol::setvalue()
{
    switch(currentIndex()){
    case 0: uart->dcb.fOutX = 0;uart->dcb.fInX=0;break;
    case 1: uart->dcb.fOutX = 0;uart->dcb.fInX=0;break;
    case 2: uart->dcb.fOutX = 1;uart->dcb.fInX=1;break;
    default: uart->dcb.fOutX = 0;uart->dcb.fInX=0;break;
    }
}

QComboBox_uart_flowcontrol::QComboBox_uart_flowcontrol():QComboBox()
{
    config();
}

void QComboBox_uart_flowcontrol::config()
{
    this->addItem(QString());
    this->addItem(QString());
    this->addItem(QString());
    this->setGeometry(QRect(70, 80, 70, 25));

    baud2index_map ["None"] = 0;
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
    refresh();
}



#include "QComboBox_uart_data.h"


void QComboBox_uart_data::refresh()
{

    std::map <Byte,int>::iterator it;
    if(uart==nullptr){
        qDebug()<<"uart is not binding, cannot fresh uart uart_data setting, ignore";
    }
    else{
   //     uart->load_default();
        if((it = baud2index_map.find(uart->dcb.ByteSize))!=baud2index_map.end())
            setCurrentIndex(it->second);
        else
            setCurrentIndex(0);
    }
}

void QComboBox_uart_data::setvalue()
{
    switch(currentIndex()){
    case 0: uart->dcb.ByteSize= 8 ;break;
    case 1: uart->dcb.ByteSize= 7;break;
    case 2: uart->dcb.ByteSize= 6;break;
    case 3: uart->dcb.ByteSize= 5;break;
    default: uart->dcb.ByteSize= 8;break;
    }
}

QComboBox_uart_data::QComboBox_uart_data():QComboBox()
{
    config();
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
    refresh();
}





