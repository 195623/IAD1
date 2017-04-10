#include <iostream>
#include <tgmath.h>
#include <vector>

#include "headers.h"

// Functions: H has a sigmoidal Activation Function, and O has an "y(x)=x" Activation Function.

using namespace std ;

void Display_Pairs( vector<Pair> trainingPair );


int main()
{
    //Network network = Network(4,3,4,.5,0,"","","",0,0);

    Reader reader = Reader();
    vector<Quad> quads = reader.Create_Quads("texts/transformation.txt");

    double sum = 0 ;
    double n = 1 ;

    Network network0 = Network(4,3,4);
    network0.Set_Biases(0,0);

    for( int a = 0 ; a<=10 ; a+=2 )
    {
        cout << a+1 << ":\n" ;
        Network network = network0 ;
        network.Set_momentum(double(a)/10);

        network.Show_Network();

        for( int i = 0 ;i<10000;i++)
        {
            network.All_Lessons(quads,quads);

            if( i%100 == 0 ) cout << i+1 << "\tError = " << network.Total_Error(quads,quads) << '\n' ;
        }

        sum += network.Total_Error(quads,quads) ;
    }
    cout << "Average error: " << sum/n ;


    //network.Show_Network();


    return 0 ;
}
