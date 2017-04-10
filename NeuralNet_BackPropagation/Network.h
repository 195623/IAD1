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
             double momentum = 0,
             std::string hFunctionType = "logistic",
             std::string oFunctionType = "linear",
             std::string parametersChoice = "all random",
             double biasO = 0,
             double biasH = 0,
             bool showComments = false ) ;

    void Set_Biases( double biasH, double biasO ) ;
    void Set_eta( double eta ) ;
    void Set_momentum( double momentum );

    void Show_Network();

    double Output_HWeight( int from, int to ) ;
    double Output_OWeight( int from, int to ) ;

    void Modify_HWeight_mom( int from, int to, double value ) ;
    void Modify_OWeight_mom( int from, int to, double value ) ;

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

    double BH_Diff( Quad input, Quad target, int h ) ;
    double BiasH_Diff( Quad input, Quad target ) ;

    double WeightO_Diff( Quad input, Quad target, int fromH, int toO );
    double WeightH_Diff( Quad input, Quad target, int fromI, int toH );

    void Add_To_biasH_etamom( double value ) ;
    void Add_To_biasO_etamom( double value ) ;

    void Single_Lesson( Quad input, Quad target ) ;
    void All_Lessons( std::vector<Quad> inputs, std::vector<Quad> targets ) ;


private:
    int iNeuronsNumber ;
    std::vector<Neuron> hiddenNeurons ;
    std::vector<Neuron> outputNeurons ;

    std::string hFunctionType ;
    std::string oFunctionType ;
    double eta ;
    double momentum ;
    double biasH ;
    double biasO ;

    double lastBiasHchange ;
    double lastBiasOchange ;
};


