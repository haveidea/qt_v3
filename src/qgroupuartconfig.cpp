#include "QGroupUartConfig.h"
#include "myglobal.h"

QGroupUartConfig::~QGroupUartConfig()
{

}

QGroupUartConfig::QGroupUartConfig(int id, QWidget * parent):QGroupBox(parent)
{
    setObjectName(QStringLiteral("uart_setting"));
    setGeometry(QRect(id*180 +260, 70, 250, 400));

    uart_port = new QComboBox_uart_port(this);
    uart_port->setObjectName(QStringLiteral("uart_port"));
    uart_port->setGeometry(QRect(70, 40, 150, 25));
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

    this->label_20->setText(QApplication::translate("MainWindow", "端口", nullptr));
    this->label_16->setText(QApplication::translate("MainWindow", "波特率", nullptr));
    this->label_19->setText(QApplication::translate("MainWindow", "数据位", nullptr));
    this->label_15->setText(QApplication::translate("MainWindow", "流量控制", nullptr));
    this->label_18->setText(QApplication::translate("MainWindow", "校验位", nullptr));
    this->label_21->setText(QApplication::translate("MainWindow", "停止位", nullptr));

   //OpenClose button
    OpenClose = new QPushButton(this);
    OpenClose->setObjectName(QStringLiteral("OpenClose"));
    OpenClose->setGeometry(QRect(25, 350, 100, 30));
    sizePolicy.setHeightForWidth(OpenClose->sizePolicy().hasHeightForWidth());
    OpenClose->setSizePolicy(sizePolicy);

    OpenClose->setText(QApplication::translate("MainWindow", "打开串口", nullptr));

    QObject::connect(this->OpenClose, SIGNAL( clicked(bool)), this, SLOT(on_OpenClose_Clicked()));
}

void QGroupUartConfig::on_OpenClose_Clicked(){
    qDebug("open close uart button clicked, current status is %d",this->uart->is_opened);
    if(this->uart->is_opened)
     {
        if(uart->close()){
            this->uart_baud->setEnabled(true);
            this->uart_paritybit->setEnabled(true);
            this->uart_port->setEnabled(true);
            this->uart_databits->setEnabled(true);
            this->uart_flowcontrol->setEnabled(true);
            this->uart_stopbits->setEnabled(true);
            OpenClose->setText(QApplication::translate("MainWindow", "打开串口", nullptr));
        }
        else{
            qInfo("Close Uart error!!!");
        }

    }
    else{
        this->setvalue();
        if(uart->open()){
            this->uart_baud->setEnabled(false);
            this->uart_paritybit->setEnabled(false);
            this->uart_port->setEnabled(false);
            this->uart_databits->setEnabled(false);
            this->uart_flowcontrol->setEnabled(false);
            this->uart_stopbits->setEnabled(false);
            OpenClose->setText(QApplication::translate("MainWindow", "关闭串口", nullptr));
        }
        else{
            qInfo("Open Uart error!!!");
        }
    }

}

void QGroupUartConfig::bind_uart(UART * uart){
    this->uart=uart;
    this->uart_baud->bind_uart(uart);
    this->uart_paritybit->bind_uart(uart);
    this->uart_databits->bind_uart(uart);
    this->uart_flowcontrol->bind_uart(uart);
    this->uart_port->bind_uart(uart);
    this->uart_stopbits->bind_uart(uart);
}

void QGroupUartConfig::setvalue(){
    this->uart_baud->setvalue();
    this->uart_paritybit->setvalue();
    this->uart_databits->setvalue();
    this->uart_flowcontrol->setvalue();
    this->uart_port->setvalue();
    this->uart_stopbits->setvalue();
}
