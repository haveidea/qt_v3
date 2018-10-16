#define QT_NO_DEBUG_OUTPUT

#ifndef MYOVEN_H
#define MYOVEN_H
#include <UART.h>
#include <myglobal.h>


class myOven:public UART
{
public:
    myOven();
    void load_oven();
 //   bool set_temp(float);
};

#endif // MYOVEN_H
