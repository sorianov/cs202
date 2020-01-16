# sample makefile showing dependency lists

PROG = stringTest
CC = g++
FLAGS = -m32 -Wall -g
OBJS = mystring.o main.o

stringTest: mystring.o main.o
	$(CC) $(FLAGS) -o $(PROG) $(OBJS)

main.o: main.cpp mystring.o
	$(CC) $(FLAGS) -c main.cpp

mystring.o: mystring.cpp mystring.h
	$(CC) $(FLAGS) -c mystring.cpp

clean:
	rm $(PROG) $(OBJS)

