#include <iostream>
#include <tgmath.h>
#include <vector>

#include "Analyzer.h"
#include "Reader.h"
#include "TrainingPair.h"

using namespace std ;

int main()
{
    Reader reader ;
    Analyzer analyzer ;

    float w1 = .5, w2 = .5 ;

    vector<string> lines = reader.Read("example.txt") ; //stops reading when two successive lines are the same
    cout << lines.size() << " lines.\n\n" ;

    vector<TrainingPair> trainingPairs = reader.Parse_All_Lines(lines) ;

    cout << "Total error: " << analyzer.E_total(trainingPairs,w1,w2) ;

    /*Analyzer analyzer ;

    float w1 = .5, w2 = .5 ;
    float i1 = .5 ;
    float tar_o = .2 ;

    float error = analyzer.E_single(analyzer.Out_o(w1,w2,i1),tar_o) ;

    cout << error << '\n' ;

    float dw1 = analyzer.dE_dw1(w1,w2,i1,tar_o) ;
    cout << dw1 << '\n' ;*/

    return 0 ;
}
