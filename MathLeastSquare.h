#define QT_NO_DEBUG_OUTPUT

#ifndef LEASTSQUARE_H
#define LEASTSQUARE_H
#include <myglobal.h>



#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class MatchLeastSquare{
public:
    float a, b;
    MatchLeastSquare( vector<float>& x,  vector<float>& y);
    float getY( float x) ;
    float geta() ;
    float getb() ;

    void   print() ;
};

#endif // LEASTSQUARE_H
