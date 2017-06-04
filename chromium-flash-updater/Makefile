CC=g++
CFLAGS=-c -std=c++11 
LFLAGS=-std=c++11

all: main.o read_tarfile.o 
	$(CC) $(LFLAGS) -o flash-upgrade main.o read_tarfile.o -larchive -lstdc++fs

main.o: main.cpp json.hpp
	$(CC) $(CFLAGS) main.cpp -larchive -lstdc++fs
	
read_tarfile.o: read_tarfile.cpp read_tarfile.h
	$(CC) $(CFLAGS) read_tarfile.cpp -larchive 
clean:
	rm *.o flash-upgrade