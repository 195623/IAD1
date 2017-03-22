#include <tgmath.h>
#include "Analyzer.h"
#include "TrainingPair.h"
#include "Reader.h"
using namespace std ;

Analyzer::Analyzer( float w1, float w2, float eta )
{
    this->w1 = w1;
    this->w2 = w2;
    this->eta = eta;
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
    int err = 0.5 * (out-tar)*(out-tar) ;

    //cout << " + " << err  ;

    return err ;
}


float Analyzer::dE_dw1 (float w1, float w2, float i1, float tar )
{
    return ( (Out_o(w1,w2,i1)-tar) * Out_o(w1,w2,i1) * (1-Out_o(w1,w2,i1)) * w2 * Out_h(w1,i1) * (1-Out_h(w1,i1) ) * i1 ) ;
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

void Analyzer::Learn( string fileName )
{
    Reader reader ;

    vector<string> lines = reader.Read(fileName) ; //stops reading when two successive lines are the same
    cout << lines.size() << " lines.\n\n" ;

    vector<TrainingPair> trainingPairs = reader.Parse_All_Lines(lines) ;

    for( vector<TrainingPair>::iterator it = trainingPairs.begin() ; it != trainingPairs.end() ; it++ )
    {
        cout << "W1 = " << w1 << " --> Current error: " << this->E_total(trainingPairs,w1,w2) << "\n" ;
        float d = this->dE_dw1(w1,w2,(*it).Get_input(),(*it).Get_output()) ;
        w1 -= eta*d ;
    }
}
