#include <tgmath.h>
#include "Analyzer.h"
#include "Pair.h"
#include "Reader.h"
#include <ctime>
#include <stdlib.h>

using namespace std ;

double square( double x )
{
    return x*x ;
}

Analyzer::Analyzer( int hiddenNeurons, double eta, double biasH, double biasO, double w_in, double w_out )
{
    srand (time(NULL));

    if ( w_in == 0 && w_out == 0 )
    {
        double randNum1, randNum2 ;

        cout << "( input_weight --> output_weight ):\n\n" ;

        for(int i = 0 ; i<hiddenNeurons ; i++ )
        {
            randNum1 = (double) (rand()%1000)/1000 ;
            randNum2 = (double) (rand()%1000)/1000 ;

            cout << "#" << i+1 << ": ( " << randNum1 << " --> " << randNum2 << " )\n" ;

            w_ins.push_back(randNum1) ;
            w_outs.push_back(randNum2);
        }
        cout << "\n\n" ;
    }
    else
    {
        for(int i = 0 ; i<hiddenNeurons ; i++ )
        {
            w_ins.push_back(w_in) ;
            w_outs.push_back(w_out) ;
        }
    }


    this->hiddenNeurons = hiddenNeurons ;
    this->eta = eta;
    this->biasH = biasH ;
    this->biasO = biasO ;
}

double Analyzer::newNet_h ( double input, int neuronIndex )
{
    if (neuronIndex>=0 && neuronIndex < hiddenNeurons ) return (input*w_ins[neuronIndex]+biasH) ;
    else cout << "[ newNet_h: inputed an invalid neuronIndex = " << neuronIndex << " ]\n\n" ;

    return 0 ;
}

double Analyzer::newOut_h ( double input, int neuronIndex ) // first function
{
    double newouth = 1/(1+exp(-newNet_h(input,neuronIndex))) ;

    return newouth ;
}


double Analyzer::newNet_o ( double input )
{
        double nNet_o = 0 ;

        for( int i = 0 ; i<hiddenNeurons ;  i++ )
        {
            nNet_o += newOut_h(input,i) * w_outs[i] ;
        }

        nNet_o += biasO ;

        return nNet_o ;
}

double Analyzer::newOut_o ( double input ) // second function
{
    return newNet_o(input) ;
}

double Analyzer::newError ( double input, double target )
{
    return square(newOut_o(input)-target)/2 ;
}

double Analyzer::newAvgTotalError ( vector<Pair> trainingPairs )
{
    double error = 0 ;
    double num = trainingPairs.size() ;

    for(vector<Pair>::iterator it = trainingPairs.begin() ; it != trainingPairs.end() ; it++ )
    {
        error += newError( (*it).Get_input(), (*it).Get_output() ) ;
    }

    return error/num ;
}


double Analyzer::Hidden_weight_diff ( Pair trainingPair, int h_num )
{
    if( h_num >= 0 && h_num<hiddenNeurons )
    {
        double noh = newOut_h(trainingPair.Get_input(),h_num) ;

        double output = ( newOut_o(trainingPair.Get_input()) - trainingPair.Get_output() )
                        * this->w_ins[h_num]
                        * noh
                        * (1-noh)  ;

        return output ;
    }

    cout << "Inputed non-existent Hidden Layer index: " << h_num ;

    return 0 ;
}

double Analyzer::Output_weight_diff ( Pair trainingPair, int h_num )
{
    if( h_num >= 0 && h_num<hiddenNeurons )
    {
        float out = newOut_o(trainingPair.Get_input()) ;
        float tar = trainingPair.Get_output() ;

        double output = ( out - tar ) * newOut_h(trainingPair.Get_input(),h_num) ;

        return output ;
    }

    cout << "Inputed non-existent Hidden Layer index: " << h_num ;

    return 0 ;
}



void Analyzer::Train( vector<Pair> trainingPairs )
{
    for( vector<Pair>::iterator it = trainingPairs.begin() ; it != trainingPairs.end() ; it++ )
    {
        for( int i = 0 ; i<hiddenNeurons ; i++ )
        {
            w_ins[i] -= eta*Hidden_weight_diff(*it,i) ;
            w_outs[i] -= eta*Output_weight_diff(*it,i) ;

            //if ( w_outs[i] > 1000000 ) return ;

        }
    }

    cout << "("<< newAvgTotalError(trainingPairs) << ")\n";

}


// ----------------------------------------------------------------------------------------------------------



double Analyzer::Pair_Averages( vector<Pair> trainingPair, bool column )
{
    double sum = 0.0 ;
    double number = double(trainingPair.size()) ;

    for(vector<Pair>::iterator it = trainingPair.begin() ; it != trainingPair.end() ; it++)
    {
        if( column == 0 ) sum += (*it).Get_input()  ;
        else              sum += (*it).Get_output() ;
    }

    return sum/number ;
}



double Analyzer::Pair_Variance( vector<Pair> trainingPair, bool column )
{
    double squareSum = 0.0 ;
    double number = double(trainingPair.size()) ;
    double average = Pair_Averages(trainingPair,column) ;

    for(vector<Pair>::iterator it = trainingPair.begin() ; it != trainingPair.end() ; it++)
    {
        if( column == 0 ) squareSum += square( (*it).Get_input() - average ) ;
        else              squareSum += square( (*it).Get_output() - average ) ;
    }

    return squareSum/number ;
}





























/*double Analyzer::Net_h (double w1, double i1 )
{
    return w1*i1 ;
}

double Analyzer::Out_h ( double w1, double i1 )
{
    return 1/(1+exp(-Net_h(w1,i1))) ;
}

double Analyzer::Net_o ( double w1, double w2, double i1 )
{
    return w2 * Out_h(w1,i1) ;
}

double Analyzer::Out_o ( double w1, double w2, double i1 )
{
    return 1/(1+exp(-Net_o(w1,w2,i1))) ;
}


double Analyzer::E_single( double out, double tar )
{
    int err = 0.5 * (out-tar)*(out-tar) ;

    //cout << " + " << err  ;

    return err ;
}


double Analyzer::dE_dw1 (double w1, double w2, double i1, double tar )
{
    return ( (Out_o(w1,w2,i1)-tar) * Out_o(w1,w2,i1) * (1-Out_o(w1,w2,i1)) * w2 * Out_h(w1,i1) * (1-Out_h(w1,i1) ) * i1 ) ;
}


double Analyzer::dE_dw2 (double w1, double w2, double i1, double tar )
{
    return ( (Out_o(w1,w2,i1)-tar) * Out_o(w1,w2,i1) * (1-Out_o(w1,w2,i1)) * Out_h(w1,i1) ) ;
}



double Analyzer::E_total( vector<Pair> trainingPair, double w1, double w2 )
{
    double totalError = 0 ;

    for( vector<Pair>::iterator i = trainingPair.begin() ; i != trainingPair.end() ; i++ )
    {
        totalError += E_single(Out_o(w1,w2,(*i).Get_input()),(*i).Get_output()) ;
    }

    return totalError ;
}

double Analyzer::E_max( vector<Pair> trainingPair, double w1, double w2 )
{
    double maxError = 0, error ;

    for( vector<Pair>::iterator i = trainingPair.begin() ; i != trainingPair.end() ; i++ )
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

    vector<Pair> trainingPairs = reader.Parse_All_Lines(lines) ;

    cout << "Inputs average:   " << this->Pair_Averages(trainingPairs,0) << '\n' ;
    cout << "Inputs variance:  " << this->Pair_Variance(trainingPairs,0) << "\n\n" ;
    cout << "Outputs average:  " << this->Pair_Averages(trainingPairs,1) << '\n' ;
    cout << "Outputs variance: " << this->Pair_Variance(trainingPairs,1) << "\n\n" ;





    cout << "before: (" << w1 << "," << w2 << ") --> max error: " << this->E_max(trainingPairs,w1,w2) << "\n" ;

    for( int i = 0 ; i<reps ; i++ )
    {
        double D1 = 0, D2 = 0 ;

        for( vector<Pair>::iterator it = trainingPairs.begin() ; it != trainingPairs.end() ; it++ )
        {
            //cout << "(" << w1 << "," << w2 << ") --> Current error: " << this->E_total(trainingPairs,w1,w2) << "\n" ;
            double d1 = this->dE_dw1(w1,w2,(*it).Get_input(),(*it).Get_output()) ;
            double d2 = this->dE_dw2(w1,w2,(*it).Get_input(),(*it).Get_output()) ;

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


