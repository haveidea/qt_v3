#-------------------------------------------------
#
# Project created by QtCreator 2018-02-10T10:02:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#DEFINES += QT_NO_WARNING_OUTPUT\ QT_NO_DEBUG_OUTPUT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
		main.cpp \
		mainwindow.cpp \
		myPackage.cpp \
		myChip.cpp \
		myChipMap.cpp \
		RunGuard.cpp \
		UART.cpp \
		myOven.cpp \
		myMCU.cpp \
		myGlobal.cpp \
		MathBiCubic.cpp \
		QTabOven.cpp \
		QComboBoxUart.cpp \
		myAgent.cpp \
		QTabBoard.cpp \
		QGroupUartConfig.cpp \
		MathLeastSquare.cpp \
		myMCUAgent.cpp \
    qcomboboxuart.cpp

HEADERS += \
        mainwindow.h \
		myPackage.h \
		myChipMap.h \
		myMsgmessage.h \
		RunGuard.h \
		UART.h \
		myMCU.h \
		myOven.h \
		myGlobal.h \
		ui_mainwindow.h \
		MathBiCubic.h \
		QTabOven.h \
		QComboBoxUart.h \
		myAgent.h \
		myChip.h \
		myMsgmessage.h \
		QTabBoard.h \
		QGroupUartConfig.h \
		MathLeastSquare.h \
		myMCUAgent.h \
    qcomboboxuart.h

FORMS +=
