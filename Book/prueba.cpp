#include <iostream>
#include "mapCreator.h"
int main(){
    mapCreator a;
    map<string,int> palabras=a.getMapFromFile("./archivo.txt");
    map<string,int> lectura=a.getMapFromFile("./1.txt");
    /*
    for(auto it = lectura.cbegin(); it != lectura.cend(); ++it){
        std::cout << it->first<<endl;    
    }
    */
    int words=0;
    for(auto it = palabras.cbegin(); it != palabras.cend(); ++it){
        auto ap = lectura.find(it->first);
        if (ap != lectura.end()){
            words=words+ap->second;
        }
    }
    cout<<palabras.size()<<endl;
    cout<<lectura.size()<<endl;
    cout<<words<<endl;
}