#include "QTabBoard.h"
#include <QGroupUartConfig.h>

QTabBoard::QTabBoard():QTabWidget()
{

    // tab_run_board[ii] = new QWidget();
    this->setObjectName(QStringLiteral("tab_run"));
    // sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);

    /////////////////////////////
    this->setObjectName(QStringLiteral("tab_test_cmd"));

    int x_off   = 680;
    int label_x = 60;
    int label_y = 25;


    int x_inc = 10;

    // int line_x = 35;
    // int line_y = 25;
    // cmd
    label_cmd = new QLabel(this);
    label_cmd->setObjectName(QStringLiteral("label_cmd"));
    label_cmd->setGeometry(QRect(x_off, 30, label_x, label_y));
    sizePolicy.setHeightForWidth(label_cmd->sizePolicy().hasHeightForWidth());
    label_cmd->setSizePolicy(sizePolicy);
    this->label_cmd->setText(QApplication::translate("MainWindow", "命令", nullptr));

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


    uart_cmd_cmd->setItemText(0, QApplication::translate("MainWindow", "开始测温", nullptr));
    uart_cmd_cmd->setItemText(1, QApplication::translate("MainWindow", "读取温度", nullptr));
    uart_cmd_cmd->setItemText(2, QApplication::translate("MainWindow", "读取参考芯片温度", nullptr));
    uart_cmd_cmd->setItemText(3, QApplication::translate("MainWindow", "写入配置参数", nullptr));
    uart_cmd_cmd->setItemText(4, QApplication::translate("MainWindow", "读取romcode", nullptr));
    uart_cmd_cmd->setItemText(5, QApplication::translate("MainWindow", "设置系数", nullptr));

    // sel
    label_sel = new QLabel(this);
    label_sel->setObjectName(QStringLiteral("label_sel"));
    label_sel->setGeometry(QRect(x_off, 90, label_x, label_y));
    sizePolicy.setHeightForWidth(label_sel->sizePolicy().hasHeightForWidth());
    label_sel->setSizePolicy(sizePolicy);
    this->label_sel->setText(QApplication::translate("MainWindow", "选取范围", nullptr));

    uart_cmd_sel = new QComboBox(this);
    uart_cmd_sel->setObjectName(QStringLiteral("uart_cmd_sel"));
    uart_cmd_sel->setGeometry(QRect(x_off, 120, 220, 25));
    sizePolicy.setHeightForWidth(uart_cmd_sel->sizePolicy().hasHeightForWidth());
    uart_cmd_sel->setSizePolicy(sizePolicy);

    uart_cmd_sel->addItem(QString());
    uart_cmd_sel->addItem(QString());
    uart_cmd_sel->addItem(QString());
   // uart_cmd_sel->addItem(QString());
 //   uart_cmd_sel->addItem(QString());

    uart_cmd_sel->setItemText(0, QApplication::translate("MainWindow", "整张母板", nullptr));
    uart_cmd_sel->setItemText(1, QApplication::translate("MainWindow", "子板", nullptr));
    //uart_cmd_sel->setItemText(2, QApplication::translate("MainWindow", "行", nullptr));
    //uart_cmd_sel->setItemText(3, QApplication::translate("MainWindow", "列", nullptr));
    uart_cmd_sel->setItemText(2, QApplication::translate("MainWindow", "单颗", nullptr));

    // pos board
    label_board_x = new QLabel(this);
    label_board_x->setObjectName(QStringLiteral("label_board_x"));
    label_board_x->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 0, 150, label_x, label_y));
    sizePolicy.setHeightForWidth(label_board_x->sizePolicy().hasHeightForWidth());
    label_board_x->setSizePolicy(sizePolicy);
    this->label_board_x->setText(QApplication::translate("MainWindow", "子板X坐标", nullptr));


    label_board_y = new QLabel(this);
    label_board_y->setObjectName(QStringLiteral("label_board_y"));
    label_board_y->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 1, 150, label_x, label_y));
    sizePolicy.setHeightForWidth(label_board_y->sizePolicy().hasHeightForWidth());
    label_board_y->setSizePolicy(sizePolicy);
    this->label_board_y->setText(QApplication::translate("MainWindow", "子板Y坐标", nullptr));



    label_row = new QLabel(this);
    label_row->setObjectName(QStringLiteral("label_row"));
    label_row->setGeometry(QRect(x_off + (label_x + x_inc*2) * 2, 150, label_x, label_y));
    sizePolicy.setHeightForWidth(label_row->sizePolicy().hasHeightForWidth());
    label_row->setSizePolicy(sizePolicy);
    this->label_row->setText(QApplication::translate("MainWindow", "行", nullptr));


    label_col = new QLabel(this);
    label_col->setObjectName(QStringLiteral("label_col"));
    label_col->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 3, 150, label_x, label_y));
    sizePolicy.setHeightForWidth(label_col->sizePolicy().hasHeightForWidth());
    label_col->setSizePolicy(sizePolicy);
    this->label_col->setText(QApplication::translate("MainWindow", "列", nullptr));


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
    RunCmd->setText(QApplication::translate("MainWindow", "执行命令", nullptr));
    RunCmd->setObjectName(QStringLiteral("RunCmd"));

    qgroup_uart_conf = new QGroupUartConfig(4,this);
 //   qgroup_uart_conf->setGeometry();
    qgroup_uart_conf->setTitle(QApplication::translate("MainWindow", "uart设置", nullptr));

    RunAll= new QPushButton(this);
    RunAll->setGeometry(QRect(x_off, 400, 220, 50));
    sizePolicy.setHeightForWidth(RunAll->sizePolicy().hasHeightForWidth());
    RunAll->setSizePolicy(sizePolicy);
    RunAll->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250\346\265\213\350\257\225", nullptr));
    RunAll->setObjectName(QStringLiteral("RunAll"));
    // Text browser
    TextWindow = new QTextBrowser(this);
    TextWindow->setGeometry(QRect(10, 480, 1300, 170));
    sizePolicy.setHeightForWidth(TextWindow->sizePolicy().hasHeightForWidth());
    TextWindow->setObjectName(QStringLiteral("TextWindow"));


    pixmap=new QPixmap(400,400);
// signals and slots
   QObject::connect(this->RunCmd,SIGNAL(clicked()),this,SLOT(on_RunCmd_clicked()),Qt::UniqueConnection);

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

void	QTabBoard::paintEvent(QPaintEvent *event)
{

}
void QTabBoard::uart_response_handler()
{

        QByteArray arr =     this->qgroup_uart_conf->uart->serial->readAll();
        QString string;
        char *ch;//不要定义成ch[n];
        ch = arr.data();
        string = QString(arr);

         this->TextWindow->append("update text");
        for (int i =0; i<arr.size();i++)
                qInfo("0x%x\n",ch[i]);
}

void QTabBoard::on_RunCmd_clicked()
{
    qInfo()<<"run_cmd clicked";
    this->TextWindow->append("Run Command with:");

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
    bool    cmd_valid;

    cmd_valid = TRUE;
    qs_row          = this->uart_cmd_pos_row->text();
    qs_col          = this->uart_cmd_pos_col->text();
    qs_board_x      = this->uart_cmd_pos_board_x->text();
    qs_board_y      = this->uart_cmd_pos_board_y->text();

    qs_payload      = this->uart_cmd_payload->text();

    uart_cmd_cmd    = this->uart_cmd_cmd->currentIndex();
    uart_cmd_sel    = this->uart_cmd_sel->currentIndex();

    QByteArray ba   = qs_payload.toLatin1();
    unsigned char *payload = (unsigned char *)ba.data();
    int payload_len = ba.size();
     QString str;
    // check for valid
    if(uart_cmd_sel == 2){ //individual
        qInfo()<<"run_cmd clicked";

        this->TextWindow->append(str.sprintf("\tIndividual Selected"));
        std::string current_qs_row = qs_row.toLocal8Bit().constData();
        qInfo()<<"run_cmd clicked222";

        if(isNum(current_qs_row)){
            qInfo()<<"run_cmd clicked333";
            uart_cur_row = stoi(current_qs_row);
            qInfo()<<"run_cmd clicke4444";

            this->TextWindow->append(str.sprintf("\tSelect row %d", uart_cur_row));
            qInfo()<<"run_cmd clicke5555";
            qInfo("\tSelect row %d", uart_cur_row);
        }else{
              qInfo()<<"run_cmd clicked444";
              this->TextWindow->append(str.sprintf("\tSelect row wrong"));
              cmd_valid = FALSE;
        }
        qInfo()<<"run_cmd clicked111";

        if(isNum( qs_col.toLocal8Bit().constData())){
            uart_cur_col = stoi( qs_col.toLocal8Bit().constData());
            this->TextWindow->append(str.sprintf("\tSelect col %d", uart_cur_col));
            qInfo("Select col %d", uart_cur_col);
        }else{
            this->TextWindow->append(str.sprintf("\tSelect row wrong"));
            qInfo("Select col wrong");
            cmd_valid = FALSE;

        }

        std::string current_qs_board_x = qs_board_x.toLocal8Bit().constData();
        if(isNum(current_qs_board_x)){
            uart_cur_board_x = stoi(current_qs_board_x);
            qInfo("Select col %d", uart_cur_board_x);
            this->TextWindow->append(str.sprintf("\tSelect boardx : %d", uart_cur_board_x));
        }else{
            this->TextWindow->append(str.sprintf("\tSelect boardx Wrong"));
            cmd_valid = FALSE;
            qInfo("Select BoardX wrong");
            cmd_valid = FALSE;

        }
        std::string current_qs_board_y = qs_board_y.toLocal8Bit().constData();
        if(isNum(current_qs_board_y)){
            uart_cur_board_y = stoi(current_qs_board_y);
            qInfo("Select col %d", uart_cur_board_y);
            this->TextWindow->append(str.sprintf("\tSelect boardy : %d", uart_cur_board_y));

        }else{
            QMessageBox msgBox;
            qInfo("Select BoardY wrong");
            this->TextWindow->append(str.sprintf("\tSelect boardy Wrong"));
            cmd_valid = FALSE;

        }
    }
    else if(uart_cmd_sel == 1){ //board
        std::string current_qs_board_x = qs_board_x.toLocal8Bit().constData();
        if(isNum(current_qs_board_x)){
            uart_cur_board_x = stoi(current_qs_board_x);
            qInfo("Select col %d", uart_cur_board_x);
        }else{
            qInfo("Select BoardX wrong");
            cmd_valid = FALSE;
        }
        std::string current_qs_board_y = qs_board_y.toLocal8Bit().constData();
        if(isNum(current_qs_board_y)){
            uart_cur_board_y = stoi(current_qs_board_y);
            qInfo("Select col %d", uart_cur_board_y);
        }else{
            qInfo("Select BoardY wrong");
            cmd_valid = FALSE;
        }
        uart_cur_row = 0;
        uart_cur_col = 0;
    }
    else{   // mother board
        uart_cur_board_x = 0;
        uart_cur_board_y = 0;

        uart_cur_row = 0;
        uart_cur_col = 0;
    }


    if(cmd_valid){
        this->TextWindow->append(str.sprintf("\tExecute cmd"));
        qInfo("command valid.");
        this->TextWindow->append(str.sprintf("\tcommand valid, I am here 1"));
        emit uart_cmd_clicked(uart_cmd_sel, uart_cmd_cmd,uart_cur_board_x,uart_cur_board_y,uart_cur_row,uart_cur_col,payload,payload_len);
    }
    else{
         qInfo("Command not valid.Operation aborted");
         qInfo("Command not valid.Operation aborted");
         this->TextWindow->append(str.sprintf("\tCommand not valid. Operation aborted"));
    }
}
