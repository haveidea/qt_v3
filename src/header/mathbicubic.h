#define QT_NO_DEBUG_OUTPUT

#ifndef MATH_BICUBIC_H
#define MATH_BICUBIC_H

#include <myglobal.h>

namespace MathBiCubic
{
template<typename T>
bool GetTable(T***& out_fTable, int in_iTH, int in_iTW, int in_iTK)
{
    out_fTable = 0;
    out_fTable = new T**[in_iTH];
    if( 0 == out_fTable)
        return false;
    for(int i=0; i<in_iTH; i++)
    {
        out_fTable[i] = new T*[in_iTW];
        if( 0 == out_fTable[i])
            return false;
        for(int j=0; j<in_iTW; j++)
        {
            out_fTable[i][j] = new T[in_iTK];
            if( 0 == out_fTable[i][j])
                return false;
        }
    }
    for(int i=0; i<in_iTH; i++)
    {
        for(int j=0; j<in_iTW; j++)
        {
            for(int k=0; k<in_iTK; k++)
                out_fTable[i][j][k] = 0;
        }
    }
    return true;
}

template<typename T>
void DeleteTable(T*** in_dTable, int in_iTH, int in_iTW)
{
    for(int i=0; i<in_iTH; i++)
    {
        for(int j=0; j<in_iTW; j++)
        {
            delete[] in_dTable[i][j];
            //  in_dTable[i][j] = nullptr;
        }
        delete[] in_dTable[i];
        // in_dTable[i] = nullptr;
    }
    delete[] in_dTable;
    // in_dTable = nullptr;
}

template<typename T>
void Sort(T* in_tData, int in_iSize)
{
    for(int i=0; i<in_iSize; i++)
    {
        int iRecored = i;
        for(int j=i+1; j<in_iSize; j++)
        {
            if( in_tData[j] < in_tData[iRecored])
                iRecored = j;
        }
        if( i != iRecored)
        {
            T tTemp = in_tData[i];
            in_tData[i] = in_tData[iRecored];
            in_tData[iRecored] = tTemp;
        }
    }
}



/* 三次样条曲线
 out_fVal   所求函数值
 out_fD1  所求插值点的一阶导数
 out_fD2 所求插值点的二阶导数
 in_iM 已知节点个数
 in_fPos    所求插值点的插值点的X轴坐标(无次序要求且可含已知点)
 in_fKnowPos,in_fKnowVal  已知点的节点坐标(要求升序排列)
 in_fKnowD1,  in_fKnowD2 已知点的节点的一阶导和二阶导(要求升序排列)
 in_iN 已知节点个数
 */
void CubicSpline(float out_fVal[], float out_fD1[], float out_fD2[],
                 float in_fPos[], int in_iM,
                 float in_fKnowPos[], float in_fKnowVal[],
                 float in_fKnowD1[], float in_fKnowD2[],
                 int in_iN);


//以估计的方法计算导数
void CalculateDyDdy(float out_fD1[], float out_fD2[],
                    float in_fPos[], float in_fVal[], int in_iN,
                    float in_fStartD1 = 0, float in_fEndD1 = 0,
                    float in_fStartD2 = 0, float in_fEndD2 = 0);

/* 三次样条曲线
 out_fVal   所求函数值
 in_fPos    所求插值点的插值点的X轴坐标(无次序要求且可含已知点)
 in_iM 已知节点个数
 in_fKnowPos  已知点的节点坐标(要求升序排列)
 in_fKnowVal  已知点的节点坐标值(要求升序排列)
 in_iN 已知节点个数
 */
//三次样条曲线(1维(输出结果可含已知点))
void CubicSplineEx(float* out_fVal, float* in_fPos, int in_iM,
                   float* in_fKnowPos, float* in_fKnowVal, int in_iN);


//三次样条曲线(2维)
bool CubicSplineEx2_ROW(float*** inout_fVal,int in_iValRows,int in_iValLines,
                        float*** in_fKnowVal,int in_iKnowRows,int in_iKnowLines);

//三次样条曲线(2维)
bool CubicSplineEx2_LINE(float*** inout_fVal,int in_iValRows,int in_iValLines,
                         float*** in_fKnowVal,int in_iKnowRows,int in_iKnowLines);

//三次样条曲线(2维)
bool CubicSplineEx2_RowLine(float*** inout_fVal,int in_iValRows,int in_iValLines,
                            float*** in_fKnowVal,int in_iKnowRows,int in_iKnowLines);

//三次样条曲线(2维)
bool CubicSplineEx2_LineRow(float*** inout_fVal,int in_iValRows,int in_iValLines,
                            float*** in_fKnowVal,int in_iKnowRows,int in_iKnowLines);
}

#endif // MATH_BICUBIC_H
