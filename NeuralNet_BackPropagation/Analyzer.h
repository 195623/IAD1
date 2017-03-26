#include <vector>
#include <iostream>
class TrainingPair ;

class Analyzer
{
public:
    Analyzer( int h_n, float w_in, float w_out, float eta, float b_in, float b_out ) ;

    float newNet_h ( float input, int w_num ) ;
    float newOut_h ( float input, int w_num );
    float newNet_o ( float input );
    float newOut_o ( float input );

    float newError ( float input, float target ) ;


    float Pair_Averages( std::vector<TrainingPair> trainingPair, bool column ) ;
    float Pair_Variance( std::vector<TrainingPair> trainingPair, bool column ) ;


    /*float Net_h (float w1, float i1 ) ;
    float Out_h ( float w1, float i1 ) ;
    float Net_o ( float w1, float w2, float i1 ) ;
    float Out_o ( float w1, float w2, float i1 ) ;
    float E_single( float out, float tar ) ;
    float dE_dw1 (float w1, float w2, float i1, float tar ) ;
    float dE_dw2 (float w1, float w2, float i1, float tar ) ;
    float E_total( std::vector<TrainingPair> trainingPair, float w1, float w2 ) ;
    float E_max( std::vector<TrainingPair> trainingPair, float w1, float w2 ) ;
    void Learn( std::string fileName, int reps = 1 ) ;*/

private:
    //std::vector<TrainingPair*> trainingPairs ;
    float w1 ;
    float w2 ;

    float eta ;

    std::vector<float> w_ins ;
    std::vector<float> w_outs ;

    std::vector<float> out_h ;

    int h_n ;
    float b_in ;
    float b_out ;
};
