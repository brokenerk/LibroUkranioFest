//Programa para crear registros de votos [celular, CURP, partido, separador], con el campo "celular" como clave 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "Solicitud.h"
#include <sys/time.h>
#include <unistd.h>
#include <iostream> 
#include <fstream>
#include <list> 
#include <thread>  
#include <iterator> 
using namespace std;
int n = 0;
list <int> lista;
list<int>::iterator itr;

struct registro GenerarVoto(int j){
	char telefono[11], curp[19], t[11], sexo;
	int i, destino, opcion, elemento;
	struct registro reg1;
	//Partidos disponibles 2018
	char const partidos[9][4] = {"PRI", "PAN", "PRD", "P_T", "VDE", "MVC", "MOR", "PES", "PNL"};
	//Entidades federativas
	char const entidad[32][3] =  {"AS", "BC", "BS", "CC", "CS", "CH", "CL", "CM", "DF", "DG", "GT", "GR", "HG", "JC", "MC", "MN", "MS", "NT", "NL", "OC", "PL", "QT", "QR", "SP", "SL", "SR", "TC", "TL", "TS", "VZ", "YN", "ZS"};
	//Obtiene un elemento aleatorio de la lista de telefonos y lo elimina de la lista para evitar la repeticion
	i = n - j;
	elemento = rand()%i;		
	itr = lista.begin();
	for(int k = 0; k < elemento; k++)
		++itr;
	elemento = *itr;
	lista.erase(itr);
	sprintf(telefono, "5%9d", elemento);
	strcpy(reg1.celular, telefono);

	if(rand()%2 == 0)
		sexo = 77;
	else
		sexo = 72;
	i = rand()%32;
	sprintf(curp, "%c%c%c%c%c%c%c%c%c%c%c%s%c%c%c%c%c", 65 + rand()%25 , 65 + rand()%25, 65 + rand()%25, 65 + rand()%25, rand()%10 + 48, rand()%10 + 48, rand()%10 + 48, rand()%10 + 48, rand()%10 + 48, rand()%10 + 48, 
	sexo, entidad[i], 65 + rand()%25, 65 + rand()%25, 65 + rand()%25, rand()%10 + 48, rand()%10 + 48);
	strcpy(reg1.CURP, curp);
	i = rand()%9;
	strcpy(reg1.partido, partidos[i]);
	return reg1;
}

void enviar(char* ip, int puerto, struct registro r, Solicitud s){
	timeval res;
	memcpy(&res, s.doOperation(ip, puerto, 1, (char *)&r),sizeof(timeval));
	cout << res.tv_sec << endl;
	cout << res.tv_usec << endl;
}

int main(int argc, char *argv[]){
	if (argc != 8){
		printf("Forma de uso: %s ip_servidorA puertoA ip_servidorB puertoB ip_servidorC puertoC n\n", argv[0]);
		exit(0);
	}
//	srand(time(NULL));

	char* s1Ip = argv[1];
	int s1Port = atoi(argv[2]);

	char* s2Ip = argv[3];
	int s2Port = atoi(argv[4]);

	char* s3Ip = argv[5];
	int s3Port = atoi(argv[6]);

	n = atoi(argv[7]);
	int cont = 0;
	Solicitud s;

/*	//Llena una lista con numeros telefonicos de 9 digitos secuenciales creibles
	int inicial = 500000000 + rand()%100000000;
	for (int i = inicial; i < inicial + n; i++) { 
		lista.push_back(i);
	}
*/
	string line;
	std::ifstream infile("registroCliente.txt");
	struct registro reg;
	char tel[11], cp[19],par[4];
	while(cont < n) {
		getline(infile, line);
		char *cstr = new char[line.length() + 1];
		strcpy(cstr, line.c_str());
		string str(cstr);
		strcpy(reg.celular, str.substr(0,10).c_str());
		strcpy(reg.CURP, str.substr(10,18).c_str());
		strcpy(reg.partido, str.substr(28,4).c_str());
	
		string lastc = string(reg.celular);
		lastc = lastc.back();
		int lastN = atoi(lastc.c_str());

		if(0 <= lastN and lastN <= 3){
			enviar(s1Ip, s1Port, reg, s);
			//thread t(enviar, s1Ip, s1Port, r);
			//t.detach();
		}
		else if(4 <= lastN and lastN <= 6){
			enviar(s2Ip, s2Port, reg, s);
			//thread t(enviar, s2Ip, s2Port, r);
			//t.detach();
		}
		else if(7 <= lastN and lastN <= 9){
			enviar(s3Ip, s3Port, reg, s);
			//thread t(enviar, s3Ip, s3Port, r);
			//t.detach();
		}
		cont++;
	}
	return 0;
}