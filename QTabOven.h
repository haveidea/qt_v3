#define QT_NO_DEBUG_OUTPUT

#ifndef QTABOVEN_H
#define QTABOVEN_H
#include <QComboBox>
#include <QApplication>
#include "UART.h"
#include <QDebug>
#include <QObject>

#include <Qt>
#include <myglobal.h>

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
#include "QMessageBox"

#include "myAgent.h"

class QTabOven:public QTabWidget
{
    Q_OBJECT
public:
    QTabOven();
    QLineEdit   * TextTempInput;
    QLCDNumber  * lcdNumber;
    QPushButton * SetTemp;
    QPushButton * OvenRun;
    QPushButton * OvenStop;
    //QPushButton * SetTemp7;
    //QPushButton * SetTemp27;
    //QPushButton * SetTemp47;

    QPushButton * SetPara;
    QPushButton * CheckPara;

    QPushButton * AutoCheckTemp;
    QPushButton * ManualCheckTemp;

    QPushButton * GetTemp;
    QPushButton * RunAll;

    QLabel* label_calibre_low;
    QLabel* label_calibre_high;
    QLabel* label_temp_check;

    QLabel* label_calibre_low_period;
    QLabel* label_calibre_high_period;
    QLabel* label_temp_check_period;
    QLabel* label_temp_calibre_serial;
    QLabel* label_mother_board_num;

    QLineEdit * temp_calibre_low;
    QLineEdit * temp_calibre_high;
    QLineEdit * temp_check;

    QLineEdit * time_calibre_low;
    QLineEdit * time_calibre_high;
    QLineEdit * time_check;
    QLineEdit * calibre_serial;
    QLineEdit * mother_board_num;

    //myAgent * myAgen;
    //myAgent * myAgen = new myAgent;

signals:
    void set_oven_temp(float );
    void set_oven_cmd(int);
    //float get_oven_temp();
    void get_oven_temp2(double&);
    //void run_all_board();
    void run_all_board(float , float , float , long int , long int , long int , int , int);
    void set_parameters_all_board(int);
    void check_parameters_all_board(int);
    void auto_check_temp_all_board(float , long int , int );
    void manual_check_temp_all_board(int);

private slots:
    void on_RunAll_clicked();
    void on_GetTemp_clicked();
    void on_SetTemp_clicked();
    //void on_SetTemp7_clicked();
    //void on_SetTemp27_clicked();
    //void on_SetTemp47_clicked();
    void on_SetPara_clicked();
    void on_CheckPara_clicked();

    void on_OvenRun_clicked();
    void on_OvenStop_clicked();
    void on_AutoCheckTemp_clicked();
    void on_ManualCheckTemp_clicked();

    void onTimeOut();


};

#endif // QTABOVEN_H
