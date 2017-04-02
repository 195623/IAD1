#include <vector>
#include <iostream>

class Neuron ;

class Network
{
public:
    Network( int iNeurons = 1,
             int hNeurons = 1,
             int oNeurons = 1,
             double eta = 0.5,
             std::string hFunctionType = "logistic",
             std::string oFunctionType = "linear",
             std::string parametersChoice = "random" ) ;

private:
    int iNeuronsNumber ;
    std::vector<Neuron> hiddenNeurons ;
    std::vector<Neuron> outputNeurons ;

    std::string hFunctionType ;
    std::string oFunctionType ;
    double eta ;
    double biasH ;
    double biasO ;
};


