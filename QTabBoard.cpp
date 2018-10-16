#include "QTabBoard.h"

QTabBoard::QTabBoard():QTabWidget()
{
   // tab_run_board[ii] = new QWidget();
    this->setObjectName(QStringLiteral("tab_run"));
  //  sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);

    /////////////////////////////
    this->setObjectName(QStringLiteral("tab_test_cmd"));

    int x_off = 680;
    int label_x = 40;
    int label_y = 25;


    int x_inc = 10;

    int line_x = 35;
    int line_y = 25;

    // cmd
    label_cmd = new QLabel(this);
    label_cmd->setObjectName(QStringLiteral("label_cmd"));
    label_cmd->setGeometry(QRect(x_off, 30, label_x, label_y));
    sizePolicy.setHeightForWidth(label_cmd->sizePolicy().hasHeightForWidth());
    label_cmd->setSizePolicy(sizePolicy);
    this->label_cmd->setText(QApplication::translate("MainWindow", "cmd", nullptr));

    uart_cmd_cmd = new QComboBox(this);
    uart_cmd_cmd->setObjectName(QStringLiteral("uart_cmd_cmd"));
    uart_cmd_cmd->setGeometry(QRect(x_off, 60, 220, 25));
    sizePolicy.setHeightForWidth(uart_cmd_cmd->sizePolicy().hasHeightForWidth());
    uart_cmd_cmd->setSizePolicy(sizePolicy);

    uart_cmd_cmd->addItem(QString());
    uart_cmd_cmd->addItem(QString());
    uart_cmd_cmd->addItem(QString());
    uart_cmd_cmd->addItem(QString());
    uart_cmd_cmd->addItem(QString());
    uart_cmd_cmd->addItem(QString());


    uart_cmd_cmd->setItemText(0, QApplication::translate("MainWindow", "doconvert", nullptr));
    uart_cmd_cmd->setItemText(1, QApplication::translate("MainWindow", "gettemp", nullptr));
    uart_cmd_cmd->setItemText(2, QApplication::translate("MainWindow", "gettemp_ref", nullptr));
    uart_cmd_cmd->setItemText(3, QApplication::translate("MainWindow", "writeparameters", nullptr));
    uart_cmd_cmd->setItemText(4, QApplication::translate("MainWindow", "getromcode", nullptr));
    uart_cmd_cmd->setItemText(5, QApplication::translate("MainWindow", "setcoeff", nullptr));

    // sel
    label_sel = new QLabel(this);
    label_sel->setObjectName(QStringLiteral("label_sel"));
    label_sel->setGeometry(QRect(x_off, 90, label_x, label_y));
    sizePolicy.setHeightForWidth(label_sel->sizePolicy().hasHeightForWidth());
    label_sel->setSizePolicy(sizePolicy);
    this->label_sel->setText(QApplication::translate("MainWindow", "sel", nullptr));

    uart_cmd_sel = new QComboBox(this);
    uart_cmd_sel->setObjectName(QStringLiteral("uart_cmd_sel"));
    uart_cmd_sel->setGeometry(QRect(x_off, 120, 220, 25));
    sizePolicy.setHeightForWidth(uart_cmd_sel->sizePolicy().hasHeightForWidth());
    uart_cmd_sel->setSizePolicy(sizePolicy);

    uart_cmd_sel->addItem(QString());
    uart_cmd_sel->addItem(QString());
    uart_cmd_sel->addItem(QString());
    uart_cmd_sel->addItem(QString());
    uart_cmd_sel->addItem(QString());

    uart_cmd_sel->setItemText(0, QApplication::translate("MainWindow", "all", nullptr));
    uart_cmd_sel->setItemText(1, QApplication::translate("MainWindow", "board", nullptr));
    uart_cmd_sel->setItemText(2, QApplication::translate("MainWindow", "row", nullptr));
    uart_cmd_sel->setItemText(3, QApplication::translate("MainWindow", "col", nullptr));
    uart_cmd_sel->setItemText(4, QApplication::translate("MainWindow", "individual", nullptr));

    // pos board
    label_board_x = new QLabel(this);
    label_board_x->setObjectName(QStringLiteral("label_board_x"));
    label_board_x->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 0, 150, label_x, label_y));
    sizePolicy.setHeightForWidth(label_board_x->sizePolicy().hasHeightForWidth());
    label_board_x->setSizePolicy(sizePolicy);
    this->label_board_x->setText(QApplication::translate("MainWindow", "boardx", nullptr));


    label_board_y = new QLabel(this);
    label_board_y->setObjectName(QStringLiteral("label_board_y"));
    label_board_y->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 1, 150, label_x, label_y));
    sizePolicy.setHeightForWidth(label_board_y->sizePolicy().hasHeightForWidth());
    label_board_y->setSizePolicy(sizePolicy);
    this->label_board_y->setText(QApplication::translate("MainWindow", "boardy", nullptr));



    label_row = new QLabel(this);
    label_row->setObjectName(QStringLiteral("label_row"));
    label_row->setGeometry(QRect(x_off + (label_x + x_inc*2) * 2, 150, label_x, label_y));
    sizePolicy.setHeightForWidth(label_row->sizePolicy().hasHeightForWidth());
    label_row->setSizePolicy(sizePolicy);
    this->label_row->setText(QApplication::translate("MainWindow", "row", nullptr));


    label_col = new QLabel(this);
    label_col->setObjectName(QStringLiteral("label_col"));
    label_col->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 3, 150, label_x, label_y));
    sizePolicy.setHeightForWidth(label_col->sizePolicy().hasHeightForWidth());
    label_col->setSizePolicy(sizePolicy);
    this->label_col->setText(QApplication::translate("MainWindow", "col", nullptr));


    uart_cmd_pos_board_x=new QLineEdit(this);
    uart_cmd_pos_board_x->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 0, 180, label_x, label_y));
    sizePolicy.setHeightForWidth(uart_cmd_pos_board_x->sizePolicy().hasHeightForWidth());
    uart_cmd_pos_board_x->setSizePolicy(sizePolicy);


    uart_cmd_pos_board_y=new QLineEdit(this);
    uart_cmd_pos_board_y->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 1, 180, label_x, label_y));
    sizePolicy.setHeightForWidth(uart_cmd_pos_board_y->sizePolicy().hasHeightForWidth());
    uart_cmd_pos_board_y->setSizePolicy(sizePolicy);

    uart_cmd_pos_row=new QLineEdit(this);
    uart_cmd_pos_row->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 2, 180, label_x, label_y));
    sizePolicy.setHeightForWidth(uart_cmd_pos_row->sizePolicy().hasHeightForWidth());
    uart_cmd_pos_row->setSizePolicy(sizePolicy);

    uart_cmd_pos_col=new QLineEdit(this);
    uart_cmd_pos_col->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 3, 180, label_x, label_y));
    sizePolicy.setHeightForWidth(uart_cmd_pos_col->sizePolicy().hasHeightForWidth());
    uart_cmd_pos_col->setSizePolicy(sizePolicy);

    label_payload = new QLabel(this);
    label_payload->setObjectName(QStringLiteral("label_payload"));
    label_payload->setGeometry(QRect(x_off, 210, label_x+20, label_y));
    sizePolicy.setHeightForWidth(label_payload->sizePolicy().hasHeightForWidth());
    label_payload->setSizePolicy(sizePolicy);
    this->label_payload->setText(QApplication::translate("MainWindow", "payload", nullptr));


    uart_cmd_payload=new QLineEdit(this);
    uart_cmd_payload->setGeometry(QRect(x_off, 240, 220, 30));
    sizePolicy.setHeightForWidth(uart_cmd_payload->sizePolicy().hasHeightForWidth());
    uart_cmd_payload->setSizePolicy(sizePolicy);

    uart_cmd_pos_board_x->setObjectName(QStringLiteral("uart_cmd_pos_board_x"));
    uart_cmd_pos_board_y->setObjectName(QStringLiteral("uart_cmd_pos_board_y"));

    uart_cmd_pos_row->setObjectName(QStringLiteral("uart_cmd_pos_row"));
    uart_cmd_pos_col->setObjectName(QStringLiteral("uart_cmd_pos_col"));
    uart_cmd_payload->setObjectName(QStringLiteral("uart_cmd_payload"));


    uart_cmd_payload->setText(QApplication::translate("MainWindow", "", nullptr));
    uart_cmd_pos_row->setText(QApplication::translate("MainWindow", "", nullptr));
    uart_cmd_pos_col->setText(QApplication::translate("MainWindow", "", nullptr));
    uart_cmd_pos_board_x->setText(QApplication::translate("MainWindow", "", nullptr));
    uart_cmd_pos_board_y->setText(QApplication::translate("MainWindow", "", nullptr));



    RunCmd = new QPushButton(this);
    RunCmd->setGeometry(QRect(x_off, 300, 220, 50));
    sizePolicy.setHeightForWidth(RunCmd->sizePolicy().hasHeightForWidth());
    RunCmd->setSizePolicy(sizePolicy);
    RunCmd->setText(QApplication::translate("MainWindow", "RUN CMD", nullptr));
    RunCmd->setObjectName(QStringLiteral("RunCmd"));

    RunAll= new QPushButton(this);
    RunAll->setGeometry(QRect(x_off, 400, 220, 50));
    sizePolicy.setHeightForWidth(RunAll->sizePolicy().hasHeightForWidth());
    RunAll->setSizePolicy(sizePolicy);
    RunAll->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250\346\265\213\350\257\225", nullptr));
    RunAll->setObjectName(QStringLiteral("RunAll"));

    pixmap=new QPixmap(400,400);

    /////
//    QApplication a(argc, argv);

//    QMainWindow *win1 = new QMainWindow();
//    win1->resize(500,500);
//    win1->show();


//    QGraphicsScene *scene = new QGraphicsScene(win1);
//    QGraphicsView view(scene, win1);
//    view.show();
//    view.resize(500,500);

//    QPixmap *pix = new QPixmap(500,500);
//    this->->addPixmap(*pix);

//      QPainter *paint = new QPainter(pix);
//      paint->setPen(*(new QColor(255,34,255,255)));
//      paint->drawRect(15,15,100,100);


}

//QTabBoard():QTabWidget()
void	QTabBoard::paintEvent(QPaintEvent *event)
{

}

void QTabBoard::on_RunCmd_clicked()
{
    qDebug()<<"run_cmd clicked";

    QString qs_row;
    QString qs_col;
    QString qs_board_x;
    QString qs_board_y;

    QString qs_payload;

    uint    uart_cmd_sel;
    uint    uart_cmd_cmd;
    uint    uart_cur_row;
    uint    uart_cur_col;
    uint    uart_cur_board_x;
    uint    uart_cur_board_y;


    qs_row     = this->uart_cmd_pos_row->text();
    qs_col     = this->uart_cmd_pos_col->text();
    qs_board_x   = this->uart_cmd_pos_board_x->text();
    qs_board_y   = this->uart_cmd_pos_board_y->text();

    qs_payload = this->uart_cmd_payload->text();

    uart_cmd_cmd = this->uart_cmd_cmd->currentIndex();
    uart_cmd_sel = this->uart_cmd_sel->currentIndex();

    QByteArray ba = qs_payload.toLatin1();
    unsigned char *payload = (unsigned char *)ba.data();
    int payload_len = ba.size();

    // check for valid
    if(uart_cmd_sel == 4){ //individual
        std::string current_qs_row = qs_row.toLocal8Bit().constData();
        if(isNum(current_qs_row)){
            uart_cur_row = stoi(current_qs_row);
            qDebug("Select row %d", uart_cur_row);
        }else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Wrong");
            msgBox.setText("row Wrong!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            qDebug("Select row wrong");
            return;
        }

        std::string current_qs_col = qs_col.toLocal8Bit().constData();
        if(isNum(current_qs_col)){
            uart_cur_col = stoi(current_qs_col);
            qDebug("Select col %d", uart_cur_col);
        }else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Wrong");
            msgBox.setText("Col Wrong!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            qDebug("Select col wrong");
            return;

        }

        std::string current_qs_board_x = qs_board_x.toLocal8Bit().constData();
        if(isNum(current_qs_board_x)){
            uart_cur_board_x = stoi(current_qs_board_x);
            qDebug("Select col %d", uart_cur_board_x);
        }else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Wrong");
            msgBox.setText("BoardX Wrong!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            qDebug("Select BoardX wrong");
            return;

        }
        std::string current_qs_board_y = qs_board_y.toLocal8Bit().constData();
        if(isNum(current_qs_board_y)){
            uart_cur_board_y = stoi(current_qs_board_y);
            qDebug("Select col %d", uart_cur_board_y);
        }else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Wrong");
            msgBox.setText("BoardY Wrong!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            qDebug("Select BoardY wrong");
            return;

        }
    }
    else if(uart_cmd_sel == 3){ //col
        std::string current_qs_col = qs_col.toLocal8Bit().constData();
        if(isNum(current_qs_col)){
            uart_cur_col = stoi(current_qs_col);
            qDebug("Select col %d", uart_cur_col);
        }else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Wrong");
            msgBox.setText("Col Wrong!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            qDebug("Select col wrong");
            return;

        }

        std::string current_qs_board_x = qs_board_x.toLocal8Bit().constData();
        if(isNum(current_qs_board_x)){
            uart_cur_board_x = stoi(current_qs_board_x);
            qDebug("Select col %d", uart_cur_board_x);
        }else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Wrong");
            msgBox.setText("BoardX Wrong!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            qDebug("Select BoardX wrong");
            return;

        }
        std::string current_qs_board_y = qs_board_y.toLocal8Bit().constData();
        if(isNum(current_qs_board_y)){
            uart_cur_board_y = stoi(current_qs_board_y);
            qDebug("Select col %d", uart_cur_board_y);
        }else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Wrong");
            msgBox.setText("BoardY Wrong!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            qDebug("Select BoardY wrong");
            return;
        }

        uart_cur_row = 0;
    }
    else if(uart_cmd_sel == 2){ //row
        std::string current_qs_row = qs_row.toLocal8Bit().constData();
        if(isNum(current_qs_row)){
            uart_cur_row = stoi(current_qs_row);
            qDebug("Select row %d", uart_cur_row);
        }else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Wrong");
            msgBox.setText("row Wrong!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            qDebug("Select row wrong");
            return;
        }

        std::string current_qs_board_x = qs_board_x.toLocal8Bit().constData();
        if(isNum(current_qs_board_x)){
            uart_cur_board_x = stoi(current_qs_board_x);
            qDebug("Select col %d", uart_cur_board_x);
        }else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Wrong");
            msgBox.setText("BoardX Wrong!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            qDebug("Select BoardX wrong");
            return;

        }
        std::string current_qs_board_y = qs_board_y.toLocal8Bit().constData();
        if(isNum(current_qs_board_y)){
            uart_cur_board_y = stoi(current_qs_board_y);
            qDebug("Select col %d", uart_cur_board_y);
        }else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Wrong");
            msgBox.setText("BoardY Wrong!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            qDebug("Select BoardY wrong");
            return;

        }

        uart_cur_col = 0;
    }
    else if(uart_cmd_sel == 1){ //board
        std::string current_qs_board_x = qs_board_x.toLocal8Bit().constData();
        if(isNum(current_qs_board_x)){
            uart_cur_board_x = stoi(current_qs_board_x);
            qDebug("Select col %d", uart_cur_board_x);
        }else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Wrong");
            msgBox.setText("BoardX Wrong!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            qDebug("Select BoardX wrong");
            return;

        }
        std::string current_qs_board_y = qs_board_y.toLocal8Bit().constData();
        if(isNum(current_qs_board_y)){
            uart_cur_board_y = stoi(current_qs_board_y);
            qDebug("Select col %d", uart_cur_board_y);
        }else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Wrong");
            msgBox.setText("BoardY Wrong!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            qDebug("Select BoardY wrong");
            return;
        }

        uart_cur_row = 0;
        uart_cur_col = 0;
    }
    else{
        uart_cur_board_x = 0;
        uart_cur_board_y = 0;

        uart_cur_row = 0;
        uart_cur_col = 0;
    }
    emit execute_uart_cmd(uart_cmd_sel, uart_cmd_cmd,uart_cur_board_x,uart_cur_board_y,uart_cur_row,uart_cur_col,payload,payload_len);
}

//void QTabBoard::on_AutoTest_clicked()
//{
    //emit run_all();
//}



