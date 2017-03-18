#include <vector>
class TrainingPair ;

class Analyzer
{
public:
    Analyzer() ;
    float Net_h (float w1, float i1 ) ;
    float Out_h ( float w1, float i1 ) ;
    float Net_o ( float w1, float w2, float i1 ) ;
    float Out_o ( float w1, float w2, float i1 ) ;
    float E_single( float out, float tar ) ;
    float dE_dw1 (float w1, float w2, float i1, float tar ) ;
    float E_total( std::vector<TrainingPair> trainingPair, float w1, float w2 ) ;

private:
    std::vector<TrainingPair*> trainingPairs ;
};
