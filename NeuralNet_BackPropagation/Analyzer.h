#include <vector>
#include <iostream>
class Pair ;

class Analyzer
{
public:
    Analyzer( int hiddenNeurons = 1, double eta = .5, double biasH = 0, double biasO = 0, double w_in = 0, double w_out = 0 ) ;

    double newNet_h ( double input, int hiddenIndex ) ;
    double newOut_h ( double input, int hiddenIndex );
    double newNet_o ( double input );
    double newOut_o ( double input );

    double newError ( double input, double target ) ;
    double newAvgTotalError ( std::vector<Pair> trainingPair );


    double Pair_Averages( std::vector<Pair> trainingPair, bool column ) ;
    double Pair_Variance( std::vector<Pair> trainingPair, bool column ) ;

    double Hidden_weight_diff ( Pair trainingPair, int h_num ) ;
    double Output_weight_diff ( Pair trainingPair, int h_num ) ;
    void Train(std::vector<Pair> trainingPairs) ;


    /*double Net_h (double w1, double i1 ) ;
    double Out_h ( double w1, double i1 ) ;
    double Net_o ( double w1, double w2, double i1 ) ;
    double Out_o ( double w1, double w2, double i1 ) ;
    double E_single( double out, double tar ) ;
    double dE_dw1 (double w1, double w2, double i1, double tar ) ;
    double dE_dw2 (double w1, double w2, double i1, double tar ) ;
    double E_total( std::vector<Pair> trainingPair, double w1, double w2 ) ;
    double E_max( std::vector<Pair> trainingPair, double w1, double w2 ) ;
    void Learn( std::string fileName, int reps = 1 ) ;*/

private:
    //std::vector<Pair*> trainingPairs ;
    double w1 ;
    double w2 ;

    double eta ;

    std::vector<double> w_ins ;
    std::vector<double> w_outs ;

    std::vector<double> out_h ;

    int hiddenNeurons ;
    double biasH ;
    double biasO ;
};
