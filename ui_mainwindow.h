/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#define QT_NO_DEBUG_OUTPUT

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <Qt>

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLCDNumber>
#include <QPalette>
#include <QTextBrowser>
#include <QGroupUartConfig.h>
#include <QTabOven.h>
#include <QTabBoard.h>


#include <myglobal.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;

    // tab_setup_uart and children
    QWidget *tab_setup_uart;
    QGroupUartConfig * qgroup_uart_conf[5];

    // tab_run_board and children
    QTabBoard *tab_run_board[4];

    // tab set_oven and children
    QTabOven *tab_set_oven;


    // tab test_uart and children
    QWidget *tab_test_uart;
    QPushButton *TestUart;
    QPushButton *TextUartResponse_Clear;
    QTextBrowser   * TextUartResponse;

    //  QToolBar *mainToolBar;
    QSizePolicy sizePolicy;




    void setupUi(QMainWindow *MainWindow)
    {
        // Mainwindow
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MY18B20_FT"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1024, 612);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1024, 612));
        MainWindow->setMaximumSize(QSize(1024, 612));
        //   qDebug("I am here 111");

        //centralWidget
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(1024, 600));
        centralWidget->setMaximumSize(QSize(1024, 600));
        //tabWidget
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(0, 0, 1024, 600));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        //tab_setup_uart
        tab_setup_uart = new QWidget();
        tab_setup_uart->setObjectName(QStringLiteral("tab_setup_uart"));
        sizePolicy.setHeightForWidth(tab_setup_uart->sizePolicy().hasHeightForWidth());
        tab_setup_uart->setSizePolicy(sizePolicy);
        qgroup_uart_conf[0] = new QGroupUartConfig(0,tab_setup_uart);
        qgroup_uart_conf[1] = new QGroupUartConfig(1,tab_setup_uart);
        qgroup_uart_conf[2] = new QGroupUartConfig(2,tab_setup_uart);
        qgroup_uart_conf[3] = new QGroupUartConfig(3,tab_setup_uart);
        qgroup_uart_conf[4] = new QGroupUartConfig(4,tab_setup_uart);

        tabWidget->addTab(tab_setup_uart, QString());

        //    qDebug("I am here 222");

        // tab_run
        for (int ii = 0; ii<4; ii++)
        {
            tab_run_board[ii] = new(QTabBoard);
            tabWidget->addTab(tab_run_board[ii], QString());


        }

        //    qDebug("I am here 444");

        // set oven
        tab_set_oven = new QTabOven();
        tab_set_oven->setObjectName(QStringLiteral("tab_set_oven"));
        sizePolicy.setHeightForWidth(tab_set_oven->sizePolicy().hasHeightForWidth());
        tab_set_oven->setSizePolicy(sizePolicy);
        tabWidget->addTab(tab_set_oven, QString());


        //
        tab_test_uart = new QWidget();
        tab_test_uart->setObjectName(QStringLiteral("tab_test_uart"));
        sizePolicy.setHeightForWidth(tab_test_uart->sizePolicy().hasHeightForWidth());
        tab_test_uart->setSizePolicy(sizePolicy);

        TestUart = new QPushButton(tab_test_uart);
        TestUart->setGeometry(QRect(590, 50, 150, 23));
        sizePolicy.setHeightForWidth(TestUart->sizePolicy().hasHeightForWidth());
        TestUart->setSizePolicy(sizePolicy);



        TextUartResponse_Clear = new QPushButton(tab_test_uart);
        TextUartResponse_Clear->setGeometry(QRect(590, 100, 150, 23));
        sizePolicy.setHeightForWidth(TextUartResponse_Clear->sizePolicy().hasHeightForWidth());
        TextUartResponse_Clear->setSizePolicy(sizePolicy);

        TextUartResponse = new QTextBrowser(tab_test_uart);
        TextUartResponse->setGeometry(QRect(100, 50, 150, 100));
        sizePolicy.setHeightForWidth(TextUartResponse->sizePolicy().hasHeightForWidth());
        TextUartResponse->setSizePolicy(sizePolicy);

        TestUart->setObjectName(QStringLiteral("TestUart"));

        TextUartResponse_Clear->setObjectName(QStringLiteral("TextUartResponse_Clear"));

        TextUartResponse->setObjectName(QStringLiteral("TextUartResponse"));

        //test cmd
        //   tab_test_cmd=new QTabTestCMD();
        //   tabWidget->addTab(tab_test_cmd, QString());

        //MainWindow
        MainWindow->setCentralWidget(centralWidget);
        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
        QMetaObject::connectSlotsByName(tab_set_oven);
        QMetaObject::connectSlotsByName(tab_run_board[0]);
        QMetaObject::connectSlotsByName(tab_run_board[1]);
        QMetaObject::connectSlotsByName(tab_run_board[2]);
        QMetaObject::connectSlotsByName(tab_run_board[3]);



        //        QMetaObject::connectSlotsByName(qgroup_uart_conf[0]);
        //        QMetaObject::connectSlotsByName(qgroup_uart_conf[1]);
        //        QMetaObject::connectSlotsByName(qgroup_uart_conf[2]);
        //        QMetaObject::connectSlotsByName(qgroup_uart_conf[3]);
        //        QMetaObject::connectSlotsByName(qgroup_uart_conf[4]);


    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MY18B20_FT", "MY18B20_FT", nullptr));


        qgroup_uart_conf[0]->setTitle(QApplication::translate("MainWindow", "mcu0", nullptr));
        qgroup_uart_conf[1]->setTitle(QApplication::translate("MainWindow", "mcu1", nullptr));
        qgroup_uart_conf[2]->setTitle(QApplication::translate("MainWindow", "mcu2", nullptr));
        qgroup_uart_conf[3]->setTitle(QApplication::translate("MainWindow", "mcu3", nullptr));
        qgroup_uart_conf[4]->setTitle(QApplication::translate("MainWindow", "\346\270\251\347\256\261", nullptr));

        //  qDebug("I am here 100");

        tabWidget->setTabText(tabWidget->indexOf(tab_setup_uart), QApplication::translate("MainWindow", "UART", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_test_uart), QApplication::translate("MainWindow", "Test UART", nullptr));

        TestUart->setText(QApplication::translate("MainWindow", "Test Uart", nullptr));

        TextUartResponse_Clear->setText(QApplication::translate("MainWindow", "TextUartResponse_Clear", nullptr));

        TextUartResponse->setText(QApplication::translate("MainWindow", "", nullptr));

        // tabWidget->setTabText(tabWidget->indexOf(tab_test_cmd), QApplication::translate("MainWindow", "Test CMD", nullptr));


        tabWidget->setTabText(tabWidget->indexOf(tab_run_board[0]), QApplication::translate("MainWindow", "RUN0", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_run_board[1]), QApplication::translate("MainWindow", "RUN1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_run_board[2]), QApplication::translate("MainWindow", "RUN2", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_run_board[3]), QApplication::translate("MainWindow", "RUN3", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_set_oven), QApplication::translate("MainWindow", "OVEN", nullptr));


    } // retranslateUi

};

namespace Ui {
class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
