#include <tgmath.h>
#include "Analyzer.h"
#include "Pair.h"
#include "Reader.h"
#include <ctime>
#include <stdlib.h>

using namespace std ;
double square( double x );




void Analyzer::Show_Weights()
{
    cout << "Biases: " << biasH << ", " << biasO << "\n" ;
    cout << "eta: " << eta << "\n" ;
    cout << "\n#N: ( input_weight --> output_weight ):\n" ;

    for(int i = 0 ; i<w_ins.size() ; i++ )
    {
        cout << "#" << i+1 << ": ( " << w_ins[i] << " --> " << w_outs[i] << " )\n" ;
    }
    cout << "\n\n" ;
}

Analyzer::Analyzer( int hiddenNeurons, double eta, double biasH, double biasO, string weightChoice )
{
    srand (time(NULL));

    if ( weightChoice == "random" )
    {
        cout << "ALL WEIGHTS RANDOMIZED.\n\n" ;
        double randNum1, randNum2 ;

        for(int i = 0 ; i< hiddenNeurons ; i++ )
        {
            randNum1 = (double) (rand()%1000)/1000 ;
            randNum2 = (double) (rand()%1000)/1000  ;

            w_ins.push_back(randNum1) ;
            w_outs.push_back(randNum2);
        }
    }
    else if ( weightChoice == "linear" )
    {
        double interval = .5/hiddenNeurons ;

        for(int i = 0 ; i< hiddenNeurons ; i++ )
        {
            w_ins.push_back(0.3+i*interval) ;
            w_outs.push_back(0.7-i*interval) ;
        }
    }

    this->biasH = biasH ; //(double) (rand()%1000)/1000 ;
    this->biasO = biasO ;   //(double) (rand()%1000)/1000  ;
    this->eta = eta ;  //(double) (rand()%1000)/1000  ;

    if( w_outs.size() == w_ins.size() && hiddenNeurons == w_outs.size() ) cout << "Weights successfully added to vector.\n\n" ;
    else cout << "Failed adding some weights to vector; (w_ins - w_outs) = " << (w_ins.size()-w_outs.size()) << "\n\n" ;

}

double Analyzer::Net_h ( double input, int neuronIndex )
{
    if (neuronIndex>=0 && neuronIndex < w_ins.size() ) return (input*w_ins[neuronIndex]+biasH) ;
    else cout << "[ Net_h: inputed an invalid neuronIndex = " << neuronIndex << " ]\n\n" ;

    return 0 ;
}

double Analyzer::Out_h ( double input, int neuronIndex ) // first function
{
    double outh = 1/(1+exp(-Net_h(input,neuronIndex))) ;

    return outh ;
}


double Analyzer::Net_o ( double input )
{
        double nNet_o = 0 ;

        for( int i = 0 ; i<w_ins.size() ;  i++ )
        {
            nNet_o += Out_h(input,i) * w_outs[i] ;
        }

        nNet_o += biasO ;

        return nNet_o ;
}

double Analyzer::Out_o ( double input ) // second function
{
    double output = Net_o(input) ;
    //cout << " log10(outO): " << log10(output) << "\n" ;
    return output ;
}

double Analyzer::Error ( double input, double target )
{
    double error = square( Out_o(input)-target )/2 ;

    //cout << "+" << error << '\n' ;

    return error ;
}

double Analyzer::AvgTotalError ( vector<Pair> testPairs )
{
    double error = 0 ;
    double num = testPairs.size() ;

    for(vector<Pair>::iterator it = testPairs.begin() ; it != testPairs.end() ; it++ )
    {
        error += Error( (*it).Get_input(), (*it).Get_output() ) ;
        //average outO values count
    }

    return error/num ;
}


double Analyzer::Hidden_weight_diff ( Pair trainingPair, int h_num )
{
    if( h_num >= 0 && h_num<w_ins.size() )
    {
        double outH = Out_h(trainingPair.Get_input(),h_num) ;
        double outO = Out_o(trainingPair.Get_input()) ;
        double tarO = trainingPair.Get_output() ;

        double output = ( outO - tarO )
                        * this->w_outs[h_num]
                        * outH
                        * (1-outH)
                        * trainingPair.Get_input() ;

        return output ;
    }

    cout << "Inputed non-existent Hidden Layer index: " << h_num ;

    return 0 ;
}

double Analyzer::Output_weight_diff ( Pair trainingPair, int h_num )
{
    if( h_num >= 0 && h_num<w_ins.size() )
    {
        float out = Out_o(trainingPair.Get_input()) ;
        float tar = trainingPair.Get_output() ;

        double output = ( out - tar ) * Out_h(trainingPair.Get_input(),h_num) ;

        return output ;
    }

    cout << "Inputed non-existent Hidden Layer index: " << h_num ;

    return 0 ;
}



void Analyzer::Train( vector<Pair> trainingPairs )
{
    for( int i = 0 ; i<w_ins.size() ; i++ )
    {
        double dwin = 0 ;
        double dwout = 0 ;

        for( vector<Pair>::iterator it = trainingPairs.begin() ; it != trainingPairs.end() ; it++ )
        {
            dwin  += Hidden_weight_diff(*it,i) ;
        }

        dwin = dwin/trainingPairs.size();
        //cout << "dwin = " << dwin << '\n' ;

        w_ins[i]  -= eta*dwin ;

        for( vector<Pair>::iterator it = trainingPairs.begin() ; it != trainingPairs.end() ; it++ )
        {
            dwout += Output_weight_diff(*it,i) ;
        }

        dwout = dwout/trainingPairs.size() ;
        //cout << "dwout = " << dwout << '\n' ;

        w_outs[i] -= eta*dwout ;
    }

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
