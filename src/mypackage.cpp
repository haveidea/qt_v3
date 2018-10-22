#include "myPackage.h"
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */

myPackage::myPackage()
{

}

void myPackage::pack()
{
    switch(cur_package.suffix)
    {
    case SEL_ALL   : pkg[2] = 0x5a;break;
    case SEL_BOARD : pkg[2] = 0x6b;break;
    case SEL_ROW   : pkg[2] = 0x7c;break;
    case SEL_COL   : pkg[2] = 0x8d;break;
    case SEL_CHIP  : pkg[2] = 0x9e;break;
 pkg[2] = 0x0; break;
    }
    switch(cur_package.cmd)
    {
    case OW_DOCONVERTT:     pkg[4] = 0x11,pkg[3]=0x00;break;
    case OW_GETTEMP:        pkg[4] = 0x11,pkg[3]=0x01;break;
    case OW_GETTEMP_REF:    pkg[4] = 0x11,pkg[3]=0x02;break;
    case OW_WRITEROMCODE:   pkg[4] = 0x12,pkg[3]=0x00;break;
    case OW_GETROMCODE:     pkg[4] = 0x12,pkg[3]=0x01;break;
    case OW_SETCOEFF:       pkg[4] = 0x13,pkg[3]=0x00;break;
    case OW_GETPARA:        pkg[4] = 0x14,pkg[3]=0x00;break;
    case OW_GETSCRPAD:      pkg[4] = 0x14,pkg[3]=0x01;break;
 pkg[2] = 0x00,pkg[1]=0x00;break;

    }

    pkg[5] = (Byte)(cur_package.board %256);
    pkg[6] = (Byte)(cur_package.row  %256) ;
    pkg[7] = (Byte)(cur_package.col  %256) ;

    for (int ii = 0; ii <cur_package.len;ii++)
    {
        pkg[8+ii] = cur_package.payload[ii];
    }

}
void myPackage::unpack()
{

}
