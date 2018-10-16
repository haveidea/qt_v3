#include "QGroupUartConfig.h"

QGroupUartConfig::~QGroupUartConfig()
{

}
QGroupUartConfig::QGroupUartConfig(int id, QWidget * parent):QGroupBox(parent)
{
    //this = new QGroupBox(parent);
    setObjectName(QStringLiteral("uart_setting"));
    setGeometry(QRect(id*180 +60, 70, 150, 400));
    //   sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    //    this->setSizePolicy(sizePolicy);

    uart_port = new QComboBox_uart_port(this);
    uart_port->setObjectName(QStringLiteral("uart_port"));
    uart_port->setGeometry(QRect(70, 40, 70, 25));
    sizePolicy.setHeightForWidth(uart_port->sizePolicy().hasHeightForWidth());
    uart_port->setSizePolicy(sizePolicy);

    label_20 = new QLabel(this);

    label_20->setObjectName(QStringLiteral("label_20"));
    label_20->setGeometry(QRect(15, 40, 60, 25));
    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
    label_20->setSizePolicy(sizePolicy1);

    uart_flowcontrol = new QComboBox_uart_flowcontrol(this);
    uart_flowcontrol->setObjectName(QStringLiteral("uart_flowcontrol"));
    uart_flowcontrol->setGeometry(QRect(70, 240, 70, 25));
    sizePolicy.setHeightForWidth(uart_flowcontrol->sizePolicy().hasHeightForWidth());
    uart_flowcontrol->setSizePolicy(sizePolicy);
    uart_baud = new QComboBox_uart_baudrate(this);
    uart_baud->setObjectName(QStringLiteral("uart_baud"));
    uart_baud->setGeometry(QRect(70, 80, 70, 25));
    sizePolicy.setHeightForWidth(uart_baud->sizePolicy().hasHeightForWidth());
    uart_baud->setSizePolicy(sizePolicy);
    uart_databits = new QComboBox_uart_data(this);
    uart_databits->setObjectName(QStringLiteral("oven_databits"));
    uart_databits->setGeometry(QRect(70, 120, 70, 25));
    sizePolicy.setHeightForWidth(uart_databits->sizePolicy().hasHeightForWidth());
    uart_databits->setSizePolicy(sizePolicy);
    label_16 = new QLabel(this);
    label_16->setObjectName(QStringLiteral("label_16"));
    label_16->setGeometry(QRect(15, 80, 60, 25));
    sizePolicy1.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
    label_16->setSizePolicy(sizePolicy1);
    label_19 = new QLabel(this);
    label_19->setObjectName(QStringLiteral("label_19"));
    label_19->setGeometry(QRect(15, 120, 60, 25));
    sizePolicy1.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
    label_19->setSizePolicy(sizePolicy1);
    uart_paritybit = new QComboBox_uart_parity(this);

    uart_paritybit->setObjectName(QStringLiteral("oven_paritybit"));
    uart_paritybit->setGeometry(QRect(70, 160, 70, 25));
    sizePolicy.setHeightForWidth(uart_paritybit->sizePolicy().hasHeightForWidth());
    uart_paritybit->setSizePolicy(sizePolicy);
    label_15 = new QLabel(this);
    label_15->setObjectName(QStringLiteral("label_15"));
    label_15->setGeometry(QRect(15, 240, 60, 25));
    sizePolicy1.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
    label_15->setSizePolicy(sizePolicy1);
    uart_stopbits = new QComboBox_uart_stopbits(this);

    uart_stopbits->setObjectName(QStringLiteral("uart_stopbits"));
    uart_stopbits->setGeometry(QRect(70, 200, 70, 25));
    sizePolicy.setHeightForWidth(uart_stopbits->sizePolicy().hasHeightForWidth());
    uart_stopbits->setSizePolicy(sizePolicy);
    label_18 = new QLabel(this);
    label_18->setObjectName(QStringLiteral("label_18"));
    label_18->setGeometry(QRect(15, 160, 60, 25));
    sizePolicy1.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
    label_18->setSizePolicy(sizePolicy1);
    label_21 = new QLabel(this);
    label_21->setObjectName(QStringLiteral("label_21"));
    label_21->setGeometry(QRect(15, 200, 60, 25));
    sizePolicy1.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
    label_21->setSizePolicy(sizePolicy1);
    label_13 = new QLabel(this);
    label_13->setObjectName(QStringLiteral("label_13"));
    label_13->setGeometry(QRect(15, 40, 60, 25));
    sizePolicy1.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
    label_13->setSizePolicy(sizePolicy1);

    this->label_20->setText(QApplication::translate("MainWindow", "\347\253\257\345\217\243", nullptr));

    this->label_16->setText(QApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", nullptr));

    this->label_19->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", nullptr));


    this->label_15->setText(QApplication::translate("MainWindow", "\346\265\201\351\207\217\346\216\247\345\210\266", nullptr));


    this->label_18->setText(QApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215", nullptr));
    this->label_21->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", nullptr));

    this->label_13->setText(QApplication::translate("MainWindow", "\347\253\257\345\217\243", nullptr));

    SetUart = new QPushButton(this);
    SetUart->setObjectName(QStringLiteral("SetUart"));
    SetUart->setGeometry(QRect(20, 300, 50, 30));
    sizePolicy.setHeightForWidth(SetUart->sizePolicy().hasHeightForWidth());
    SetUart->setSizePolicy(sizePolicy);
    SetUart->setAutoDefault(false);
    //ResetUart button
    ResetUart = new QPushButton(this);
    ResetUart->setObjectName(QStringLiteral("ResetUart"));
    ResetUart->setGeometry(QRect(80, 300, 50, 30));
    sizePolicy.setHeightForWidth(ResetUart->sizePolicy().hasHeightForWidth());
    ResetUart->setSizePolicy(sizePolicy);
    //OpenClose button
    OpenClose = new QPushButton(this);
    OpenClose->setObjectName(QStringLiteral("OpenClose"));
    OpenClose->setGeometry(QRect(25, 350, 100, 30));
    sizePolicy.setHeightForWidth(OpenClose->sizePolicy().hasHeightForWidth());
    OpenClose->setSizePolicy(sizePolicy);

    SetUart->setText(QApplication::translate("MainWindow", "Set", nullptr));
    ResetUart->setText(QApplication::translate("MainWindow", "Reset", nullptr));
    OpenClose->setText(QApplication::translate("MainWindow", "Click to Open", nullptr));

    QObject::connect(this->OpenClose, SIGNAL( clicked(bool)), this, SLOT(on_OpenClose_Clicked()));
    QObject::connect(this->SetUart,   SIGNAL( clicked(bool)), this, SLOT(on_SetUart_clicked()));
    QObject::connect(this->ResetUart, SIGNAL( clicked(bool)), this, SLOT(on_ResetUart_clicked()));

}


void QGroupUartConfig::on_SetUart_clicked()
{
    qDebug()<<"SetUart clicked";
    setvalue();
}

void QGroupUartConfig::on_ResetUart_clicked()
{
    qDebug()<<"ResetUart clicked";
   // this->uart->load_default();
    refresh();
}

void QGroupUartConfig::on_OpenClose_Clicked(){
    qDebug("open close uart button clicked, current status is %d",this->uart->is_opened);

    if(this->uart->is_opened)
    {
        if(uart->close())
            OpenClose->setText(QApplication::translate("MainWindow", "Click to Open", nullptr));

    }
    else{
        if(uart->open())
            OpenClose->setText(QApplication::translate("MainWindow", "Click to Close", nullptr));
    }

}

void QGroupUartConfig::bind_uart(UART * uart){
    this->uart=uart;
    this->uart_paritybit->bind_uart(uart);
    this->uart_baud->bind_uart(uart);
    this->uart_databits->bind_uart(uart);
    this->uart_flowcontrol->bind_uart(uart);
    this->uart_port->bind_uart(uart);
    this->uart_stopbits->bind_uart(uart);
}
void QGroupUartConfig::refresh(){
    this->uart_paritybit->refresh();
    this->uart_baud->refresh();
    this->uart_databits->refresh();
    this->uart_flowcontrol->refresh();
    this->uart_port->refresh();
    this->uart_stopbits->refresh();
}
void QGroupUartConfig::setvalue(){
    this->uart_paritybit->setvalue();
    this->uart_baud->setvalue();
    this->uart_databits->setvalue();
    this->uart_flowcontrol->setvalue();
    this->uart_port->setvalue();
    this->uart_stopbits->setvalue();
}











