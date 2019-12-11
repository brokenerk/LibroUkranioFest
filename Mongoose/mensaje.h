#define TAM_MAX_DATA 65000
//Definicion de identificadores para operaciones permitidas
#define suma 1
// Definicion del formato de mensaje
struct mensaje{
	int messageType; //0= Solicitud, 1 = Respuesta
	unsigned int requestId; //Identificador del mensaje
	int operationId; //Identificador de la operación
	int tam; //Tamaño arguments
	int wordTimes; //Numero de veces que aparece la palabra
	char arguments[TAM_MAX_DATA];
};