#include <iostream>

class Quad
{
public:
    Quad( double a, double b, double c, double d ) ;
    double Get_a();
    double Get_b();
    double Get_c();
    double Get_d();
    double Get_x( int x ) ;
    void Display();

private:
    double a ;
    double b ;
    double c ;
    double d ;
};

