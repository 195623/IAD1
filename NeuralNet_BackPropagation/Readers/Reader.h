#include <iostream>
#include <fstream>
#include <vector>

class Pair ;
class Quad ;

class Reader
{
public:
    Reader() ;
    std::vector<std::string> Read( std::string fileName ) ;

    Pair Parse_Line( std::string textLine ) ;
    Quad QuadParse_Line( std::string textLine ) ;

    std::vector<Pair> Parse_All_Lines( std::vector<std::string> lines ) ;


    void Create_Pairs( std::string FileNameA, std::vector<Pair>* pPairsA, std::string FileNameB, std::vector<Pair>* pPairsB );

    private:

};
