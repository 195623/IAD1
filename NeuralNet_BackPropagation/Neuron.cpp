#include "headers.h"
using namespace std ;

Neuron::Neuron( int numberOfWeights )
{
    for( int i = 0 ; i<numberOfWeights ; i++ ) this->inputWeights.push_back((rand()%1000) / 1000) ;
}
