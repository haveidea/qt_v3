#define QT_NO_DEBUG_OUTPUT

#include "myMCUAgent.h"
//#include "myAgent.h"
#include "MathLeastSquare.h"

myMCUAgent::~myMCUAgent()
{

    MathBiCubic::DeleteTable(fKnow,NUM_DAUGHTER_BOARDS_X,NUM_DAUGHTER_BOARDS_Y);
    MathBiCubic::DeleteTable(fRet,NUM_DAUGHTER_BOARDS_X*NUM_CHIPS_X,NUM_DAUGHTER_BOARDS_Y*NUM_CHIPS_Y);
}

myMCUAgent::myMCUAgent()
{

    timer = new QTimer(this);
    //  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    //  timer->start(1000);

    MathBiCubic::GetTable(fKnow,NUM_DAUGHTER_BOARDS_X,NUM_DAUGHTER_BOARDS_Y,3);
    MathBiCubic::GetTable(fRet,NUM_DAUGHTER_BOARDS_X*NUM_CHIPS_X,NUM_DAUGHTER_BOARDS_Y*NUM_CHIPS_Y,3);

    this->mcu_uart = new(myMCU);


    // set fKnow value(ref pos)
    for(int i=0; i<NUM_DAUGHTER_BOARDS_X; i++)
    {
        for(int j=0; j<NUM_DAUGHTER_BOARDS_Y; j++)
        {
            fKnow[i][j][0] = (0.8 + 8.3 + 0.6+0.4+0.5)*i+ (0.8 + 8.3 + 0.6); // ref xpos
            fKnow[i][j][1] = (7.9 + 0.5)*j +0.6; // ref y pos
            //   fKnow[i][j][0] = 50* i; // ref xpos
            //   fKnow[i][j][1] = 50 * j; // ref y pos
        }
    }

    for(int i=0; i<NUM_DAUGHTER_BOARDS_X; i++)
    {
        for(int j=0; j<NUM_DAUGHTER_BOARDS_Y; j++)
        {
            for (int k = 0; k < NUM_CHIPS_X; k++)
            {
                for (int l = 0; l < NUM_CHIPS_Y; l++)
                {
                    fRet[i*NUM_CHIPS_X + k][j*NUM_CHIPS_Y + l ][0] = i * (0.8+8.3+1+0.5) + 0.8 + 8.3/NUM_CHIPS_X * k;
                    fRet[i*NUM_CHIPS_X + k][j*NUM_CHIPS_Y + l ][1] = j * (7.9+0.5)  + 5.5/NUM_CHIPS_Y * l;
                    // fRet[i*NUM_CHIPS_X + k][j*NUM_CHIPS_Y + l ][0] = i * (0.8+8.3+1+0.5) + 0.8 + 8.3/NUM_CHIPS_X * k;
                    //  fRet[i*NUM_CHIPS_X + k][j*NUM_CHIPS_Y + l ][1] = j * (7.9+0.5)  + 5.5/NUM_CHIPS_Y * l;
                }
            }

        }
    }

}

bool myMCUAgent::pack_cmd(int sel, int cmd, int board, int row,int col,Byte* payload, int payload_len, Byte *&char_cmd, int* send_len)
{
    //    ow_doconvert        0x1100: 单纯发送convertT指令（含6ms dealy）
    //    ow_gettemp          0x1101：读取当前温度值（含convertT指令，返回原始16-bit读值 (MSB先行)）
    //    ow_gettemp_ref      0x1102：读取Si7051温度值（返回原始16-bit读值 (MSB先行)）
    //    ow_writeparameters  0x1200：功能为设置ROM code的crc和初始化相应scratchpad value，无需payload
    //    ow_getromcode       0x1201：读取ROM code （payload中ROM code为MSB先行）
    //    ow_setcoeff         0x1300：设置校准参数，发送计算好的3-byte coeff到MCU，低字节先行(对应芯片scratchpad中adc_coeff由低到高次序)
    Byte fld_cmd[3];
    switch(cmd){
    case 0: fld_cmd[1]= 0x11; fld_cmd[2] = 0x00;break;
    case 1: fld_cmd[1]= 0x11; fld_cmd[2] = 0x01;break;
    case 2: fld_cmd[1]= 0x11; fld_cmd[2] = 0x02;break;
    case 3: fld_cmd[1]= 0x12; fld_cmd[2] = 0x00;break;
    case 4: fld_cmd[1]= 0x12; fld_cmd[2] = 0x01;break;
    case 5: fld_cmd[1]= 0x13; fld_cmd[2] = 0x00;break;
    case 6: fld_cmd[1]= 0x14; fld_cmd[2] = 0x00;break;
    case 7: fld_cmd[1]= 0x14; fld_cmd[2] = 0x01;break;
    default: return false;
    }
    switch(sel){
    case 0: fld_cmd[0] = 0x5a;break;
    case 1: fld_cmd[0] = 0x6b;break;
    case 2: fld_cmd[0] = 0x7c;break;
    case 3: fld_cmd[0] = 0x8d;break;
    case 4: fld_cmd[0] = 0x9e;break;
    default: return false;
    }
    *send_len = 2+3+3+payload_len+1+1;
    char_cmd = (Byte *)malloc(sizeof(Byte)*(*send_len));
    Byte send_len_hi = (Byte)((*send_len)>>8);
    Byte send_len_lo = (Byte)((*send_len)&0xff);
    char_cmd[0] = send_len_hi;
    char_cmd[1] = send_len_lo;
    char_cmd[2] = fld_cmd[0];
    char_cmd[3] = fld_cmd[1];
    char_cmd[4] = fld_cmd[2];
    char_cmd[5] = unsigned char(board);
    char_cmd[6] = unsigned char(row);
    char_cmd[7] = unsigned char(col);


    for (int ii = 0; ii <payload_len; ii++)
    {
        char_cmd[8+ii] = payload[ii];
    }

    char_cmd[8+payload_len] = 0xfe; //eof
    char_cmd[8+payload_len+1] = 0xff;//crc

    return true;
}

void  ab2coeff_demo(double a,double b, Byte * coeff){

    unsigned short coeff_a, coeff_a_temp;
    short coeff_b;
    unsigned int coeff_b_temp, temp_cal_res;

    if(a>=1)
        coeff_a_temp = (unsigned short)((a-1)*4092);
    else if(a<1)
        coeff_a_temp = (unsigned short)((1-a)*4092);

    if((a-1) >= 0)
        coeff_a = coeff_a_temp & 1023;
    else if((a-1) < 0)
        coeff_a = coeff_a_temp | 1024;


    coeff_b = (short) (b*128);
    coeff_b_temp = coeff_b << 11;
    temp_cal_res = (coeff_b_temp | coeff_a) & 16777215;

    if(b<=32 && b>=-32 && a <= 1.25 && a >= 0.75) {
        coeff[0] = temp_cal_res & 0xff;
        coeff[1] = ((temp_cal_res & 0x00ff00) >> 8) & 0xff;
        coeff[2] = ((temp_cal_res & 0xff0000) >> 16) & 0xff;

        qInfo("coeff float a: %f, float b: %f, char c[0] : %02x, c[1]: %02x, c[2]: %02x\r\n\r\n", a, b, coeff[0], coeff[1], coeff[2]);
    }
    else {
        coeff[0] = 0x00;
        coeff[1] = 0x00;
        coeff[2] = 0x80;

        qInfo("ERROR!!! coeff float a: %f, float b: %f, char c[0] : %02x, c[1]: %02x, c[2]: %02x\r\n\r\n", a, b, coeff[0], coeff[1], coeff[2]);
    }




}/*
void update_coeff(float a, float b, Byte * coeff)
{

    qDebug("TODO: update_coeff");

}*/
void myMCUAgent::calc_coeff(int boardx, int boardy,int row,int col)
{
    vector<sTestRecord>::iterator it;

    vector<float> x;
    vector<float> y;
    for(it = map.map[boardx][boardy][row][col].test_records.begin(); it !=  map.map[boardx][boardy][row][col].test_records.end(); it++)
    {
        x.push_back(it->temp+128);
        y.push_back(it->ref_temp+128);
        qInfo("cal_coeff temp :%f, ref_temp: %f", it->temp, it->ref_temp);
    }

    MatchLeastSquare LSKernel(x,y);

    int board_indx = 1+ boardy*4 + boardx;
    int chip_indx = row*10 + 10 - col;
    //qInfo("Board %d Chip %d: a afer LS op: %f, b : %f",board_indx,chip_indx, LSKernel.a, LSKernel.b);


    if(LSKernel.a > 1.25 || LSKernel.a < 0.75 || LSKernel.b > 32 || LSKernel.b < -32)
    {
        map.set_chip_state(boardx,boardy,row,col,BAD);
        qInfo("Board %d Chip %d: a afer LS op: %f, b : %f-------------------------------------------> Board %d's Chip %d coeff set goes WRONG!!!",board_indx,chip_indx, LSKernel.a, LSKernel.b,board_indx,chip_indx);
    }
    else
    {
        map.set_chip_state(boardx,boardy,row,col,GOOD);
        qInfo("Board %d Chip %d: a afer LS op: %f, b : %f---> Board %d's Chip %d coeff set DONE!!!",board_indx,chip_indx, LSKernel.a, LSKernel.b,board_indx,chip_indx);
        //ab2coeff_demo(LSKernel.a, LSKernel.b, &(map.map[boardx][boardy][row][col].coeff.coeff[0]));
    }

    ab2coeff_demo(LSKernel.a, LSKernel.b, &(map.map[boardx][boardy][row][col].coeff.coeff[0]));
}

//void myMCUAgent::run_once(float temp_set, long int wait_msec){
void myMCUAgent::run_once(float temp_set){
    Byte* payload;
    //double temp2 = 0;

    //emit set_oven_cmd(1); //oven run
    //sleep(2000);
    //emit set_oven_temp(temp_set); //set oven temperature

    qInfo("Begin to wait oven temp goes to %f...",temp_set);
    //sleep(1800000);  //wait 30min
    //sleep(wait_msec);

    qInfo("Check Oven stable");
    //do{
        //emit get_oven_temp2(temp2);
    //}while(abs(temp2-temp_set)>1.5);

    execute_cmd_check_stable(temp_set);

    qInfo("Get temperature all");
    //execute_uart_cmd(0, 2, 0, 0, 0, 0, payload, 0); //get temp ref
    //get_ref(temp_set);
    execute_uart_cmd_new(0, 2, 0, 0, 0, 0, payload, 0,temp_set); //get temp ref
    execute_uart_cmd(0, 1, 0, 0, 0, 0, payload, 0); //get temp

    ///////////////////////////////////
    qInfo("Got ref temp and MY18B20 temp in %f point",temp_set);
    sleep(2000);

}


//void myMCUAgent::check_temp(float temp_set, long int wait_msec){
void myMCUAgent::check_temp(float temp_set) {
    Byte* payload;

    //sleep(wait_msec);

    qInfo("Check Oven stable");
    //do{
        //emit get_oven_temp2(temp2);
    //}while(abs(temp2-temp_set)>1.5);

    execute_cmd_check_stable(temp_set);

    qInfo("Checking temp and MY18B20 temp in %f point",temp_set);
    //execute_uart_cmd(0, 2, 0, 0, 0, 0, payload, 0); //get temp ref
    //execute_getref_cmd(0, 2, 0, 0, 0, 0, payload, 0, temp_set);
    //get_ref(temp_set);
    execute_uart_cmd_new(0, 2, 0, 0, 0, 0, payload, 0,temp_set); //get temp ref

    //execute_uart_cmd(0, 1, 0, 0, 0, 0, payload, 0); //get temp
    execute_temp_check();

    ///////////////////////////////////
    qInfo("Check temp done in %f point",temp_set);
    sleep(2000);

}

void myMCUAgent::manual_check_temp_indoor() {
    Byte* payload;

    //sleep(wait_msec);

    qInfo("Check Oven stable");

    qInfo("Checking temp and MY18B20 temp");
    execute_uart_cmd(0, 2, 0, 0, 0, 0, payload, 0); //get temp ref
    //execute_getref_cmd(0, 2, 0, 0, 0, 0, payload, 0, temp_set);
    execute_uart_cmd(0, 1, 0, 0, 0, 0, payload, 0); //get temp

    ///////////////////////////////////
    qInfo("Check temp done");
    sleep(2000);

}


void myMCUAgent::update_temp_plan(){

    for(int i=0; i<NUM_DAUGHTER_BOARDS_Y; i++)
    {
        for(int j=0; j<NUM_DAUGHTER_BOARDS_X; j++)
        {
            qDebug("update fknow x: %d, y:%d", j, i);
            fKnow[j][i][2] = map.ref_map[i *NUM_DAUGHTER_BOARDS_X + j].get_last_ref_temp();
        }
    }
    qDebug("calc fret");
    // MathBiCubic::CubicSplineEx2_ROW(fRet,NUM_DAUGHTER_BOARDS_X*NUM_CHIPS_X,NUM_DAUGHTER_BOARDS_Y*NUM_CHIPS_Y,fKnow,NUM_DAUGHTER_BOARDS_X,NUM_DAUGHTER_BOARDS_Y);
    //MathBiCubic::CubicSplineEx2_RowLine(fRet,NUM_DAUGHTER_BOARDS_X*NUM_CHIPS_X,NUM_DAUGHTER_BOARDS_Y*NUM_CHIPS_Y,fKnow,NUM_DAUGHTER_BOARDS_X,NUM_DAUGHTER_BOARDS_Y);
    for(int i=0; i<NUM_DAUGHTER_BOARDS_X; i++)
    {
        for(int j=0; j<NUM_DAUGHTER_BOARDS_Y; j++)
        {
            for (int k = 0; k < NUM_CHIPS_X; k++)
            {
                for (int l = 0; l < NUM_CHIPS_Y; l ++){
                    fRet[i*NUM_CHIPS_X + k ][j*NUM_CHIPS_Y + l][2] = fKnow[i][j][2];
                }
            }
        }
    }
    qDebug ("fRet2: %f     ",fRet[0][0][2]);
    qDebug ("fRet1: %f     ",fRet[0][0][1]);

    qDebug ("fRet0: %f     ",fRet[0][0][0]);

    qDebug("calc fret done");
    qDebug ("fknow pos x : %f %f",fKnow[0][0][0],fKnow[1][0][0]);
    qDebug ("fknow pos y : %f %f",fKnow[0][0][1],fKnow[1][0][1]);

    qDebug ("fknow: %f %f",fKnow[0][0][2],fKnow[1][0][2]);



    qDebug ("fRet: %f     ",fRet[0][0][0]);
    qDebug ("fRet: %f     ",fRet[0][0][0]);
    qDebug ("fRet: %f     ",fRet[0][0][0]);
    qDebug ("fRet: %f     ",fRet[0][0][0]);
    qDebug ("fRet: %f     ",fRet[0][0][0]);
    qDebug ("fRet: %f     ",fRet[0][0][0]);
    //,fRet[1][0][0],
    //            fRet[2][0][0],fRet[3][0][0],
    //            fRet[4][0][0],fRet[5][0][0],
    //            fRet[6][0][0],fRet[7][0][0],
    //            fRet[8][0][0],fRet[9][0][0]
    //            fRet[10][0][0],fRet[11][0][0],
    //            fRet[12][0][0],fRet[13][0][0],
    //            fRet[14][0][0],fRet[15][0][0],
    //            fRet[15][0][0],fRet[17][0][0],
    //            fRet[18][0][0],fRet[19][0][0]
    //);
    qDebug ("fRet: %f %f %f %f %f  %f %f %f %f %f  %f %f %f %f %f  %f %f %f %f %f",fRet[0][0][2],fRet[1][0][2],
            fRet[2][0][2],fRet[3][0][2],
            fRet[4][0][2],fRet[5][0][2],
            fRet[6][0][2],fRet[7][0][2],
            fRet[8][0][2],fRet[9][0][2],
            fRet[10][0][2],fRet[11][0][2],
            fRet[12][0][2],fRet[13][0][2],
            fRet[14][0][2],fRet[15][0][2],
            fRet[15][0][2],fRet[17][0][2],
            fRet[18][0][2],fRet[19][0][2]
            );
    qDebug ("fRet: %f %f %f %f %f  %f %f %f %f %f  %f %f %f %f %f  %f %f %f %f %f",fRet[0][9][2],fRet[1][9][2],
            fRet[2][9][2],fRet[3][9][2],
            fRet[4][9][2],fRet[5][9][2],
            fRet[6][9][2],fRet[7][9][2],
            fRet[8][9][2],fRet[9][9][2],
            fRet[10][9][2],fRet[11][9][2],
            fRet[12][9][2],fRet[13][9][2],
            fRet[14][9][2],fRet[15][9][2],
            fRet[15][9][2],fRet[17][9][2],
            fRet[18][9][2],fRet[19][9][2]
            );

}

//void myMCUAgent::cmd_set_coeff_all(){

//}

void myMCUAgent::run_all(){
    Byte* payload;

    qInfo("Begin to set parameters...");
    execute_uart_cmd(0, 3, 0, 0, 0, 0, payload, 0); //set parameters

    //run_once(77.0,2400000); //get 77.0 result, wait 40min
    //run_once(22.0,5000); //for Beijing test
    sleep(2000);
    //run_once(7.0,6000000);  //get 7.0 result, wait 1h40min

    qInfo("Begin to calculate coeff...");
    execute_uart_cmd(0, 5, 0, 0, 0, 0, payload, 0); //set coeff

    emit set_oven_cmd(0); //oven off
    emit run_all_done();
}

void myMCUAgent::set_parameters(){
    Byte* payload;

    qInfo("Begin to set parameters...");
    execute_uart_cmd(0, 3, 0, 0, 0, 0, payload, 0); //set parameters
}

void myMCUAgent::check_parameters(){
    Byte* payload;

    qInfo("Begin to check parameters...");
    execute_uart_cmd(0, 4, 0, 0, 0, 0, payload, 0); //read rom
    execute_uart_cmd(0, 6, 0, 0, 0, 0, payload, 0); //read parameter
    execute_uart_cmd(0, 7, 0, 0, 0, 0, payload, 0); //read scratchpad
}

void myMCUAgent::set_coeff(){
    Byte* payload;
    sleep(5000);

    qInfo("Begin to calculate coeff...");
    execute_uart_cmd(0, 5, 0, 0, 0, 0, payload, 0); //set coeff
}

void myMCUAgent::update_map( Byte * buffer, unsigned int len){
    qDebug()<<"TODO";
    // map.set_chip_state(0,0,0,0,GOOD);
    //    map.set_chip_state(1,1,0,0,BAD);
}

void  myMCUAgent::execute_uart_cmd(int sel, int cmd, int boardx, int boardy,int row,int col,Byte* payload, int payload_len){
    Byte * char_cmd;
    Byte response_len[2];
    int send_len;
    int sample_count = 1;

    if(cmd == 1 || cmd == 2)
        sample_count = 10;
    else
        sample_count = 1;

    if(sel == 0 && (cmd !=0 && cmd != 2 && cmd != 3)) {
        qDebug("select all");
        int sel_inner = 1;

        //for(int ii=0; ii<sample_count; ii++)
        //for(int bx=0; bx<NUM_DAUGHTER_BOARDS_X; bx++) {
        //for(int by=0; by<NUM_DAUGHTER_BOARDS_Y; by++) {
        for(int by=0; by<NUM_DAUGHTER_BOARDS_Y; by++) {
            for(int bx=0; bx<NUM_DAUGHTER_BOARDS_X; bx++) {
                qDebug("%d %d %d %d %d %d",sel_inner,cmd,bx,by,row,col);

                for(int iii=0; iii<sample_count; iii++) {
                    //qInfo("CMD run the %d time.",iii+1);

                    if (cmd == 5) // set coeff
                    {
                        // when execute set coeff, suppose the coeffs are already in chip map.
                        for (int ii = 0;ii < 10; ii++)
                        {
                            for (int jj = 0; jj < 10; jj ++)
                            {
                                calc_coeff(bx,by,ii,(9-jj));
                            }

                        }
                        //calc_coeff()
                        Byte  payload_new[300] ;
                        for (int i =0; i < 10; i++)
                        {
                            for (int j = 0; j < 10; j++)
                            {
                                payload_new[(i*10 + j)*3 +0] = map.map[bx][by][i][(9-j)].coeff.coeff[0];
                                payload_new[(i*10 + j)*3 +1] = map.map[bx][by][i][(9-j)].coeff.coeff[1];
                                payload_new[(i*10 + j)*3 +2] = map.map[bx][by][i][(9-j)].coeff.coeff[2];
                            }
                        }
                        int payload_len_new = 300;
                        pack_cmd(sel_inner, cmd, by*NUM_DAUGHTER_BOARDS_X + bx, row, col,  payload_new,  payload_len_new, char_cmd, &send_len);

                    }
                    else{
                        pack_cmd(sel_inner, cmd, by*NUM_DAUGHTER_BOARDS_X + bx, row, col,  payload,  payload_len, char_cmd, &send_len);
                    }

                    for(int ii = 0; ii < send_len; ii++)
                    {
                        qDebug("%02x",char_cmd[ii]);
                    }

                    //   if(this->mcu_uart->is_opened!=TRUE)
                    if(this->mcu_uart->open()!=TRUE)
                    {
                        s_errorbox("cmd execute error, uart is not opened");
                        return;
                    }

                    for(int ii = 0; ii < send_len; ii++)
                    {
                        qDebug("len %02x",char_cmd[ii]);
                    }


                    this->mcu_uart->write(char_cmd,send_len);
                    delete char_cmd;

                    if(this->mcu_uart->read(response_len,2) == false)
                    {
                        qDebug("mcu uart comand failed due to read timeout");
                        return ;
                    }

                    uint res_len = response_len[0] * 256 + response_len[1]-2;
                    Byte * response_res;
                    qDebug("need to read %d data", res_len);
                    // exit(0);
                    qDebug("port: %d, baud: %d, data:%d, parity:%d, stop:%d, flow;%d", this->mcu_uart->port_id, this->mcu_uart->dcb.BaudRate, this->mcu_uart->dcb.ByteSize,this->mcu_uart->dcb.Parity,this->mcu_uart->dcb.StopBits,this->mcu_uart->dcb.fInX);
                    //exit(0);

                    response_res = (Byte*)malloc(sizeof(Byte)*res_len);
                    if(this->mcu_uart->read(response_res,res_len) == false)
                    {
                        qDebug("mcu uart comand failed due to read timeout");
                        return ;
                    }
                    qDebug("before parsing [0]:%02x", response_len[0]);
                    qDebug("before parsing [1]:%02x", response_len[1]);
                    for(uint ii = 0; ii < res_len; ii++){
                        qDebug("before parsing [%d]:%02x", ii,response_res[ii]);
                    }
                    parsing_response(response_res, 1);
                }
            }
        }
    }
    else {
        qDebug("not select all");

        for(int ii=0; ii<sample_count; ii++) {
            qDebug("%d %d %d %d %d %d",sel,cmd,boardx,boardy,row,col);
            if (cmd == 5) // set coeff
            {
                // when execute set coeff, suppose the coeffs are already in chip map.
                for (int ii = 0;ii < 10; ii++)
                {
                    for (int jj = 0; jj < 10; jj ++)
                    {
                        calc_coeff(boardx,boardy,ii,(9-jj));
                    }

                }
                //calc_coeff()
                Byte  payload_new[300] ;
                for (int i =0; i < 10; i++)
                {
                    for (int j = 0; j < 10; j++)
                    {
                        payload_new[(i*10 + j)*3 +0] = map.map[boardx][boardy][i][(9-j)].coeff.coeff[0];
                        payload_new[(i*10 + j)*3 +1] = map.map[boardx][boardy][i][(9-j)].coeff.coeff[1];
                        payload_new[(i*10 + j)*3 +2] = map.map[boardx][boardy][i][(9-j)].coeff.coeff[2];
                    }
                }
                int payload_len_new = 300;
                pack_cmd(sel, cmd, boardy*NUM_DAUGHTER_BOARDS_X + boardx, row, col,  payload_new,  payload_len_new, char_cmd, &send_len);

            }
            else{
                pack_cmd(sel, cmd, boardy*NUM_DAUGHTER_BOARDS_X + boardx, row, col,  payload,  payload_len, char_cmd, &send_len);
            }

            for(int ii = 0; ii < send_len; ii++)
            {
                qDebug("%02x",char_cmd[ii]);
            }

            //   if(this->mcu_uart->is_opened!=TRUE)
            if(this->mcu_uart->open()!=TRUE)
            {
                s_errorbox("cmd execute error, uart is not opened");
                return;
            }

            for(int ii = 0; ii < send_len; ii++)
            {
                qDebug("len %02x",char_cmd[ii]);
            }


            this->mcu_uart->write(char_cmd,send_len);
            delete char_cmd;

            if(this->mcu_uart->read(response_len,2) == false)
            {
                qDebug("mcu uart comand failed due to read timeout");
                return ;
            }

            uint res_len = response_len[0] * 256 + response_len[1]-2;
            Byte * response_res;
            qDebug("need to read %d data", res_len);
            // exit(0);
            qDebug("port: %d, baud: %d, data:%d, parity:%d, stop:%d, flow;%d", this->mcu_uart->port_id, this->mcu_uart->dcb.BaudRate, this->mcu_uart->dcb.ByteSize,this->mcu_uart->dcb.Parity,this->mcu_uart->dcb.StopBits,this->mcu_uart->dcb.fInX);
            //exit(0);

            response_res = (Byte*)malloc(sizeof(Byte)*res_len);
            if(this->mcu_uart->read(response_res,res_len) == false)
            {
                qDebug("mcu uart comand failed due to read timeout");
                return ;
            }
            qDebug("before parsing [0]:%02x", response_len[0]);
            qDebug("before parsing [1]:%02x", response_len[1]);
            for(uint ii = 0; ii < res_len; ii++){
                qDebug("before parsing [%d]:%02x", ii,response_res[ii]);
            }
            parsing_response(response_res, 0);

        }
    }
}


void  myMCUAgent::execute_uart_cmd_new(int sel, int cmd, int boardx, int boardy,int row,int col,Byte* payload, int payload_len, float temp_set){
    Byte * char_cmd;
    Byte response_len[2];
    int send_len;
    int sample_count = 1;

    vector<vector<float>> resultSet;
    vector<float> vec;
    vector<float> ref;
    bool ready = FALSE;

    resultSet.resize(15);

    for (int i = 0; i < resultSet.size(); i++) {
        resultSet[i].resize(20);
        //qInfo("i: %d", i);
    }

    if(cmd == 1)
        sample_count = 10;
    else if(cmd == 2)
        sample_count = 20;
    else
        sample_count = 1;

    if(sel == 0 && (cmd !=0 && cmd != 3)) {
        qDebug("select all");
        int sel_inner = 1;

        //for(int ii=0; ii<sample_count; ii++)
        //for(int bx=0; bx<NUM_DAUGHTER_BOARDS_X; bx++) {
        //for(int by=0; by<NUM_DAUGHTER_BOARDS_Y; by++) {
        for(int by=0; by<NUM_DAUGHTER_BOARDS_Y; by++) {
            for(int bx=0; bx<NUM_DAUGHTER_BOARDS_X; bx++) {
                qDebug("%d %d %d %d %d %d",sel_inner,cmd,bx,by,row,col);



                for(int iii=0; iii<sample_count; iii++) {
                    //qInfo("CMD run the %d time.",iii+1);
                    if(by==NUM_DAUGHTER_BOARDS_Y-1 && bx==NUM_DAUGHTER_BOARDS_X-1 && iii == sample_count-1) {
                       ready = TRUE;
                    }
                    else {
                        ready = FALSE;
                    }

                    if (cmd == 5) // set coeff
                    {
                        // when execute set coeff, suppose the coeffs are already in chip map.
                        for (int ii = 0;ii < 10; ii++)
                        {
                            for (int jj = 0; jj < 10; jj ++)
                            {
                                calc_coeff(bx,by,ii,(9-jj));
                            }

                        }
                        //calc_coeff()
                        Byte  payload_new[300] ;
                        for (int i =0; i < 10; i++)
                        {
                            for (int j = 0; j < 10; j++)
                            {
                                payload_new[(i*10 + j)*3 +0] = map.map[bx][by][i][(9-j)].coeff.coeff[0];
                                payload_new[(i*10 + j)*3 +1] = map.map[bx][by][i][(9-j)].coeff.coeff[1];
                                payload_new[(i*10 + j)*3 +2] = map.map[bx][by][i][(9-j)].coeff.coeff[2];
                            }
                        }
                        int payload_len_new = 300;
                        pack_cmd(sel_inner, cmd, by*NUM_DAUGHTER_BOARDS_X + bx, row, col,  payload_new,  payload_len_new, char_cmd, &send_len);

                    }
                    else{
                        pack_cmd(sel_inner, cmd, by*NUM_DAUGHTER_BOARDS_X + bx, row, col,  payload,  payload_len, char_cmd, &send_len);
                    }

                    for(int ii = 0; ii < send_len; ii++)
                    {
                        qDebug("%02x",char_cmd[ii]);
                    }

                    //   if(this->mcu_uart->is_opened!=TRUE)
                    if(this->mcu_uart->open()!=TRUE)
                    {
                        s_errorbox("cmd execute error, uart is not opened");
                        return;
                    }

                    for(int ii = 0; ii < send_len; ii++)
                    {
                        qDebug("len %02x",char_cmd[ii]);
                    }


                    this->mcu_uart->write(char_cmd,send_len);
                    delete char_cmd;

                    if(this->mcu_uart->read(response_len,2) == false)
                    {
                        qDebug("mcu uart comand failed due to read timeout");
                        return ;
                    }

                    uint res_len = response_len[0] * 256 + response_len[1]-2;
                    Byte * response_res;
                    qDebug("need to read %d data", res_len);
                    // exit(0);
                    qDebug("port: %d, baud: %d, data:%d, parity:%d, stop:%d, flow;%d", this->mcu_uart->port_id, this->mcu_uart->dcb.BaudRate, this->mcu_uart->dcb.ByteSize,this->mcu_uart->dcb.Parity,this->mcu_uart->dcb.StopBits,this->mcu_uart->dcb.fInX);
                    //exit(0);

                    response_res = (Byte*)malloc(sizeof(Byte)*res_len);
                    if(this->mcu_uart->read(response_res,res_len) == false)
                    {
                        qDebug("mcu uart comand failed due to read timeout");
                        return ;
                    }
                    qDebug("before parsing [0]:%02x", response_len[0]);
                    qDebug("before parsing [1]:%02x", response_len[1]);
                    for(uint ii = 0; ii < res_len; ii++){
                        qDebug("before parsing [%d]:%02x", ii,response_res[ii]);
                    }
                    parsing_response_new(response_res, 1, iii, resultSet,vec, ref,temp_set, ready);
                }
            }
        }
    }
    else {
        qDebug("not select all");

        for(int ii=0; ii<sample_count; ii++) {
            qDebug("%d %d %d %d %d %d",sel,cmd,boardx,boardy,row,col);
            if (cmd == 5) // set coeff
            {
                // when execute set coeff, suppose the coeffs are already in chip map.
                for (int ii = 0;ii < 10; ii++)
                {
                    for (int jj = 0; jj < 10; jj ++)
                    {
                        calc_coeff(boardx,boardy,ii,(9-jj));
                    }

                }
                //calc_coeff()
                Byte  payload_new[300] ;
                for (int i =0; i < 10; i++)
                {
                    for (int j = 0; j < 10; j++)
                    {
                        payload_new[(i*10 + j)*3 +0] = map.map[boardx][boardy][i][(9-j)].coeff.coeff[0];
                        payload_new[(i*10 + j)*3 +1] = map.map[boardx][boardy][i][(9-j)].coeff.coeff[1];
                        payload_new[(i*10 + j)*3 +2] = map.map[boardx][boardy][i][(9-j)].coeff.coeff[2];
                    }
                }
                int payload_len_new = 300;
                pack_cmd(sel, cmd, boardy*NUM_DAUGHTER_BOARDS_X + boardx, row, col,  payload_new,  payload_len_new, char_cmd, &send_len);

            }
            else{
                pack_cmd(sel, cmd, boardy*NUM_DAUGHTER_BOARDS_X + boardx, row, col,  payload,  payload_len, char_cmd, &send_len);
            }

            for(int ii = 0; ii < send_len; ii++)
            {
                qDebug("%02x",char_cmd[ii]);
            }

            //   if(this->mcu_uart->is_opened!=TRUE)
            if(this->mcu_uart->open()!=TRUE)
            {
                s_errorbox("cmd execute error, uart is not opened");
                return;
            }

            for(int ii = 0; ii < send_len; ii++)
            {
                qDebug("len %02x",char_cmd[ii]);
            }


            this->mcu_uart->write(char_cmd,send_len);
            delete char_cmd;

            if(this->mcu_uart->read(response_len,2) == false)
            {
                qDebug("mcu uart comand failed due to read timeout");
                return ;
            }

            uint res_len = response_len[0] * 256 + response_len[1]-2;
            Byte * response_res;
            qDebug("need to read %d data", res_len);
            // exit(0);
            qDebug("port: %d, baud: %d, data:%d, parity:%d, stop:%d, flow;%d", this->mcu_uart->port_id, this->mcu_uart->dcb.BaudRate, this->mcu_uart->dcb.ByteSize,this->mcu_uart->dcb.Parity,this->mcu_uart->dcb.StopBits,this->mcu_uart->dcb.fInX);
            //exit(0);

            response_res = (Byte*)malloc(sizeof(Byte)*res_len);
            if(this->mcu_uart->read(response_res,res_len) == false)
            {
                qDebug("mcu uart comand failed due to read timeout");
                return ;
            }
            qDebug("before parsing [0]:%02x", response_len[0]);
            qDebug("before parsing [1]:%02x", response_len[1]);
            for(uint ii = 0; ii < res_len; ii++){
                qDebug("before parsing [%d]:%02x", ii,response_res[ii]);
            }
            parsing_response_new(response_res, 0, ii, resultSet, vec, ref, temp_set, ready);

        }
    }
}



bool myMCUAgent::parsing_response(Byte * response_a, int selAll)
{
    //    ow_doconvert        0x1100: 单纯发送convertT指令（含6ms dealy）
    //    ow_gettemp          0x1101：读取当前温度值（含convertT指令，返回原始16-bit读值 (MSB先行)）
    //    ow_gettemp_ref      0x1102：读取Si7051温度值（返回原始16-bit读值 (MSB先行)）
    //    ow_writeparameters  0x1200：功能为设置ROM code的crc和初始化相应scratchpad value，无需payload
    //    ow_getromcode       0x1201：读取ROM code （payload中ROM code为MSB先行）
    //    ow_setcoeff         0x1300：设置校准参数，发送计算好的3-byte coeff到MCU，低字节先行(对应芯片scratchpad中adc_coeff由低到高次序)
    //    ow_getpara          0x1400: 读取8-byte parameter
    //    ow_getscrpad        0x1401: 读取9-byte scratchpad

    //00 0E 5A 11 02 00 00 00 68 AC 69 80 FE FF

    //char response[16]  = { 0x5a, 0x11, 0x02, 0x00, 0x00, 0x00, 0x68, 0xac, 0x69, 0x80,0x68, 0xac, 0x69, 0x80,0xfe, 0xff};
    Byte* response = response_a;

    UartCmdType cmd;
    UartSelype sel;
    int boardx;
    int boardy;
    int board;
    int row;
    int col;
    //Byte * payload;
    qDebug("sel byte : %02x", response[0]);
    if(response[0] == 0x5a )
    {
        sel = all; // sel all
    }
    else if(response[0] == 0x9e){
        sel = individule; // sel individual
    }
    else if(response[0] == 0x6b){
        sel = board_sel; // sel board
    }
    else if(response[0] == 0x7c){
        sel = row_sel; //sel row
    }
    else if(response[0] == 0x8d){
        sel = col_sel; //sel col
    }
    else{
        qDebug("response sel field not recognized");
        return false;
    }
    if((response[1] == 0x11) && (response[2] ==0x00)) {
        cmd = ow_doconvert;//ow_doconvert
        qDebug("ow_doconvert response");
    }
    else if((response[1] == 0x11) && (response[2] ==0x01)) {
        cmd = ow_gettemp;
        qDebug("ow_gettemp response");
    }
    else if((response[1] == 0x11) && (response[2] ==0x02)) {
        cmd = ow_gettemp_ref;
        qDebug("ow_gettemp_ref response");
    }
    else if((response[1] == 0x12) && (response[2] ==0x00)) {
        cmd = ow_writeparameters;
        qDebug("ow_writeparameters response");
    }
    else if((response[1] == 0x12) && (response[2] ==0x01)) {
        cmd = ow_getromcode;
        qDebug("ow_getromcode response");
    }
    else if((response[1] == 0x13) && (response[2] ==0x00)) {
        cmd = ow_setcoeff;
        qDebug("ow_setcoeff response");
    }
    else if((response[1] == 0x14) && (response[2] ==0x00)) {
        cmd = ow_getpara;
        qDebug("ow_getpara response");
    }
    else if((response[1] == 0x14) && (response[2] ==0x01)) {
        cmd = ow_getscrpad;
        qDebug("ow_getscrpad response");
    }
    else{
        qDebug("response cmd field not recognized");
        return false;
    }

    board = response[3];
    boardx = board % NUM_DAUGHTER_BOARDS_X;
    boardy = board / NUM_DAUGHTER_BOARDS_X;

    row   = response[4];
    col   = response[5];
    // valid check
    if((cmd == ow_gettemp_ref) && (sel != all && sel != board_sel)){ // only work for in mode
        qDebug("gettemp_ref should sel all or board");
        return false;
    }
    // function
    Byte temp_ref[2];
    float f_temp_ref;
    Byte temp[2];
    Byte rom[8];
    Byte para[8];
    Byte scrpad[9];
    Byte set_coeff_res;
    Byte write_parameters_res;

    vector<float> ref_vec;

    if (cmd == ow_gettemp_ref)
    {
        if(sel != all && sel != board_sel){
            s_errorbox("gettemp_ref should sel all or board");
            return false;
        }
        if(sel == all){
            for (int ii = 0; ii < NUM_DAUGHTER_BOARDS_Y; ii ++)
            {
                for (int jj = 0; jj < NUM_DAUGHTER_BOARDS_X; jj ++)
                {
                    temp_ref[0] = response[6+(ii*NUM_DAUGHTER_BOARDS_X +jj)*2];
                    temp_ref[1] = response[6+(ii*NUM_DAUGHTER_BOARDS_X +jj)*2+1];
                    f_temp_ref = convert_reftemp(temp_ref);
                    qDebug("i ma here");
                    map.ref_map[ii*NUM_DAUGHTER_BOARDS_X +jj].update_temp_record(f_temp_ref,f_temp_ref);
                    ref_vec.push_back(f_temp_ref);

                    sleep(5000);
                }
            }

            //vector<float>::iterator it;
            //for(it=ref_vec.begin();it!=ref_vec.end();) {

            //}

//            float sum = std::accumulate(std::begin(ref_vec), std::end(ref_vec), 0.0);
//            float max =  *max_element(ref_vec.begin(),ref_vec.end());
//            float min =  *min_element(ref_vec.begin(),ref_vec.end());
//            float mean;
//            if(ref_vec.size() > 2) {
//                mean =  (sum-max-min) / (ref_vec.size()-2);

//                for (int ii = 0; ii < NUM_DAUGHTER_BOARDS_Y; ii ++)
//                {
//                    for (int jj = 0; jj < NUM_DAUGHTER_BOARDS_X; jj ++)
//                    {
//                        if(abs(ref_vec[ii*NUM_DAUGHTER_BOARDS_X+jj]-mean) > 1.2) {
//                            int board_indx = ii*NUM_DAUGHTER_BOARDS_X +jj+1;
//                            map.ref_map[ii*NUM_DAUGHTER_BOARDS_X +jj].update_temp_record(mean,mean);
//                            qInfo("Board %d's ref %f has been changed to %f",board_indx,ref_vec[ii*NUM_DAUGHTER_BOARDS_X+jj],mean);
//                        }
//                    }
//                }
//            }

            float sum_ref = 0;
            int counter = 0;

            for(int ij=0; ij<ref_vec.size(); ij++) {
                if(ref_vec[ij] < -30) {
                    counter++;
                }
                else {
                    sum_ref += ref_vec[ij];
                }
            }

            float mean_ref = sum_ref / (ref_vec.size()-counter);

            for (int ii = 0; ii < NUM_DAUGHTER_BOARDS_Y; ii ++)
            {
                for (int jj = 0; jj < NUM_DAUGHTER_BOARDS_X; jj ++)
                {
                    if(abs(ref_vec[ii*NUM_DAUGHTER_BOARDS_X+jj]-mean_ref) > 1.2) {
                        int board_indx = ii*NUM_DAUGHTER_BOARDS_X +jj+1;
                        map.ref_map[ii*NUM_DAUGHTER_BOARDS_X +jj].update_temp_record(mean_ref,mean_ref);
                        qInfo("Board %d's ref %f has been changed to %f",board_indx,ref_vec[ii*NUM_DAUGHTER_BOARDS_X+jj],mean_ref);
                    }
                }
            }

            ref_vec.clear();
        }
        else if(sel == board_sel)
        {
            temp_ref[0] = response[6];
            temp_ref[1] = response[7];
            f_temp_ref = convert_reftemp(temp_ref);
            qDebug("i ma here");
            map.ref_map[boardx*NUM_DAUGHTER_BOARDS_X +boardy].update_temp_record(f_temp_ref,f_temp_ref);
            sleep(100);
        }

        qDebug("update temtemp plan");

        if(sel == all)
            update_temp_plan();
    }
    else if (cmd == ow_gettemp)
    {
        if(sel == all)
        {
            qDebug("i'm here 000");
            for(int ii = 0; ii<NUM_DAUGHTER_BOARDS_Y;ii++){
                for(int jj = 0; jj<NUM_DAUGHTER_BOARDS_X;jj++){
                    for(int kk = 0; kk<NUM_CHIPS_Y;kk++){
                        for(int ll = 0; ll<NUM_CHIPS_X;ll++){
                            temp[0] = response[6+((ii*NUM_DAUGHTER_BOARDS_X +jj) * (NUM_CHIPS_X * NUM_CHIPS_Y) + kk * NUM_CHIPS_X + ll)*2];
                            temp[1] = response[6+((ii*NUM_DAUGHTER_BOARDS_X +jj) * (NUM_CHIPS_X * NUM_CHIPS_Y) + kk * NUM_CHIPS_X + ll)*2 +1];
                            //     mcu_uart->read_temp_board(ii);
                            // not correct, to be modify, TODO: temp is Byte, need to convert to float.
                            qDebug("set chip state boardx: %02x", jj);
                            qDebug("set chip state boardy: %02x", ii);
                            qDebug("set chip state row: %02x", kk);
                            qDebug("set chip state col: %02x", ll);

                            map.update_temp_record(ii, jj,kk,ll,fRet[jj * NUM_CHIPS_X +ll][ii*NUM_CHIPS_Y+kk][2],convert_temp(temp));
                        }
                    }
                }
            }
        }
        else if(sel == board_sel)
        {
            int right_count = 0;
            if(selAll == 0)
                map.reset_chip_state();
            //for(int kk = 0; kk<NUM_CHIPS_Y;kk++){
                //for(int ll = 0; ll<NUM_CHIPS_X;ll++){
            for(int kk = 0; kk<NUM_CHIPS_X;kk++){
                for(int ll = 0; ll<NUM_CHIPS_Y;ll++){
                    temp[0] = response[6+(kk * NUM_CHIPS_X + ll)*2];
                    temp[1] = response[6+(kk * NUM_CHIPS_X + ll)*2 +1];
                    //     mcu_uart->read_temp_board(ii);
                    // not correct, to be modify, TODO: temp is Byte, need to convert to float.
                    map.update_temp_record(boardx, boardy,kk,(9-ll),fRet[boardx * NUM_CHIPS_X +kk][boardy*NUM_CHIPS_Y+(9-ll)][2],convert_temp(temp));

                    if(abs(convert_temp(temp) - fRet[NUM_CHIPS_X*boardx+kk][NUM_CHIPS_Y*boardy+(9-ll)][2]) >= 1)
                    {
                       int board_indx = 1+ boardy*4 + boardx;
                       int chip_indx = 1+kk*10 +ll;
                       //qInfo("Board %d's Chip %d temperature: %f, Temp ref: %f. The diff is: %f-------------------------------------------> Board %d's Chip %d temp check goes WRONG!!!",board_indx,chip_indx,convert_temp(temp),fRet[NUM_CHIPS_X*boardx+kk][NUM_CHIPS_Y*boardy+(9-ll)][2],(abs(convert_temp(temp) - fRet[NUM_CHIPS_X*boardx+kk][NUM_CHIPS_Y*boardy+(9-ll)][2])),board_indx,chip_indx);
                       map.set_chip_state(boardx,boardy,kk,(9-ll),BAD);
                    }
                    else {
                       int board_indx = 1+ boardy*4 + boardx;
                       int chip_indx = 1+kk*10 +ll;
                       //qInfo("Board %d's Chip %d temperature: %f, Temp ref %f. The diff is: %f---> Board %d's Chip %d temp check PASS!!!",board_indx,chip_indx,convert_temp(temp),fRet[NUM_CHIPS_X*boardx+kk][NUM_CHIPS_Y*boardy+(9-ll)][2],(abs(convert_temp(temp) - fRet[NUM_CHIPS_X*boardx+kk][NUM_CHIPS_Y*boardy+(9-ll)][2])),board_indx,chip_indx);
                       map.set_chip_state(boardx,boardy,kk,(9-ll),GOOD);
                       right_count++;
                    }
                }
            }
            //qInfo("\r\nBoard %d Temperature check pass %d chips, fail %d chips.\r\n\r\n",1+ boardy*4 + boardx,right_count,NUM_CHIPS_X*NUM_CHIPS_Y-right_count);
            right_count = 0;
        }
        else if(sel == row_sel)
        {
            if(selAll == 0)
                map.reset_chip_state();
            for(int kk = 0; kk<NUM_CHIPS_Y;kk++){
                temp[0] = response[6+kk*2];
                temp[1] = response[6+kk*2 +1];
                //     mcu_uart->read_temp_board(ii);
                // not correct, to be modify, TODO: temp is Byte, need to convert to float.
                map.update_temp_record(boardx, boardy,kk,row,fRet[boardx * NUM_CHIPS_X +col][boardy*NUM_CHIPS_Y+kk][2],convert_temp(temp));

                if(abs(convert_temp(temp) - fRet[10*boardx+kk][10*boardy+col][2]) > 1)
                {
                   map.set_chip_state(boardx,boardy,kk,row,BAD);
                }
                else {
                   map.set_chip_state(boardx,boardy,kk,row,GOOD);
                }
            }
        }
        else if(sel == col_sel)
        {
            if(selAll == 0)
                map.reset_chip_state();
            for(int ll = 0; ll<NUM_CHIPS_X;ll++){
                temp[0] = response[6+ll*2];
                temp[1] = response[6+ll*2 +1];
                //     mcu_uart->read_temp_board(ii);
                // not correct, to be modify, TODO: temp is Byte, need to convert to float.
                map.update_temp_record(boardx, boardy,col,ll,fRet[boardx * NUM_CHIPS_X +ll][boardy*NUM_CHIPS_Y+row][2],convert_temp(temp));

                if(abs(convert_temp(temp) - fRet[10*boardx+row][10*boardy+ll][2]) > 1.5)
                {
                   map.set_chip_state(boardx,boardy,col,ll,BAD);
                }
                else {
                   map.set_chip_state(boardx,boardy,col,ll,GOOD);
                }
            }
        }
        else if(sel == individule)
        {
            if(selAll == 0)
                map.reset_chip_state();
            temp[0] = response[6];
            temp[1] = response[7];
            map.update_temp_record(boardx, boardy,row,col,fRet[ boardx * NUM_CHIPS_X +row][boardy *NUM_CHIPS_Y+col][2],convert_temp(temp));

            if(abs(convert_temp(temp) - fRet[10*boardx+row][10*boardy+col][2]) > 1.5)
            {
               map.set_chip_state(boardx,boardy,row,col,BAD);
            }
            else {
               map.set_chip_state(boardx,boardy,row,col,GOOD);
            }
        }
    }
    else if (cmd == ow_getromcode)
    {
        if(sel == all)
        {
            map.reset_chip_state();
            for(int ii = 0; ii<NUM_DAUGHTER_BOARDS_Y;ii++){
                for(int jj = 0; jj<NUM_DAUGHTER_BOARDS_X;jj++){
                    for(int kk = 0; kk<NUM_CHIPS_Y;kk++){
                        for(int ll = 0; ll<NUM_CHIPS_X;ll++){
                            rom[0] = response[6+((ii*NUM_DAUGHTER_BOARDS_X +jj) * (NUM_CHIPS_X * NUM_CHIPS_Y) + kk * NUM_CHIPS_X + ll)*8];
                            rom[1] = response[6+((ii*NUM_DAUGHTER_BOARDS_X +jj) * (NUM_CHIPS_X * NUM_CHIPS_Y) + kk * NUM_CHIPS_X + ll)*8 +1];
                            rom[2] = response[6+((ii*NUM_DAUGHTER_BOARDS_X +jj) * (NUM_CHIPS_X * NUM_CHIPS_Y) + kk * NUM_CHIPS_X + ll)*8 +2];
                            rom[3] = response[6+((ii*NUM_DAUGHTER_BOARDS_X +jj) * (NUM_CHIPS_X * NUM_CHIPS_Y) + kk * NUM_CHIPS_X + ll)*8 +3];
                            rom[4] = response[6+((ii*NUM_DAUGHTER_BOARDS_X +jj) * (NUM_CHIPS_X * NUM_CHIPS_Y) + kk * NUM_CHIPS_X + ll)*8 +4];
                            rom[5] = response[6+((ii*NUM_DAUGHTER_BOARDS_X +jj) * (NUM_CHIPS_X * NUM_CHIPS_Y) + kk * NUM_CHIPS_X + ll)*8 +5];
                            rom[6] = response[6+((ii*NUM_DAUGHTER_BOARDS_X +jj) * (NUM_CHIPS_X * NUM_CHIPS_Y) + kk * NUM_CHIPS_X + ll)*8 +6];
                            rom[7] = response[6+((ii*NUM_DAUGHTER_BOARDS_X +jj) * (NUM_CHIPS_X * NUM_CHIPS_Y) + kk * NUM_CHIPS_X + ll)*8 +7];

                            // Save to some structure TODO
                            map.update_rom_record(ii, jj,kk,ll,rom);

                            if(rom[7] != 0x28 || rom[1] != 0x00)
                            {
                               map.set_chip_state(jj,ii,kk,ll,BAD);
                            }
                            else {
                               map.set_chip_state(jj,ii,kk,ll,GOOD);
                            }
                        }
                    }
                }
            }
        }
        else if(sel == board_sel)
        {
            int right_count = 0;
            bool nonrepeat = TRUE;

            if(selAll == 0)
                map.reset_chip_state();
            for(int kk = 0; kk<NUM_CHIPS_X;kk++){
                for(int ll = 0; ll<NUM_CHIPS_Y;ll++){
            //for(int kk = 0; kk<NUM_CHIPS_Y;kk++){
                //for(int ll = 0; ll<NUM_CHIPS_X;ll++){
                    rom[0] = response[6+(kk * NUM_CHIPS_X + ll)*8];
                    rom[1] = response[6+(kk * NUM_CHIPS_X + ll)*8 +1];
                    rom[2] = response[6+(kk * NUM_CHIPS_X + ll)*8 +2];
                    rom[3] = response[6+(kk * NUM_CHIPS_X + ll)*8 +3];
                    rom[4] = response[6+(kk * NUM_CHIPS_X + ll)*8 +4];
                    rom[5] = response[6+(kk * NUM_CHIPS_X + ll)*8 +5];
                    rom[6] = response[6+(kk * NUM_CHIPS_X + ll)*8 +6];
                    rom[7] = response[6+(kk * NUM_CHIPS_X + ll)*8 +7];

                    // Save to some structure TODO
                    map.update_rom_record(boardx, boardy,kk,(9-ll),rom);

                    for(int mm=0; mm<=NUM_CHIPS_X; mm++){
                        for(int nn=(NUM_CHIPS_X-1); nn>=0;nn--) {
                            myChip my_chip;
                            map.get_chip_info(boardx, boardy,mm,nn,my_chip);

                            if(rom[7]==0x28&&my_chip.rom_code[7]==0x28&&my_chip.rom_code[0]==rom[0]&&my_chip.rom_code[1]==rom[1]&&my_chip.rom_code[2]==rom[2]&&my_chip.rom_code[3]==rom[3]&&my_chip.rom_code[4]==rom[4]&&my_chip.rom_code[5]==rom[5]&&my_chip.rom_code[6]==rom[6]&&my_chip.rom_code[7]==rom[7]) {
                                int board_indxx = 1+ boardy*NUM_DAUGHTER_BOARDS_X + boardx;
                                int chip_indxx = 1+kk*10 +ll;
                                if(!(mm==kk&&nn==(9-ll))) {
                                    qInfo("Board %d's Chip %d rom: %02x%02x%02x%02x%02x%02x%02x%02x-----------------------------------------> Board %d's Chip %d rom check REPEAT!!!",board_indxx,chip_indxx,rom[7],rom[6],rom[5],rom[4],rom[3],rom[2],rom[1],rom[0],board_indxx,chip_indxx);
                                    nonrepeat = FALSE;
                                }
                            }
                        }
                    }

                    if(rom[0] != 0x28 || rom[3] != 0x77|| rom[4] != 0x91|| rom[5] != 0x01|| rom[6] != 0x02)
                    {
                        int board_indx = 1+ boardy*4 + boardx;
                        int chip_indx = 1+kk*10 +ll;
                        qInfo("Board %d's Chip %d rom: %02x%02x%02x%02x%02x%02x%02x%02x-----------------------------------------> Board %d's Chip %d rom check goes WRONG!!!",board_indx,chip_indx,rom[0],rom[1],rom[2],rom[3],rom[4],rom[5],rom[6],rom[7],board_indx,chip_indx);
                        map.set_chip_state(boardx,boardy,kk,(9-ll),BAD);
                    }
                    else if(nonrepeat) {
                       int board_indx = 1+ boardy*4 + boardx;
                       int chip_indx = 1+kk*10 +ll;
                       qInfo("Board %d's Chip %d rom: %02x%02x%02x%02x%02x%02x%02x%02x---> Board %d's Chip %d rom check PASS!!!",board_indx,chip_indx,rom[0],rom[1],rom[2],rom[3],rom[4],rom[5],rom[6],rom[7],board_indx,chip_indx);
                       map.set_chip_state(boardx,boardy,kk,(9-ll),GOOD);
                       right_count++;
                    }
                }
            }
            qInfo("\r\nBoard %d ROM check pass %d chips, fail %d chips.\r\n\r\n",1+ boardy*4 + boardx,right_count,NUM_CHIPS_X*NUM_CHIPS_Y-right_count);
            right_count = 0;
        }
        else if(sel == row_sel)
        {
            if(selAll == 0)
                map.reset_chip_state();
            for(int kk = 0; kk<NUM_CHIPS_Y;kk++){
                rom[0] = response[6+kk*8];
                rom[1] = response[6+kk*8 +1];
                rom[2] = response[6+kk*8 +2];
                rom[3] = response[6+kk*8 +3];
                rom[4] = response[6+kk*8 +4];
                rom[5] = response[6+kk*8 +5];
                rom[6] = response[6+kk*8 +6];
                rom[7] = response[6+kk*8 +7];

                qDebug("rom[0]:%02x", rom[0]);
                qDebug("rom[1]:%02x", rom[1]);
                qDebug("rom[2]:%02x", rom[2]);
                qDebug("rom[3]:%02x", rom[3]);
                qDebug("rom[4]:%02x", rom[4]);
                qDebug("rom[5]:%02x", rom[5]);
                qDebug("rom[6]:%02x", rom[6]);
                qDebug("rom[7]:%02x", rom[7]);

                if(rom[7] != 0x28 || rom[1] != 0x00)
                {
                   map.set_chip_state(boardx,boardy,kk,row,BAD);
                   qDebug("set chip state boardx: %02x", boardx);
                   qDebug("set chip state boardy: %02x", boardy);
                   qDebug("set chip state row: %02x", row);
                   qDebug("set chip state col: %02x", col);
                }
                else {
                   map.set_chip_state(boardx,boardy,kk,row,GOOD);
                   qDebug("set chip state boardx: %02x", boardx);
                   qDebug("set chip state boardy: %02x", boardy);
                   qDebug("set chip state row: %02x", row);
                   qDebug("set chip state col: %02x", col);
                }
                // Save to some structure TODO
                map.update_rom_record(boardx, boardy,kk,row,rom);
            }
        }
        else if(sel == col_sel)
        {
            if(selAll == 0)
                map.reset_chip_state();
            for(int ll = 0; ll<NUM_CHIPS_X;ll++){
                rom[0] = response[6+ll*8];
                rom[1] = response[6+ll*8 +1];
                rom[2] = response[6+ll*8 +2];
                rom[3] = response[6+ll*8 +3];
                rom[4] = response[6+ll*8 +4];
                rom[5] = response[6+ll*8 +5];
                rom[6] = response[6+ll*8 +6];
                rom[7] = response[6+ll*8 +7];


                if(rom[7] != 0x28 || rom[1] != 0x00)
                {
                   map.set_chip_state(boardx,boardy,col,ll,BAD);
                }
                else {
                   map.set_chip_state(boardx,boardy,col,ll,GOOD);
                }
                // Save to some structure TODO
                map.update_rom_record(boardx, boardy,col,ll,rom);
            }
        }
        else if(sel == individule)
        {
            rom[0] = response[6];
            rom[1] = response[7];
            rom[2] = response[8];
            rom[3] = response[9];
            rom[4] = response[10];
            rom[5] = response[11];
            rom[6] = response[12];
            rom[7] = response[13];

            if(selAll == 0)
                map.reset_chip_state();

            qDebug("rom[0]:%02x", rom[0]);
            qDebug("rom[1]:%02x", rom[1]);
            qDebug("rom[2]:%02x", rom[2]);
            qDebug("rom[3]:%02x", rom[3]);
            qDebug("rom[4]:%02x", rom[4]);
            qDebug("rom[5]:%02x", rom[5]);
            qDebug("rom[6]:%02x", rom[6]);
            qDebug("rom[7]:%02x", rom[7]);

            if(rom[7] != 0x28 || rom[1] != 0x00)
            {
               map.set_chip_state(boardx,boardy,row,col,BAD);
               qDebug("set chip state boardx: %02x", boardx);
               qDebug("set chip state boardy: %02x", boardy);
               qDebug("set chip state row: %02x", row);
               qDebug("set chip state col: %02x", col);
            }
            else {
               map.set_chip_state(boardx,boardy,row,col,GOOD);
               qDebug("set chip state boardx: %02x", boardx);
               qDebug("set chip state boardy: %02x", boardy);
               qDebug("set chip state row: %02x", row);
               qDebug("set chip state col: %02x", col);
            }
            // Save to some structure TODO
            map.update_rom_record(boardx, boardy,row,col,rom);
        }
    }
    else if (cmd == ow_getpara)
    {
        if(sel == board_sel)
        {
            int right_count = 0;


            if(selAll == 0)
                map.reset_chip_state();
            for(int kk = 0; kk<NUM_CHIPS_X;kk++){
                for(int ll = 0; ll<NUM_CHIPS_Y;ll++){
            //for(int kk = 0; kk<NUM_CHIPS_Y;kk++){
                //for(int ll = 0; ll<NUM_CHIPS_X;ll++){
                    para[0] = response[6+(kk * NUM_CHIPS_X + ll)*8];
                    para[1] = response[6+(kk * NUM_CHIPS_X + ll)*8 +1];
                    para[2] = response[6+(kk * NUM_CHIPS_X + ll)*8 +2];
                    para[3] = response[6+(kk * NUM_CHIPS_X + ll)*8 +3];
                    para[4] = response[6+(kk * NUM_CHIPS_X + ll)*8 +4];
                    para[5] = response[6+(kk * NUM_CHIPS_X + ll)*8 +5];
                    para[6] = response[6+(kk * NUM_CHIPS_X + ll)*8 +6];
                    para[7] = response[6+(kk * NUM_CHIPS_X + ll)*8 +7];

                    // Save to some structure TODO
                    //map.update_rom_record(boardx, boardy,kk,(9-ll),rom);


                    if(para[7] != 0x1c || para[2] != 0x81|| para[1] != 0x00|| para[0] != 0x02 )
                    {
                        int board_indx = 1+ boardy*4 + boardx;
                        int chip_indx = 1+kk*10 +ll;
                        qInfo("Board %d's Chip %d para: %02x%02x%02x%02x%02x%02x%02x%02x-----------------------------------------> Board %d's Chip %d para check goes WRONG!!!",board_indx,chip_indx,para[0],para[1],para[2],para[3],para[4],para[5],para[6],para[7],board_indx,chip_indx);
                        map.set_chip_state(boardx,boardy,kk,(9-ll),BAD);
                    }
                    else {
                       int board_indx = 1+ boardy*4 + boardx;
                       int chip_indx = 1+kk*10 +ll;
                       qInfo("Board %d's Chip %d para: %02x%02x%02x%02x%02x%02x%02x%02x---> Board %d's Chip %d para check PASS!!!",board_indx,chip_indx,para[0],para[1],para[2],para[3],para[4],para[5],para[6],para[7],board_indx,chip_indx);
                       map.set_chip_state(boardx,boardy,kk,(9-ll),GOOD);
                       right_count++;
                    }
                }
            }
            qInfo("\r\nBoard %d PARA check pass %d chips, fail %d chips.\r\n\r\n",1+ boardy*4 + boardx,right_count,NUM_CHIPS_X*NUM_CHIPS_Y-right_count);
            right_count = 0;
        }

    }
    else if (cmd == ow_getscrpad)
    {
        if(sel == board_sel)
        {
            int right_count = 0;


            if(selAll == 0)
                map.reset_chip_state();
            for(int kk = 0; kk<NUM_CHIPS_X;kk++){
                for(int ll = 0; ll<NUM_CHIPS_Y;ll++){
            //for(int kk = 0; kk<NUM_CHIPS_Y;kk++){
                //for(int ll = 0; ll<NUM_CHIPS_X;ll++){
                    scrpad[0] = response[6+(kk * NUM_CHIPS_X + ll)*9];
                    scrpad[1] = response[6+(kk * NUM_CHIPS_X + ll)*9 +1];
                    scrpad[2] = response[6+(kk * NUM_CHIPS_X + ll)*9 +2];
                    scrpad[3] = response[6+(kk * NUM_CHIPS_X + ll)*9 +3];
                    scrpad[4] = response[6+(kk * NUM_CHIPS_X + ll)*9 +4];
                    scrpad[5] = response[6+(kk * NUM_CHIPS_X + ll)*9 +5];
                    scrpad[6] = response[6+(kk * NUM_CHIPS_X + ll)*9 +6];
                    scrpad[7] = response[6+(kk * NUM_CHIPS_X + ll)*9 +7];
                    scrpad[8] = response[6+(kk * NUM_CHIPS_X + ll)*9 +8];

                    // Save to some structure TODO
                    //map.update_rom_record(boardx, boardy,kk,(9-ll),rom);



                    if(scrpad[7] != 0xff ||scrpad[6] != 0x00 ||scrpad[5] != 0x00 || scrpad[4] != 0x7f|| scrpad[3] != 0x05|| scrpad[2] != 0x64 )
                    {
                        int board_indx = 1+ boardy*4 + boardx;
                        int chip_indx = 1+kk*10 +ll;
                        qInfo("Board %d's Chip %d scrpad: %02x%02x%02x%02x%02x%02x%02x%02x%02x-----------------------------------------> Board %d's Chip %d scrpad check goes WRONG!!!",board_indx,chip_indx,scrpad[0],scrpad[1],scrpad[2],scrpad[3],scrpad[4],scrpad[5],scrpad[6],scrpad[7],scrpad[8],board_indx,chip_indx);
                        map.set_chip_state(boardx,boardy,kk,(9-ll),BAD);
                    }
                    else {
                       int board_indx = 1+ boardy*4 + boardx;
                       int chip_indx = 1+kk*10 +ll;
                       qInfo("Board %d's Chip %d scrpad: %02x%02x%02x%02x%02x%02x%02x%02x%02x---> Board %d's Chip %d scrpad check PASS!!!",board_indx,chip_indx,scrpad[0],scrpad[1],scrpad[2],scrpad[3],scrpad[4],scrpad[5],scrpad[6],scrpad[7],scrpad[8],board_indx,chip_indx);
                       map.set_chip_state(boardx,boardy,kk,(9-ll),GOOD);
                       right_count++;
                    }
                }
            }
            qInfo("\r\nBoard %d SCRPAD check pass %d chips, fail %d chips.\r\n\r\n",1+ boardy*4 + boardx,right_count,NUM_CHIPS_X*NUM_CHIPS_Y-right_count);
            right_count = 0;
        }

    }
    else if(cmd == ow_setcoeff) {
        if(sel == board_sel) {
            set_coeff_res = response[6];

            int board_indx = 1+ boardy*4 + boardx;
            if(set_coeff_res == 0x01) {
                qInfo("Board %d coeff set Done!", board_indx);
            }
            else {
                qInfo("Board %d coeff set Error!!!", board_indx);
                sleep(10000);
            }
        }


        sleep(500);
    }
    else if(cmd == ow_writeparameters) {
        if(sel == board_sel || sel == all) {
            write_parameters_res = response[6];

            int board_indx = 1+ boardy*4 + boardx;
            if(write_parameters_res == 0x01) {
                qInfo("\r\nMBoard parameters set Done!\r\n");
                qInfo("*************************************************");
            }
            else {
                qInfo("\r\nMBoard parameters set Error!!!\r\n");
                qInfo("*************************************************");
                sleep(5000);
            }
        }
        sleep(100);
    }
    else {
        //qDebug("TODO: reponse need to be parsed");
        qDebug("executed command without payload send back");
    }
    return true;
}




bool myMCUAgent::parsing_response_new(Byte * response_a, int selAll, int count, vector<vector<float>> &vv, vector<float> &v, vector<float> &ref_vec,float temp_set, bool ready)
{
    //    ow_doconvert        0x1100: 单纯发送convertT指令（含6ms dealy）
    //    ow_gettemp          0x1101：读取当前温度值（含convertT指令，返回原始16-bit读值 (MSB先行)）
    //    ow_gettemp_ref      0x1102：读取Si7051温度值（返回原始16-bit读值 (MSB先行)）
    //    ow_writeparameters  0x1200：功能为设置ROM code的crc和初始化相应scratchpad value，无需payload
    //    ow_getromcode       0x1201：读取ROM code （payload中ROM code为MSB先行）
    //    ow_setcoeff         0x1300：设置校准参数，发送计算好的3-byte coeff到MCU，低字节先行(对应芯片scratchpad中adc_coeff由低到高次序)
    //    ow_getpara          0x1400: 读取8-byte parameter
    //    ow_getscrpad        0x1401: 读取9-byte scratchpad

    //00 0E 5A 11 02 00 00 00 68 AC 69 80 FE FF

    //char response[16]  = { 0x5a, 0x11, 0x02, 0x00, 0x00, 0x00, 0x68, 0xac, 0x69, 0x80,0x68, 0xac, 0x69, 0x80,0xfe, 0xff};
    Byte* response = response_a;

    UartCmdType cmd;
    UartSelype sel;
    int boardx;
    int boardy;
    int board;
    int row;
    int col;
    //Byte * payload;
    qDebug("sel byte : %02x", response[0]);
    if(response[0] == 0x5a )
    {
        sel = all; // sel all
    }
    else if(response[0] == 0x9e){
        sel = individule; // sel individual
    }
    else if(response[0] == 0x6b){
        sel = board_sel; // sel board
    }
    else if(response[0] == 0x7c){
        sel = row_sel; //sel row
    }
    else if(response[0] == 0x8d){
        sel = col_sel; //sel col
    }
    else{
        qDebug("response sel field not recognized");
        return false;
    }
    if((response[1] == 0x11) && (response[2] ==0x00)) {
        cmd = ow_doconvert;//ow_doconvert
        qDebug("ow_doconvert response");
    }
    else if((response[1] == 0x11) && (response[2] ==0x01)) {
        cmd = ow_gettemp;
        qDebug("ow_gettemp response");
    }
    else if((response[1] == 0x11) && (response[2] ==0x02)) {
        cmd = ow_gettemp_ref;
        qDebug("ow_gettemp_ref response");
    }
    else if((response[1] == 0x12) && (response[2] ==0x00)) {
        cmd = ow_writeparameters;
        qDebug("ow_writeparameters response");
    }
    else if((response[1] == 0x12) && (response[2] ==0x01)) {
        cmd = ow_getromcode;
        qDebug("ow_getromcode response");
    }
    else if((response[1] == 0x13) && (response[2] ==0x00)) {
        cmd = ow_setcoeff;
        qDebug("ow_setcoeff response");
    }
    else if((response[1] == 0x14) && (response[2] ==0x00)) {
        cmd = ow_getpara;
        qDebug("ow_getpara response");
    }
    else if((response[1] == 0x14) && (response[2] ==0x01)) {
        cmd = ow_getscrpad;
        qDebug("ow_getscrpad response");
    }
    else{
        qDebug("response cmd field not recognized");
        return false;
    }

    board = response[3];
    boardx = board % NUM_DAUGHTER_BOARDS_X;
    boardy = board / NUM_DAUGHTER_BOARDS_X;

    row   = response[4];
    col   = response[5];
    // valid check
    if((cmd == ow_gettemp_ref) && (sel != all && sel != board_sel)){ // only work for in mode
        qDebug("gettemp_ref should sel all or board");
        return false;
    }
    // function
    Byte temp_ref[2];
    float f_temp_ref;
    Byte temp[2];
    Byte rom[8];
    Byte para[8];
    Byte scrpad[9];
    Byte set_coeff_res;
    Byte write_parameters_res;

    //vector<float> ref_vec;

    //vv.resize(5);

    //for (int i = 0; i < vv.size(); i++) {
        //vv[i].resize(20);
        //qInfo("i: %d", i);
    //}


    if (cmd == ow_gettemp_ref)
    {
        if(sel != all && sel != board_sel){
            s_errorbox("gettemp_ref should sel all or board");
            return false;
        }
        if(sel == all){
//            for (int ii = 0; ii < NUM_DAUGHTER_BOARDS_Y; ii ++)
//            {
//                for (int jj = 0; jj < NUM_DAUGHTER_BOARDS_X; jj ++)
//                {
//                    temp_ref[0] = response[6+(ii*NUM_DAUGHTER_BOARDS_X +jj)*2];
//                    temp_ref[1] = response[6+(ii*NUM_DAUGHTER_BOARDS_X +jj)*2+1];
//                    f_temp_ref = convert_reftemp(temp_ref);
//                    qInfo("i ma here");
//                    //map.ref_map[ii*NUM_DAUGHTER_BOARDS_X +jj].update_temp_record(f_temp_ref,f_temp_ref);
//                    //ref_vec.push_back(f_temp_ref);

//                    vv[ii*NUM_DAUGHTER_BOARDS_X + jj].push_back(f_temp_ref);
//                    //vv[ii*NUM_DAUGHTER_BOARDS_X + jj][count] = f_temp_ref;


//                    if(count == 19) {
//                        vector<float>::iterator it;
//                        vector<float> resultSet_filter;

//                        for(it=vv[ii*NUM_DAUGHTER_BOARDS_X + jj].begin(); it!=vv[ii*NUM_DAUGHTER_BOARDS_X + jj].end();) {
//                            if(abs(*it-temp_set) > 5 && vv[ii*NUM_DAUGHTER_BOARDS_X + jj].size() > 1)
//                                it = vv[ii*NUM_DAUGHTER_BOARDS_X + jj].erase(it);
//                            else
//                                ++it;
//                        }

//                        for(int idx=vv[ii*NUM_DAUGHTER_BOARDS_X + jj].size()/2; idx<vv[ii*NUM_DAUGHTER_BOARDS_X + jj].size(); idx++) {
//                            resultSet_filter.push_back(vv[ii*NUM_DAUGHTER_BOARDS_X + jj][idx]);
//                        }

//                        float sum = std::accumulate(std::begin(resultSet_filter), std::end(resultSet_filter), 0.0);
//                        float max =  *max_element(resultSet_filter.begin(),resultSet_filter.end());
//                        float min =  *min_element(resultSet_filter.begin(),resultSet_filter.end());
//                        float mean =  sum / resultSet_filter.size();

//                        if(resultSet_filter.size() > 2) {
//                            mean = (sum-max-min)/(resultSet_filter.size()-2);
//                        }

//                        qInfo("Mean value of Si7051 on Board %d is: %f",(ii*NUM_DAUGHTER_BOARDS_X + jj+1),mean);
//                        map.ref_map[ii*NUM_DAUGHTER_BOARDS_X +jj].update_temp_record(mean,mean);
//                        ref_vec.push_back(mean);
//                    }

//                    sleep(5000);
//                }
//            }

//            //vector<float>::iterator it;
//            //for(it=ref_vec.begin();it!=ref_vec.end();) {

//            //}

////            float sum = std::accumulate(std::begin(ref_vec), std::end(ref_vec), 0.0);
////            float max =  *max_element(ref_vec.begin(),ref_vec.end());
////            float min =  *min_element(ref_vec.begin(),ref_vec.end());
////            float mean;
////            if(ref_vec.size() > 2) {
////                mean =  (sum-max-min) / (ref_vec.size()-2);

////                for (int ii = 0; ii < NUM_DAUGHTER_BOARDS_Y; ii ++)
////                {
////                    for (int jj = 0; jj < NUM_DAUGHTER_BOARDS_X; jj ++)
////                    {
////                        if(abs(ref_vec[ii*NUM_DAUGHTER_BOARDS_X+jj]-mean) > 1.2) {
////                            int board_indx = ii*NUM_DAUGHTER_BOARDS_X +jj+1;
////                            map.ref_map[ii*NUM_DAUGHTER_BOARDS_X +jj].update_temp_record(mean,mean);
////                            qInfo("Board %d's ref %f has been changed to %f",board_indx,ref_vec[ii*NUM_DAUGHTER_BOARDS_X+jj],mean);
////                        }
////                    }
////                }
////            }

//            if(count == 19) {
//                float sum_ref = 0;
//                int counter = 0;

//                for(int ij=0; ij<ref_vec.size(); ij++) {
//                    if(ref_vec[ij] < -30) {
//                        counter++;
//                    }
//                    else {
//                        sum_ref += ref_vec[ij];
//                    }
//                }

//                float mean_ref = sum_ref / (ref_vec.size()-counter);

//                for (int ii = 0; ii < NUM_DAUGHTER_BOARDS_Y; ii ++)
//                {
//                    for (int jj = 0; jj < NUM_DAUGHTER_BOARDS_X; jj ++)
//                    {
//                        if(abs(ref_vec[ii*NUM_DAUGHTER_BOARDS_X+jj]-mean_ref) > 1.2) {
//                            int board_indx = ii*NUM_DAUGHTER_BOARDS_X +jj+1;
//                            map.ref_map[ii*NUM_DAUGHTER_BOARDS_X +jj].update_temp_record(mean_ref,mean_ref);
//                            qInfo("Board %d's ref %f has been changed to %f",board_indx,ref_vec[ii*NUM_DAUGHTER_BOARDS_X+jj],mean_ref);
//                        }
//                    }
//                }

//                ref_vec.clear();
//            }
        }
        else if(sel == board_sel)
        {
            temp_ref[0] = response[6];
            temp_ref[1] = response[7];
            f_temp_ref = convert_reftemp(temp_ref);
            qDebug("i ma here");
            v.push_back(f_temp_ref);
            qInfo("Board %d's Si7051 get temp: %f",(boardy*NUM_DAUGHTER_BOARDS_X +boardx+1), f_temp_ref);

            //map.ref_map[boardx*NUM_DAUGHTER_BOARDS_X +boardy].update_temp_record(f_temp_ref,f_temp_ref);
            sleep(100);

            if(count == 9) {
                qInfo("wait 0.5s after first 10 times sample.");
                sleep(500);
            }

            if(count == 19) {
                vector<float>::iterator it;
                vector<float> resultSet_filter;

                for(it=v.begin(); it!=v.end();) {
                    if(abs(*it-temp_set) > 5 && v.size() > 1)
                        it = v.erase(it);
                    else
                        ++it;
                }

                for(int idx=v.size()/2; idx<v.size(); idx++) {
                    resultSet_filter.push_back(v[idx]);
                }

                float sum = std::accumulate(std::begin(resultSet_filter), std::end(resultSet_filter), 0.0);
                float max =  *max_element(resultSet_filter.begin(),resultSet_filter.end());
                float min =  *min_element(resultSet_filter.begin(),resultSet_filter.end());
                float mean =  sum / resultSet_filter.size();

                if(resultSet_filter.size() > 2) {
                    mean = (sum-max-min)/(resultSet_filter.size()-2);
                }

                qInfo("Mean value of Si7051 on Board %d is: %f",(boardy*NUM_DAUGHTER_BOARDS_X +boardx+1),mean);
                //map.ref_map[ii*NUM_DAUGHTER_BOARDS_X +jj].update_temp_record(mean,mean);
                map.ref_map[boardy*NUM_DAUGHTER_BOARDS_X +boardx].update_temp_record(mean,mean);
                ref_vec.push_back(mean);

                v.clear();
            }

            if(ready) {
                float sum_ref = 0;
                int counter = 0;

                for(int ij=0; ij<ref_vec.size(); ij++) {
                    if(ref_vec[ij] < -30) {
                        counter++;
                    }
                    else {
                        sum_ref += ref_vec[ij];
                    }
                }

                float mean_ref = sum_ref / (ref_vec.size()-counter);

                for (int ii = 0; ii < NUM_DAUGHTER_BOARDS_Y; ii ++)
                {
                    for (int jj = 0; jj < NUM_DAUGHTER_BOARDS_X; jj ++)
                    {
                        if(abs(ref_vec[ii*NUM_DAUGHTER_BOARDS_X+jj]-mean_ref) > 1.2) {
                            int board_indx = ii*NUM_DAUGHTER_BOARDS_X +jj+1;
                            map.ref_map[ii*NUM_DAUGHTER_BOARDS_X +jj].update_temp_record(mean_ref,mean_ref);
                            qInfo("Board %d's ref %f has been changed to %f",board_indx,ref_vec[ii*NUM_DAUGHTER_BOARDS_X+jj],mean_ref);
                        }
                    }
                }
                update_temp_plan();
                ref_vec.clear();
            }
        }

        qDebug("update temtemp plan");

        if(sel == all)
            update_temp_plan();
    }
    else {
        //qDebug("TODO: reponse need to be parsed");
        qDebug("executed command without payload send back");
    }
    return true;
}



float myMCUAgent::convert_reftemp(Byte a[2])
{
    return  (a[0] * 256 + a[1]) *175.72/65536-46.85;

}

float myMCUAgent::convert_temp(Byte a[2])
{
    return  (a[0] * 256 + a[1]) * (0.0625);

}

void myMCUAgent::sleep(long int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);

    while(QTime::currentTime() < reachTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}

void  myMCUAgent::execute_cmd_check_stable(float temp_set)
{
    Byte * char_cmd;
    Byte response_len[2];
    int send_len;
    vector<float> resultSet;
    vector<double> stdev_vec;
    double stdev;
    //double mean_stdev;

    int boardx = 0;
    int boardy = 0;
    int row = 0;
    int col = 0;
    Byte* payload;
    int payload_len = 0;

    int sel = 1; //board
    int cmd = 2; //get ref

    int timeout_count = 0;

    do{
        pack_cmd(sel, cmd, boardy*NUM_DAUGHTER_BOARDS_X + boardx, row, col,  payload,  payload_len, char_cmd, &send_len);
        for(int ii = 0; ii < send_len; ii++)
        {
            qDebug("%02x",char_cmd[ii]);
        }

        //   if(this->mcu_uart->is_opened!=TRUE)
        if(this->mcu_uart->open()!=TRUE)
        {
            s_errorbox("cmd execute error, uart is not opened");
            return;
        }

        for(int ii = 0; ii < send_len; ii++)
        {
            qDebug("len %02x",char_cmd[ii]);
        }


        this->mcu_uart->write(char_cmd,send_len);
        delete char_cmd;

        if(this->mcu_uart->read(response_len,2) == false)
        {
            qDebug("mcu uart comand failed due to read timeout");
            return ;
        }

        uint res_len = response_len[0] * 256 + response_len[1]-2;
        Byte * response_res;
        qDebug("need to read %d data", res_len);
        // exit(0);
        qDebug("port: %d, baud: %d, data:%d, parity:%d, stop:%d, flow;%d", this->mcu_uart->port_id, this->mcu_uart->dcb.BaudRate, this->mcu_uart->dcb.ByteSize,this->mcu_uart->dcb.Parity,this->mcu_uart->dcb.StopBits,this->mcu_uart->dcb.fInX);
        //exit(0);

        response_res = (Byte*)malloc(sizeof(Byte)*res_len);
        if(this->mcu_uart->read(response_res,res_len) == false)
        {
            qDebug("mcu uart comand failed due to read timeout");
            return ;
        }
        qDebug("before parsing [0]:%02x", response_len[0]);
        qDebug("before parsing [1]:%02x", response_len[1]);
        for(uint ii = 0; ii < res_len; ii++){
            qDebug("before parsing [%d]:%02x", ii,response_res[ii]);
        }
        parsing_response_getref(response_res, resultSet);
        sleep(500);
        timeout_count++;

        if(timeout_count == 10000){
            abort();
        }

        if(abs(resultSet.back()-temp_set) > 6) {
            if(boardx < (NUM_DAUGHTER_BOARDS_X-1)) {
                boardx++;
            }    
            else if(boardx == (NUM_DAUGHTER_BOARDS_X-1) && boardy < (NUM_DAUGHTER_BOARDS_Y-1)) {
                boardx = 0;
                boardy++;
            }
        }

    }while(abs(resultSet.back()-temp_set) > 4);

    resultSet.clear();
    timeout_count = 0;
    boardx = 0;
    boardy = 0;

//    do{  //check stable by Si7051 left up
//        stdev_vec.clear();
//        resultSet.clear();

//        for(int iii=0; iii<10; iii++) {
//            pack_cmd(sel, cmd, boardy*NUM_DAUGHTER_BOARDS_X + boardx, row, col,  payload,  payload_len, char_cmd, &send_len);
//            for(int ii = 0; ii < send_len; ii++)
//            {
//                qDebug("%02x",char_cmd[ii]);
//            }

//            //   if(this->mcu_uart->is_opened!=TRUE)
//            if(this->mcu_uart->open()!=TRUE)
//            {
//                s_errorbox("cmd execute error, uart is not opened");
//                return;
//            }

//            for(int ii = 0; ii < send_len; ii++)
//            {
//                qDebug("len %02x",char_cmd[ii]);
//            }


//            this->mcu_uart->write(char_cmd,send_len);
//            delete char_cmd;

//            if(this->mcu_uart->read(response_len,2) == false)
//            {
//                qDebug("mcu uart comand failed due to read timeout");
//                return ;
//            }

//            uint res_len = response_len[0] * 256 + response_len[1]-2;
//            Byte * response_res;
//            qDebug("need to read %d data", res_len);
//            // exit(0);
//            qDebug("port: %d, baud: %d, data:%d, parity:%d, stop:%d, flow;%d", this->mcu_uart->port_id, this->mcu_uart->dcb.BaudRate, this->mcu_uart->dcb.ByteSize,this->mcu_uart->dcb.Parity,this->mcu_uart->dcb.StopBits,this->mcu_uart->dcb.fInX);
//            //exit(0);

//            response_res = (Byte*)malloc(sizeof(Byte)*res_len);
//            if(this->mcu_uart->read(response_res,res_len) == false)
//            {
//                qDebug("mcu uart comand failed due to read timeout");
//                return ;
//            }
//            qDebug("before parsing [0]:%02x", response_len[0]);
//            qDebug("before parsing [1]:%02x", response_len[1]);
//            for(uint ii = 0; ii < res_len; ii++){
//                qDebug("before parsing [%d]:%02x", ii,response_res[ii]);
//            }
//            parsing_response_getref(response_res, resultSet);

//            sleep(10000);
//        }

//          vector<float>::iterator it;

//          for(it=resultSet.begin(); it!=resultSet.end();) {
//              if(abs(*it-temp_set) > 5)
//                  it = resultSet.erase(it);
//              else
//                  ++it;
//          }

//        double sum = std::accumulate(std::begin(resultSet), std::end(resultSet), 0.0);
//        double mean =  sum / resultSet.size();

//        double accum  = 0.0;
//        std::for_each (std::begin(resultSet), std::end(resultSet), [&](const double d) {
//            accum  += (d-mean)*(d-mean);
//        });

//        stdev = sqrt(accum/(resultSet.size()-1));
//        stdev_vec.push_back(stdev);
//        qInfo("board %d's stdev is: %lf", (boardy*4+boardx+1), stdev);

//        resultSet.clear();

//        if(stdev > 0.7) {
//            if(boardx < (NUM_DAUGHTER_BOARDS_X-1)) {
//                boardx++;
//            }
//            else if(boardx == (NUM_DAUGHTER_BOARDS_X-1) && boardy < (NUM_DAUGHTER_BOARDS_Y-1)) {
//                boardx = 0;
//                boardy++;
//            }
//        }

//        timeout_count++;
//        if(timeout_count == 10000){
//            abort();
//        }

//    }while(stdev > 0.05);

/////////////////////////////////////////////////////////////////////////////////////////////////
//    resultSet.clear();
//    timeout_count = 0;
//    boardx = 0;
//    boardy = NUM_DAUGHTER_BOARDS_Y-1;

//    do{  //check stable by Si7051 left down
//        stdev_vec.clear();
//        resultSet.clear();

//        for(int iii=0; iii<10; iii++) {
//            pack_cmd(sel, cmd, boardy*NUM_DAUGHTER_BOARDS_X + boardx, row, col,  payload,  payload_len, char_cmd, &send_len);
//            for(int ii = 0; ii < send_len; ii++)
//            {
//                qDebug("%02x",char_cmd[ii]);
//            }

//            //   if(this->mcu_uart->is_opened!=TRUE)
//            if(this->mcu_uart->open()!=TRUE)
//            {
//                s_errorbox("cmd execute error, uart is not opened");
//                return;
//            }

//            for(int ii = 0; ii < send_len; ii++)
//            {
//                qDebug("len %02x",char_cmd[ii]);
//            }


//            this->mcu_uart->write(char_cmd,send_len);
//            delete char_cmd;

//            if(this->mcu_uart->read(response_len,2) == false)
//            {
//                qDebug("mcu uart comand failed due to read timeout");
//                return ;
//            }

//            uint res_len = response_len[0] * 256 + response_len[1]-2;
//            Byte * response_res;
//            qDebug("need to read %d data", res_len);
//            // exit(0);
//            qDebug("port: %d, baud: %d, data:%d, parity:%d, stop:%d, flow;%d", this->mcu_uart->port_id, this->mcu_uart->dcb.BaudRate, this->mcu_uart->dcb.ByteSize,this->mcu_uart->dcb.Parity,this->mcu_uart->dcb.StopBits,this->mcu_uart->dcb.fInX);
//            //exit(0);

//            response_res = (Byte*)malloc(sizeof(Byte)*res_len);
//            if(this->mcu_uart->read(response_res,res_len) == false)
//            {
//                qDebug("mcu uart comand failed due to read timeout");
//                return ;
//            }
//            qDebug("before parsing [0]:%02x", response_len[0]);
//            qDebug("before parsing [1]:%02x", response_len[1]);
//            for(uint ii = 0; ii < res_len; ii++){
//                qDebug("before parsing [%d]:%02x", ii,response_res[ii]);
//            }
//            parsing_response_getref(response_res, resultSet);

//            sleep(10000);
//        }

//          vector<float>::iterator it;

//          for(it=resultSet.begin(); it!=resultSet.end();) {
//              if(abs(*it-temp_set) > 5)
//                  it = resultSet.erase(it);
//              else
//                  ++it;
//          }

//        double sum = std::accumulate(std::begin(resultSet), std::end(resultSet), 0.0);
//        double mean =  sum / resultSet.size();

//        double accum  = 0.0;
//        std::for_each (std::begin(resultSet), std::end(resultSet), [&](const double d) {
//            accum  += (d-mean)*(d-mean);
//        });

//        stdev = sqrt(accum/(resultSet.size()-1));
//        stdev_vec.push_back(stdev);
//        qInfo("board %d's stdev is: %lf", (boardy*4+boardx+1), stdev);

//        resultSet.clear();

//        if(stdev > 0.7) {
//            if(boardx < (NUM_DAUGHTER_BOARDS_X-1)) {
//                boardx++;
//            }
//            else if(boardx == (NUM_DAUGHTER_BOARDS_X-1) && boardy > 0) {
//                boardx = 0;
//                boardy--;
//            }
//        }

//        timeout_count++;
//        if(timeout_count == 10000){
//            abort();
//        }

//    }while(stdev > 0.05);

///////////////////////////////////////////////////////////////////////////////////////////////
    resultSet.clear();
    timeout_count = 0;
    boardx = NUM_DAUGHTER_BOARDS_X-1;
    boardy = 0;

    do{  //check stable by Si7051 right up
        stdev_vec.clear();
        resultSet.clear();

        for(int iii=0; iii<10; iii++) {
            pack_cmd(sel, cmd, boardy*NUM_DAUGHTER_BOARDS_X + boardx, row, col,  payload,  payload_len, char_cmd, &send_len);
            for(int ii = 0; ii < send_len; ii++)
            {
                qDebug("%02x",char_cmd[ii]);
            }

            //   if(this->mcu_uart->is_opened!=TRUE)
            if(this->mcu_uart->open()!=TRUE)
            {
                s_errorbox("cmd execute error, uart is not opened");
                return;
            }

            for(int ii = 0; ii < send_len; ii++)
            {
                qDebug("len %02x",char_cmd[ii]);
            }


            this->mcu_uart->write(char_cmd,send_len);
            delete char_cmd;

            if(this->mcu_uart->read(response_len,2) == false)
            {
                qDebug("mcu uart comand failed due to read timeout");
                return ;
            }

            uint res_len = response_len[0] * 256 + response_len[1]-2;
            Byte * response_res;
            qDebug("need to read %d data", res_len);
            // exit(0);
            qDebug("port: %d, baud: %d, data:%d, parity:%d, stop:%d, flow;%d", this->mcu_uart->port_id, this->mcu_uart->dcb.BaudRate, this->mcu_uart->dcb.ByteSize,this->mcu_uart->dcb.Parity,this->mcu_uart->dcb.StopBits,this->mcu_uart->dcb.fInX);
            //exit(0);

            response_res = (Byte*)malloc(sizeof(Byte)*res_len);
            if(this->mcu_uart->read(response_res,res_len) == false)
            {
                qDebug("mcu uart comand failed due to read timeout");
                return ;
            }
            qDebug("before parsing [0]:%02x", response_len[0]);
            qDebug("before parsing [1]:%02x", response_len[1]);
            for(uint ii = 0; ii < res_len; ii++){
                qDebug("before parsing [%d]:%02x", ii,response_res[ii]);
            }
            parsing_response_getref(response_res, resultSet);

            sleep(500);
        }

        vector<float>::iterator it;

        for(it=resultSet.begin(); it!=resultSet.end();) {
            if(abs(*it-temp_set) > 5 && resultSet.size() > 1)
                it = resultSet.erase(it);
            else
                ++it;
        }

        double sum = std::accumulate(std::begin(resultSet), std::end(resultSet), 0.0);
        double mean =  sum / resultSet.size();

        double accum  = 0.0;
        std::for_each (std::begin(resultSet), std::end(resultSet), [&](const double d) {
            accum  += (d-mean)*(d-mean);
        });

        stdev = sqrt(accum/(resultSet.size()-1));
        stdev_vec.push_back(stdev);
        qInfo("board %d's stdev is: %lf", (boardy*4+boardx+1), stdev);

        resultSet.clear();

        if(stdev > 0.7) {
            if(boardx > 0) {
                boardx--;
            }
            else if(boardx == 0 && boardy < (NUM_DAUGHTER_BOARDS_Y-1)) {
                boardx = NUM_DAUGHTER_BOARDS_X-1;
                boardy++;
            }
            resultSet.clear();
        }

        timeout_count++;
        if(timeout_count == 10000){
            abort();
        }

    }while(stdev > 0.06);

//////////////////////////////////////////////////////////////////////////////////////////////////////

//    resultSet.clear();
//    timeout_count = 0;
//    boardx = NUM_DAUGHTER_BOARDS_X-1;
//    boardy = NUM_DAUGHTER_BOARDS_Y-1;

//    do{  //check stable by Si7051 right down
//        stdev_vec.clear();
//        resultSet.clear();

//        for(int iii=0; iii<10; iii++) {
//            pack_cmd(sel, cmd, boardy*NUM_DAUGHTER_BOARDS_X + boardx, row, col,  payload,  payload_len, char_cmd, &send_len);
//            for(int ii = 0; ii < send_len; ii++)
//            {
//                qDebug("%02x",char_cmd[ii]);
//            }

//            //   if(this->mcu_uart->is_opened!=TRUE)
//            if(this->mcu_uart->open()!=TRUE)
//            {
//                s_errorbox("cmd execute error, uart is not opened");
//                return;
//            }

//            for(int ii = 0; ii < send_len; ii++)
//            {
//                qDebug("len %02x",char_cmd[ii]);
//            }


//            this->mcu_uart->write(char_cmd,send_len);
//            delete char_cmd;

//            if(this->mcu_uart->read(response_len,2) == false)
//            {
//                qDebug("mcu uart comand failed due to read timeout");
//                return ;
//            }

//            uint res_len = response_len[0] * 256 + response_len[1]-2;
//            Byte * response_res;
//            qDebug("need to read %d data", res_len);
//            // exit(0);
//            qDebug("port: %d, baud: %d, data:%d, parity:%d, stop:%d, flow;%d", this->mcu_uart->port_id, this->mcu_uart->dcb.BaudRate, this->mcu_uart->dcb.ByteSize,this->mcu_uart->dcb.Parity,this->mcu_uart->dcb.StopBits,this->mcu_uart->dcb.fInX);
//            //exit(0);

//            response_res = (Byte*)malloc(sizeof(Byte)*res_len);
//            if(this->mcu_uart->read(response_res,res_len) == false)
//            {
//                qDebug("mcu uart comand failed due to read timeout");
//                return ;
//            }
//            qDebug("before parsing [0]:%02x", response_len[0]);
//            qDebug("before parsing [1]:%02x", response_len[1]);
//            for(uint ii = 0; ii < res_len; ii++){
//                qDebug("before parsing [%d]:%02x", ii,response_res[ii]);
//            }
//            parsing_response_getref(response_res, resultSet);

//            sleep(10000);
//        }

//          vector<float>::iterator it;

//          for(it=resultSet.begin(); it!=resultSet.end();) {
//              if(abs(*it-temp_set) > 5)
//                  it = resultSet.erase(it);
//              else
//                  ++it;
//          }

//        double sum = std::accumulate(std::begin(resultSet), std::end(resultSet), 0.0);
//        double mean =  sum / resultSet.size();

//        double accum  = 0.0;
//        std::for_each (std::begin(resultSet), std::end(resultSet), [&](const double d) {
//            accum  += (d-mean)*(d-mean);
//        });

//        stdev = sqrt(accum/(resultSet.size()-1));
//        stdev_vec.push_back(stdev);
//        qInfo("board %d's stdev is: %lf", (boardy*4+boardx+1), stdev);

//        resultSet.clear();

//        if(stdev > 0.7) {
//            if(boardx > 0) {
//                boardx--;
//            }
//            else if(boardx == 0 && boardy > 0) {
//                boardx = (NUM_DAUGHTER_BOARDS_Y-1)-1;
//                boardy--;
//            }
//        }

//        timeout_count++;
//        if(timeout_count == 10000){
//            abort();
//        }

//    }while(stdev > 0.05);


    timeout_count = 0;
    boardx = 0;
    boardy = 0;
    resultSet.clear();
    stdev_vec.clear();
}


bool myMCUAgent::parsing_response_getref(Byte * response_a, vector<float> &vec)
{

    Byte* response = response_a;

    UartCmdType cmd;
    UartSelype sel;
    int boardx;
    int boardy;
    int board;
    int row;
    int col;
    //Byte * payload;
    qDebug("sel byte : %02x", response[0]);
    if(response[0] == 0x5a )
    {
        sel = all; // sel all
    }
    else if(response[0] == 0x9e){
        sel = individule; // sel individual
    }
    else if(response[0] == 0x6b){
        sel = board_sel; // sel board
    }
    else if(response[0] == 0x7c){
        sel = row_sel; //sel row
    }
    else if(response[0] == 0x8d){
        sel = col_sel; //sel col
    }
    else{
        qDebug("response sel field not recognized");
        return false;
    }
    if((response[1] == 0x11) && (response[2] ==0x00)) {
        cmd = ow_doconvert;//ow_doconvert
        qDebug("ow_doconvert response");
    }
    else if((response[1] == 0x11) && (response[2] ==0x01)) {
        cmd = ow_gettemp;
        qDebug("ow_gettemp response");
    }
    else if((response[1] == 0x11) && (response[2] ==0x02)) {
        cmd = ow_gettemp_ref;
        qDebug("ow_gettemp_ref response");
    }
    else if((response[1] == 0x12) && (response[2] ==0x00)) {
        cmd = ow_writeparameters;
        qDebug("ow_writeparameters response");
    }
    else if((response[1] == 0x12) && (response[2] ==0x01)) {
        cmd = ow_getromcode;
        qDebug("ow_getromcode response");
    }
    else if((response[1] == 0x13) && (response[2] ==0x00)) {
        cmd = ow_setcoeff;
        qDebug("ow_setcoeff response");
    }
    else{
        qDebug("response cmd field not recognized");
        return false;
    }

    board = response[3];
    boardx = board % NUM_DAUGHTER_BOARDS_X;
    boardy = board / NUM_DAUGHTER_BOARDS_X;

    row   = response[4];
    col   = response[5];
    // valid check
    if((cmd == ow_gettemp_ref) && (sel != all && sel != board_sel)){ // only work for in mode
        qDebug("gettemp_ref should sel all or board");
        return false;
    }
    // function
    Byte temp_ref[2];
    float f_temp_ref;

    if (cmd == ow_gettemp_ref)
    {
        if(sel != all && sel != board_sel){
            s_errorbox("gettemp_ref should sel all or board");
            return false;
        }
        if(sel == all){
            for (int ii = 0; ii < NUM_DAUGHTER_BOARDS_Y; ii ++)
            {
                for (int jj = 0; jj < NUM_DAUGHTER_BOARDS_X; jj ++)
                {
                    temp_ref[0] = response[6+(ii*NUM_DAUGHTER_BOARDS_X +jj)*2];
                    temp_ref[1] = response[6+(ii*NUM_DAUGHTER_BOARDS_X +jj)*2+1];
                    f_temp_ref = convert_reftemp(temp_ref);
                    qInfo("Si7051 Get: %f",f_temp_ref);
                    vec.push_back(f_temp_ref);
                }
            }
        }
        else if(sel == board_sel)
        {
            temp_ref[0] = response[6];
            temp_ref[1] = response[7];
            f_temp_ref = convert_reftemp(temp_ref);
            qInfo("Si7051 Get: %f",f_temp_ref);
            vec.push_back(f_temp_ref);
        }
    }
    else {
        //qDebug("TODO: reponse need to be parsed");
        qDebug("executed command without payload send back");
    }
    return true;
}


bool myMCUAgent::parsing_response_getref_new(Byte * response_a, vector<float> &vec, vector<float> &ref_vec, int count, float temp_set, int mboard_y, int mboard_x)
{

    Byte* response = response_a;

    UartCmdType cmd;
    UartSelype sel;
    int boardx;
    int boardy;
    int board;
    int row;
    int col;
    //Byte * payload;
    vector<float> resultSet_filter;
    vector<float> y;

    qDebug("sel byte : %02x", response[0]);
    if(response[0] == 0x5a )
    {
        sel = all; // sel all
    }
    else if(response[0] == 0x9e){
        sel = individule; // sel individual
    }
    else if(response[0] == 0x6b){
        sel = board_sel; // sel board
    }
    else if(response[0] == 0x7c){
        sel = row_sel; //sel row
    }
    else if(response[0] == 0x8d){
        sel = col_sel; //sel col
    }
    else{
        qDebug("response sel field not recognized");
        return false;
    }
    if((response[1] == 0x11) && (response[2] ==0x00)) {
        cmd = ow_doconvert;//ow_doconvert
        qDebug("ow_doconvert response");
    }
    else if((response[1] == 0x11) && (response[2] ==0x01)) {
        cmd = ow_gettemp;
        qDebug("ow_gettemp response");
    }
    else if((response[1] == 0x11) && (response[2] ==0x02)) {
        cmd = ow_gettemp_ref;
        qDebug("ow_gettemp_ref response");
    }
    else if((response[1] == 0x12) && (response[2] ==0x00)) {
        cmd = ow_writeparameters;
        qDebug("ow_writeparameters response");
    }
    else if((response[1] == 0x12) && (response[2] ==0x01)) {
        cmd = ow_getromcode;
        qDebug("ow_getromcode response");
    }
    else if((response[1] == 0x13) && (response[2] ==0x00)) {
        cmd = ow_setcoeff;
        qDebug("ow_setcoeff response");
    }
    else{
        qDebug("response cmd field not recognized");
        return false;
    }

    board = response[3];
    boardx = board % NUM_DAUGHTER_BOARDS_X;
    boardy = board / NUM_DAUGHTER_BOARDS_X;

    row   = response[4];
    col   = response[5];
    // valid check
    if((cmd == ow_gettemp_ref) && (sel != all && sel != board_sel)){ // only work for in mode
        qDebug("gettemp_ref should sel all or board");
        return false;
    }
    // function
    Byte temp_ref[2];
    float f_temp_ref;

    if (cmd == ow_gettemp_ref)
    {
        if(sel != all && sel != board_sel){
            s_errorbox("gettemp_ref should sel all or board");
            return false;
        }
        if(sel == all){
            for (int ii = 0; ii < NUM_DAUGHTER_BOARDS_Y; ii ++)
            {
                for (int jj = 0; jj < NUM_DAUGHTER_BOARDS_X; jj ++)
                {
                    temp_ref[0] = response[6+(ii*NUM_DAUGHTER_BOARDS_X +jj)*2];
                    temp_ref[1] = response[6+(ii*NUM_DAUGHTER_BOARDS_X +jj)*2+1];
                    f_temp_ref = convert_reftemp(temp_ref);
                    qInfo("Si7051 Get: %f",f_temp_ref);
                    vec.push_back(f_temp_ref);
                }
            }
        }
        else if(sel == board_sel)
        {
            temp_ref[0] = response[6];
            temp_ref[1] = response[7];
            f_temp_ref = convert_reftemp(temp_ref);
            qInfo("Si7051 Get: %f",f_temp_ref);
            vec.push_back(f_temp_ref);

            if(count == 14) {
            //if(count == 9) {
                sleep(2000);
                qInfo("wait 2s after first 14 times...");
            }

            //if(count == 19) {
            if(count == 29) {
                vector<float>::iterator it;

                for(it=vec.begin(); it!=vec.end();) {
                    if(abs(*it-temp_set) > 5 && vec.size() > 1)
                        it = vec.erase(it);
                    else
                        ++it;
                }

                for(int idx=vec.size()/2; idx<vec.size(); idx++) {
                    resultSet_filter.push_back(vec[idx]);
                }

                float sum = std::accumulate(std::begin(resultSet_filter), std::end(resultSet_filter), 0.0);
                float max =  *max_element(resultSet_filter.begin(),resultSet_filter.end());
                float min =  *min_element(resultSet_filter.begin(),resultSet_filter.end());
                float mean =  sum / resultSet_filter.size();

                if(resultSet_filter.size() > 2) {
                    mean = (sum-max-min)/(resultSet_filter.size()-2);
                }

                qInfo("Mean value of Si7051 on Board %d is: %f",(mboard_y*NUM_DAUGHTER_BOARDS_X + mboard_x+1),mean);
                vector<sTestRecord>::iterator itt;

                map.ref_map[mboard_y*NUM_DAUGHTER_BOARDS_X +mboard_x].update_temp_record(mean,mean);
                for(itt = map.map[mboard_x][mboard_y][row][col].test_records.begin(); itt !=  map.map[mboard_x][mboard_y][row][col].test_records.end(); itt++)
                {
                    //x.push_back(it->temp+128);
                    //y.push_back(itt->ref_temp+128);
                    qInfo("cal_coeff ref_temp: %f", itt->ref_temp);
                }
                ref_vec.push_back(mean);
            }
        }
    }
    else {
        //qDebug("TODO: reponse need to be parsed");
        qDebug("executed command without payload send back");
    }

    return true;
}


bool myMCUAgent::parsing_response_checktemp(Byte * response_a, vector<vector<float> >& vv, int count, int &right_count)
{

    Byte* response = response_a;

    UartCmdType cmd;
    UartSelype sel;
    int boardx;
    int boardy;
    int board;
    int row;
    int col;
    int chip_count = 0;
    //Byte * payload;
    Byte temp[2];

    vector<float> vec;

    qDebug("sel byte : %02x", response[0]);
    if(response[0] == 0x5a )
    {
        sel = all; // sel all
    }
    else if(response[0] == 0x9e){
        sel = individule; // sel individual
    }
    else if(response[0] == 0x6b){
        sel = board_sel; // sel board
    }
    else if(response[0] == 0x7c){
        sel = row_sel; //sel row
    }
    else if(response[0] == 0x8d){
        sel = col_sel; //sel col
    }
    else{
        qDebug("response sel field not recognized");
        return false;
    }
    if((response[1] == 0x11) && (response[2] ==0x00)) {
        cmd = ow_doconvert;//ow_doconvert
        qDebug("ow_doconvert response");
    }
    else if((response[1] == 0x11) && (response[2] ==0x01)) {
        cmd = ow_gettemp;
        qDebug("ow_gettemp response");
    }
    else if((response[1] == 0x11) && (response[2] ==0x02)) {
        cmd = ow_gettemp_ref;
        qDebug("ow_gettemp_ref response");
    }
    else if((response[1] == 0x12) && (response[2] ==0x00)) {
        cmd = ow_writeparameters;
        qDebug("ow_writeparameters response");
    }
    else if((response[1] == 0x12) && (response[2] ==0x01)) {
        cmd = ow_getromcode;
        qDebug("ow_getromcode response");
    }
    else if((response[1] == 0x13) && (response[2] ==0x00)) {
        cmd = ow_setcoeff;
        qDebug("ow_setcoeff response");
    }
    else{
        qDebug("response cmd field not recognized");
        return false;
    }

    board = response[3];
    boardx = board % NUM_DAUGHTER_BOARDS_X;
    boardy = board / NUM_DAUGHTER_BOARDS_X;

    row   = response[4];
    col   = response[5];

    // valid check
    //if((cmd == ow_gettemp_ref) && (sel != all && sel != board_sel)){ // only work for in mode
        //qDebug("gettemp_ref should sel all or board");
        //return false;
    //}
    // function
    //Byte temp_ref[2];
    //float f_temp_ref;

    if (cmd == ow_gettemp)
    {

        if(sel == board_sel)
        {
            //int right_count = 0;

            //for(int kk = 0; kk<NUM_CHIPS_Y;kk++){
                //for(int ll = 0; ll<NUM_CHIPS_X;ll++){
            for(int kk = 0; kk<NUM_CHIPS_X;kk++){
                for(int ll = 0; ll<NUM_CHIPS_Y;ll++){
                    temp[0] = response[6+(kk * NUM_CHIPS_X + ll)*2];
                    temp[1] = response[6+(kk * NUM_CHIPS_X + ll)*2 +1];
                    //     mcu_uart->read_temp_board(ii);
                    // not correct, to be modify, TODO: temp is Byte, need to convert to float.

                    vv[chip_count++].push_back(convert_temp(temp));
                    //map.update_temp_record(boardx, boardy,kk,(9-ll),fRet[boardx * NUM_CHIPS_X +kk][boardy*NUM_CHIPS_Y+(9-ll)][2],convert_temp(temp));

                    if(count == 9) {
                        //for(int cc=0; cc<100; cc++) {
                            float sum = std::accumulate(std::begin(vv[kk*10 +ll]), std::end(vv[kk*10 +ll]), 0.0);
                            float mean =  sum / vv[kk*10 +ll].size();

                            for(int tt=0; tt<vv[kk*10 +ll].size();tt++) {
                                qInfo("The %dth value is: %f",(tt+1),vv[kk*10+ll][tt]);
                            }

                            if(abs(mean - fRet[10*boardx+kk][10*boardy+(9-ll)][2]) >= 1)
                            {
                               int board_indx = 1+ boardy*4 + boardx;
                               int chip_indx = 1+kk*10 +ll;
                               qInfo("Board %d's Chip %d temperature: %f, Temp ref: %f. The diff is: %f-------------------------------------------> Board %d's Chip %d temp check goes WRONG!!!",board_indx,chip_indx,mean,fRet[10*boardx+kk][10*boardy+ll][2],(mean - fRet[10*boardx+kk][10*boardy+(9-ll)][2]),board_indx,chip_indx);
                               map.set_chip_state(boardx,boardy,kk,(9-ll),BAD);
                            }
                            else {
                               int board_indx = 1+ boardy*4 + boardx;
                               int chip_indx = 1+kk*10 +ll;
                               qInfo("Board %d's Chip %d temperature: %f, Temp ref %f. The diff is: %f---> Board %d's Chip %d temp check PASS!!!",board_indx,chip_indx,mean,fRet[10*boardx+kk][10*boardy+ll][2],(mean - fRet[10*boardx+kk][10*boardy+(9-ll)][2]),board_indx,chip_indx);
                               map.set_chip_state(boardx,boardy,kk,(9-ll),GOOD);
                               //right_count++;
                            }
                        //}
                    }
                }  
            }
            chip_count = 0;
            if(count == 9) {
                //qInfo("\r\nBoard %d Temperature check pass %d chips, fail %d chips.\r\n\r\n",1+ boardy*4 + boardx,right_count,NUM_CHIPS_X*NUM_CHIPS_Y-right_count);
                //right_count = 0;
            }

        }

        else if(sel == individule)
        {
            //if(selAll == 0)
                //map.reset_chip_state();
            temp[0] = response[6];
            temp[1] = response[7];

            vec.push_back(convert_temp(temp));

            if(count == 4) {
                //for(int cc=0; cc<100; cc++) {
                    float sum = std::accumulate(std::begin(vec), std::end(vec), 0.0);
                    float mean =  sum / vec.size();

                    if(abs(mean - fRet[NUM_CHIPS_X*boardx+row][NUM_CHIPS_Y*boardy+col][2]) >= 0.5)
                    {
                       int board_indx = 1+ boardy*4 + boardx;
                       int chip_indx = row*10+col+1;
                       //qInfo("Row: %2x; Col: %2x", row, col);
                       qInfo("Board %d's Chip %d temperature: %f, Temp ref: %f. The diff is: %f-------------------------------------------> Board %d's Chip %d temp check goes WRONG!!!",board_indx,chip_indx,mean,fRet[NUM_CHIPS_X*boardx+row][NUM_CHIPS_Y*boardy+col][2],(mean - fRet[NUM_CHIPS_X*boardx+row][NUM_CHIPS_Y*boardy+col][2]),board_indx,chip_indx);
                       map.set_chip_state(boardx,boardy,row,col,BAD);
                    }
                    else {
                       int board_indx = 1+ boardy*4 + boardx;
                       int chip_indx = row*10 +col + 1;
                       //qInfo("Row: %2x; Col: %2x", row, col);
                       qInfo("Board %d's Chip %d temperature: %f, Temp ref %f. The diff is: %f---> Board %d's Chip %d temp check PASS!!!",board_indx,chip_indx,mean,fRet[NUM_CHIPS_X*boardx+row][NUM_CHIPS_Y*boardy+col][2],(mean - fRet[NUM_CHIPS_X*boardx+row][NUM_CHIPS_Y*boardy+col][2]),board_indx,chip_indx);
                       map.set_chip_state(boardx,boardy,row,col,GOOD);
                       right_count++;
                    }
                //}
            }
            //chip_count = 0;
//            if(count == 9) {
//                //qInfo("\r\nBoard %d Temperature check pass %d chips, fail %d chips.\r\n\r\n",1+ boardy*4 + boardx,right_count,NUM_CHIPS_X*NUM_CHIPS_Y-right_count);
//                //right_count = 0;
//            }
        }
    }
    else {
        //qDebug("TODO: reponse need to be parsed");
        qDebug("executed command without payload send back");
    }
    return true;
}

void  myMCUAgent::execute_temp_check()
{
    Byte * char_cmd;
    Byte response_len[2];
    int send_len;
    //vector<float> resultSet;
    //double stdev;

    int boardx = 0;
    int boardy = 0;
    int row = 0;
    int col = 0;
    Byte* payload;
    int payload_len = 0;

    //int sel = 1; //board
    int sel = 4; //individual
    int cmd = 1; //get temp

    //int timeout_count = 0;
    int right_count = 0;
    int right_count_total = 0;

    vector<vector<float>> vvec(200,vector<float>(20));

    for(boardy=0; boardy<NUM_DAUGHTER_BOARDS_Y; boardy++) {
        for(boardx=0; boardx<NUM_DAUGHTER_BOARDS_X; boardx++) {
            for(int kk = 0; kk<NUM_CHIPS_X;kk++){
                for(int ll = 0; ll<NUM_CHIPS_Y;ll++){
                    for(int iii=0; iii<5; iii++) {
                        pack_cmd(sel, cmd, boardy*NUM_DAUGHTER_BOARDS_X + boardx, kk, (ll),  payload,  payload_len, char_cmd, &send_len);
                        for(int ii = 0; ii < send_len; ii++)
                        {
                            qDebug("%02x",char_cmd[ii]);
                        }

                        //   if(this->mcu_uart->is_opened!=TRUE)
                        if(this->mcu_uart->open()!=TRUE)
                        {
                            s_errorbox("cmd execute error, uart is not opened");
                            return;
                        }

                        for(int ii = 0; ii < send_len; ii++)
                        {
                            qDebug("len %02x",char_cmd[ii]);
                        }


                        this->mcu_uart->write(char_cmd,send_len);
                        delete char_cmd;

                        if(this->mcu_uart->read(response_len,2) == false)
                        {
                            qDebug("mcu uart comand failed due to read timeout");
                            return ;
                        }

                        uint res_len = response_len[0] * 256 + response_len[1]-2;
                        Byte * response_res;
                        qDebug("need to read %d data", res_len);
                        // exit(0);
                        qDebug("port: %d, baud: %d, data:%d, parity:%d, stop:%d, flow;%d", this->mcu_uart->port_id, this->mcu_uart->dcb.BaudRate, this->mcu_uart->dcb.ByteSize,this->mcu_uart->dcb.Parity,this->mcu_uart->dcb.StopBits,this->mcu_uart->dcb.fInX);
                        //exit(0);

                        response_res = (Byte*)malloc(sizeof(Byte)*res_len);
                        if(this->mcu_uart->read(response_res,res_len) == false)
                        {
                            qDebug("mcu uart comand failed due to read timeout");
                            return ;
                        }
                        qDebug("before parsing [0]:%02x", response_len[0]);
                        qDebug("before parsing [1]:%02x", response_len[1]);
                        for(uint ii = 0; ii < res_len; ii++){
                            qDebug("before parsing [%d]:%02x", ii,response_res[ii]);
                        }
                        //parsing_response_getref(response_res, resultSet);
                        parsing_response_checktemp(response_res, vvec, iii, right_count);

                        //sleep(1000);
                    }
                }

            }
            qInfo("\r\nBoard %d Temperature check pass %d chips, fail %d chips.\r\n\r\n",1+ boardy*4 + boardx,right_count,NUM_CHIPS_X*NUM_CHIPS_Y-right_count);
            right_count_total += right_count;
            right_count = 0;

            //vvec.clear();
        }
    }
    qInfo("\r\nTotal pass %d chips, fail %d chips.\r\n\r\n",right_count_total,NUM_CHIPS_X*NUM_CHIPS_Y*NUM_DAUGHTER_BOARDS_X*NUM_DAUGHTER_BOARDS_Y-right_count_total);
    right_count_total = 0;

        //double sum = std::accumulate(std::begin(resultSet), std::end(resultSet), 0.0);
        //double mean =  sum / resultSet.size();

        //double accum  = 0.0;
        //std::for_each (std::begin(resultSet), std::end(resultSet), [&](const double d) {
                //accum  += (d-mean)*(d-mean);
            //});

        //stdev = sqrt(accum/(resultSet.size()-1));
        //qInfo("stdev is: %lf", stdev);


        //vvec.clear();

}

void myMCUAgent::execute_getref_cmd(int sel, int cmd, int boardx, int boardy,int row,int col,Byte* payload, int payload_len, float temp_set){
    Byte * char_cmd;
    Byte response_len[2];
    int send_len;

    qDebug("%d %d %d %d %d %d",sel,cmd,boardx,boardy,row,col);


    pack_cmd(sel, cmd, boardy*NUM_DAUGHTER_BOARDS_X + boardx, row, col,  payload,  payload_len, char_cmd, &send_len);


    for(int ii = 0; ii < send_len; ii++)
    {
        qDebug("%02x",char_cmd[ii]);
    }

    //   if(this->mcu_uart->is_opened!=TRUE)
    if(this->mcu_uart->open()!=TRUE)
    {
        s_errorbox("cmd execute error, uart is not opened");
        return;
    }

    for(int ii = 0; ii < send_len; ii++)
    {
        qDebug("len %02x",char_cmd[ii]);
    }


    this->mcu_uart->write(char_cmd,send_len);
    delete char_cmd;

    if(this->mcu_uart->read(response_len,2) == false)
    {
        qDebug("mcu uart comand failed due to read timeout");
        return ;
    }

    uint res_len = response_len[0] * 256 + response_len[1]-2;
    Byte * response_res;
    qDebug("need to read %d data", res_len);
    // exit(0);
    qDebug("port: %d, baud: %d, data:%d, parity:%d, stop:%d, flow;%d", this->mcu_uart->port_id, this->mcu_uart->dcb.BaudRate, this->mcu_uart->dcb.ByteSize,this->mcu_uart->dcb.Parity,this->mcu_uart->dcb.StopBits,this->mcu_uart->dcb.fInX);
    //exit(0);

    response_res = (Byte*)malloc(sizeof(Byte)*res_len);
    if(this->mcu_uart->read(response_res,res_len) == false)
    {
        qDebug("mcu uart comand failed due to read timeout");
        return ;
    }
    qDebug("before parsing [0]:%02x", response_len[0]);
    qDebug("before parsing [1]:%02x", response_len[1]);
    for(uint ii = 0; ii < res_len; ii++){
        qDebug("before parsing [%d]:%02x", ii,response_res[ii]);
    }
    parsing_response_for_getref(response_res, temp_set);
}

bool myMCUAgent::parsing_response_for_getref(Byte * response_a, float temp_set)
{

    Byte* response = response_a;

    UartCmdType cmd;
    UartSelype sel;
    int boardx;
    int boardy;
    int board;
    int row;
    int col;
    //Byte * payload;
    qDebug("sel byte : %02x", response[0]);
    if(response[0] == 0x5a )
    {
        sel = all; // sel all
    }
    else if(response[0] == 0x9e){
        sel = individule; // sel individual
    }
    else if(response[0] == 0x6b){
        sel = board_sel; // sel board
    }
    else if(response[0] == 0x7c){
        sel = row_sel; //sel row
    }
    else if(response[0] == 0x8d){
        sel = col_sel; //sel col
    }
    else{
        qDebug("response sel field not recognized");
        return false;
    }
    if((response[1] == 0x11) && (response[2] ==0x00)) {
        cmd = ow_doconvert;//ow_doconvert
        qDebug("ow_doconvert response");
    }
    else if((response[1] == 0x11) && (response[2] ==0x01)) {
        cmd = ow_gettemp;
        qDebug("ow_gettemp response");
    }
    else if((response[1] == 0x11) && (response[2] ==0x02)) {
        cmd = ow_gettemp_ref;
        qDebug("ow_gettemp_ref response");
    }
    else if((response[1] == 0x12) && (response[2] ==0x00)) {
        cmd = ow_writeparameters;
        qDebug("ow_writeparameters response");
    }
    else if((response[1] == 0x12) && (response[2] ==0x01)) {
        cmd = ow_getromcode;
        qDebug("ow_getromcode response");
    }
    else if((response[1] == 0x13) && (response[2] ==0x00)) {
        cmd = ow_setcoeff;
        qDebug("ow_setcoeff response");
    }
    else{
        qDebug("response cmd field not recognized");
        return false;
    }

    board = response[3];
    boardx = board % NUM_DAUGHTER_BOARDS_X;
    boardy = board / NUM_DAUGHTER_BOARDS_X;

    row   = response[4];
    col   = response[5];
    // valid check
    if((cmd == ow_gettemp_ref) && (sel != all && sel != board_sel)){ // only work for in mode
        qDebug("gettemp_ref should sel all or board");
        return false;
    }
    // function
    Byte temp_ref[2];
    float f_temp_ref;

    vector<float> ref_vec;

    if (cmd == ow_gettemp_ref)
    {
        if(sel != all && sel != board_sel){
            s_errorbox("gettemp_ref should sel all or board");
            return false;
        }
        if(sel == all){
            for (int ii = 0; ii < NUM_DAUGHTER_BOARDS_Y; ii ++)
            {
                for (int jj = 0; jj < NUM_DAUGHTER_BOARDS_X; jj ++)
                {
                    temp_ref[0] = response[6+(ii*NUM_DAUGHTER_BOARDS_X +jj)*2];
                    temp_ref[1] = response[6+(ii*NUM_DAUGHTER_BOARDS_X +jj)*2+1];
                    f_temp_ref = convert_reftemp(temp_ref);
                    qDebug("i ma here");
                    map.ref_map[ii*NUM_DAUGHTER_BOARDS_X +jj].update_temp_record(f_temp_ref,f_temp_ref);
                    ref_vec.push_back(f_temp_ref);
                }
            }

            vector<float>::iterator it;
            for(it=ref_vec.begin();it!=ref_vec.end();) {
                if(abs(*it-temp_set) > 5)
                    it = ref_vec.erase(it);
                else
                    ++it;
            }

            float sum = std::accumulate(std::begin(ref_vec), std::end(ref_vec), 0.0);
            float max =  *max_element(ref_vec.begin(),ref_vec.end());
            float min =  *min_element(ref_vec.begin(),ref_vec.end());
            float mean;
            if(ref_vec.size() > 2) {
                mean =  (sum-max-min) / (ref_vec.size()-2);

                for (int ii = 0; ii < NUM_DAUGHTER_BOARDS_Y; ii ++)
                {
                    for (int jj = 0; jj < NUM_DAUGHTER_BOARDS_X; jj ++)
                    {
                        if(abs(ref_vec[ii*NUM_DAUGHTER_BOARDS_X+jj]-mean) > 0.6) {
                            int board_indx = ii*NUM_DAUGHTER_BOARDS_X +jj;
                            map.ref_map[ii*NUM_DAUGHTER_BOARDS_X +jj].update_temp_record(mean,mean);
                            qInfo("Board %d's ref %f has been changed to %f",board_indx,ref_vec[ii*NUM_DAUGHTER_BOARDS_X+jj],mean);
                        }
                    }
                }
            }

            ref_vec.clear();
        }
        else if(sel == board_sel)
        {
            temp_ref[0] = response[6];
            temp_ref[1] = response[7];
            f_temp_ref = convert_reftemp(temp_ref);
            qDebug("i ma here");
            map.ref_map[boardx*NUM_DAUGHTER_BOARDS_X +boardy].update_temp_record(f_temp_ref,f_temp_ref);
        }

        qDebug("update temtemp plan");

        if(sel == all)
            update_temp_plan();
    }
    else {
        //qDebug("TODO: reponse need to be parsed");
        qDebug("executed command without payload send back");
    }
    return true;
}


void myMCUAgent::get_ref(float temp_set) {
    Byte * char_cmd;
    Byte response_len[2];
    int send_len;
    vector<float> resultSet;
    vector<float> resultSet_filter;
    vector<float> ref_vec;
    //double mean_stdev;

    //int boardx = 0;
    //int boardy = 0;
    int row = 0;
    int col = 0;
    Byte* payload;
    int payload_len = 0;

    int sel = 1; //board
    int cmd = 2; //get ref

    vector<float>::iterator it;

    for (int ii = 0; ii < NUM_DAUGHTER_BOARDS_Y; ii ++)
    {
        for (int jj = 0; jj < NUM_DAUGHTER_BOARDS_X; jj ++)
        {
            resultSet.clear();

            for(int iii=0; iii<20; iii++) {
                pack_cmd(sel, cmd, ii*NUM_DAUGHTER_BOARDS_X + jj, row, col,  payload,  payload_len, char_cmd, &send_len);
                for(int ii = 0; ii < send_len; ii++)
                {
                    qDebug("%02x",char_cmd[ii]);
                }

                //   if(this->mcu_uart->is_opened!=TRUE)
                if(this->mcu_uart->open()!=TRUE)
                {
                    s_errorbox("cmd execute error, uart is not opened");
                    return;
                }

                for(int ii = 0; ii < send_len; ii++)
                {
                    qDebug("len %02x",char_cmd[ii]);
                }


                this->mcu_uart->write(char_cmd,send_len);
                delete char_cmd;

                if(this->mcu_uart->read(response_len,2) == false)
                {
                    qDebug("mcu uart comand failed due to read timeout");
                    return ;
                }

                uint res_len = response_len[0] * 256 + response_len[1]-2;
                Byte * response_res;
                qDebug("need to read %d data", res_len);
                // exit(0);
                qDebug("port: %d, baud: %d, data:%d, parity:%d, stop:%d, flow;%d", this->mcu_uart->port_id, this->mcu_uart->dcb.BaudRate, this->mcu_uart->dcb.ByteSize,this->mcu_uart->dcb.Parity,this->mcu_uart->dcb.StopBits,this->mcu_uart->dcb.fInX);
                //exit(0);

                response_res = (Byte*)malloc(sizeof(Byte)*res_len);
                if(this->mcu_uart->read(response_res,res_len) == false)
                {
                    qDebug("mcu uart comand failed due to read timeout");
                    return ;
                }
                qDebug("before parsing [0]:%02x", response_len[0]);
                qDebug("before parsing [1]:%02x", response_len[1]);
                for(uint ii = 0; ii < res_len; ii++){
                    qDebug("before parsing [%d]:%02x", ii,response_res[ii]);
                }
                //parsing_response_getref(response_res, resultSet);
                parsing_response_getref_new(response_res, resultSet, ref_vec, iii, temp_set, ii, jj);

                sleep(5000);  //5s sample
            }

            //vector<float>::iterator it;

//            for(it=resultSet.begin(); it!=resultSet.end();) {
//                if(abs(*it-temp_set) > 5 && resultSet.size() > 1)
//                    it = resultSet.erase(it);
//                else
//                    ++it;
//            }

//            for(int idx=resultSet.size()/2; idx<resultSet.size(); idx++) {
//                resultSet_filter.push_back(resultSet[idx]);
//            }

            //float sum = std::accumulate(std::begin(resultSet), std::end(resultSet), 0.0);
            //float max =  *max_element(resultSet.begin(),resultSet.end());
            //float min =  *min_element(resultSet.begin(),resultSet.end());
            //float mean =  sum / resultSet.size();

            //if(resultSet.size() > 2) {
                //mean = (sum-max-min)/(resultSet.size()-2);
            //}


//            float sum = std::accumulate(std::begin(resultSet_filter), std::end(resultSet_filter), 0.0);
//            float max =  *max_element(resultSet_filter.begin(),resultSet_filter.end());
//            float min =  *min_element(resultSet_filter.begin(),resultSet_filter.end());
//            float mean =  sum / resultSet_filter.size();

//            if(resultSet_filter.size() > 2) {
//                mean = (sum-max-min)/(resultSet_filter.size()-2);
//            }

//            qInfo("Mean value of Si7051 on Board %d is: %f",(ii*NUM_DAUGHTER_BOARDS_X + jj+1),mean);

//            map.ref_map[ii*NUM_DAUGHTER_BOARDS_X +jj].update_temp_record(mean,mean);


//            ref_vec.push_back(mean);

            //sleep(1500);
        }
    }

    //for(it=ref_vec.begin(); it!=ref_vec.end();) {
        //if(*it < -30 && ref_vec.size() > 1)
            //it = ref_vec.erase(it);
        //else
            //++it;
    //}


    //float sum_ref = std::accumulate(std::begin(ref_vec), std::end(ref_vec), 0.0);

    float sum_ref = 0;
    int counter = 0;

    for(int ij=0; ij<ref_vec.size(); ij++) {
        if(ref_vec[ij] < -30) {
            counter++;
        }
        else {
            sum_ref += ref_vec[ij];
        }
    }

    float mean_ref = sum_ref / (ref_vec.size()-counter);

    for (int ii = 0; ii < NUM_DAUGHTER_BOARDS_Y; ii ++)
    {
        for (int jj = 0; jj < NUM_DAUGHTER_BOARDS_X; jj ++)
        {
            if(abs(ref_vec[ii*NUM_DAUGHTER_BOARDS_X+jj]-mean_ref) > 1.2) {
                int board_indx = ii*NUM_DAUGHTER_BOARDS_X +jj+1;
                map.ref_map[ii*NUM_DAUGHTER_BOARDS_X +jj].update_temp_record(mean_ref,mean_ref);
                qInfo("Board %d's ref %f has been changed to %f",board_indx,ref_vec[ii*NUM_DAUGHTER_BOARDS_X+jj],mean_ref);
            }
        }
    }
    ref_vec.clear();

}
