#include <iostream>
#include <tgmath.h>
#include <vector>

#include "headers.h"

// Functions: H has a sigmoidal Activation Function, and O has an "y(x)=x" Activation Function.

using namespace std ;

void Display_Pairs( vector<Pair> trainingPair );


int main()
{
    Network network = Network(4,3,4);
    Reader reader = Reader();
    vector<Quad> quads = reader.Create_Quads("texts/transformation.txt");

    //network.Show_Network();

    cout << "\nError = " << network.Total_Error(quads,quads) << '\n' ;
    for( int i = 0 ;i<1000;i++)
    {
        network.All_Lessons(quads,quads);
    }
    cout << "Error = " << network.Total_Error(quads,quads) << '\n' ;

    //network.Show_Network();


    return 0 ;
}
