#include "mapCreator.h"
#include "Respuesta.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]){
	mapCreator a;
    map<string,int> rae=a.getMapFromFile("./rae.txt");

    Respuesta resp(5000);

    while (true) {
        struct mensaje *msj = resp.getRequest();
        if(msj != NULL) {
            cout << "Recibido" << endl;
        	struct registro r;
            memcpy(&r, &msj->arguments, sizeof(registro));

            cout << r.cadenota << endl;
            resp.sendReply("OK");
        }
    }
}