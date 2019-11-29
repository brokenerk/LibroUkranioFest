#include <istream>
#include "FileOpener.h"
#include <sstream>


string FileOpener::getInfo(string ruta){
    ifstream in(ruta, ios::binary );
    if( in.fail() ) throw 0;
    std::stringstream strStream;
    strStream << in.rdbuf(); //read the file
    std::string str = strStream.str();
    return str;
}