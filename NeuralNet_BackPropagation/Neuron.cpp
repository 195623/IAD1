#include "headers.h"
using namespace std ;

Neuron::Neuron( int numberOfWeights, bool showComments )
{
    for( int i = 0 ; i<numberOfWeights ; i++ )
    {
        this->inputWeights.push_back( double(rand()%2000)/1000.0 - 1.0 ) ;
        this->lastChange.push_back(0) ;
        if(showComments) cout << "  * Weight #" << i+1 << " = " << inputWeights[i] << "\n" ;
    }
}

void Neuron::Show_Neuron()
{
    for( int i = 0 ; i<this->inputWeights.size() ; i++ )
    {
        cout << "w[" << i << "] = " << this->inputWeights[i] << ' ';
    }
}

double Neuron::Get_weight( int i )
{
    if( i>=0 && i<this->inputWeights.size() ) return this->inputWeights[i] ;
    else cout << "[ Neuron::Get_weight: invalid weight index requested: " << i << " ]\n" ;
    return 0 ;
}

void Neuron::Add_To_weight( double value, int i )
{
    if( i>=0 && i<this->inputWeights.size() )
    {
        this->inputWeights[i] += value ;
        this->lastChange[i] = value ;
    }
    else cout << "[ Neuron::Add_To_weight: invalid weight index requested. ]\n" ;
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
