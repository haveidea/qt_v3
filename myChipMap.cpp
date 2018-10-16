#include <windows.h>
#include <commctrl.h>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include "myChipMap.h"

void myChipMap::update_temp_record(int BX, int BY, int CX, int CY, float ref_temp, float temp)
{
    //  qDebug("BX %d, BY %d, CX %d, CY %d",BX,BY,CX,CY);
    map[BX][BY][CX][CY].update_temp_record( ref_temp, temp);
}

void myChipMap::update_rom_record(int BX, int BY, int CX, int CY, Byte* rom)
{
    //  qDebug("BX %d, BY %d, CX %d, CY %d",BX,BY,CX,CY);
    map[BX][BY][CX][CY].update_rom_record(rom);
}


bool myChipMap::reset_chip_state()
{
    if(map!=NULL){
        for(int ii = 0; ii <board_X_NUM; ii++){
            for (int jj = 0; jj < board_Y_NUM;jj++)
                for (int kk = 0; kk < chip_X_NUM; kk++)
                    for (int ll = 0;ll < chip_Y_NUM;ll++)
                        map[ii][jj][kk][ll].state = UNTESTED;
        }
        return true;
    }
    return false;

}

bool myChipMap::get_chip_state(int ii, int jj, int kk, int ll, CHIPSTATE& value)
{
    if((ii >= board_X_NUM) ||(jj>=board_Y_NUM)||(kk>=chip_X_NUM)||(ll>=chip_Y_NUM)||(map == nullptr))
        return false;
    else{
        value = map[ii][jj][kk][ll].state ;
    }
    return true;
}


bool myChipMap::set_chip_state(int ii, int jj, int kk, int ll, CHIPSTATE value)
{
    if((ii >= board_X_NUM) ||(jj>=board_Y_NUM)||(kk>=chip_X_NUM)||(ll>=chip_Y_NUM)||(map == nullptr))
        return false;
    else{
        map[ii][jj][kk][ll].state = value;
    }
    return true;
}


int myChipMap::get_chip_X()
{
    return chip_X_NUM;
}
int myChipMap::get_chip_Y()
{
    return chip_Y_NUM;
}
int myChipMap::get_board_X()
{
    return board_X_NUM;
}
int myChipMap::get_board_Y()
{
    return board_Y_NUM;
}

myChipMap::~myChipMap()
{
    for(int i=0; i<board_X_NUM; i++)
    {
        for(int j=0; j<board_Y_NUM; j++)
        {

            for(int k=0; k<chip_X_NUM; k++){

                for(int l = 0; l<chip_Y_NUM; l++)
                {
                    map[i][j][k][l] = *(new (myChip));
                }
                delete [] map[i][j][k];
                map[i][j][k] = nullptr;
            }
            delete [] map[i][j];
            map[i][j]=nullptr;
        }
        delete [] map[i];
        map[i]=nullptr;
    }
    map = nullptr;
}

myChipMap::myChipMap()
{
    map = nullptr;

    map = new myChip***[board_X_NUM];

    for(int i=0; i<board_X_NUM; i++)
    {
        map[i] = new myChip**[board_Y_NUM];
        for(int j=0; j<board_Y_NUM; j++)
        {
            map[i][j] = new myChip * [chip_X_NUM];
            for(int k=0; k<chip_X_NUM; k++){
                map[i][j][k] = new myChip[chip_Y_NUM];
                for(int l = 0; l<chip_Y_NUM; l++)
                {
                    map[i][j][k][l] = *(new (myChip));
                }
            }
        }
    }

}




bool myChipMap::get_chip_info(int ii, int jj, int kk, int ll, myChip& value)
{
    if((ii >= board_X_NUM) ||(jj>=board_Y_NUM)||(kk>=chip_X_NUM)||(ll>=chip_Y_NUM)||(map == nullptr))
        return false;
    else{
        value = map[ii][jj][kk][ll] ;
    }
    return true;
}


bool myChipMap::set_chip_info(int ii, int jj, int kk, int ll, myChip value)
{
    if((ii >= board_X_NUM) ||(jj>=board_Y_NUM)||(kk>=chip_X_NUM)||(ll>=chip_Y_NUM)||(map == nullptr))
        return false;
    else{
        map[ii][jj][kk][ll] = value;
    }
    return true;
}


