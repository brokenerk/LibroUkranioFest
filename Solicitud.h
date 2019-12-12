#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include "mensaje.h"
class Solicitud{
	public:
		Solicitud();
		int doOperation(char *IP, int puerto, int operationId, char *arguments, int tam, int wordTimes);
	private:
		SocketDatagrama *socketlocal;
};