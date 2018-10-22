#include "MathLeastSquare.h"


MatchLeastSquare::MatchLeastSquare( vector<float>& x,  vector<float>& y)
{
    float t1=0, t2=0, t3=0, t4=0;
    for(int i=0; i<x.size(); ++i)
    {
        t1 += x[i]*x[i];
        t2 += x[i];
        t3 += x[i]*y[i];
        t4 += y[i];
    }
    if((t1*x.size() - t2*t2) == 0){
        a = 0;
        b = 0;

    }
    else{
        a = (t3*x.size() - t2*t4) / (t1*x.size() - t2*t2);
        //b = (t4 - a*t2) / x.size();
        b = (t1*t4 - t2*t3) / (t1*x.size() - t2*t2);
    }
}

float MatchLeastSquare::getY( float x)
{
    return a*x + b;
}
float MatchLeastSquare::geta()
{
    return a;
}
float MatchLeastSquare::getb()
{
    return b;
}

void MatchLeastSquare::print()
{
    //  cout<<"y = "<<a<<"x + "<<b<<"\n";
}
