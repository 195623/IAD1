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

    void Show_Network();

    double Output_HWeight( int from, int to ) ;
    double Output_OWeight( int from, int to ) ;

    void Modify_HWeight( int from, int to, double value ) ;
    void Modify_OWeight( int from, int to, double value ) ;

    double OutH( std::vector<double> iInputs, int neuronIndex );
    double OutH( Quad input, int neuronIndex );

    double OutO( std::vector<double> iInputs, int outputIndex ) ;
    double OutO( Quad input, int outputIndex );

    std::vector<double> Output_OutputSet( std::vector<double> iInputs ) ;

    Quad Output_OutputQuad( Quad input );
    Quad Convert_To_Quad( std::vector<double> inputs );

    double Error(std::vector<double> inputs, std::vector<double> expectedOutputs );
    double Error( Quad in, Quad tar ) ;
    double Total_Error( std::vector<Quad> inSet, std::vector<Quad> tarSet );

    double BiasO_Diff( Quad input, Quad target );
    double WeightO_Diff( Quad input, Quad target, int fromH, int toO );
    double WeightH_Diff( Quad input, Quad target, int fromI, int toH );

    void Single_Lesson( Quad input, Quad target ) ;
    void All_Lessons( std::vector<Quad> inputs, std::vector<Quad> targets ) ;


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


