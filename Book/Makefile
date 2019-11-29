run: prueba.cpp Solicitud.o SocketDatagrama.o PaqueteDatagrama.o Respuesta.o
	g++ FileOpener.cpp mapCreator.cpp prueba.cpp Solicitud.o SocketDatagrama.o PaqueteDatagrama.o -o prueba
	g++ FileOpener.cpp mapCreator.cpp servidor.cpp Respuesta.o SocketDatagrama.o PaqueteDatagrama.o -o servidor

Respuesta.o: Respuesta.cpp SocketDatagrama.o PaqueteDatagrama.o Respuesta.h
	g++ Respuesta.cpp -c 	
	
Solicitud.o: Solicitud.cpp SocketDatagrama.o PaqueteDatagrama.o Solicitud.h
	g++ Solicitud.cpp -c 	

SocketDatagrama.o: SocketDatagrama.cpp PaqueteDatagrama.o SocketDatagrama.h
	g++ SocketDatagrama.cpp -c 

PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c

clean:
	rm *.o