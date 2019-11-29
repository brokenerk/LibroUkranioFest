#include "ServidorWeb.h"
#include <unistd.h>
#include <iostream>
using namespace std;

void servidorWeb() {
	ServidorWeb web(".", "8000");
	//web.inicializaDatos((char*)ip1.c_str(), ult1, segs);
	web.escuchar();
}

int main(int argc, char* argv[]) {
	servidorWeb();
	return 0;
}