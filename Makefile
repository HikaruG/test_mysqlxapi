test: test.o
		g++ -o test test.o

test.o: test.cpp test.h
		g++ -o test.o test.cpp 
