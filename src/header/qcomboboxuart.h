#ifndef QCOMBOBOXUART_H
#define QCOMBOBOXUART_H

#define QT_NO_DEBUG_OUTPUT



#include <map>
#include "UART.h"
#include <QDebug>
#include <QObject>
#include <myglobal.h>
#include <QComboBox>
#include <QApplication>
#include <iostream>
#include <string>

#include <vector>


using namespace std;

class QComboBox_uart_port:public QComboBox
{
    Q_OBJECT
public:
    QComboBox_uart_port();
    QComboBox_uart_port(QWidget *parent=nullptr);
    void bind_uart(UART * uart= nullptr);
  //  void refresh();
    void config();
    void setvalue();
   // void addvalidport(int);
    std::vector<QSerialPort> vec_valid_ports;
signals:
    void refresh_valid_ports();
private:
    int index = 0;

  //  void config();
    std::map <DWORD, int> baud2index_map;
    std::map <int, DWORD> index2baud_map;
    UART * uart;

};


class QComboBox_uart_parity:public QComboBox
{
    Q_OBJECT
public:
    QComboBox_uart_parity(QWidget *parent=nullptr);
    void bind_uart(UART * uart= nullptr);
  //  void refresh();
    void setvalue();
private:
    void config();
    std::map <string, int> baud2index_map;
    std::map <int, string> index2baud_map;
    UART * uart;

};


class QComboBox_uart_flowcontrol:public QComboBox
{
    Q_OBJECT
public:
    QComboBox_uart_flowcontrol();
    QComboBox_uart_flowcontrol(QWidget *parent=nullptr);
    void bind_uart(UART * uart= nullptr);
 //   void refresh();
    void setvalue();
private:
    void config();
    std::map <string, int> baud2index_map;
    std::map <int, string> index2baud_map;
    UART * uart;

};



class QComboBox_uart_data:public QComboBox
{
    Q_OBJECT
public:
    QComboBox_uart_data();
    QComboBox_uart_data(QWidget *parent=nullptr);
    void bind_uart(UART * uart= nullptr);
   // void refresh();
    void setvalue();
private:
    void config();
    std::map <BYTE, int> baud2index_map;
    std::map <int, BYTE> index2baud_map;
    UART * uart;

};


class QComboBox_uart_baudrate:public QComboBox
{
    Q_OBJECT
public:
    QComboBox_uart_baudrate();
    QComboBox_uart_baudrate(QWidget *parent=nullptr);
    void bind_uart(UART * uart= nullptr);
  //  void refresh();
    void setvalue();
private:
    void config();
    std::map <DWORD, int> baud2index_map;
    std::map <int, DWORD> index2baud_map;
    UART * uart;

};


class QComboBox_uart_stopbits:public QComboBox
{
    Q_OBJECT
public:
    QComboBox_uart_stopbits();
    QComboBox_uart_stopbits(QWidget *parent=nullptr);
    void bind_uart(UART * uart= nullptr);
 //   void refresh();
    void setvalue();
private:
    void config();
    UART * uart;

};

#endif // QCOMBOBOXUART_H
