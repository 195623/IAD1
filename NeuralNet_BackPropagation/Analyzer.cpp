#include <tgmath.h>
#include "Analyzer.h"
#include "TrainingPair.h"
#include "Reader.h"
using namespace std ;

Analyzer::Analyzer( int h_n, float w_in, float w_out, float eta, float b_in, float b_out )
{
    /*this->w1 = w1;
    this->w2 = w2;*/

    for(int i = 0 ; i<h_n ; i++ )
    {
        w_ins.push_back(w_in) ;
        w_outs.push_back(w_out) ;
    }

    this->h_n = h_n ;
    this->eta = eta;
    this->b_in = b_in ;
    this->b_out = b_out ;
}

float Analyzer::newNet_h ( float input, int w_num )
{
    if (w_num>=0 && w_num <h_n) return (input*w_ins[w_num]+b_in) ;

    return 0 ;
}

float Analyzer::newOut_h ( float input, int w_num )
{
    float newouth = 1/(1+exp(-newNet_h(input,w_num))) ;

    //cout << newouth << "|" ;

    return newouth ;
}


float Analyzer::newNet_o ( float input )
{
        //cout << "&&&";
        float nNet_o = 0 ;

        for( int i = 0 ; i<h_n ;  i++ )
        {
            //cout << "*";
            nNet_o += newOut_h(input,i)*w_outs[i] ;
        }
        nNet_o += b_out ;

        return nNet_o ;

    return 0 ;
}

float Analyzer::newOut_o ( float input )
{
    return newNet_o(input) ;
}

float Analyzer::newError ( float input, float target )
{
    return 0 ;
}












/*float Analyzer::Net_h (float w1, float i1 )
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


float Analyzer::dE_dw2 (float w1, float w2, float i1, float tar )
{
    return ( (Out_o(w1,w2,i1)-tar) * Out_o(w1,w2,i1) * (1-Out_o(w1,w2,i1)) * Out_h(w1,i1) ) ;
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

float Analyzer::E_max( vector<TrainingPair> trainingPair, float w1, float w2 )
{
    float maxError = 0, error ;

    for( vector<TrainingPair>::iterator i = trainingPair.begin() ; i != trainingPair.end() ; i++ )
    {
        error = E_single(Out_o(w1,w2,(*i).Get_input()),(*i).Get_output()) ;

        if(error>maxError)maxError=error;
    }

    return maxError ;
}



bool oneByOne = true ;

void Analyzer::Learn( string fileName, int reps )
{
    Reader reader ;

    vector<string> lines = reader.Read(fileName) ; //stops reading when two successive lines are the same
    cout << lines.size() << " lines.\n\n" ;

    vector<TrainingPair> trainingPairs = reader.Parse_All_Lines(lines) ;

    cout << "Inputs average:   " << this->Pair_Averages(trainingPairs,0) << '\n' ;
    cout << "Inputs variance:  " << this->Pair_Variance(trainingPairs,0) << "\n\n" ;
    cout << "Outputs average:  " << this->Pair_Averages(trainingPairs,1) << '\n' ;
    cout << "Outputs variance: " << this->Pair_Variance(trainingPairs,1) << "\n\n" ;





    cout << "before: (" << w1 << "," << w2 << ") --> max error: " << this->E_max(trainingPairs,w1,w2) << "\n" ;

    for( int i = 0 ; i<reps ; i++ )
    {
        float D1 = 0, D2 = 0 ;

        for( vector<TrainingPair>::iterator it = trainingPairs.begin() ; it != trainingPairs.end() ; it++ )
        {
            //cout << "(" << w1 << "," << w2 << ") --> Current error: " << this->E_total(trainingPairs,w1,w2) << "\n" ;
            float d1 = this->dE_dw1(w1,w2,(*it).Get_input(),(*it).Get_output()) ;
            float d2 = this->dE_dw2(w1,w2,(*it).Get_input(),(*it).Get_output()) ;

            if (oneByOne)
            {
                w1-=eta*d1 ;
                w2-=eta*d2 ;
            }
            else
            {
                D1 += d1 ;
                D2 += d2 ;
            }

            //w1 -= eta*d1 ;
            //w2 -= eta*d2 ;
        }

        if(!oneByOne)
        {
            w1-=eta*D1 ;
            w2-=eta*D2 ;
        }
    }
    cout << "after: (" << w1 << "," << w2 << ") --> max error: " << this->E_max(trainingPairs,w1,w2) << "\n\n" ;


}*/

float Analyzer::Pair_Averages( vector<TrainingPair> trainingPair, bool column )
{
    float sum = 0.0 ;
    float number = float(trainingPair.size()) ;

    for(vector<TrainingPair>::iterator it = trainingPair.begin() ; it != trainingPair.end() ; it++)
    {
        if( column == 0 ) sum += (*it).Get_input()  ;
        else              sum += (*it).Get_output() ;
    }

    return sum/number ;
}

float square( float x )
{
    return x*x ;
}

float Analyzer::Pair_Variance( vector<TrainingPair> trainingPair, bool column )
{
    float squareSum = 0.0 ;
    float number = float(trainingPair.size()) ;
    float average = Pair_Averages(trainingPair,column) ;

    for(vector<TrainingPair>::iterator it = trainingPair.begin() ; it != trainingPair.end() ; it++)
    {
        if( column == 0 ) squareSum += square( (*it).Get_input() - average ) ;
        else              squareSum += square( (*it).Get_output() - average ) ;
    }

    return squareSum/number ;
}









