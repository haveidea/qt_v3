#define QT_NO_DEBUG_OUTPUT

#ifndef MY_PACKAGE_H
#define MY_PACKAGE_H
#include <myglobal.h>


typedef enum {
    SEL_ALL,
    SEL_BOARD,
    SEL_ROW,
    SEL_COL,
    SEL_CHIP
} eCmdSuffix;

typedef enum{
    OW_WRITEROMCODE,
    OW_DOCONVERTT,
    OW_GETTEMP,
    OW_GETTEMP_REF,
    OW_GETROMCODE,
    OW_SETCOEFF,
    OW_GETPARA,
    OW_GETSCRPAD,
    OW_GETPOWERMODE
} eBaseCmd;

typedef struct{
    int  len;
    eCmdSuffix  suffix;
    eBaseCmd    cmd;
    int         board;
    int         col;
    int         row;
    Byte        payload[1024];
}tPackage;


class myPackage
{
private:
    tPackage cur_package;
public:
    Byte pkg[1024];
    unsigned int  len;

public:
    myPackage();
    void pack();
    void unpack();
};

#endif // MY_PACKAGE_H
