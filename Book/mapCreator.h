#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;
#if !defined(MAPCREATOR_H_)
#define MAPCREATOR_H_
class mapCreator
{
private:
    /* data */
public:
    map<string,int> getMapFromFile(string path);
    map<string,int> getMapFromString(string path);
};
#endif // FILEOPENER_H_