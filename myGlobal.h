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



#endif // MYGLOBAL_H
