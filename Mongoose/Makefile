run: pc_central.cpp ServidorWeb.o
	g++ -DMG_ENABLE_HTTP_STREAMING_MULTIPART pc_central.cpp ServidorWeb.o mongoose.c -w -o pc_central

ServidorWeb.o: ServidorWeb.cpp ServidorWeb.h
	g++ ServidorWeb.cpp -w -c

clean:
	rm -r *.o