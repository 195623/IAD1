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
    std::vector<Quad> QuadParse_All_Lines( std::vector<std::string> lines );

    std::vector<Quad> Create_Quads( std::string FileName );


    void Create_Pairs( std::string FileNameA, std::vector<Pair>* pPairsA, std::string FileNameB, std::vector<Pair>* pPairsB );

    private:

};
