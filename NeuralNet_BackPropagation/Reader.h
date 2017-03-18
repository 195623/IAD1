#include <iostream>
#include <fstream>
#include <vector>

class TrainingPair ;

class Reader
{
public:
    Reader() ;
    std::vector<std::string> Read( std::string fileName ) ;
    TrainingPair Parse_Line( std::string textLine ) ;
    std::vector<TrainingPair> Parse_All_Lines( std::vector<std::string> lines ) ;

    private:

};
