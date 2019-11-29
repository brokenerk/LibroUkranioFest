#include <iostream> 
#include <iterator> 
#include <string>
#include <regex>
#include "mapCreator.h"
#include "FileOpener.h"
  
using namespace std; 
  
map<string,int> mapCreator::getMapFromFile(string path){
    FileOpener a;
    map<string,int> words;
    regex rgx("[a-zA-ZñÑáéíóúÁÉÍÓÚüç]+");
    string data = a.getInfo(path);
    vector<string> palabras;
    regex_iterator<string::iterator> it(data.begin(), data.end(), rgx);
    regex_iterator<string::iterator> end;
    for (; it != end; ++it)
    {
        palabras.push_back(it->str());
    }
    for(int i = 0; i < palabras.size(); i++){
        auto place=words.find(palabras[i]);
        if(place == words.end()){
            words.insert(pair<string, int>(palabras[i], 1));
        }else{
            
            place->second=place->second+1;
        }
    }
    
    return words;
}

map<string,int> mapCreator::getMapFromString(string path){
    map<string,int> words;
    regex rgx("[a-zA-ZñÑáéíóúÁÉÍÓÚüç]+");
    string data =path;
    vector<string> palabras;
    regex_iterator<string::iterator> it(data.begin(), data.end(), rgx);
    regex_iterator<string::iterator> end;
    for (; it != end; ++it)
    {
        palabras.push_back(it->str());
    }
    int numPalabras=palabras.size();
    for(int i = 0; i < palabras.size(); i++){
        auto place=words.find(palabras[i]);
        if(place == words.end()){
            words.insert(pair<string, int>(palabras[i], 1));
        }else{
            place->second=place->second+1;
        }
    }
    return words;
}