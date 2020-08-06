test: main.o ImageRead.o BMPreading.o
	g++ -o test main.o ImageRead.o BMPreading.o
main.o: main.cpp
	g++ -c main.cpp
ImageRead.o: ImageRead.cpp
	g++ -c ImageRead.cpp
BMPreading.o: BMPreading.cpp
	g++ -c BMPreading.cpp
all: test
clean:
	rm -f *.o test

