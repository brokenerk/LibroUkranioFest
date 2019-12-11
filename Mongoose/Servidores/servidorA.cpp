#include "Respuesta.h"
#include "MapCreator.h"
#include <cstring>
#include <iostream>
using namespace std;
int main()
{
    MapCreator m;
    map<string, int> rae = m.getMapFromFile("rae.txt");
    map<string, int> palabras;
    Respuesta resp(7200);
    cout << "Servidor A iniciado....\n";
    int nbd = 0;
    while (true) {
        struct mensaje *msj = resp.getRequest();
        
        if(msj != NULL) {
            int tam = 0;
            memcpy(&tam, &msj->tam, 4);

            int wordTimes = 0;
            memcpy(&wordTimes, &msj->wordTimes, 4);

        	char* rec = (char*)calloc(tam, sizeof(char));
	        memcpy(rec, msj->arguments, tam);

            if(strcmp(rec, "FIN") == 0) {
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
                resp.sendReply((char*)&error, sizeof(int));
            }
            else {
                palabras.insert(pair<string, int>(rec, wordTimes));
                resp.sendReply("OK", 2);
            }
            delete [] rec;
            //cout << "Enviando respuesta" << endl;
        }
        
    }
}