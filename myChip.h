#define QT_NO_DEBUG_OUTPUT

#ifndef CHIP_H
#define CHIP_H
#include <iostream>
#include <string>
#include <vector>
#include <QDebug>
#include <myglobal.h>

using namespace std;

typedef struct {
    Byte coeff[3];
} sCoeff;

typedef struct {
    float ref_temp;
    float temp;
    sCoeff cur_coeff;
} sTestRecord;

typedef enum {
    GOOD=1,
    BAD=2,
    UNTESTED=8
}CHIPSTATE;

typedef struct{
    bool valid;
    Byte mtp[32];
}CHIP_INFO_HW;

//typedef struct{
    //bool valid;
    //Byte rom[8];
//}CHIP_ROM;

class myChip
{
public:
    Byte rom_code[8];
    sCoeff coeff;
    string version;
    string wafer_id;
    string date;
    CHIPSTATE state;
    CHIP_INFO_HW mtp;
    //CHIP_ROM rom_id;
    std::vector<sTestRecord> test_records;
    bool is_ref_chip;
    myChip();
    void  update_temp_record(float  ref_temp, float temp);
    float get_last_ref_temp();

    void update_rom_record(Byte* rom);


//    virtual void reset_chip_hw();
//    virtual CHIP_INFO_HW get_chip_info_hw();

private:


};

#endif // CHIP_H
