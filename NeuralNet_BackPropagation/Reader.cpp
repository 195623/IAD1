#include "Reader.h"
#include "TrainingPair.h"
#include <string>
#include <cstdlib>
using namespace std ;

Reader::Reader()
{

}

vector<string> Reader::Read( string fileName )
{
    char* fileNameC = (char*) &fileName[0] ;
    vector<string> textLines ;
    string thisLine, previousLine ;

    ifstream myFile;
    myFile.open (fileNameC);

    if( myFile.is_open() )
    {
        for(int i = 0;;i++)
        {
            previousLine = thisLine ;
            getline(myFile,thisLine);

            if ( thisLine == previousLine ) break ;
            else textLines.push_back(thisLine);
        }
    }
    myFile.close();

    return textLines ;
}

vector<TrainingPair> Reader::Parse_All_Lines( vector<string> lines )
{
    vector<TrainingPair> pairs ;

    for( vector<string>::iterator i = lines.begin() ; i != lines.end() ; i++ )
    {
        pairs.push_back( Parse_Line(*i) );
    }

    //cout << "\n\n" ;

    return pairs ;
}

TrainingPair Reader::Parse_Line( string textLine )
{
    int len = textLine.length() ;
    int spaceIndex ;

    for( int i = 0 ; i<len ; i++ )
    {
        if ( textLine[i] == ' ' )
        {
            spaceIndex = i ;
            break ;
        }
    }

    string sinput, soutput ;

    sinput = textLine.substr(0,spaceIndex) ;
    soutput = textLine.substr(spaceIndex+1,len-spaceIndex-1) ;
    //cout << sinput << "_" << soutput << endl ;

    //float input, output ; // convert strings to floats

    float input = atof(sinput.c_str());
    float output = atof(soutput.c_str());

    return TrainingPair(input,output) ;
}
