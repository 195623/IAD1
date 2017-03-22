#include <iostream>
#include <tgmath.h>
#include <vector>

#include "Analyzer.h"
#include "Reader.h"
#include "TrainingPair.h"

using namespace std ;

int main()
{
    float w1 = .5, w2 = .5, eta = .5 ;
    string fileName = "approximation_train_1.txt" ;


    Analyzer analyzer = Analyzer(w1,w2,eta);
    analyzer.Learn(fileName) ;

    //float w1 = .5, w2 = .5 ;
    //float i1 = .5, tar = .5 ;

    //vector<string> lines = reader.Read("approximation_train_1.txt") ; //stops reading when two successive lines are the same
    //cout << lines.size() << " lines.\n\n" ;

    //vector<TrainingPair> trainingPairs = reader.Parse_All_Lines(lines) ;

    /*cout << "\nTotal error: " << analyzer.E_total(trainingPairs,w1,w2) ;

    cout << "\ndE/dw1: " << analyzer.dE_dw1(w1,w2,i1,tar) ;*/


    cin.get() ;

    return 0 ;
}
