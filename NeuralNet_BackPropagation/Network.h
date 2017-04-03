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
             std::string parametersChoice = "random",
             bool showComments = false ) ;

    double Output_Hidden_weight( int from, int to ) ;
    double Output_Output_weight( int from, int to ) ;

    double Output_HiddenNeuron( std::vector<double> iInputs, int neuronIndex );
    double Output_OutputNeuron( std::vector<double> iInputs, int neuronIndex ) ;
    double Output_OutputNeuron( Quad input, int outputIndex );

    std::vector<double> Output_OutputSet( std::vector<double> iInputs ) ;

    Quad Output_OutputQuad( Quad input );
    Quad Convert_To_Quad( std::vector<double> inputs );

    double Error(std::vector<double> inputs, std::vector<double> expectedOutputs );
    double Error( Quad in, Quad tar ) ;
    double Total_Error( Quad in, std::vector<Quad> tarSet );

    double BiasO_Diff( Quad input, Quad target );
    double WeightO_Diff( Quad input, Quad target );



    void Single_Lesson( Quad input, Quad target ) ;


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


