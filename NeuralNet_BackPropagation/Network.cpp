#include <tgmath.h>
#include <ctime>
#include <stdlib.h>
#include "headers.h"

using namespace std ;
double square( double x );

Network::Network( int iNeurons,
                  int hNeurons,
                  int oNeurons,
                  double eta,
                  string hFunctionType,
                  string oFunctionType,
                  string parametersChoice,
                  bool showComments )
{
    srand (time(NULL));

    this->eta = eta ;
    this->hFunctionType = hFunctionType ;
    this->oFunctionType = oFunctionType ;

    if(showComments)
    {
        cout << "CREATING A NETWORK:\n\n" ;
        cout << "Creating Hidden Neurons:\n";
    }

    this->iNeuronsNumber = iNeurons ;

    for( int i = 0 ; i <hNeurons ; i++ )
    {
        if(showComments) cout << "- created a hidden neuron #" << i+1 << '\n' ;
        this->hiddenNeurons.push_back( Neuron(iNeurons) ) ;
    }

    if(showComments) cout << "\nCreating Output Neurons:\n" ;

    for( int i = 0 ; i <oNeurons ; i++ )
    {
        if(showComments) cout << "- created an output neuron #" << i+1 << '\n' ;
        this->outputNeurons.push_back( Neuron(hNeurons) );
    }

    if(showComments) cout << "\n\nCREATED A NETWORK." ;

}

double Network::Output_Hidden_weight( int from, int to )
{
    return this->hiddenNeurons[to].Get_weight(from) ;
}

double Network::Output_Output_weight( int from, int to )
{
    return this->outputNeurons[to].Get_weight(from) ;
}






double Network::Output_HiddenNeuron( vector<double> iInputs, int neuronIndex )
{
    double output = 0 ;
    if( neuronIndex >= 0 && neuronIndex < this->hiddenNeurons.size() ) output = this->hiddenNeurons[neuronIndex].Output_Logistic(iInputs,this->biasH);

    return output ;
}


double Network::Output_OutputNeuron( vector<double> iInputs, int neuronIndex )
{
    double output = 0 ;
    vector<double> hiddenOutputs ;

    for( int i = 0 ; i<hiddenNeurons.size() ; i++ )
    {
        hiddenOutputs.push_back(Output_HiddenNeuron(iInputs,i));
    }

    if( neuronIndex >= 0 && neuronIndex < this->outputNeurons.size() ) output = this->outputNeurons[neuronIndex].Output_Logistic(hiddenOutputs,this->biasO);

    return output ;
}

vector<double> Network::Output_OutputSet( vector<double> iInputs )
{
    vector<double> outputs ;
    for( int i = 0 ; i < this->outputNeurons.size() ; i++ )
    {
        double output = Output_OutputNeuron(iInputs,i) ;
        outputs.push_back(output);
    }

    return outputs ;
}



double Network::Output_OutputNeuron( Quad input, int outputIndex )
{
    double output = 0 ;
    vector<double> hiddenOutputs ;

    vector<double> iInputs ;
    iInputs.push_back(input.Get_a()) ;
    iInputs.push_back(input.Get_b()) ;
    iInputs.push_back(input.Get_c()) ;
    iInputs.push_back(input.Get_d()) ;

    for( int i = 0 ; i<hiddenNeurons.size() ; i++ )
    {
        hiddenOutputs.push_back(Output_HiddenNeuron(iInputs,i));
    }

    if( outputIndex >= 0 && outputIndex < this->outputNeurons.size() ) output = this->outputNeurons[outputIndex].Output_Logistic(hiddenOutputs,this->biasO);

    return output ;
}




Quad Network::Output_OutputQuad( Quad input )
{
    double a, b, c, d ;
    vector<double> hiddenOutputs ;

    vector<double> iInputs ;
    iInputs.push_back(input.Get_a()) ;
    iInputs.push_back(input.Get_b()) ;
    iInputs.push_back(input.Get_c()) ;
    iInputs.push_back(input.Get_d()) ;

    for( int i = 0 ; i<hiddenNeurons.size() ; i++ )
    {
        hiddenOutputs.push_back(Output_HiddenNeuron(iInputs,i));
    }

    a = this->outputNeurons[0].Output_Logistic(hiddenOutputs,this->biasO);
    b = this->outputNeurons[1].Output_Logistic(hiddenOutputs,this->biasO);
    c = this->outputNeurons[2].Output_Logistic(hiddenOutputs,this->biasO);
    d = this->outputNeurons[3].Output_Logistic(hiddenOutputs,this->biasO);

    return Quad(a,b,c,d) ;
}






double Network::Error(vector<double> inputs, vector<double> expectedOutputs )
{
    double error = 0 ;
    if( inputs.size() == expectedOutputs.size() )
    for( int i = 0 ; i<outputNeurons.size() ; i++ )
    {
         error += (inputs[i]-expectedOutputs[i])*(inputs[i]-expectedOutputs[i]);
    }

    return error ;
}

double Network::Error( Quad in, Quad tar  )
{
    Quad out = Output_OutputQuad(in);

    double error = -1 ;
    if( this->iNeuronsNumber == 4 && this->outputNeurons.size() == 4 )
    {
         error  = (out.Get_a() - tar.Get_a()) * (out.Get_a() - tar.Get_a())
                + (out.Get_b() - tar.Get_b()) * (out.Get_b() - tar.Get_b())
                + (out.Get_c() - tar.Get_c()) * (out.Get_c() - tar.Get_c())
                + (out.Get_d() - tar.Get_d()) * (out.Get_d() - tar.Get_d()) ;
    }
    else cout << "[ Network::Error(Quad,Quad): Network inputs and outputs in different number than 4 ]" ;

    return error ;
}


double Network::Total_Error( Quad in, vector<Quad> tarSet )
{
    double error = 0 ;

    vector<double> outputs ;
    for (int i = 0 ; i<tarSet.size() ; i++ )
    {
        error += Error(in,tarSet[i]) ;
    }

    return error/tarSet.size(); ;
}





Quad Network::Convert_To_Quad( vector<double> inputs )
{
    double a, b, c, d ;
    if( outputNeurons.size() == 4 )
    {
        a = Output_OutputNeuron(inputs,0);
        b = Output_OutputNeuron(inputs,1);
        c = Output_OutputNeuron(inputs,2);
        d = Output_OutputNeuron(inputs,3);
    }
    else cout << "[ Network::Output_Quad: function accepts only 4 arguments. ]" ;

    return Quad(a,b,c,d) ;
}

double Network::BiasO_Diff( Quad input, Quad target )
{
    double out0, out1, out2, out3 ;
    double tar0, tar1, tar2, tar3 ;

    out0 = Output_OutputNeuron(input,0);
    out1 = Output_OutputNeuron(input,1);
    out2 = Output_OutputNeuron(input,2);
    out3 = Output_OutputNeuron(input,3);

    tar0 = target.Get_a() ;
    tar1 = target.Get_b() ;
    tar2 = target.Get_c() ;
    tar3 = target.Get_d() ;

    double diff = 0 ;

    diff += (out0-tar0)*out0*(1-out0) ;
    diff += (out1-tar1)*out0*(1-out1) ;
    diff += (out2-tar2)*out0*(1-out2) ;
    diff += (out3-tar3)*out0*(1-out3) ;

    return diff ;
}




double Network::WeightO_Diff( Quad input, Quad target )
{
    double out0, out1, out2, out3 ;
    double tar0, tar1, tar2, tar3 ;

    out0 = Output_OutputNeuron(input,0);
    out1 = Output_OutputNeuron(input,1);
    out2 = Output_OutputNeuron(input,2);
    out3 = Output_OutputNeuron(input,3);

    tar0 = target.Get_a() ;
    tar1 = target.Get_b() ;
    tar2 = target.Get_c() ;
    tar3 = target.Get_d() ;

    double diff = 0 ;

    diff += (out0-tar0)*out0*(1-out0) ;
    diff += (out1-tar1)*out0*(1-out1) ;
    diff += (out2-tar2)*out0*(1-out2) ;
    diff += (out3-tar3)*out0*(1-out3) ;

    return diff ;
}





void Network::Single_Lesson( Quad input, Quad target )
{
    double dBiasO = BiasO_Diff(input,target) ;
    cout << "(Added " << -eta*dBiasO << " to the output bias.)\n" ;
    this->biasO -= eta*dBiasO ;
}
