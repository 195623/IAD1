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
                  double momentum,
                  string hFunctionType,
                  string oFunctionType,
                  string parametersChoice,
                  bool showComments )
{
    srand (time(NULL));

    this->eta = eta ;
    this->momentum = momentum ;
    this->hFunctionType = hFunctionType ;
    this->oFunctionType = oFunctionType ;
    this->iNeuronsNumber = iNeurons ;

    this->biasH = double(rand()%2000)/1000.0 - 1.0 ;
    this->biasO = double(rand()%2000)/1000.0 - 1.0 ;

    lastBiasHchange = 0 ;
    lastBiasOchange = 0 ;

    if(showComments)
    {
        cout << "CREATING A NETWORK:\n\n" ;
        cout << "Creating Hidden Neurons:\n";
    }



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

void Network::Show_Network()
{
    cout << "BiasH = " << biasH << '\n' ;
    cout << "BiasO = " << biasO << '\n' ;

    cout << "Hidden neurons:\n" ;
    for( int i = 0 ; i<this->hiddenNeurons.size() ; i++ )
    {
        hiddenNeurons[i].Show_Neuron() ;
        cout << '\n' ;
    }

    cout << "\n\nOutput neurons:\n" ;
    for( int i = 0 ; i<this->outputNeurons.size() ; i++ )
    {
        outputNeurons[i].Show_Neuron() ;
        cout << '\n' ;
    }
}

double Network::Output_HWeight( int from, int to )
{
    return this->hiddenNeurons[to].Get_weight(from) ;
}

double Network::Output_OWeight( int from, int to )
{
    return this->outputNeurons[to].Get_weight(from) ;
}






double Network::OutH( vector<double> iInputs, int neuronIndex )
{
    double output = 0 ;
    if( neuronIndex >= 0 && neuronIndex < this->hiddenNeurons.size() ) output = this->hiddenNeurons[neuronIndex].Output_Logistic(iInputs,this->biasH);

    return output ;
}




double Network::OutH( Quad input, int neuronIndex )
{
    double output = 0 ;

    vector<double> iInputs ;
    iInputs.push_back(input.Get_a()) ;
    iInputs.push_back(input.Get_b()) ;
    iInputs.push_back(input.Get_c()) ;
    iInputs.push_back(input.Get_d()) ;

    if( neuronIndex >= 0 && neuronIndex < this->hiddenNeurons.size() ) output = this->hiddenNeurons[neuronIndex].Output_Logistic(iInputs,this->biasH);

    return output ;
}


double Network::OutO( vector<double> iInputs, int neuronIndex )
{
    double output = 0 ;
    vector<double> hiddenOutputs ;

    for( int i = 0 ; i<hiddenNeurons.size() ; i++ )
    {
        hiddenOutputs.push_back(OutH(iInputs,i));
    }

    if( neuronIndex >= 0 && neuronIndex < this->outputNeurons.size() ) output = this->outputNeurons[neuronIndex].Output_Logistic(hiddenOutputs,this->biasO);

    return output ;
}

vector<double> Network::Output_OutputSet( vector<double> iInputs )
{
    vector<double> outputs ;
    for( int i = 0 ; i < this->outputNeurons.size() ; i++ )
    {
        double output = OutO(iInputs,i) ;
        outputs.push_back(output);
    }

    return outputs ;
}



double Network::OutO( Quad input, int outputIndex )
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
        hiddenOutputs.push_back(OutH(iInputs,i));
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
        hiddenOutputs.push_back(OutH(iInputs,i));
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
    //in.Display(); cout << "-->" ; out.Display() ; cout << "\n" ;
    //out.Display(); cout << "<>" ; tar.Display() ; cout << "\n" ;

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


double Network::Total_Error( vector<Quad> inSet, vector<Quad> tarSet )
{
    double error = 0 ;

    if( inSet.size() != tarSet.size() )
    {
        cout << "[ Network::Total_Error: inSet.size() != tarSet.size() ]\n" ;
        return 0 ;
    }

    for (int i = 0 ; i<tarSet.size() ; i++ )
    {
        error += Error(inSet[i],tarSet[i]) ;
    }

    return error/tarSet.size(); ;
}





Quad Network::Convert_To_Quad( vector<double> inputs )
{
    double a, b, c, d ;
    if( outputNeurons.size() == 4 )
    {
        a = OutO(inputs,0);
        b = OutO(inputs,1);
        c = OutO(inputs,2);
        d = OutO(inputs,3);
    }
    else cout << "[ Network::Output_Quad: function accepts only 4 arguments. ]" ;

    return Quad(a,b,c,d) ;
}

double Network::BiasO_Diff( Quad input, Quad target )
{
    double out0, out1, out2, out3 ;
    double tar0, tar1, tar2, tar3 ;

    out0 = OutO(input,0);
    out1 = OutO(input,1);
    out2 = OutO(input,2);
    out3 = OutO(input,3);

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

double Network::BH_Diff( Quad input, Quad target, int h )
{
    double diff = 0 ;

    for( int o = 0 ; o < this->outputNeurons.size() ; o++ )
    {
        double outO = OutO(input,o);
        double tarO = target.Get_x(o) ;
        double Who  = Output_OWeight(h,o) ;

        diff += (outO-tarO)*outO*(1-outO)*Who ;
    }

    double outH = OutH(input,h);

    diff = diff*outH*(1-outH) ;

    return diff ;
}

double Network::BiasH_Diff( Quad input, Quad target )
{
    double diff = 0 ;
    for( int h = 0 ; h<hiddenNeurons.size() ; h++ )
    {
        diff += BH_Diff(input,target,h) ;
    }

    return diff ;
}


double Network::WeightO_Diff( Quad input, Quad target, int fromH, int toO )
{
    double outH = OutH(input,fromH) ;
    double outO = OutO(input,toO)   ;
    double tarO = target.Get_x(toO) ;

    return (outO-tarO)*outO*(1-outO)*outH ;
}

double Network::WeightH_Diff( Quad input, Quad target, int fromI, int toH )
{
    double diff = 0 ;

    for( int o = 0 ; o < this->outputNeurons.size() ; o++ )
    {
        double outO = OutO(input,o);
        double tarO = target.Get_x(o) ;
        double Who  = Output_OWeight(toH,o) ;

        diff += (outO-tarO)*outO*(1-outO)*Who ;
    }

    double outH = OutH(input,toH);

    diff = diff*outH*(1-outH)*input.Get_x(fromI) ;

    return diff ;
}







void Network::Modify_HWeight_mom( int from, int to, double value )
{
    this->hiddenNeurons[to].Add_To_weight(value,from,momentum);
}

void Network::Modify_OWeight_mom( int from, int to, double value )
{
    this->outputNeurons[to].Add_To_weight(value,from,momentum);
}



void Network::Single_Lesson( Quad input, Quad target )
{
    double dBiasO = BiasO_Diff(input,target) ;
    Add_To_biasO_etamom(-dBiasO) ;

    double dBiasH = BiasH_Diff(input,target) ;
    Add_To_biasH_etamom(-dBiasH) ;

    for( int h = 0 ; h < hiddenNeurons.size() ; h++ )
    {
        for( int o = 0 ; o < outputNeurons.size() ; o++ )
        {
            double dWeightO = -eta*WeightO_Diff(input,target,h,o) ;
            this->Modify_OWeight_mom(h,o,dWeightO) ;
        }

        for( int i = 0 ; i < iNeuronsNumber ; i++ )
        {
            double dWeightH = -eta*WeightH_Diff(input,target,i,h) ;
            this->Modify_HWeight_mom(i,h,dWeightH) ;
        }
    }
    //this->
}

void Network::Add_To_biasH_etamom( double value )
{
    double thisChange = value*(1-momentum) + momentum*lastBiasHchange ;
    thisChange = thisChange*eta ;
    this->biasH += thisChange ;

    lastBiasHchange = thisChange ;
}


void Network::Add_To_biasO_etamom( double value )
{
    double thisChange = value*(1-momentum) + momentum*lastBiasOchange ;
    thisChange = thisChange*eta ;
    this->biasO += thisChange ;

    lastBiasOchange = thisChange ;
}



void Network::All_Lessons( vector<Quad> inputs, vector<Quad> targets )
{
    for( int i = 0 ; i<inputs.size() ; i++ ) Single_Lesson(inputs[i],targets[i]) ;
}
