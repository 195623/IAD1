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

    for(int i = 0 ; i<w_h.size() ; i++ )
    {
        cout << "w_h[" << i+1 << "] = " << w_h[i] << ",\t w_o[" << i+1 << "] = " << w_o[i] << "\n" ;
    }
    cout << "\n" ;
}

Analyzer::Analyzer( int hiddenNeurons, double eta, double biasH, double biasO, string weightChoice )
{
    srand (time(NULL));

    if ( weightChoice == "defined" )
    {
        w_h.push_back(-.88) ;
        w_h.push_back(-.16) ;
        w_h.push_back(.24) ;
        w_h.push_back(-.07) ;
        w_h.push_back(.21) ;

        w_o.push_back(-52.38) ;
        w_o.push_back(446.17) ;
        w_o.push_back(106.87) ;
        w_o.push_back(70.78) ;
        w_o.push_back(72.74) ;

        biasH = -1.46 ;
        biasO = -122.56 ;

        /*w_h.push_back(-0.8856) ;
        w_h.push_back(-0.1592) ;
        w_h.push_back(0.23791) ;
        w_h.push_back(-0.0748) ;
        w_h.push_back(0.20699) ;

        w_o.push_back(-52.3875);
        w_o.push_back(446.1796);
        w_o.push_back(106.8689);
        w_o.push_back(70.78377);
        w_o.push_back(72.46707);

        biasH = -1.4575 ;
        biasO = 122.5619 ;*/
    }
    else if ( weightChoice == "random narrow" )
    {
        cout << "ALL WEIGHTS RANDOMIZED.\n\n" ;
        double randNum1, randNum2 ;

        for(int i = 0 ; i< hiddenNeurons ; i++ )
        {
            randNum1 = (double) (rand()%1000)/1000 ;
            randNum2 = (double) (rand()%1000)/1000 ;

            w_h.push_back(randNum1) ;
            w_o.push_back(randNum2);
        }

        biasH = (double) (rand()%1000)/1000 ;
        biasO = (double) (rand()%1000)/1000 ;
    }
    else if ( weightChoice == "random wide" )
    {
        cout << "ALL WEIGHTS RANDOMIZED.\n\n" ;
        double randNum1, randNum2 ;

        for(int i = 0 ; i< hiddenNeurons ; i++ )
        {
            randNum1 = (double) (rand()%20000 - 10000)/100 ;
            randNum2 = (double) (rand()%20000 - 10000)/100 ;

            w_h.push_back(randNum1) ;
            w_o.push_back(randNum2);
        }

        biasH = (double) (rand()%20000 - 10000)/100 ;
        biasO = (double) (rand()%20000 - 10000)/100 ;
    }
    else if ( weightChoice == "linear" )
    {
        double interval = .5/hiddenNeurons ;

        for(int i = 0 ; i< hiddenNeurons ; i++ )
        {
            w_h.push_back(0.3+i*interval) ;
            w_o.push_back(0.7-i*interval) ;
        }
    }
    else cout << "Analyzer: invalid weightChoice string: \"" << weightChoice << "\"\n\n" ;

    this->biasH = biasH ; //(double) (rand()%1000)/1000 ;
    this->biasO = biasO ;   //(double) (rand()%1000)/1000  ;
    this->eta = eta ;  //(double) (rand()%1000)/1000  ;

    if( w_o.size() == w_h.size() && hiddenNeurons == w_o.size() ) cout << "Weights successfully added to vector.\n\n" ;
    else cout << "Failed adding some weights to vector; (w_h - w_o) = " << (w_h.size()-w_o.size()) << "\n\n" ;

}


// a few "x" / "this->x" confusions in constructor ^^^

double Analyzer::Net_h ( double input, int neuronIndex )
{
    if (neuronIndex>=0 && neuronIndex < w_h.size() ) return (input*w_h[neuronIndex]+biasH) ;
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

        for( int i = 0 ; i<w_h.size() ;  i++ )
        {

            nNet_o += Out_h(input,i) * w_o[i] ;
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
    if( h_num >= 0 && h_num<w_h.size() )
    {
        double outH = Out_h(trainingPair.Get_input(),h_num) ;
        double outO = Out_o(trainingPair.Get_input()) ;
        double tarO = trainingPair.Get_output() ;

        double output = ( outO - tarO )
                        * this->w_o[h_num]
                        * outH
                        * (1-outH)
                        ; trainingPair.Get_input() ;

        return output ;
    }

    cout << "Inputed non-existent Hidden Layer index: " << h_num ;

    return 0 ;
}

double Analyzer::Output_weight_diff ( Pair trainingPair, int h_num )
{
    if( h_num >= 0 && h_num<w_h.size() )
    {
        double out = Out_o(trainingPair.Get_input()) ;
        double tar = trainingPair.Get_output() ;

        double output = ( out - tar ) * Out_h(trainingPair.Get_input(),h_num) ;

        return output ;
    }

    cout << "Inputed non-existent Hidden Layer index: " << h_num ;

    return 0 ;
}

double Analyzer::biasHiddenDiff( Pair trainingPair )
{
    double input = trainingPair.Get_input() ;

    //double outO = Out_o(input) ;
    //double tarO = trainingPair.Get_output() ;

    double output = 0 ;

    for( int i = 0 ; i< this->w_h.size() ; i++ )
    {
        output += Out_h(input,i)*(1-Out_h(input,i))*w_o[i] ;
    }

    return output ;
}

double Analyzer::biasOutputDiff( Pair trainingPair )
{
    int i = 0 ;
    double input = trainingPair.Get_input() ;

    double outO = Out_o(input) ;
    double tarO = trainingPair.Get_output() ;

    double output = (outO-tarO) ;

    return output ;
}





// biasO & w_o[i] update correctly -- good E-diff functions


void Analyzer::Train( vector<Pair> trainingPairs )
{

    //for( int i = 0 ; i<w_h.size() ; i++ )
    {
        double dwH = 0 ;
        double dwO = 0 ;

        /*for( vector<Pair>::iterator it = trainingPairs.begin() ; it != trainingPairs.end() ; it++ )
        {
            dwO += Output_weight_diff(*it,i) ;
            dbiasO += biasOutputDiff(*it) ;
        }

        dwO = dwO/trainingPairs.size() ;
        this->w_o[i] -= eta*dwO ;*/

        /*for( vector<Pair>::iterator it = trainingPairs.begin() ; it != trainingPairs.end() ; it++ )
        {
            dwH  += Hidden_weight_diff(*it,i) ;
        }

        dwH = dwH/trainingPairs.size();

        this->w_h[i]  -= eta*dwH ;*/


        /*for( vector<Pair>::iterator it = trainingPairs.begin() ; it != trainingPairs.end() ; it++ )
        {
            dbiasO += biasOutputDiff(*it) ;
        }
        dbiasO = dbiasO/trainingPairs.size();
        this->biasO  -= eta*dbiasO ;*/

    }

    double dbiasH = 0 ;
    double dbiasO = 0 ;

    for( vector<Pair>::iterator it = trainingPairs.begin() ; it != trainingPairs.end() ; it++ )
    {
        dbiasH += biasHiddenDiff(*it) ;
    }
    dbiasH = dbiasH/trainingPairs.size();
    this->biasH -= eta*dbiasH ;
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



double Analyzer::Pair_Variance( vector<Pair> aPair, bool column )
{
    double squareSum = 0.0 ;
    double number = double(aPair.size()) ;
    double average = Pair_Averages(aPair,column) ;

    for(vector<Pair>::iterator it = aPair.begin() ; it != aPair.end() ; it++)
    {
        if( column == 0 ) squareSum += square( (*it).Get_input() - average ) ;
        else              squareSum += square( (*it).Get_output() - average ) ;
    }

    return squareSum/number ;
}

double Analyzer::Display_Example_Outputs()
{
    for( double x = -5 ; x<=5 ; x += 0.1 )
    {
        cout << x << '\t' << Out_o(x) << '\n' ;
    }
}

void Analyzer::Display_Pairs( vector<Pair> trainingPair )
{
    double x, y ;
    for( vector<Pair>::iterator it = trainingPair.begin() ; it!=trainingPair.end() ; it++ )
    {
        x = (*it).Get_input() ;
        y = (*it).Get_output() ;
        cout << x << "    " << y << "    " << Out_o(x) << '\n' ;
    }
}
