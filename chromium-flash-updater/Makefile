CC=g++
CFLAGS=-c -std=c++11 
LFLAGS=-std=c++11

all: main.o read_tarfile.o 
	$(CC) $(LFLAGS) -g -o test main.o read_tarfile.o -larchive 

main.o: main.cpp json.hpp
	$(CC) $(CFLAGS) -g main.cpp -larchive
	
read_tarfile.o: read_tarfile.cpp read_tarfile.h
	$(CC) $(CFLAGS) -g read_tarfile.cpp -larchive
clean:
	rm *.o test manifest.json libpepflashplayer.so