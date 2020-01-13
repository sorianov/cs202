# sample makefile showing dependency lists

PROG = stringTest
CC = g++
FLAGS = -m32 -Wall -g
OBJS = mystring.o

stringTest: mystring.o
	$(CC) $(FLAGS) -o $(PROG) $(OBJS)

mystring.o: mystring.cpp mystring.h
	$(CC) $(FLAGS) -c mystring.cpp

clean:
	rm $(PROG) $(OBJS) 

