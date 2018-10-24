#define QT_NO_DEBUG_OUTPUT

#include "mainwindow.h"
#include <QApplication>
#include "UART.h"
#include <QTextCodec>
#include <myMsgmessage.h>
#include <QMessageBox>
#include "RunGuard.h"
//Log4Qt::Logger *programlog;
//Log4Qt::Logger *runlog ;
//Log4Qt::Logger *a2 ;
//Log4Qt::Logger *a3 ;

int main(int argc, char *argv[])
{
    RunGuard guard( "some_random_key" );
    if ( !guard.tryToRun() )
        return 0;

    QApplication app(argc, argv);

//    LogNames[0] = QString("(%1)").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")).append("LogInfo.log");
//    LogNames[1] = QString("(%1)").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")).append("LogDebug.log");
//    LogNames[2] = QString("(%1)").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")).append("LogWarning.log");
//    LogNames[3] = QString("(%1)").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")).append("LogCritical.log");
//    LogNames[4] = QString("(%1)").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")).append("LogFatal.log");


//    qInstallMessageHandler(outputMessage);
//    Log4Qt::BasicConfigurator::configure();
//    Log4Qt::Logger * log = Log4Qt::Logger::rootLogger();
//    log->debug("Hello DbZhang800!");
//    log->info("Hello Qt!");
//    log->warn("Hello 1+1=2");
//    Log4Qt::Logger * log1 = Log4Qt::Logger::rootLogger();
//    log->debug("Hello DbZhang1100!");
//    log->info("Hello 111Qt!");
//    log->warn("Hello 1111+1=2");
    // start log4QT configuration
    /*
    Log4Qt::BasicConfigurator::configure();
    Log4Qt::PropertyConfigurator::configure(QCoreApplication::applicationDirPath() + "log4qt.properties");

  //  Log4Qt::Logger *a4 = Log4Qt::Logger::logger("A4");
  //  a1->info("the message of log");//the log save at logs/a1.log

    a2= Log4Qt::Logger::logger("A2");
    //a1->logger()->setObjectName();
    a2->info("the message of log");//the log save at logs/a2.log

    a3 = Log4Qt::Logger::logger("A3");
    a3->info("the message of log");//the log save at logs/a3.log

    programlog= Log4Qt::Logger::logger("programlog");
    //a1->logger()->setObjectName();
    programlog->info("the message of log");//the log save at logs/a2.log

    runlog = Log4Qt::Logger::logger("runlog");
    runlog->info("the message of log");//the log save at logs/a3.log
    */
    // Create a layout
    // Create a layout


//    TTCCLayout
//    Log4Qt::TTCCLayout *p_layout = new TTCCLayout();
//    p_layout->setName(QLatin1String("My Layout"));
//    p_layout->activateOptions();
//    // Create an appender
//    ConsoleAppender *p_appender = new ConsoleAppender(p_layout, ConsoleAppender::STDOUT_TARGET);
//    p_appender->setName(QLatin1String("My Appender"));
//    p_appender->activateOptions();

//    // Set appender on root logger
//    Log4Qt::Logger::rootLogger()->setAppender(p_appender);
//    // end log4QT configuration

//    // TEST log4qt
//    // Request a logger and output "Hello World!"
//   // Log4Qt::Logger::logger(QLatin1String("My Logger"))->info("Hello World!");
//    // end TEST log4qt

  //  Log4Qt::PropertyConfigurator::configure(a.applicationDirPath()+ "/log4j.properties");
 //   Log4Qt::PropertyConfigurator::configure(QCoreApplication::applicationDirPath() + "/log4qt.properties");

    QDateTime dateTime = QDateTime::currentDateTime();
    qInfo() << dateTime.toString("HH:mm:ss.zzz") << "\r\n";

    qInfo("[BoardA]:i AM HRE boarda\n");
    qInfo("[BoardB]:i AM HRE boardb\n");
    qInfo("i AM HRE, noboard\n");
    qDebug("this is debug info");


    int a = 123;
    qInfo("qINFO......%d",a);
    qDebug("qDEBUG......%d",a);

    //打印日志到文件中
    qInfo("This is a Info message");
    qDebug("This is a debug message");          //  qDebug：调试信息
    qWarning("This is a warning message");      //  qWarning：警告信息
    qCritical("This is a critical message");    //  qCritical：严重错误
    //qFatal("This is a fatal message");          //  qFatal：致命错误(会报错，然后准备退出)

    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));

    MainWindow w;

    w.show();

    return app.exec();
}
