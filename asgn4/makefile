# sample makefile showing dependency lists

PROG = quiz3
CC = g++
FLAGS = -Wall -g
OBJS = QuestionSA.o QuestionMC.o QuestionTF.o Question.o Quiz.o main.o

quiz: $(OBJS)
	$(CC) $(FLAGS) -o $(PROG) $(OBJS)

main.o: Question.o Quiz.o main.cpp
	$(CC) $(FLAGS) -c main.cpp

Question.o: Question.cpp Question.h
	$(CC) $(FLAGS) -c Question.cpp

QuestionTF.o: QuestionTF.h QuestionTF.cpp Question.o
	$(CC) $(FLAGS) -c QuestionTF.cpp

QuestionMC.o: QuestionMC.h QuestionMC.cpp Question.o
	$(CC) $(FLAGS) -c QuestionMC.cpp

QuestionSA.o: QuestionSA.h QuestionSA.cpp Question.o
	$(CC) $(FLAGS) -c QuestionSA.cpp

Quiz.o: Quiz.cpp Quiz.h
	$(CC) $(FLAGS) -c Quiz.cpp

clean:
	rm $(PROG) $(OBJS)

