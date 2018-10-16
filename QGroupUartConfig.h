#define QT_NO_DEBUG_OUTPUT

#ifndef MYUARTCONFIGUI_H
#define MYUARTCONFIGUI_H
#include "QComboBox_uart_port.h"
#include "QComboBox_uart_parity.h"
#include "QComboBox_uart_stopbits.h"
#include "QComboBox_uart_flowcontrol.h"
#include "QComboBox_uart_baudrate.h"
#include "QComboBox_uart_data.h"
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <Qt>
#include <myglobal.h>

#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QWidget>
#include <QSizePolicy>
#include <QtWidgets/QPushButton>



class QGroupUartConfig:public QGroupBox
{
    Q_OBJECT

public slots:
    void refresh();
    void setvalue();
    void on_OpenClose_Clicked();
    void on_SetUart_clicked();
    void on_ResetUart_clicked();

public:
    QGroupUartConfig(int id, QWidget *parent=nullptr );

    ~QGroupUartConfig();
    void bind_uart(UART * uart= nullptr);

    QComboBox_uart_parity * uart_paritybit;
    QComboBox_uart_baudrate * uart_baud;
    QComboBox_uart_data * uart_databits;
    QComboBox_uart_flowcontrol * uart_flowcontrol;
    QComboBox_uart_port * uart_port;
    QComboBox_uart_stopbits * uart_stopbits;

    QGroupBox *uart_set_group;
    QLabel* label_13;
    QLabel* label_15;
    QLabel* label_16;
    QLabel* label_18;
    QLabel* label_19;
    QLabel* label_20;
    QLabel* label_21;

    QPushButton *SetUart;
    QPushButton *ResetUart;
    QPushButton * OpenClose;
    UART * uart;

    QSizePolicy sizePolicy;
};

#endif // MYUARTCONFIGUI_H
