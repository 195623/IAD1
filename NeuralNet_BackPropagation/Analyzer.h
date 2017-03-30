#include <vector>
#include <iostream>
class Pair ;

class Analyzer
{
public:
    Analyzer( int hiddenNeurons = 1, double eta = .5, double biasH = 0, double biasO = 0, std::string weightChoice = "random" ) ;

    double Net_h ( double input, int hiddenIndex ) ;
    double Out_h ( double input, int hiddenIndex );
    double Net_o ( double input );
    double Out_o ( double input );

    void Show_Weights() ;
    double Error ( double input, double target ) ;
    double AvgTotalError ( std::vector<Pair> trainingPair );


    double Pair_Averages( std::vector<Pair> trainingPair, bool column ) ;
    double Pair_Variance( std::vector<Pair> trainingPair, bool column ) ;

    double Hidden_weight_diff ( Pair trainingPair, int h_num ) ;
    double Output_weight_diff ( Pair trainingPair, int h_num ) ;
    void Train(std::vector<Pair> trainingPairs) ;

private:
    double eta ;

    std::vector<double> w_ins ;
    std::vector<double> w_outs ;

    //std::vector<double> out_h ;

    //int hiddenNeurons ;
    double biasH ;
    double biasO ;
};
