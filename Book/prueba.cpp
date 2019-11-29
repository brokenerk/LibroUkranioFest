#include "mapCreator.h"
#include "Solicitud.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]){
    if (argc != 2)
    {
        printf("Forma de uso: %s ip_servidor\n", argv[0]);
        exit(0);
    }
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
            cout << auxCadena<<"\n\n\n" << endl;
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
        Solicitud s;
        string res;
        cout << cadenas.at(i) << endl;

        /*
        memcpy(&res, s.doOperation(argv[1], 5000, 1, cadenas.at(cont2).c_str(), strlen(cadenas.at(cont2).c_str())));
        cont2++;
        while (res == "OK")
        {
            cout << "Enviado y recibido" << endl;
        }
        */
    }
    
}