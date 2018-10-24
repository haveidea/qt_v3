#define QT_NO_DEBUG_OUTPUT

#ifndef MYMCU_H
#define MYMCU_H
#include <UART.h>
#include <myPackage.h>
#include <myglobal.h>


class myMCU:public UART,public myPackage
{
public:

    myMCU();
    virtual void load_default();
};

#endif // MYMCU_H
