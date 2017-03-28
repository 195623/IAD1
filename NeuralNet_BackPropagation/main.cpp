#include <iostream>
#include <tgmath.h>
#include <vector>

#include "Analyzer.h"
#include "Reader.h"
#include "Pair.h"

// newFunctions: H has a sigmoidal Activation Function, and O has an "y(x)=x" Activation Function.

using namespace std ;

void Display_Pairs( vector<Pair> trainingPair );

int main()
{

    string fileName = "approximation_test.txt" ;


    int   hiddenNeurons = 10 ;
    double inputWeights = 0.5,
          outputWeights = 0.5,
          eta = .001, biasH = 0, biasO = 0 ;

    cout << "w_in = " ;
    cin >> inputWeights ;

    cout << "\nw_out = " ;
    cin >> outputWeights ;

    Reader reader ;
    vector<string> lines = reader.Read(fileName) ;
    vector<Pair> trainingPairs = reader.Parse_All_Lines(lines) ;

// ----------------
    /*Display_Pairs(trainingPairs) ;
    cin.get();
    return 0 ;*/
// ----------------

    Analyzer analyzer = Analyzer(hiddenNeurons,eta,biasH,biasO,inputWeights,outputWeights);


    cout << "Average Total error: " << analyzer.newAvgTotalError(trainingPairs) ;

    string text ;

    int i = 0 ;
    do
    {
        i++ ;
        cout << "\n#" << i << ":\n" ;
        analyzer.Train(trainingPairs) ;
        getline(cin,text) ;

    } while(text!="x") ;


    //double w1 = .5, w2 = .5, eta = .5 ;
    //Analyzer analyzer = Analyzer(w1,w2,eta);
    //analyzer.Learn(fileName,1000) ;


    cin.get() ;

    return 0 ;
}

void Display_Pairs( vector<Pair> trainingPair )
{
    double x, y ;
    for( vector<Pair>::iterator it = trainingPair.begin() ; it!=trainingPair.end() ; it++ )
    {
        x = (*it).Get_input() ;
        y = (*it).Get_output() ;
        cout << x << "             " << y << '\n' ;
    }
}
