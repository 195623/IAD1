#include "../headers.h"
using namespace std ;

Quad::Quad( double a, double b, double c, double d )
{
    this->a = a ;
    this->b = b ;
    this->c = c ;
    this->d = d ;
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
