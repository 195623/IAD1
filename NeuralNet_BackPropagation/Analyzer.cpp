#include <tgmath.h>
#include "Analyzer.h"
#include "TrainingPair.h"
using namespace std ;

Analyzer::Analyzer()
{

}

float Analyzer::Net_h (float w1, float i1 )
{
    return w1*i1 ;
}

float Analyzer::Out_h ( float w1, float i1 )
{
    return 1/(1+exp(-Net_h(w1,i1))) ;
}

float Analyzer::Net_o ( float w1, float w2, float i1 )
{
    return w2 * Out_h(w1,i1) ;
}

float Analyzer::Out_o ( float w1, float w2, float i1 )
{
    return 1/(1+exp(-Net_o(w1,w2,i1))) ;
}


float Analyzer::E_single( float out, float tar )
{
    return 0.5 * (out-tar)*(out-tar) ;
}


float Analyzer::dE_dw1 (float w1, float w2, float i1, float tar )
{
    return (   (Out_o(w1,w2,i1)-tar) * Out_o(w1,w2,i1) * (1-Out_o(w1,w2,i1)) * w2 * Out_h(w1,i1) * (1-Out_h(w1,i1) * i1 )   ) ;
}



float Analyzer::E_total( vector<TrainingPair> trainingPair, float w1, float w2 )
{
    float totalError = 0 ;

    for( vector<TrainingPair>::iterator i = trainingPair.begin() ; i != trainingPair.end() ; i++ )
    {
        totalError += E_single(Out_o(w1,w2,(*i).Get_input()),(*i).Get_output()) ;
    }

    return totalError ;
}

