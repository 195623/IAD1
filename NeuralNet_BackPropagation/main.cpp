#include <iostream>
#include <tgmath.h>
#include <vector>

#include "Analyzer.h"
#include "Reader.h"
#include "Pair.h"

// Functions: H has a sigmoidal Activation Function, and O has an "y(x)=x" Activation Function.

using namespace std ;

void Display_Pairs( vector<Pair> trainingPair );

int main()
{
    string train1 = "approximation_train_1.txt",
           train2 = "approximation_train_2.txt",
           test   = "approximation_test.txt" ;

    int   hiddenNeurons = 10 ;
    double eta = 0.2, biasH = .3, biasO = 0.6 ;

    /*cout << "eta = " ;
    cin >> eta ;

    if( eta > 0 )
    {
        cout << "#hidden_neurons = " ;
        cin >> hiddenNeurons ;
        cout << "biasH = " ;
        cin >> biasH ;
        cout << "biasO = " ;
        cin >> biasO ;
    }*/


            Reader reader ;
            vector<string> lines = reader.Read(train1) ;
            vector<Pair> trainingPairs = reader.Parse_All_Lines(lines) ;

            lines = reader.Read(test) ;
            vector<Pair> testPairs = reader.Parse_All_Lines(lines) ;

    Analyzer analyzer = Analyzer(hiddenNeurons,eta,biasH,biasO,"random");

    analyzer.Show_Weights();
    cout << "Average Total error: " << analyzer.AvgTotalError(testPairs) << '\n' ;

    string text ;
    int reps = 0 ;
    cout << "Reps: " ;
    cin >> reps ;

    double milestone = analyzer.AvgTotalError(testPairs) ;
    double previousError = 0, currentError = milestone ;

    do
    {
        for( int i = 0 ; i<reps ; i++ )
        {
            analyzer.Train(trainingPairs);
            //if ( i%100 == 0 || i == reps-1 )
            double error = analyzer.AvgTotalError(testPairs) ;
            if( error < milestone )
            {
                cout << "HALVED ERROR - #" << i+1 << ": ERROR = " << error << '\n' ;
                milestone = milestone/2 ;

                previousError = currentError ;
                currentError = error ;
            }

            if ( i%1000 == 0 || i == reps-1 )
            {
                previousError = currentError ;
                currentError = error ;
                cout << "#" << i+1 << ": Error = " << error << " ( last change =" << currentError-previousError << " )\n" ;
            }

        }

        cout << '\n' ;

        analyzer.Show_Weights();

        cout << "\n\nExit? " ;
        cin >> text ;

    } while(text != "exit" && text != "yes" && text != "y" ) ;

    return 0 ;
}


















