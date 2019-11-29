#include <iostream>
#include <cmath>
#include "mapCreator.h"
int main(){
    mapCreator a;
    map<string,int> lectura=a.getMapFromFile("./file.txt");

    int words = 0;
    int numServidores = 3;
    for(auto it = lectura.cbegin(); it != lectura.cend(); ++it){
        words = words + it->second;
    }

    int reparto = words / numServidores;
    int procesadas = 0;

    for(int i = 0; i < numServidores; i++) {
        int inicio = 0;
        int cant = 0;
        if(i == numServidores -1){
            cant = words - procesadas;
        }
        else{
            cant = trunc(reparto);
        }

        int j = 0;
        for(auto it2 = lectura.cbegin(); it2 != lectura.cend(); ++it2){
            if(j == cant)
                cout << "Aqui se envia" << endl;
            cout << it2->first << endl;
            j++;
        }

        inicio = cant + 1;
        procesadas += cant;
    }
    cout<<words<<endl;
    cout << procesadas << endl;



    /*
    int words=0;
    for(auto it = palabras.cbegin(); it != palabras.cend(); ++it){
        auto ap = lectura.find(it->first);
        if (ap != lectura.end()){
            words=words+ap->second;
        }
    }
    */
    //cout<<palabras.size()<<endl;
    //cout<<lectura.size()<<endl;
    
}