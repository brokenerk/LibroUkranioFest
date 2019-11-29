#include <iostream>
#include <vector>
#include <cstring>
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

    int reparto = lectura.size() / numServidores;
    int procesadas = 0;

    //se llena para obtener las posiciones
    vector<int> posiciones;
    for (int k = 0; k <numServidores ; ++k) {
        posiciones.push_back(reparto*(k+1));
    }

    vector<string>cadenas;
    int z = 0;
    /*
     * Aqui se generan las cadenas
     * */
    int j=0;
    string auxCadena="";
    for(auto it2 = lectura.cbegin(); it2 != lectura.cend(); ++it2){
        auxCadena +=it2->first+ ',';
        if(j == posiciones[z]) {
            cout << "Aqui se envia cadena: "<< auxCadena<<"\n\n\n" << endl;
            cadenas.push_back(auxCadena);
            auxCadena="";
            z++;
        }
        j++;
    }
    /*
     * Aqui se envian las cadenas a los servidores, almacenas en el arreglo cadenas
     * */

    for(int i = 0; i < numServidores; i++) {
        int inicio = 0;
        int cant = 0;
        if(i == numServidores -1){
            cant = words - procesadas;
        }
        else{
            cant = trunc(reparto);
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