#include <iostream>
#include <tgmath.h>
#include <vector>

#include "headers.h"

// Functions: H has a sigmoidal Activation Function, and O has an "y(x)=x" Activation Function.

using namespace std ;

void Display_Pairs( vector<Pair> trainingPair );
double Learning_Loop( Analyzer analyzer, vector<Pair> trainingPairs, vector<Pair> testPairs, int printIntervals = 0 );

int main()
{
    Network network = Network(4,5,4);
    vector<double> inputs ;
    inputs.push_back(.3);
    inputs.push_back(.4);
    inputs.push_back(.7);

    cout << endl ;

    Reader reader = Reader();

    vector<Quad> quads = reader.Create_Quads("texts/transformation.txt");

    cout << endl ;

    //cout << "Error = " << network.Total_Error(quads[0],quads) << '\n' ;
    cout << "Error = " << network.Error(quads[0],quads[1])  << endl ;
    network.Single_Lesson(quads[0],quads[1]) ;
    cout << "\nError = " << network.Error(quads[0],quads[1]) ;

    network.Single_Lesson(quads[0],quads[1]) ;
    cout << "\nError = " << network.Error(quads[0],quads[1]) ;

    network.Single_Lesson(quads[0],quads[1]) ;
    cout << "\nError = " << network.Error(quads[0],quads[1]) ;

    network.Single_Lesson(quads[0],quads[1]) ;
    cout << "\nError = " << network.Error(quads[0],quads[1]) ;



    return 0 ;
}
/*    string train1 = "texts/approximation_train_1.txt",
           train2 = "texts/approximation_train_2.txt",
           test12   = "texts/approximation_test.txt" ;

    string train0 = "texts/linear_training.txt",
           test0  = "texts/linear_testing.txt" ;

    string thisTraining = train1,
           thisTesting  = test12,
           thisDisplay  = train1 ;

    // ----------------------------------------------------------------

    string startingValuesLabel = "random narrow" ;

    int repsIncrement = 10000 ;

    int hiddenNeurons = 5;
    double eta = .5;

    string text = "yes" ;


    cout << "(d - display Out_o()'s output table)\n" ;
    cin >> text ;

    int skip = 100 ;

    vector<Pair> trainingPairs ;
    vector<Pair> testPairs ;
    Reader reader ;
    reader.Create_Pairs(thisTraining,&trainingPairs,thisTesting,&testPairs);

    Analyzer analyzer = Analyzer(hiddenNeurons,eta,startingValuesLabel);

    if ( text == "d" )
    {
        cout << "(Error = " << analyzer.AvgTotalError(testPairs) << ")\n\n";
        analyzer.Display_Example_Outputs() ;
        cin.get();
        cin.get();
        return 0 ;
    }

    double epsilon = analyzer.Pair_Variance(trainingPairs,1)/1000 ;

    // ----------------------------------------------------------------

    analyzer.Show_Weights();

    cout << "Epsilon: " << epsilon << "\n\n" ;

    double error = analyzer.AvgTotalError(testPairs) ;
    cout << "0\tError = " << error << '\n' ;


    double previousError = 0, currentError = analyzer.AvgTotalError(testPairs) ;

    // ----------------------------------------------------------------

    do
    {
        previousError = currentError ;
        currentError = analyzer.Learning_Loop(trainingPairs,testPairs,skip) ;

        cout << '\n' ;

        cout << "exit?" ;
        cin >> text ;

        if( text == "d" ) analyzer.Display_Example_Outputs() ;

        if ( text == "w" ) analyzer.Show_Weights();

    } while(text != "exit" && text != "yes" && text != "y" ) ;

    cin.get() ;

    return 0 ;
}*/


















