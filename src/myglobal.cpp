#include "myGlobal.h"
#include<iostream>
#include<fstream>
#include "qdebug.h"
Byte * ab2coeff(double a,double b){
    static Byte coeff[3];
    //TODO
    // std::cout<< "to be implemented"<<std::endl;
    qDebug()<<"TODO";

    return coeff;

}


bool isNum(string str)
{
    stringstream sin(str);
    double d;
    Byte c;
    if(!(sin >> d))
    {
        return false;
    }
    if (sin >> c)
    {
        return false;
    }
    return true;
}
