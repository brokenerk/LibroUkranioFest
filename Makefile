run: cliente-web.cpp servidor.cpp MapCreator.o Respuesta.o Solicitud.o SocketDatagrama.o PaqueteDatagrama.o
	g++ -DMG_ENABLE_HTTP_STREAMING_MULTIPART cliente-web.cpp mongoose.c MapCreator.o Solicitud.o SocketDatagrama.o PaqueteDatagrama.o -w -o cliente-web
	g++ servidor.cpp MapCreator.o Respuesta.o SocketDatagrama.o PaqueteDatagrama.o -w -o servidor

MapCreator.o: MapCreator.cpp MapCreator.h
	g++ MapCreator.cpp -c

Solicitud.o: Solicitud.cpp SocketDatagrama.o PaqueteDatagrama.o Solicitud.h
	g++ Solicitud.cpp -c  	

Respuesta.o: Respuesta.cpp SocketDatagrama.o PaqueteDatagrama.o Respuesta.h
	g++ Respuesta.cpp -c  	

SocketDatagrama.o: SocketDatagrama.cpp PaqueteDatagrama.o SocketDatagrama.h
	g++ SocketDatagrama.cpp -c 

PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c 

clean:
	rm -r *.o