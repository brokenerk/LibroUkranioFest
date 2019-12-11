#ifndef MAPCREATOR_H_
#define MAPCREATOR_H_
#include <cstring>
#include <sstream>
#include <istream>
#include <fstream>
#include <iterator> 
#include <map>
#include <vector>
#include <regex>
#include <iostream>
using namespace std;
class MapCreator{
	public:
	    map<string, int> getMapFromFile(string path);
	    map<string, int> getMapFromString(string path);
};
#endif