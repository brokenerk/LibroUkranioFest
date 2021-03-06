#include "Respuesta.h"
#include "MapCreator.h"
#include <cstring>
#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Forma de uso: %s pto\n", argv[0]);
        exit(0);
    }
    MapCreator m;
    map<string, int> rae = m.getMapFromFile("rae.txt");
    map<string, int> palabras;
    Respuesta resp(atoi(argv[1]));
    cout << "Servidor iniciado pto: " << argv[1] << "....\n";
    int r = -1;
    while (true) {
        struct mensaje *msj = resp.getRequest();
        
        if(msj != NULL) {
            int tam = 0;
            memcpy(&tam, &msj->tam, 4);

            int wordTimes = 0;
            memcpy(&wordTimes, &msj->wordTimes, 4);

        	char* rec = (char*)calloc(tam, sizeof(char));
	        memcpy(rec, msj->arguments, tam);

            if(strcmp(rec, "END+") == 0) {
                cout << "Terminando" << endl;
                for(auto it = rae.cbegin(); it != rae.cend(); it++) {
                    if(palabras.find(it->first) != palabras.end()){
                        palabras.erase(it->first);
                    }
                }

                int error = -1;
                for(auto it = palabras.cbegin(); it != palabras.cend(); it++) {
                    error = error + it->second;
                }

                printf("Errores: %d\n", error);
                palabras.clear();
                resp.sendReply((char*)&error);
            }
            else {
                palabras.insert(pair<string, int>(rec, wordTimes));
                resp.sendReply((char*)&r);
            }
            delete [] rec;
            //cout << "Enviando respuesta" << endl;
        }
        
    }
}