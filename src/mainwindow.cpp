#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QGraphicsPixmapItem>
#include "myAgent.h"
#include <qDebug>
#include "myglobal.h"
#include "QSignalMapper"
#include <atlstr.h>
#include <mainwindow.h>


#include <myglobal.h>

void MainWindow::refresh_result_map_paint(int mboard_id)
{
    const static int x_off = 30;
    const static int y_off = 15;
    QPainter painter;

    // QPainter *painter = new QPainter(this->ui->tab_run_board[mboard_id]);
    painter.begin(this->ui->tab_run_board[mboard_id]);

    for (int ii = 0; ii <NUM_DAUGHTER_BOARDS_X; ii ++){
        for (int jj = 0; jj <NUM_DAUGHTER_BOARDS_Y; jj ++){
            for(int kk = 0; kk <NUM_CHIPS_X; kk ++){
                for (int ll = 0; ll <NUM_CHIPS_Y; ll++){
                    CHIPSTATE chip_state;
                    if(cur_agent->mcu_uart_agent[mboard_id]->map.get_chip_state(ii,jj,kk,ll, chip_state)) {
                        switch(chip_state){
                        case GOOD: painter.drawImage(x_off+ii*140+kk*12,y_off+jj*140+ll*12,*image_good); break;
                        case BAD : painter.drawImage(x_off+ii*140+kk*12,y_off+jj*140+ll*12,*image_bad ); break;
                        case UNTESTED: painter.drawImage(x_off+ii*140+kk*12,y_off+jj*140+ll*12,*image_none ); break;
                        default  : painter.drawImage(x_off+ii*140+kk*12,y_off+jj*140+ll*12,*image_none); break;
                        }
                    }
                    else{
                        painter.drawImage(ii*140+kk*12,jj*140 + ll*12,*image_none);
                    }
                }
            }
        }
    }
    painter.end();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug()<<"enter MainWindow constructor";
    cur_agent = new (myAgent);

    ui->setupUi(this);

    //  cur_agent->moveToThread(&agent_thread);


    this->ui->qgroup_uart_conf[0]->bind_uart(cur_agent->mcu_uart_agent[0]->mcu_uart);
    this->ui->qgroup_uart_conf[1]->bind_uart(cur_agent->mcu_uart_agent[1]->mcu_uart);
    this->ui->qgroup_uart_conf[2]->bind_uart(cur_agent->mcu_uart_agent[2]->mcu_uart);
    this->ui->qgroup_uart_conf[3]->bind_uart(cur_agent->mcu_uart_agent[3]->mcu_uart);
    this->ui->qgroup_uart_conf[4]->bind_uart(cur_agent->oven_uart);


    this->ui->tab_run_board[0]->installEventFilter(this);
    this->ui->tab_run_board[1]->installEventFilter(this);
    this->ui->tab_run_board[2]->installEventFilter(this);
    this->ui->tab_run_board[3]->installEventFilter(this);

    for (int ii = 0; ii < NUM_MOTHER_BOARDS; ii++){

        QObject::connect(ui->tab_run_board[ii]->RunAll, SIGNAL(pressed()), cur_agent->mcu_uart_agent[ii], SLOT(run_all()),Qt::QueuedConnection);


        QObject::connect(ui->tab_run_board[ii], SIGNAL(execute_uart_cmd(int,int,int,int,int,int,Byte*,int)), cur_agent->mcu_uart_agent[ii], SLOT(execute_uart_cmd(int,int,int,int,int,int,Byte*,int)),Qt::QueuedConnection);

        QObject::connect(cur_agent->mcu_uart_agent[ii], SIGNAL(run_all_done()), this->ui->tab_run_board[ii], SLOT(repaint()),Qt::QueuedConnection);

        QObject::connect(cur_agent->mcu_uart_agent[ii], SIGNAL(s_errorbox(QString)), this, SLOT(errorbox(QString)),Qt::QueuedConnection);


        QObject::connect(cur_agent->mcu_uart_agent[ii], SIGNAL(set_oven_cmd(int)),    cur_agent, SLOT(set_oven_cmd(int)));
        QObject::connect(cur_agent->mcu_uart_agent[ii], SIGNAL(set_oven_temp(float)), cur_agent, SLOT(set_oven_temp(float)));
        QObject::connect(cur_agent->mcu_uart_agent[ii], SIGNAL(get_oven_temp2(double&)), cur_agent, SLOT(get_oven_temp2(double&)));
    }
    QObject::connect(cur_agent, SIGNAL(refresh_oven_temp()), this, SLOT(update_display()));

    //QObject::connect(ui->tab_run_board[0]->RunCmd, SIGNAL(clicked()), this, SLOT(on_RunCmd_clicked()));

    // for oven control tab
    QObject::connect(ui->tab_set_oven, SIGNAL(set_oven_cmd(int)),    cur_agent, SLOT(set_oven_cmd(int)));
    QObject::connect(ui->tab_set_oven, SIGNAL(set_oven_temp(float)), cur_agent, SLOT(set_oven_temp(float)));
    QObject::connect(ui->tab_set_oven, SIGNAL(get_oven_temp2(double&)), cur_agent, SLOT(get_oven_temp2(double&)));
    //QObject::connect(ui->tab_set_oven, SIGNAL(run_all_board()), cur_agent, SLOT(run_all_board()));
    QObject::connect(ui->tab_set_oven, SIGNAL(run_all_board(float , float , float, long int , long int , long int , int , int)), cur_agent, SLOT(run_all_board(float , float , float, long int , long int , long int , int , int)));
    QObject::connect(ui->tab_set_oven, SIGNAL(set_parameters_all_board(int)), cur_agent, SLOT(set_parameters_all_board(int)));
    QObject::connect(ui->tab_set_oven, SIGNAL(check_parameters_all_board(int)), cur_agent, SLOT(check_parameters_all_board(int)));
    QObject::connect(ui->tab_set_oven, SIGNAL(auto_check_temp_all_board(float , long int , int )), cur_agent, SLOT(auto_check_temp_all_board(float , long int , int )));
    QObject::connect(ui->tab_set_oven, SIGNAL(manual_check_temp_all_board(int)), cur_agent, SLOT(manual_check_temp_all_board(int)));

    //  agent_thread.start();

    //    data2index_map[8] = 0;
    //    data2index_map[7] = 1;
    //    data2index_map[6] = 2;
    //    data2index_map[5] = 3;
    image_good = new QImage(10,10,QImage::Format_RGB32);
    image_bad = new QImage(10,10,QImage::Format_RGB32);
    image_none = new QImage(10,10,QImage::Format_RGB32);
    image_none->fill(qRgb(100, 100, 100));
    image_good->fill(qRgb(0, 255, 0));
    image_bad->fill(qRgb(255,0, 0));

}

MainWindow::~MainWindow()
{

    delete image_bad;
    delete image_good;
    delete image_none;
    //    agent_thread.terminate();
    //    agent_thread.wait();
    //    agent_thread.quit();
    delete ui;
}


bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    for(int i = 0; i<4; i++){
        if ((watched == this->ui->tab_run_board[i] && (event->type() == QEvent::Paint ))){
            //    qDebug("refresh result map paint");
            refresh_result_map_paint(i);
        }
    }
    return false;
}


//void MainWindow::on_SetTemp_clicked()
//{
//    qDebug()<<"SetTemp clicked";

//    QString qs;
//    float temp ;

//    // Either this if you use UTF-8 anywhere
//    qs=this->ui->tab_set_oven->TextTempInput->text();
//    // std::string utf8_text = qs.toUtf8().constData();

//    // or this if you're on Windows :-)
//    std::string current_locale_text = qs.toLocal8Bit().constData();
//    // if(current_locale_text.empty()){
//    if(isNum(current_locale_text)){
//        temp = stof(current_locale_text);
//        qDebug("GUI try to set temperature to %f", temp);
//        cur_agent->set_temp(temp);
//    }else{
//        msgBox.setWindowTitle("Wrong");
//        msgBox.setText("Temperature Wrong!");
//        //   msgBox.setInformativeText("Temperature Wrong!");
//        //     msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
//        msgBox.setStandardButtons(QMessageBox::Ok);

//        //  msgBox.setDefaultButton(QMessageBox::Save);
//        //int ret = msgBox.exec();
//        msgBox.exec();
//        qDebug("GUI try to set an invalid tempeture, ignored");
//    }
//}

//void MainWindow::on_TestUart_clicked()
//{
//    qDebug()<<"TestUart clicked";
//    Byte b[256];

//    if(cur_agent->testuart(b)==FALSE)
//    {
//        return;
//    }
//    qDebug("get char %c%c%c%c",b[0],b[1],b[2],b[3]);
//    qDebug("get char hex %02x%02x%02x%02x",b[0],b[1],b[2],b[3]);
//    for (int ii =0; ii < 256; ii++){
//        qs.append(b[ii]);

//    }
//    this->ui->TextUartResponse->clear();
//    //   this->ui->TextUartResponse->setText(qs);
//    this->ui->TextUartResponse->append(qs);
//}

//void MainWindow::on_TextUartResponse_Clear_clicked()
//{
//    qs.clear();
//    this->ui->TextUartResponse->clear();

//}

void MainWindow::update_display()
{
    this->ui->tab_set_oven->lcdNumber->display(this->cur_agent->get_oven_temp());
}

void MainWindow::errorbox(QString ErrorMessage)
{

    msgBox = new(QMessageBox);
    msgBox->setWindowTitle("Wrong");
    msgBox->setText(ErrorMessage);
    //        //   msgBox.setInformativeText("Temperature Wrong!");
    //        //     msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox->setStandardButtons(QMessageBox::Ok);

    //        //  msgBox.setDefaultButton(QMessageBox::Save);
    //        //int ret = msgBox.exec();
    msgBox->exec();

}
