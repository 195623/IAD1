#include "headers.h"
using namespace std ;

Neuron::Neuron( int numberOfWeights, bool showComments )
{
    for( int i = 0 ; i<numberOfWeights ; i++ )
    {
        this->inputWeights.push_back( double(rand()%1000) / 1000.0) ;
        if(showComments) cout << "  * Weight #" << i+1 << " = " << inputWeights[i] << "\n" ;
    }
}

double Neuron::Get_weight( int i )
{
    if( i>0 && i<this->inputWeights.size() ) return this->inputWeights[i] ;

    return 0 ;
}

double Neuron::Combine_Inputs( vector<double> inputs, double bias )
{
    int is  = inputs.size() ;

    double output = 0 ;

    if( is > 0 )
    {
        for( int i = 0 ; i<is ; i++ )
        {
            output += inputWeights[i]*inputs[i] ;
        }

        output += bias ;
    }
    else cout << "[ Neuron::Output: recieved 0 inputs. ]" ;

    return output ;
}

double Neuron::Output_Logistic( vector<double> inputs, double bias )
{
    double combinedInputs = this->Combine_Inputs(inputs,bias);

    return 1/(1+exp(-combinedInputs));
}
