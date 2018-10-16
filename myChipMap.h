#define QT_NO_DEBUG_OUTPUT

#ifndef CHIP_MAP_H
#define CHIP_MAP_H

#include <myglobal.h>

#include <windows.h>
#include <commctrl.h>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <myChip.h>
#include <QDebug>
#include <myglobal.h>



class myChipMap{
private:
   // myChip * map;
    //myChip * ref_map;

    const int board_X_NUM= NUM_DAUGHTER_BOARDS_X;
    const int board_Y_NUM= NUM_DAUGHTER_BOARDS_Y;
    const int chip_X_NUM = NUM_CHIPS_X;
    const int chip_Y_NUM = NUM_CHIPS_Y;

public:
    myChip  **** map;
    myChip  ref_map[NUM_DAUGHTER_BOARDS_X*NUM_DAUGHTER_BOARDS_Y];

    myChipMap();
    ~myChipMap();
    int get_board_X();
    int get_board_Y();
    int get_chip_X();
    int get_chip_Y();

    bool set_chip_state(int,int,int,int,CHIPSTATE);
    bool get_chip_state(int,int,int,int,CHIPSTATE&);

    void update_temp_record(int , int , int , int , float , float);

    void update_rom_record(int , int , int , int , Byte* );

    bool set_chip_info(int,int,int,int,myChip);
    bool get_chip_info(int,int,int,int,myChip&);
    bool reset_chip_state();
};

#endif // CHIP_MAP_H
