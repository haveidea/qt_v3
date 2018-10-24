#define QT_NO_DEBUG_OUTPUT

#ifndef QTABBOARD_H
#define QTABBOARD_H
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
#include <QGraphicsScene>
#include <QTextBrowser>
#include "QGroupUartConfig.h"
#include "mymcuagent.h"


class QTabBoard:public QTabWidget
{
    Q_OBJECT

public:
    QTabBoard();
    QPixmap * pixmap;

    QGroupUartConfig * qgroup_uart_conf;


    QPushButton *RunAll;
    QPushButton *RunCmd;

    QComboBox * uart_cmd_sel;
    QComboBox * uart_cmd_cmd;
    QLineEdit * uart_cmd_pos_board_x;
    QLineEdit * uart_cmd_pos_board_y;

    QLineEdit * uart_cmd_pos_row;
    QLineEdit * uart_cmd_pos_col;
    QLineEdit * uart_cmd_payload;

    QLabel* label_board_x;
    QLabel* label_board_y;

    QLabel* label_col;
    QLabel* label_row;
    QLabel* label_cmd;
    QLabel* label_sel;
    QLabel* label_payload;

   // myMCUAgent mcuagent;


    QTextBrowser* TextWindow;
    void uart_response_handler();


    QSizePolicy sizePolicy;
protected:
    virtual void	paintEvent(QPaintEvent *event);
public slots:
    void on_RunCmd_clicked();
signals:
    void uart_cmd_clicked(int sel, int cmd, int boardx, int boardy, int row,int col,Byte* payload, int payload_len);
    void run_all();
};

#endif // QTABBOARD_H
