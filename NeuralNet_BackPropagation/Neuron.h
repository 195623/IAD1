#include<iostream>
#include<vector>

class Neuron
{
public:
    Neuron( int numberOfWeights, bool showComments = false );
    double Combine_Inputs( std::vector<double> input, double bias );
    double Output_Logistic( std::vector<double> input, double bias );

    double Get_weight( int i ) ;
    void Add_To_weight( double value, int i ) ;

private:
    std::vector<double> inputWeights ;
};
