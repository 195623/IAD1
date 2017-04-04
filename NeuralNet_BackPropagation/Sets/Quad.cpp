#include "../headers.h"
using namespace std ;

Quad::Quad( double a, double b, double c, double d )
{
    this->a = a ;
    this->b = b ;
    this->c = c ;
    this->d = d ;
}

double Quad::Get_x( int x )
{
         if ( x == 0 ) return this->a ;
    else if ( x == 1 ) return this->b ;
    else if ( x == 2 ) return this->c ;
    else if ( x == 3 ) return this->d ;

    else
    {
        cout << "[ Quad::Get_x: invalid index value: " << x << " ]\n" ;
        return 0 ;
    }
}

double Quad::Get_a()
{
    return this->a ;
}

double Quad::Get_b()
{
    return this->b ;
}

double Quad::Get_c()
{
    return this->c ;
}

double Quad::Get_d()
{
    return this->d ;
}
