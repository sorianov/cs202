# sample makefile showing dependency lists

PROG = quiz
CC = g++
FLAGS = -m32 -Wall -g
OBJS = Question.o Quiz.o main.o

quiz: $(OBJS)
	$(CC) $(FLAGS) -o $(PROG) $(OBJS)

main.o: Question.o Quiz.o main.cpp
	$(CC) $(FLAGS) -c main.cpp

Question.o: Question.cpp Question.h
	$(CC) $(FLAGS) -c Question.cpp

Quiz.o: Quiz.cpp Quiz.h
	$(CC) $(FLAGS) -c Quiz.cpp

clean:
	rm $(PROG) $(OBJS)

