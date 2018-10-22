#define QT_NO_DEBUG_OUTPUT
#ifndef MESSAGE_H
#define MESSAGE_H

#include <qapplication.h>
#include <stdio.h>
#include <stdlib.h>
#include <QMutex>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <myglobal.h>
extern QString LogNames[5];

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    QFile file;
//    char filestring[255];
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
    QString current_date= QString("(%1)").arg(current_date_time);

    switch(type)
    {
    case QtInfoMsg:
        text = QString("Info:");
        file.setFileName(LogNames[0]);
        break;
    case QtDebugMsg:
        text = QString("Debug:");
        file.setFileName(LogNames[1]);
        break;
    case QtWarningMsg:
        text = QString("Warning:");
        file.setFileName(LogNames[2]);
        break;
    case QtCriticalMsg:
        text = QString("Critical:");
        file.setFileName(LogNames[3]);
        break;
    case QtFatalMsg:
        text = QString("Fatal:");
        file.setFileName(LogNames[4]);
        break;

        text = QString("Type(%1):").arg(type);
    }

    //QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);

   // QString message = QString("%1 %2 %3 %4").arg(text).arg(msg).arg(current_date);
    QString message = QString("%1 %2").arg(text).arg(msg);

    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();
    mutex.unlock();
}

#endif // MESSAGE_H
