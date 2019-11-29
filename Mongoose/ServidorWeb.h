#ifndef SERVIDORWEB_H_
#define SERVIDORWEB_H_
#define MG_ENABLE_HTTP_STREAMING_MULTIPART true
#include "mongoose.h"
#include <iostream>
using namespace std;

class ServidorWeb{
	public:
		ServidorWeb(char* directorio, char* pto);
		void escuchar();
	private:
		static void manejarEvento(struct mg_connection *nc, int ev, void *p);
		static void imprimirResultados(struct mg_connection *nc);
		struct mg_mgr mgr;
		struct mg_connection* nc;
		const char* port;
};
#endif