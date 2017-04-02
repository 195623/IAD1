#include <string>
#include <cstdlib>
#include "../headers.h"
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
    else cout << "There is no \"" << fileName << "\" file.\n\n" ;

    myFile.close();

    return textLines ;
}

vector<Pair> Reader::Parse_All_Lines( vector<string> lines )
{
    vector<Pair> pairs ;

    for( vector<string>::iterator i = lines.begin() ; i != lines.end() ; i++ )
    {
        //cout << *i << endl ;
        pairs.push_back( Parse_Line(*i) );
    }

    //cout << "\n\n" ;

    return pairs ;
}

Pair Reader::Parse_Line( string textLine )
{
    int len = textLine.length() ;
    int spaceIndex ;

    for( int i = 0 ; i<len ; i++ )
    {
        if ( textLine[i] == ' ' || textLine[i] == '\t' )
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

    return Pair(input,output) ;
}


Quad Reader::QuadParse_Line( string textLine )
{
    string a, b, c, d ;

    if( textLine.length() == 7 )
    {
        a = textLine[0] ;
        b = textLine[2] ;
        c = textLine[4] ;
        d = textLine[6] ;
    }

    double A = atof(a.c_str());
    double B = atof(a.c_str());
    double C = atof(a.c_str());
    double D = atof(a.c_str());

    return Quad(A,B,C,D) ;
}



void Reader::Create_Pairs( string FileNameA, vector<Pair>* pPairsA, string FileNameB, vector<Pair>* pPairsB )
{
        vector<string> lines = Read(FileNameA) ;
        *pPairsA = Parse_All_Lines(lines) ;

        lines = Read(FileNameB) ;
        *pPairsB = Parse_All_Lines(lines) ;
}
