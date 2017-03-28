#include "Pair.h"
using namespace std ;

Pair::Pair( float input, float output )
{
    this->input = input ;
    this->output = output ;
}

float Pair::Get_input()
{
    return this->input ;
}

float Pair::Get_output()
{
    return this->output ;
}
