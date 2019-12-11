#include "Respuesta.h"
#include <cstring>
#include <iostream>
using namespace std;
int main()
{
    Respuesta resp(7200);
    cout << "Servidor iniciado....\n";
    int nbd = 0;
    while (true) {
        struct mensaje *msj = resp.getRequest();
        
        if(msj != NULL) {
            int tam = 0;
            memcpy(&tam, &msj->tam, 4);
        	char* rec = new char[tam];
	        memcpy(rec, msj->arguments, tam);
            cout << "Recibido" << endl;
	        cout << rec << endl;
	        resp.sendReply("OK");
            cout << "Enviando OK" << endl;
        }
        
    }
}