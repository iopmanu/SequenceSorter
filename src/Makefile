.PHONY: clean

CC=g++
FLAGS=-Wall -Wextra -Werror 	
BUILD=../build/

main: main.o
	$(CC) $(FLAGS) -o $(BUILD)program main.o 

main.o: main.cpp clocking.hpp ArraySequence.hpp Sequence.hpp ListSequence.hpp Isorter.hpp testing.hpp
	$(CC) $(FLAGS) -c main.cpp


clean:
	rm -Rfv *.o *.gch *.out $(BUILD)program
