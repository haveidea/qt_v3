#define QT_NO_DEBUG_OUTPUT

#ifndef MYGLOBAL_H
#define MYGLOBAL_H
#include <string>
#include <myglobal.h>

#include <sstream>
#include "QMessageBox"

using namespace std;
typedef unsigned char Byte;
Byte * ab2coeff(double a,double b);

bool isNum(string str);

#define TEST 1

#define NUM_MOTHER_BOARDS   4

#define NUM_DAUGHTER_BOARDS_X 4
#define NUM_DAUGHTER_BOARDS_Y 3  //Dongsheng
#define NUM_CHIPS_X         10
#define NUM_CHIPS_Y         10

#define WINDOW_SIZE_X       1366
#define WINDOW_SIZE_Y       768

//#include "log4qt/consoleappender.h"
#include "log4qt/logger.h"
//#include "log4qt/ttcclayout.h"
#include "log4qt/basicconfigurator.h"

#include "log4qt/propertyconfigurator.h"

//QString LogNames[5];
extern Log4Qt::Logger *a2 ;
extern Log4Qt::Logger *a3 ;

#pragma execution_character_set("utf-8")

#endif // MYGLOBAL_H
