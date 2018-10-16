#include "myChip.h"
myChip::myChip(){
    for(int ii = 0; ii <8; ii++)
        rom_code[ii] = '0';
    for(int ii = 0; ii <3; ii++)
        coeff.coeff[ii] = '0';
    state    =  UNTESTED;
    version  = "NA";
    wafer_id = "NA";
    date     ="NA";
    is_ref_chip = false;
    mtp.valid = false;
}
float myChip::get_last_ref_temp()
{
    return this->test_records[this->test_records.size()-1].ref_temp;
}

void myChip::update_temp_record(float  ref_temp, float temp)
{
    sTestRecord s;
    s.ref_temp=ref_temp;
    s.temp=temp;
    s.cur_coeff=this->coeff;
    this->test_records.push_back(s);
}

void myChip::update_rom_record(Byte* rom)
{
    for(int ii = 0; ii <8; ii++)
        this->rom_code[ii] = rom[ii];

    //this->test_records.push_back(s);
}

