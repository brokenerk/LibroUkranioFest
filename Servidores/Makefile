run: servidorA.cpp servidorB.cpp servidorC.cpp servidorD.cpp MapCreator.o Respuesta.o SocketDatagrama.o PaqueteDatagrama.o
	g++ servidorA.cpp MapCreator.o Respuesta.o SocketDatagrama.o PaqueteDatagrama.o -w -o servidorA
	g++ servidorB.cpp MapCreator.o Respuesta.o SocketDatagrama.o PaqueteDatagrama.o -w -o servidorB
	g++ servidorC.cpp MapCreator.o Respuesta.o SocketDatagrama.o PaqueteDatagrama.o -w -o servidorC
	g++ servidorD.cpp MapCreator.o Respuesta.o SocketDatagrama.o PaqueteDatagrama.o -w -o servidorD

MapCreator.o: MapCreator.cpp MapCreator.h
	g++ MapCreator.cpp -c

Respuesta.o: Respuesta.cpp SocketDatagrama.o PaqueteDatagrama.o Respuesta.h
	g++ Respuesta.cpp -c  	
	
SocketDatagrama.o: SocketDatagrama.cpp PaqueteDatagrama.o SocketDatagrama.h
	g++ SocketDatagrama.cpp -c 

PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c 

clean:
	rm -r *.o