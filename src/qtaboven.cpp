#include "QTabOven.h"

QTabOven::QTabOven():QTabWidget()
{
    QSizePolicy sizePolicy;

    this->setObjectName(QStringLiteral("tab_oven"));

    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);

    int x_off = 180;
    int label_x = 40;
    int label_y = 25;


    int x_inc = 10;


    //lcd for temperature
    lcdNumber = new QLCDNumber(this);
    lcdNumber->setGeometry(QRect(400, 450, 170, 71));
    QPalette palette;
    QBrush brush(QColor(85, 0, 255, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Window, brush);
    lcdNumber->setPalette(palette);
    QFont font;
    font.setFamily(QStringLiteral("Adobe Arabic"));
    font.setPointSize(28);
    font.setBold(true);
    font.setWeight(75);
    lcdNumber->setFont(font);
    lcdNumber->setAutoFillBackground(true);
    lcdNumber->setDigitCount(8);
    sizePolicy.setHeightForWidth(lcdNumber->sizePolicy().hasHeightForWidth());
    lcdNumber->setSizePolicy(sizePolicy);



    OvenRun = new QPushButton(this);
    OvenRun->setGeometry(QRect(590, 80, 170, 23));
    sizePolicy.setHeightForWidth(OvenRun->sizePolicy().hasHeightForWidth());
    OvenRun->setSizePolicy(sizePolicy);
    OvenRun->setObjectName(QStringLiteral("OvenRun"));
    OvenRun->setText(QApplication::translate("MainWindow", "Oven Run", nullptr));

    OvenStop = new QPushButton(this);
    OvenStop->setGeometry(QRect(590, 110, 170, 23));
    sizePolicy.setHeightForWidth(OvenStop->sizePolicy().hasHeightForWidth());
    OvenStop->setSizePolicy(sizePolicy);
    OvenStop->setObjectName(QStringLiteral("OvenStop"));
    OvenStop->setText(QApplication::translate("MainWindow", "Oven Stop", nullptr));


//    SetTemp7 = new QPushButton(this);
//    SetTemp7->setGeometry(QRect(590, 140, 150, 23));
//    sizePolicy.setHeightForWidth(SetTemp7->sizePolicy().hasHeightForWidth());
//    SetTemp7->setSizePolicy(sizePolicy);
//    SetTemp7->setObjectName(QStringLiteral("SetTemp7"));
//    SetTemp7->setText(QApplication::translate("MainWindow", "SetTemp7", nullptr));

//    SetTemp27 = new QPushButton(this);
//    SetTemp27->setGeometry(QRect(590, 170, 150, 23));
//    sizePolicy.setHeightForWidth(SetTemp27->sizePolicy().hasHeightForWidth());
//    SetTemp27->setSizePolicy(sizePolicy);
//    SetTemp27->setObjectName(QStringLiteral("SetTemp27"));
//    SetTemp27->setText(QApplication::translate("MainWindow", "SetTemp27", nullptr));

//    SetTemp47 = new QPushButton(this);
//    SetTemp47->setGeometry(QRect(590, 200, 150, 23));
//    sizePolicy.setHeightForWidth(SetTemp47->sizePolicy().hasHeightForWidth());
//    SetTemp47->setSizePolicy(sizePolicy);
//    SetTemp47->setObjectName(QStringLiteral("SetTemp47"));
//    SetTemp47->setText(QApplication::translate("MainWindow", "SetTemp47", nullptr));

    SetPara = new QPushButton(this);
    SetPara->setGeometry(QRect(590, 220, 170, 23));
    sizePolicy.setHeightForWidth(SetPara->sizePolicy().hasHeightForWidth());
    SetPara->setSizePolicy(sizePolicy);
    SetPara->setObjectName(QStringLiteral("SetPara"));
    SetPara->setText(QApplication::translate("MainWindow", "Set Parameters", nullptr));

    CheckPara = new QPushButton(this);
    CheckPara->setGeometry(QRect(590, 250, 170, 23));
    sizePolicy.setHeightForWidth(CheckPara->sizePolicy().hasHeightForWidth());
    CheckPara->setSizePolicy(sizePolicy);
    CheckPara->setObjectName(QStringLiteral("CheckPara"));
    CheckPara->setText(QApplication::translate("MainWindow", "Check Parameters", nullptr));

    AutoCheckTemp = new QPushButton(this);
    AutoCheckTemp->setGeometry(QRect(590, 140, 170, 23));
    sizePolicy.setHeightForWidth(AutoCheckTemp->sizePolicy().hasHeightForWidth());
    AutoCheckTemp->setSizePolicy(sizePolicy);
    AutoCheckTemp->setObjectName(QStringLiteral("AutoCheckTemp"));
    AutoCheckTemp->setText(QApplication::translate("MainWindow", "Auto Check Temp in Oven", nullptr));

    ManualCheckTemp = new QPushButton(this);
    ManualCheckTemp->setGeometry(QRect(590, 170, 170, 23));
    sizePolicy.setHeightForWidth(ManualCheckTemp->sizePolicy().hasHeightForWidth());
    ManualCheckTemp->setSizePolicy(sizePolicy);
    ManualCheckTemp->setObjectName(QStringLiteral("ManualCheckTemp"));
    ManualCheckTemp->setText(QApplication::translate("MainWindow", "Manual Check Temp indoor", nullptr));


    TextTempInput = new QLineEdit(this);
    TextTempInput->setGeometry(QRect(400, 400, 170, 23));
    sizePolicy.setHeightForWidth(TextTempInput->sizePolicy().hasHeightForWidth());
    TextTempInput->setSizePolicy(sizePolicy);
    TextTempInput->setObjectName(QStringLiteral("TextTempInput"));
    TextTempInput->setText(QApplication::translate("MainWindow", "", nullptr));

    SetTemp = new QPushButton(this);
    SetTemp->setGeometry(QRect(590, 400, 170, 23));
    sizePolicy.setHeightForWidth(SetTemp->sizePolicy().hasHeightForWidth());
    SetTemp->setSizePolicy(sizePolicy);
    SetTemp->setObjectName(QStringLiteral("SetTemp"));
    SetTemp->setText(QApplication::translate("MainWindow", "Set Oven Temperature", nullptr));


    GetTemp = new QPushButton(this);
    GetTemp->setGeometry(QRect(590, 450, 170, 23));
    sizePolicy.setHeightForWidth(GetTemp->sizePolicy().hasHeightForWidth());
    GetTemp->setSizePolicy(sizePolicy);
    GetTemp->setObjectName(QStringLiteral("GetTemp"));
    GetTemp->setText(QApplication::translate("MainWindow", "Get Oven Temperature", nullptr));

    RunAll = new QPushButton(this);
    RunAll->setGeometry(QRect(x_off - (label_x + x_inc*2 ) * 1 - 80, 350, 200, 23));
    sizePolicy.setHeightForWidth(RunAll->sizePolicy().hasHeightForWidth());
    RunAll->setSizePolicy(sizePolicy);
    RunAll->setObjectName(QStringLiteral("RunAll"));
    RunAll->setText(QApplication::translate("MainWindow", "Run All Boards Calibration", nullptr));


    label_calibre_low = new QLabel(this);
    label_calibre_low->setObjectName(QStringLiteral("label_calibre_low"));
    label_calibre_low->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 0 -30, 80, label_x+25, label_y));
    sizePolicy.setHeightForWidth(label_calibre_low->sizePolicy().hasHeightForWidth());
    label_calibre_low->setSizePolicy(sizePolicy);
    this->label_calibre_low->setText(QApplication::translate("MainWindow", "CalPointLow", nullptr));


    label_calibre_high = new QLabel(this);
    label_calibre_high->setObjectName(QStringLiteral("label_calibre_high"));
    label_calibre_high->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 1, 80, label_x+35, label_y));
    sizePolicy.setHeightForWidth(label_calibre_high->sizePolicy().hasHeightForWidth());
    label_calibre_high->setSizePolicy(sizePolicy);
    this->label_calibre_high->setText(QApplication::translate("MainWindow", "CalPointHigh", nullptr));

    label_temp_check = new QLabel(this);
    label_temp_check->setObjectName(QStringLiteral("label_temp_check"));
    label_temp_check->setGeometry(QRect(x_off - (label_x + x_inc*2 ) * 1 - 80, 80, label_x+45, label_y));
    sizePolicy.setHeightForWidth(label_temp_check->sizePolicy().hasHeightForWidth());
    label_temp_check->setSizePolicy(sizePolicy);
    this->label_temp_check->setText(QApplication::translate("MainWindow", "TempCheckPoint", nullptr));


    label_calibre_low_period = new QLabel(this);
    label_calibre_low_period->setObjectName(QStringLiteral("label_calibre_low_period"));
    label_calibre_low_period->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 0 -30, 150, label_x+55, label_y));
    sizePolicy.setHeightForWidth(label_calibre_low_period->sizePolicy().hasHeightForWidth());
    label_calibre_low_period->setSizePolicy(sizePolicy);
    this->label_calibre_low_period->setText(QApplication::translate("MainWindow", "goLowTime(min)", nullptr));


    label_calibre_high_period = new QLabel(this);
    label_calibre_high_period->setObjectName(QStringLiteral("label_calibre_high_period"));
    label_calibre_high_period->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 1, 150, label_x+55, label_y));
    sizePolicy.setHeightForWidth(label_calibre_high_period->sizePolicy().hasHeightForWidth());
    label_calibre_high_period->setSizePolicy(sizePolicy);
    this->label_calibre_high_period->setText(QApplication::translate("MainWindow", "goHighTime(min)", nullptr));

    label_temp_check_period = new QLabel(this);
    label_temp_check_period->setObjectName(QStringLiteral("label_temp_check_period"));
    label_temp_check_period->setGeometry(QRect(x_off - (label_x + x_inc*2 ) * 1 - 80, 150, label_x+55, label_y));
    sizePolicy.setHeightForWidth(label_temp_check_period->sizePolicy().hasHeightForWidth());
    label_temp_check_period->setSizePolicy(sizePolicy);
    this->label_temp_check_period->setText(QApplication::translate("MainWindow", "goCheckTime(min)", nullptr));

    label_temp_calibre_serial = new QLabel(this);
    label_temp_calibre_serial->setObjectName(QStringLiteral("label_temp_calibre_serial"));
    label_temp_calibre_serial->setGeometry(QRect(x_off - (label_x + x_inc*2 ) * 1 - 80, 210, label_x+185, label_y));
    sizePolicy.setHeightForWidth(label_temp_calibre_serial->sizePolicy().hasHeightForWidth());
    label_temp_calibre_serial->setSizePolicy(sizePolicy);
    this->label_temp_calibre_serial->setText(QApplication::translate("MainWindow", "CheckSerial(0:lowTohigh;1:highTolow)", nullptr));

    label_mother_board_num = new QLabel(this);
    label_mother_board_num->setObjectName(QStringLiteral("label_mother_board_num"));
    label_mother_board_num->setGeometry(QRect(x_off - (label_x + x_inc*2 ) * 1 - 80, 270, label_x+105, label_y));
    sizePolicy.setHeightForWidth(label_mother_board_num->sizePolicy().hasHeightForWidth());
    label_mother_board_num->setSizePolicy(sizePolicy);
    this->label_mother_board_num->setText(QApplication::translate("MainWindow", "Mother Board Num", nullptr));

    temp_calibre_low=new QLineEdit(this);
    temp_calibre_low->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 0-10, 110, label_x, label_y));
    sizePolicy.setHeightForWidth(temp_calibre_low->sizePolicy().hasHeightForWidth());
    temp_calibre_low->setSizePolicy(sizePolicy);
    temp_calibre_low->setObjectName(QStringLiteral("temp_calibre_low"));
    temp_calibre_low->setText(QApplication::translate("MainWindow", "", nullptr));


    temp_calibre_high=new QLineEdit(this);
    temp_calibre_high->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 1+20, 110, label_x, label_y));
    sizePolicy.setHeightForWidth(temp_calibre_high->sizePolicy().hasHeightForWidth());
    temp_calibre_high->setSizePolicy(sizePolicy);
    temp_calibre_high->setObjectName(QStringLiteral("temp_calibre_high"));
    temp_calibre_high->setText(QApplication::translate("MainWindow", "", nullptr));

    temp_check=new QLineEdit(this);
    temp_check->setGeometry(QRect(x_off - (label_x + x_inc*2 ) * 1-60, 110, label_x, label_y));
    sizePolicy.setHeightForWidth(temp_check->sizePolicy().hasHeightForWidth());
    temp_check->setSizePolicy(sizePolicy);
    temp_check->setObjectName(QStringLiteral("temp_check"));
    temp_check->setText(QApplication::translate("MainWindow", "", nullptr));


    time_calibre_low=new QLineEdit(this);
    time_calibre_low->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 0-10, 180, label_x, label_y));
    sizePolicy.setHeightForWidth(time_calibre_low->sizePolicy().hasHeightForWidth());
    time_calibre_low->setSizePolicy(sizePolicy);
    time_calibre_low->setObjectName(QStringLiteral("time_calibre_low"));
    time_calibre_low->setText(QApplication::translate("MainWindow", "", nullptr));


    time_calibre_high=new QLineEdit(this);
    time_calibre_high->setGeometry(QRect(x_off + (label_x + x_inc*2 ) * 1+20, 180, label_x, label_y));
    sizePolicy.setHeightForWidth(time_calibre_high->sizePolicy().hasHeightForWidth());
    time_calibre_high->setSizePolicy(sizePolicy);
    time_calibre_high->setObjectName(QStringLiteral("time_calibre_high"));
    time_calibre_high->setText(QApplication::translate("MainWindow", "", nullptr));

    time_check=new QLineEdit(this);
    time_check->setGeometry(QRect(x_off - (label_x + x_inc*2 ) * 1-60, 180, label_x, label_y));
    sizePolicy.setHeightForWidth(time_check->sizePolicy().hasHeightForWidth());
    time_check->setSizePolicy(sizePolicy);
    time_check->setObjectName(QStringLiteral("time_check"));
    time_check->setText(QApplication::translate("MainWindow", "", nullptr));

    calibre_serial=new QLineEdit(this);
    calibre_serial->setGeometry(QRect(x_off - (label_x + x_inc*2 ) * 1-60, 240, label_x, label_y));
    sizePolicy.setHeightForWidth(calibre_serial->sizePolicy().hasHeightForWidth());
    calibre_serial->setSizePolicy(sizePolicy);
    calibre_serial->setObjectName(QStringLiteral("calibre_serial"));
    calibre_serial->setText(QApplication::translate("MainWindow", "", nullptr));

    mother_board_num=new QLineEdit(this);
    mother_board_num->setGeometry(QRect(x_off - (label_x + x_inc*2 ) * 1-60, 300, label_x, label_y));
    sizePolicy.setHeightForWidth(mother_board_num->sizePolicy().hasHeightForWidth());
    mother_board_num->setSizePolicy(sizePolicy);
    mother_board_num->setObjectName(QStringLiteral("mother_board_num"));
    mother_board_num->setText(QApplication::translate("MainWindow", "", nullptr));

    TextWindow = new QTextBrowser(this);
    TextWindow->setGeometry(QRect(10, 480, 1300, 170));
    sizePolicy.setHeightForWidth(TextWindow->sizePolicy().hasHeightForWidth());
    TextWindow->setObjectName(QStringLiteral("TextWindow"));
}
void QTabOven::on_OvenRun_clicked(){
    qDebug("click run oven button");
    emit set_oven_cmd(1);
}
void QTabOven::on_OvenStop_clicked(){
    qDebug("click Stop oven button");
    emit set_oven_cmd(0);
}
//void QTabOven::on_SetTemp7_clicked(){
//    qDebug("set oven temp 7");
//    emit set_oven_temp(7.0);
//}
//void QTabOven::on_SetTemp27_clicked(){
//    qDebug("set oven temp 27");

//    emit set_oven_temp(27.0);
//}
//void QTabOven::on_SetTemp47_clicked(){
//    qDebug("set oven temp 47");
//    emit set_oven_temp(47.0);
//}
void QTabOven::on_SetPara_clicked(){
    QString mboard_num   = this->mother_board_num->text();
    int cur_mboard_num = 0;

    std::string current_mboard_num = mboard_num.toLocal8Bit().constData();
    if(isNum(current_mboard_num)){
        cur_mboard_num = stoi(current_mboard_num);

    }else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wrong");
        msgBox.setText("Mother board num Set Wrong!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        qDebug("Mother board num Set Wrong");
        return;
    }

    emit set_parameters_all_board(cur_mboard_num);
}
void QTabOven::on_CheckPara_clicked(){
    QString mboard_num   = this->mother_board_num->text();
    int cur_mboard_num = 0;

    std::string current_mboard_num = mboard_num.toLocal8Bit().constData();
    if(isNum(current_mboard_num)){
        cur_mboard_num = stoi(current_mboard_num);

    }else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wrong");
        msgBox.setText("Mother board num Set Wrong!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        qDebug("Mother board num Set Wrong");
        return;
    }

    emit check_parameters_all_board(cur_mboard_num);
}

void QTabOven::on_AutoCheckTemp_clicked(){
    QString temp_check   = this->temp_check->text();
    QString time_tocheck   = this->time_check->text();
    QString mboard_num   = this->mother_board_num->text();

    int cur_mboard_num = 0;
    int cur_temp_check, cur_time_tocheck;

    std::string current_temp_check = temp_check.toLocal8Bit().constData();
    if(isNum(current_temp_check)){
        cur_temp_check = stoi(current_temp_check);

    }else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wrong");
        msgBox.setText("Temp Check Set Wrong!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        qDebug("Temp Check Set Wrong");
        return;
    }

    std::string current_check_time = time_tocheck.toLocal8Bit().constData();
    if(isNum(current_check_time)){
        cur_time_tocheck = stoi(current_check_time);

    }else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wrong");
        msgBox.setText("Check time Set Wrong!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        qDebug("Check time Set Wrong");
        return;
    }

    std::string current_mboard_num = mboard_num.toLocal8Bit().constData();
    if(isNum(current_mboard_num)){
        cur_mboard_num = stoi(current_mboard_num);

    }else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wrong");
        msgBox.setText("Mother board num Set Wrong!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        qDebug("Mother board num Set Wrong");
        return;
    }

    float check = (float)cur_temp_check;
    long int check_time = cur_time_tocheck * 60000;

    emit auto_check_temp_all_board(check, check_time, cur_mboard_num);
}


void QTabOven::on_ManualCheckTemp_clicked(){
    QString mboard_num   = this->mother_board_num->text();
    int cur_mboard_num = 0;

    std::string current_mboard_num = mboard_num.toLocal8Bit().constData();
    if(isNum(current_mboard_num)){
        cur_mboard_num = stoi(current_mboard_num);

    }else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wrong");
        msgBox.setText("Mother board num Set Wrong!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        qDebug("Mother board num Set Wrong");
        return;
    }

    emit manual_check_temp_all_board(cur_mboard_num);
}


void QTabOven::on_SetTemp_clicked()
{
    qDebug()<<"SetTemp clicked";
    QString qs;
    // Either this if you use UTF-8 anywhere
    qs=TextTempInput->text();
    float temp ;

   // temp = qs.toFloat();//can work but here we want to check input

    // std::string utf8_text = qs.toUtf8().constData();

    // or this if you're on Windows :-)
    std::string current_locale_text = qs.toLocal8Bit().constData();
    // if(current_locale_text.empty()){
    if(isNum(current_locale_text)){
        temp = stof(current_locale_text);
        qDebug("GUI try to set temperature to %f", temp);
 //       cur_agent.set_temp(temp);
        emit set_oven_temp(temp);

    }else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wrong");
        msgBox.setText("Temperature Wrong!");
        //   msgBox.setInformativeText("Temperature Wrong!");
        //     msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setStandardButtons(QMessageBox::Ok);

        //  msgBox.setDefaultButton(QMessageBox::Save);
        //int ret = msgBox.exec();
        msgBox.exec();
        qDebug("GUI try to set an invalid tempeture, ignored");
    }
}

void QTabOven::on_GetTemp_clicked()
{
    qDebug()<<"GetTemp clicked";
    //QString qs;
    // Either this if you use UTF-8 anywhere
    //qs=TextTempInput->text();
    //float temp ;
    double temp2 = 0;
    emit get_oven_temp2(temp2);
    this->lcdNumber->display(temp2);
}

void QTabOven::on_RunAll_clicked()
{
    qDebug()<<"RunAll clicked";

    //float temp_cal_hi = this->temp_calibre_high;
    //float temp_cal_low = this->temp_calibre_low;
    QString temp_cal_hi   = this->temp_calibre_high->text();
    QString temp_cal_lo   = this->temp_calibre_low->text();
    QString temp_check   = this->temp_check->text();

    QString time_cal_gohi   = this->time_calibre_high->text();
    QString time_cal_golo   = this->time_calibre_low->text();
    QString time_tocheck   = this->time_check->text();
    QString check_serial   = this->calibre_serial->text();
    QString mboard_num   = this->mother_board_num->text();

    int cur_temp_cal_hi, cur_temp_cal_lo, cur_temp_check, cur_check_serial, cur_mboard_num = 0;
    int cur_time_cal_gohi, cur_time_cal_golo, cur_time_tocheck;

    std::string current_temp_cal_hi = temp_cal_hi.toLocal8Bit().constData();
    if(isNum(current_temp_cal_hi)){
        cur_temp_cal_hi = stoi(current_temp_cal_hi);

    }else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wrong");
        msgBox.setText("Temp Calibre High Set Wrong!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        qDebug("Temp Calibre High Set Wrong");
        return;
    }

    std::string current_temp_cal_lo = temp_cal_lo.toLocal8Bit().constData();
    if(isNum(current_temp_cal_lo)){
        cur_temp_cal_lo = stoi(current_temp_cal_lo);

    }else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wrong");
        msgBox.setText("Temp Calibre Low Set Wrong!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        qDebug("Temp Calibre Low Set Wrong");
        return;
    }

    std::string current_temp_check = temp_check.toLocal8Bit().constData();
    if(isNum(current_temp_check)){
        cur_temp_check = stoi(current_temp_check);

    }else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wrong");
        msgBox.setText("Temp Check Set Wrong!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        qDebug("Temp Check Set Wrong");
        return;
    }

    std::string current_time_go_hi = time_cal_gohi.toLocal8Bit().constData();
    if(isNum(current_time_go_hi)){
        cur_time_cal_gohi = stoi(current_time_go_hi);

    }else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wrong");
        msgBox.setText("Time goes High Set Wrong!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        qDebug("Time goes High Set Wrong");
        return;
    }

    std::string current_time_go_lo = time_cal_golo.toLocal8Bit().constData();
    if(isNum(current_time_go_lo)){
        cur_time_cal_golo = stoi(current_time_go_lo);

    }else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wrong");
        msgBox.setText("Time goes Low Set Wrong!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        qDebug("Time goes Low Set Wrong");
        return;
    }

    std::string current_check_time = time_tocheck.toLocal8Bit().constData();
    if(isNum(current_check_time)){
        cur_time_tocheck = stoi(current_check_time);

    }else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wrong");
        msgBox.setText("Check time Set Wrong!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        qDebug("Check time Set Wrong");
        return;
    }

    std::string current_check_serial = check_serial.toLocal8Bit().constData();
    if(isNum(current_check_serial)){
        cur_check_serial = stoi(current_check_serial);

    }else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wrong");
        msgBox.setText("Check serial Set Wrong!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        qDebug("Check serial Set Wrong");
        return;
    }

    std::string current_mboard_num = mboard_num.toLocal8Bit().constData();
    if(isNum(current_mboard_num)){
        cur_mboard_num = stoi(current_mboard_num);

    }else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wrong");
        msgBox.setText("Mother board num Set Wrong!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        qDebug("Mother board num Set Wrong");
        return;
    }


    float cal_hi = (float)cur_temp_cal_hi;
    float cal_lo = (float)cur_temp_cal_lo;
    float check = (float)cur_temp_check;
    long int low_to_high_time = cur_time_cal_gohi * 60000;
    long int high_to_low_time = cur_time_cal_golo * 60000;
    long int check_time = cur_time_tocheck * 60000;

    //qInfo("High: %d, Low: %d, Check: %d", cur_temp_cal_hi, cur_temp_cal_lo, cur_temp_check);
    qInfo("High: %f, Low: %f, Check: %f", cal_hi, cal_lo, check);
    qInfo("HighTime: %ld, LowTime: %ld, CheckTime: %ld", low_to_high_time, high_to_low_time, check_time);
    qInfo("Check Serial: %d",cur_check_serial);
    qInfo("Mother board Num: %d", cur_mboard_num);

    //emit run_all_board();
    emit run_all_board(cal_hi, cal_lo, check, high_to_low_time, low_to_high_time, check_time, cur_check_serial, cur_mboard_num);
}

void QTabOven::onTimeOut()
{
    // 获取系统当前时间
    //QDateTime dateTime = QDateTime::currentDateTime();
    // 显示的内容
    //this->lcdNumber->display(myAgen->get_oven_temp());
    //this->lcdNumber->display(123);
}
