#include "MapCreator.h"
#include <iostream>
using namespace std;
regex rgx("[a-zA-ZñÑáéíóúÁÉÍÓÚüç]+");
  
map<string, int> MapCreator::getMapFromFile(string path){
    map<string, int> words;

    ifstream in(path, ios::binary);
    if(in.fail()) 
        exit(0);
    stringstream strStream;
    strStream << in.rdbuf(); //read the file
    string data = strStream.str();

    vector<string> palabras;
    regex_iterator<string::iterator> it(data.begin(), data.end(), rgx);
    regex_iterator<string::iterator> end;

    for (; it != end; ++it)
        palabras.push_back(it->str());

    for(int i = 0; i < palabras.size(); i++) {
        auto place = words.find(palabras[i]);
        if(place == words.end())
            words.insert(pair<string, int>(palabras[i], 1));
        else
            place->second = place->second + 1;   
    }
    
    return words;
}

map<string, int> MapCreator::getMapFromString(string path){
    map<string, int> words;
    string data = path;
    vector<string> palabras;
    regex_iterator<string::iterator> it(data.begin(), data.end(), rgx);
    regex_iterator<string::iterator> end;

    for (; it != end; ++it)
        palabras.push_back(it->str());

    int numPalabras = palabras.size();

    for(int i = 0; i < palabras.size(); i++){
        auto place = words.find(palabras[i]);
        if(place == words.end())
            words.insert(pair<string, int>(palabras[i], 1));
        else
            place->second = place->second + 1;
    }
    return words;
}