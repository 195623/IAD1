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
           test12   = "approximation_test.txt" ;

    string train0 = "linear_training.txt",
           test0  = "linear_testing.txt" ;

    string thisTraining = train1,
           thisTesting  = test12,
           thisDisplay  = train1 ;

    // ----------------------------------------------------------------

    string startingValuesLabel = "defined" ;

    int repsIncrement = 10000 ;

    int hiddenNeurons = 5;
    double eta = .01 ;
    double biasH = .5, biasO = .5 ;

    string text = "yes" ;


    cout << "Custom values? (y/n) " ;
    cin >> text ;

    int skip = 100 ;

    if( text == "yes" || text == "y" )
    {
        cout << "eta = " ;
        cin >> eta ;
        cout << "#hidden_neurons = " ;
        cin >> hiddenNeurons ;
        cout << "biasH = " ;
        cin >> biasH ;
        cout << "biasO = " ;
        cin >> biasO ;
    }
    else if ( text == "d" )
    {
        Reader reader ;
        vector<string> lines = reader.Read(thisTesting) ;
        vector<Pair> pairs = reader.Parse_All_Lines(lines) ;

        Analyzer analyzer = Analyzer(hiddenNeurons,eta,biasH,biasO,startingValuesLabel);

        cout << "(Error = " << analyzer.AvgTotalError(pairs) << ")\n\n";
        //analyzer.Display_Example_Outputs() ;
        //analyzer.Display_Pairs(pairs) ;
        cin.get();
        cin.get();
        return 0 ;
    }

    Analyzer analyzer = Analyzer(hiddenNeurons,eta,biasH,biasO,startingValuesLabel);

            Reader reader ;
            vector<string> lines = reader.Read(thisTraining) ;
            vector<Pair> trainingPairs = reader.Parse_All_Lines(lines) ;

            lines = reader.Read(thisTesting) ;
            vector<Pair> testPairs = reader.Parse_All_Lines(lines) ;

    double epsilon = analyzer.Pair_Variance(trainingPairs,1)/1000 ;

    // ----------------------------------------------------------------

    analyzer.Show_Weights();
    cout << "Average Total error: " << analyzer.AvgTotalError(testPairs) << '\n' ;

    int allReps = repsIncrement ;

    double milestone = analyzer.AvgTotalError(testPairs) ;
    double previousError = 0, currentError = milestone ;

    int i = 0 ;

    // ----------------------------------------------------------------

    do
    {
        cout << "Epsilon: " << epsilon << "\n\n" ;

        for( ; i<allReps ; i++ )
        {
            analyzer.Train(trainingPairs);

            double error = analyzer.AvgTotalError(testPairs) ;

            previousError = currentError ;
            currentError = error ;

            /*if( error < milestone )
            {
                cout << '\t' << i+1 << "\t ERROR = " << error << " \t( halved; last change =" << currentError-previousError << " )\n" ;
                milestone = error/2 ;
            }*/

            if ( i%skip == 0 || i == allReps-1 )
            {
                cout << '\t' << i+1 << "\t Error = " << error << " \t( last change =" << currentError-previousError << " )\n" ;
            }

            if( fabs(currentError-previousError)<epsilon || currentError>previousError+0.1 )
            {
                cout << '\t' << i+1 << "\t Error = " << error << " \t( last change =" << currentError-previousError << " )\n" ;
                break ;
            }
        }

        cout << '\n' ;

        analyzer.Show_Weights();

        cout << "\nExit? " ;
        cin >> text ;

        allReps += repsIncrement ;
        epsilon = epsilon/10 ;

        if( text == "d" ) analyzer.Display_Example_Outputs() ;

    } while(text != "exit" && text != "yes" && text != "y" ) ;

    cin.get() ;
    cin.get() ;

    return 0 ;
}


















