#include <iostream>
#include <tgmath.h>
#include <vector>

#include "Analyzer.h"
#include "Reader.h"
#include "TrainingPair.h"

// newFunctions: H has a sigmoidal Activation Function, and O has an "y(x)=x" Activation Function.

using namespace std ;

int main()
{

    string fileName = "approximation_train_1.txt" ;


    int   h_n = 3 ;
    float inputWeights = 0.5,
          outputWeights = 0.5,
          eta = .5, b_in = .01, b_out = .01 ;

    Analyzer analyzer = Analyzer(h_n,inputWeights,outputWeights,eta,b_in,b_out);

    cout << analyzer.newOut_o(.1) ;

    //float w1 = .5, w2 = .5, eta = .5 ;
    //Analyzer analyzer = Analyzer(w1,w2,eta);
    //analyzer.Learn(fileName,1000) ;


    cin.get() ;

    return 0 ;
}
