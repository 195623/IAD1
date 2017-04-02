#include<iostream>
#include<vector>

class Neuron
{
public:
    Neuron( int numberOfWeights );

private:
    std::vector<double> inputWeights ;
};
