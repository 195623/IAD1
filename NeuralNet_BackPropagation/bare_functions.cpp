#include <iostream>
#include <vector>
#include "headers.h"
using namespace std ;

void Display_Pairs( vector<Pair> trainingPair )
{
    double x, y ;
    for( vector<Pair>::iterator it = trainingPair.begin() ; it!=trainingPair.end() ; it++ )
    {
        x = (*it).Get_input() ;
        y = (*it).Get_output() ;
        cout << x << "             " << y << '\n' ;
    }
}

double square( double x )
{
    return x*x ;
}
