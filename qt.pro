#-------------------------------------------------
#
# Project created by QtCreator 2018-02-10T10:02:45
#
#-------------------------------------------------

QT       += core gui
QT       += serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt
TEMPLATE = app
QT += multimediawidgets
include (log4qt/src/log4qt/log4qt.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/src/header
DEPENDPATH += $$PWD/src/header
#DEPENDPATH += . header/ log4qt/src log4qt/src/log4qt log4qt/src/log4qt/helpers log4qt/src/log4qt/spi log4qt/src/log4qt/varia
#INCLUDEPATH += . header/ log4qt/src log4qt/src/log4qt log4qt/src/log4qt/helpers log4qt/src/log4qt/spi log4qt/src/log4qt/varia
##DEFINES += QT_NO_WARNING_OUTPUT\ QT_NO_DEBUG_OUTPUT


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
                $$PWD/src/main.cpp \
                $$PWD/src/mainwindow.cpp \
                $$PWD/src/mypackage.cpp \
                $$PWD/src/mychip.cpp \
                $$PWD/src/mychipmap.cpp \
                $$PWD/src/runguard.cpp \
                $$PWD/src/uart.cpp \
                $$PWD/src/myoven.cpp \
                $$PWD/src/mymcu.cpp \
                $$PWD/src/myglobal.cpp \
                $$PWD/src/mathbicubic.cpp \
                $$PWD/src/qtaboven.cpp \
                $$PWD/src/qcomboboxuart.cpp \
                $$PWD/src/myagent.cpp \
                $$PWD/src/qtabboard.cpp \
                $$PWD/src/qgroupuartconfig.cpp \
                $$PWD/src/mathleastsquare.cpp \
                $$PWD/src/mymcuagent.cpp \
                $$PWD/src/qcomboboxuart.cpp \

HEADERS += \
                $$PWD/src/header/mainwindow.h \
                $$PWD/src/header/mypackage.h \
                $$PWD/src/header/mychipmap.h \
                $$PWD/src/header/mymsgmessage.h \
                $$PWD/src/header/runguard.h \
                $$PWD/src/header/uart.h \
                $$PWD/src/header/mymcu.h \
                $$PWD/src/header/myoven.h \
                $$PWD/src/header/myglobal.h \
                $$PWD/src/header/ui_mainwindow.h \
                $$PWD/src/header/mathbicubic.h \
                $$PWD/src/header/qtaboven.h \
                $$PWD/src/header/qcomboboxuart.h \
                $$PWD/src/header/myagent.h \
                $$PWD/src/header/mychip.h \
                $$PWD/src/header/mymsgmessage.h \
                $$PWD/src/header/qtabboard.h \
                $$PWD/src/header/qgroupuartconfig.h \
                $$PWD/src/header/mathleastsquare.h \
                $$PWD/src/header/mymcuagent.h

FORMS +=
