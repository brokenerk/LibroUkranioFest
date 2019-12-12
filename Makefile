run: web.cpp MapCreator.o Solicitud.o SocketDatagrama.o PaqueteDatagrama.o
	g++ -DMG_ENABLE_HTTP_STREAMING_MULTIPART web.cpp mongoose.c MapCreator.o Solicitud.o SocketDatagrama.o PaqueteDatagrama.o -w -o web

MapCreator.o: MapCreator.cpp MapCreator.h
	g++ MapCreator.cpp -c

Solicitud.o: Solicitud.cpp SocketDatagrama.o PaqueteDatagrama.o Solicitud.h
	g++ Solicitud.cpp -c  	
	
SocketDatagrama.o: SocketDatagrama.cpp PaqueteDatagrama.o SocketDatagrama.h
	g++ SocketDatagrama.cpp -c 

PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c 

clean:
	rm -r *.o