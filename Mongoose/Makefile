run: pc_central.cpp ServidorWeb.o
	g++ pc_central.cpp mongoose.c ServidorWeb.o -w -o pc_central

ServidorWeb.o: ServidorWeb.cpp ServidorWeb.h mongoose.o
	g++ ServidorWeb.cpp -c 	

clean:
	rm -r *.o