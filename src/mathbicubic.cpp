#include "MathBiCubic.h"

///////////////////////////////////////



#define NULL 0

//以估计的方法计算导数
void MathBiCubic::CalculateDyDdy(float out_fD1[], float out_fD2[],
                                  float in_fPos[], float in_fVal[], int in_iN,
                                  float in_fStartD1, float in_fEndD1,
                                  float in_fStartD2, float in_fEndD2)
{//以估计的方法计算导数
    out_fD1[0] = in_fStartD1;
    out_fD2[0] = in_fStartD2;
    out_fD1[in_iN-1] = in_fEndD1;
    out_fD2[in_iN-1] = in_fEndD2;
    for(int i=1; i<in_iN-1; i++)
    {
        float dx = in_fPos[i+1] - in_fPos[i];
        if( 0 != dx)
        {
            out_fD1[i] = (in_fVal[i+1] - in_fVal[i]) / (2*dx);
            out_fD2[i] = (in_fVal[i+1] + in_fVal[i-1] - 2*in_fVal[i]) / dx / dx;
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
void MathBiCubic::CubicSpline(float out_fVal[], float out_fD1[], float out_fD2[],
                               float in_fPos[], int in_iM,
                               float in_fKnowPos[], float in_fKnowVal[],
                               float in_fKnowD1[], float in_fKnowD2[],
                               int in_iN)
{
    //三次样条函数
    int   i,j;
    float   h0,h1,alpha,beta,g;
    //int SCOUN = (in_iM<400)? 400:(in_iM/3);
    float* s = new float[in_iM];

    in_fKnowD1[0]=-0.5;
    h0=in_fKnowPos[1]-in_fKnowPos[0];
    s[0]=(float)3.0*(in_fKnowVal[1]-in_fKnowVal[0])/((float)2.0*h0)-in_fKnowD2[0]*h0/(float)4.0;
    for(j=1;j<=in_iN-2;j++)
    {
        h1=in_fKnowPos[j+1]-in_fKnowPos[j];
        alpha=h0/(h0+h1);
        beta=((float)1.0-alpha)*(in_fKnowVal[j]-in_fKnowVal[j-1])/h0;
        beta=(float)3.0*(beta+alpha*(in_fKnowVal[j+1]-in_fKnowVal[j])/h1);
        in_fKnowD1[j]=-alpha/((float)2.0+((float)1.0-alpha)*in_fKnowD1[j-1]);
        s[j]=(beta-((float)1.0-alpha)*s[j-1]);
        s[j]=s[j]/((float)2.0+((float)1.0-alpha)*in_fKnowD1[j-1]);
        h0=h1;
    }

    in_fKnowD1[in_iN-1]=((float)3.0*(in_fKnowVal[in_iN-1]-in_fKnowVal[in_iN-2])/h1+in_fKnowD2[in_iN-1]*h1/(float)2.0-s[in_iN-2])/((float)2.0+in_fKnowD1[in_iN-2]);
    for(j=in_iN-2;j>=0;j--)
        in_fKnowD1[j]=in_fKnowD1[j]*in_fKnowD1[j+1]+s[j];
    for(j=0;j<=in_iN-2;j++)
        s[j]=in_fKnowPos[j+1]-in_fKnowPos[j];
    for(j=0;j<=in_iN-2;j++)
    {
        h1=s[j]*s[j];
        in_fKnowD2[j]=(float)6.0*(in_fKnowVal[j+1]-in_fKnowVal[j])/h1-(float)2.0*((float)2.0*in_fKnowD1[j]+in_fKnowD1[j+1])/s[j];
    }
    h1=s[in_iN-2]*s[in_iN-2];
    in_fKnowD2[in_iN-1]=(float)6.*(in_fKnowVal[in_iN-2]-in_fKnowVal[in_iN-1])/h1+(float)2.*((float)2.*in_fKnowD1[in_iN-1]+in_fKnowD1[in_iN-2])/s[in_iN-2];
    g=0.0;
    for(i=0;i<=in_iN-2;i++)
    {
        h1=(float)0.5*s[i]*(in_fKnowVal[i]+in_fKnowVal[i+1]);
        h1=h1-s[i]*s[i]*s[i]*(in_fKnowD2[i]+in_fKnowD2[i+1])/(float)24.0;
        g=g+h1;
    }

    for(j=0;j<=in_iM-1;j++)
    {
        if(in_fPos[j]>=in_fKnowPos[in_iN-1])
            i=in_iN-2;
        else
        {
            i=0;
            while(in_fPos[j]>in_fKnowPos[i+1])
                i=i+1;
        }
        h1=(in_fKnowPos[i+1]-in_fPos[j])/s[i];
        h0=h1*h1;
        out_fVal[j]=((float)3.0*h0-(float)2.0*h0*h1)*in_fKnowVal[i];
        out_fVal[j]=out_fVal[j]+s[i]*(h0-h0*h1)*in_fKnowD1[i];
        out_fD1[j]=(float)6.0*(h0-h1)*in_fKnowVal[i]/s[i];
        out_fD1[j]=out_fD1[j]+((float)3.0*h0-(float)2.0*h1)*in_fKnowD1[i];
        out_fD2[j]=((float)6.0-(float)12.0*h1)*in_fKnowVal[i]/(s[i]*s[i]);
        out_fD2[j]=out_fD2[j]+((float)2.0-(float)6.0*h1)*in_fKnowD1[i]/s[i];
        h1=(in_fPos[j]-in_fKnowPos[i])/s[i];
        h0=h1*h1;
        out_fVal[j]=out_fVal[j]+((float)3.0*h0-(float)2.0*h0*h1)*in_fKnowVal[i+1];
        out_fVal[j]=out_fVal[j]-s[i]*(h0-h0*h1)*in_fKnowD1[i+1];
        out_fD1[j]=out_fD1[j]-(float)6.0*(h0-h1)*in_fKnowVal[i+1]/s[i];
        out_fD1[j]=out_fD1[j]+((float)3.0*h0-(float)2.0*h1)*in_fKnowD1[i+1];
        out_fD2[j]=out_fD2[j]+((float)6.0-(float)12.0*h1)*in_fKnowVal[i+1]/(s[i]*s[i]);
        out_fD2[j]=out_fD2[j]-((float)2.0-(float)6.0*h1)*in_fKnowD1[i+1]/s[i];
    }

    if( nullptr != s)
        delete s;
   // s = NULL;
}

//三次样条曲线(1维(输出结果可含已知点))
void MathBiCubic::CubicSplineEx(float* out_fVal, float* in_fPos, int in_iM, float* in_fKnowPos, float* in_fKnowVal, int in_iN)
{
    float* fKnowDy = new float[in_iN];
    float* fKnowDdy = new float[in_iN];
    float* fInsertDy = new float[in_iM];
    float* fInsertDdy = new float[in_iM];

    MathBiCubic::CalculateDyDdy(fKnowDy, fKnowDdy, in_fKnowPos, in_fKnowVal, in_iN);
    MathBiCubic::CubicSpline(out_fVal, fInsertDy, fInsertDdy, in_fPos, in_iM,
                              in_fKnowPos, in_fKnowVal, fKnowDy, fKnowDdy, in_iN);

    for(int i=0; i<in_iM; i++)
    {
        int iRecored = i;
        for(int j=i+1; j<in_iM; j++)
        {
            if( in_fPos[j] < in_fPos[iRecored])
                iRecored = j;
        }
        if( i != iRecored)
        {
            float fTemp = in_fPos[i];
            in_fPos[i] = in_fPos[iRecored];
            in_fPos[iRecored] = fTemp;

            fTemp = out_fVal[i];
            out_fVal[i] = out_fVal[iRecored];
            out_fVal[iRecored] = fTemp;
        }
    }

    if( NULL != fInsertDdy)
        delete fInsertDdy;
    fInsertDdy = NULL;
    if( NULL != fInsertDy)
        delete fInsertDy;
    fInsertDy = NULL;
    if( NULL != fKnowDdy)
        delete fKnowDdy;
    fKnowDdy = NULL;
    if( NULL != fKnowDy)
        delete fKnowDy;
    fKnowDy = NULL;
}

//三次样条曲线(2维)
bool MathBiCubic::CubicSplineEx2_ROW(float*** inout_fVal,int in_iValRows,int in_iValLines,
                                      float*** in_fKnowVal,int in_iKnowRows,int in_iKnowLines)
{
    if( in_iValRows < in_iKnowRows || in_iKnowRows <= 0)
        return false;

    // Rows
    const int ROWK = (in_iValRows-1)/(in_iKnowRows-1);
    float* fPos = new float[in_iValLines];
    float* fVal = new float[in_iValLines];
    float* fKnowPos = new float[in_iKnowLines];
    float* fKnowVal = new float[in_iKnowLines];
    for(int i=0; i<in_iValRows; i+=ROWK)
    {
        for(int j=0; j<in_iValLines; j++)
        {
            fPos[j] = inout_fVal[i][j][0];
        }
        for(int j=0; j<in_iKnowLines; j++)
        {
            fKnowPos[j] = in_fKnowVal[i/ROWK][j][0];
            fKnowVal[j] = in_fKnowVal[i/ROWK][j][2];
        }

        CubicSplineEx(fVal,fPos,in_iValLines,fKnowPos,fKnowVal,in_iKnowLines);
        for (int i = 0 ; i < in_iValLines; i++)
        {
            qDebug("fVal %f",fVal[i]);
        }

        for (int i = 0 ; i < in_iKnowLines; i++)
        {
            qDebug("fKnowVal %f",fKnowVal[i]);
        }

        qDebug("%d %d",in_iValLines,in_iKnowLines);

        for(int j=0; j<in_iValLines; j++)
        {
            inout_fVal[i][j][2] = fVal[j];
        }
    }
    if( NULL != fPos)
        delete fPos;
    fPos = NULL;
    if( NULL != fVal)
        delete fVal;
    fVal = NULL;
    if( NULL != fKnowPos)
        delete fKnowPos;
    fKnowPos = NULL;
    if( NULL != fKnowVal)
        delete fKnowVal;
    return true;
}

//三次样条曲线(2维)
bool MathBiCubic::CubicSplineEx2_LINE(float*** inout_fVal,int in_iValRows,int in_iValLines,
                                       float*** in_fKnowVal,int in_iKnowRows,int in_iKnowLines)
{
    if( in_iValLines < in_iKnowLines || in_iKnowLines<=1 )
        return false;

    // Line
    const int LINIK = (in_iValLines-1)/(in_iKnowLines-1);
    float* fPos = new float[in_iValRows];
    float* fVal = new float[in_iValRows];
    float* fKnowPos = new float[in_iKnowRows];
    float* fKnowVal = new float[in_iKnowRows];
    for(int i=0; i<in_iValLines; i+=LINIK)
    {
        for(int j=0; j<in_iValRows; j++)
        {
            fPos[j] = inout_fVal[j][i][1];
        }
        for(int j=0; j<in_iKnowRows; j++)
        {
            fKnowPos[j] = in_fKnowVal[j][i/LINIK][1];
            fKnowVal[j] = in_fKnowVal[j][i/LINIK][2];
        }

        CubicSplineEx(fVal,fPos,in_iValRows,fKnowPos,fKnowVal,in_iKnowRows);

        for(int j=0; j<in_iValRows; j++)
        {
            inout_fVal[j][i][2] = fVal[j];
        }
    }
    if( NULL != fPos)
        delete fPos;
    fPos = NULL;
    if( NULL != fVal)
        delete fVal;
    fVal = NULL;
    if( NULL != fKnowPos)
        delete fKnowPos;
    fKnowPos = NULL;
    if( NULL != fKnowVal)
        delete fKnowVal;

    return true;
}


//三次样条曲线(2维)
bool MathBiCubic::CubicSplineEx2_RowLine(float*** inout_fVal,int in_iValRows,int in_iValLines,
                                          float*** in_fKnowVal,int in_iKnowRows,int in_iKnowLines)
{
    CubicSplineEx2_ROW(inout_fVal,in_iValRows,in_iValLines,in_fKnowVal,in_iKnowRows,in_iKnowLines);
    const int ROWK = (in_iValRows-1)/(in_iKnowRows-1);
    float*** fKnow = NULL;
    GetTable(fKnow,in_iKnowRows,in_iValLines,3);
    for(int i=0; i<in_iKnowRows; i++)
    {
        for(int j=0; j<in_iValLines; j++)
        {
            fKnow[i][j][0] = inout_fVal[i*ROWK][j][0];
            fKnow[i][j][1] = inout_fVal[i*ROWK][j][1];
            fKnow[i][j][2] = inout_fVal[i*ROWK][j][2];
        }
    }
    CubicSplineEx2_LINE(inout_fVal,in_iValRows,in_iValLines,fKnow,in_iKnowRows,in_iValLines);
    DeleteTable(fKnow,in_iKnowRows,in_iValLines);
    return true;
}


//三次样条曲线(2维)
bool MathBiCubic::CubicSplineEx2_LineRow(float*** inout_fVal,int in_iValRows,int in_iValLines,
                                          float*** in_fKnowVal,int in_iKnowRows,int in_iKnowLines)
{
    CubicSplineEx2_LINE(inout_fVal,in_iValRows,in_iValLines,in_fKnowVal,in_iKnowRows,in_iKnowLines);
    const int LINIK = (in_iValLines-1)/(in_iKnowLines-1);
    float*** fKnow = NULL;
    GetTable(fKnow,in_iValRows,in_iKnowLines,3);
    for(int i=0; i<in_iValRows; i++)
    {
        for(int j=0; j<in_iKnowLines; j++)
        {
            fKnow[i][j][0] = inout_fVal[i][j*LINIK][0];
            fKnow[i][j][1] = inout_fVal[i][j*LINIK][1];
            fKnow[i][j][2] = inout_fVal[i][j*LINIK][2];
        }
    }
    CubicSplineEx2_ROW(inout_fVal,in_iValRows,in_iValLines,fKnow,in_iValRows,in_iKnowLines);
    DeleteTable(fKnow,in_iValRows,in_iKnowLines);
    return true;
}



////////////////////////////////////



//#include <iostream>
//#include "MathBiCubic.h"

//using namespace std;


//void main()
//{
// //////////const int AN = 10;
// //////////const int KN = 5;
// ////////float AnsValue[AN+KN];
// ////////float AnsPos[AN+KN];
// ////////float KnowValue[KN];
// ////////float KnowPos[KN];
// ////////for(int i=AN; i>=0; i--)
// ////////{
// //////// AnsPos[AN-i] = i-1;
// ////////}
// ////////for(int i=0; i<KN; i++)
// ////////{
// //////// KnowPos[i] = 0.5+i;
// //////// KnowValue[i] = i+i*i+1;
// ////////}
// ////////for(int i=0; i<KN; i++)
// ////////{
// //////// AnsPos[i+AN] = KnowPos[KN-i-1];
// ////////}
// ////////for(int i=0; i<AN+KN; i++)
// //////// cout<<AnsPos[i]<<endl;
// ////////cout<<endl;

// ////////MathBiCubic::CubicSplineEx(AnsValue,AnsPos,AN+KN,KnowPos,KnowValue,KN);

// ////////for(int i=0; i<KN; i++)
// ////////{
// //////// cout<<KnowPos[i]<<": "<<KnowValue[i]<<endl;
// ////////}
// ////////cout<<endl;

// ////////for(int i=0; i<AN+KN; i++)
// //////// cout<<AnsPos[i]<<": "<<AnsValue[i]<<endl;


// const int AN = 9;
// const int KN = 5;
// float*** fKnow = NULL;
// float*** fRet = NULL;
// MathBiCubic::GetTable(fKnow,KN,KN,3);
// MathBiCubic::GetTable(fRet,AN,AN,3);

// for(int i=0; i<KN; i++)
// {
//  for(int j=0; j<KN; j++)
//  {
//   fKnow[i][j][0] = 0.5+j;
//   fKnow[j][i][1] = 0.5+j;
//  }
// }

// for(int i=0; i<KN; i++)
// {
//  for(int j=i; j<KN; j++)
//  {
//   fKnow[i][j][2] = j+j*j+1;
//   fKnow[j][i][2] = j+j*j+1;
//  }
// }

// for(int i=0; i<AN; i++)
// {
//  for(int j=0; j<AN; j++)
//  {
//   fRet[i][j][0] = 0.5+j*0.5;
//   fRet[i][j][1] = 0.5+i*0.5;
//  }
// }




// for(int i=0; i<KN; i++)
// {
//  for(int j=0; j<KN; j++)
//  {
//   cout<<"("<<fKnow[i][j][1]<<","<<fKnow[i][j][0]<<")";
//  }
//  cout<<endl;
// }

// for(int i=0; i<KN; i++)
// {
//  for(int j=0; j<KN; j++)
//  {
//   cout<<fKnow[i][j][2]<<" ";
//  }
//  cout<<endl;
// }
// cout<<endl;

// for(int i=0; i<AN; i++)
// {
//  for(int j=0; j<AN; j++)
//  {
//   cout<<"("<<fRet[i][j][1]<<","<<fRet[i][j][0]<<") ";
//  }
//  cout<<endl;
// }
// cout<<endl;

// MathBiCubic::CubicSplineEx2_RowLine(fRet,AN,AN,fKnow,KN,KN);

// cout.width(8);
// cout.flags(ios::right);
// for(int i=0; i<AN; i++)
// {
//  for(int j=0; j<AN; j++)
//  {
//   cout<<fRet[i][j][2]<<"   ";
//  }
//  cout<<endl;
// }

// //for(int i=0; i<AN; i++)
// //{
// // for(int j=0; j<AN; j++)
// // {
// //  cout<<fRet[j][i][1]<<" ";
// // }
// // cout<<endl;
// //}


// MathBiCubic::DeleteTable(fRet,AN,AN);
// MathBiCubic::DeleteTable(fKnow,KN,KN);

// system("pause");
//}

///*
//0.160714
//1.83929
//4.73214
//9.73214
//16.8393
//25.1607
//32.1964
//35.375
//32.125
//19.8751
//Press any key to continue . . .
//*/

