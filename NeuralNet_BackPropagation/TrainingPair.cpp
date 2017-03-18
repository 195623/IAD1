#include "TrainingPair.h"
using namespace std ;

TrainingPair::TrainingPair( float input, float output )
{
    this->input = input ;
    this->output = output ;
}

float TrainingPair::Get_input()
{
    return this->input ;
}

float TrainingPair::Get_output()
{
    return this->output ;
}
