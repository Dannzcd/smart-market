CC=g++
CFLAGS=-std=c++17 -Wall

INCLUDE=include
SRC=src
OUTPUT=output

all: main



${OUTPUT}/funcionario.o: include/Funcionario.hpp src/Funcionario.cpp 
	${CC} ${CFLAGS} -c src/Funcionario.cpp -I include -o ${OUTPUT}/funcionario.o


${OUTPUT}/main.o: include/Funcionario.hpp src/main.cpp
	${CC} ${CFLAGS} -c src/main.cpp -I include -o ${OUTPUT}/main.o


main: ${OUTPUT}/main.o ${OUTPUT}/funcionario.o
	${CC} ${CFLAGS} ${OUTPUT}/main.o ${OUTPUT}/funcionario.o -I include -o prog

clean:
	rm -f main ${OUTPUT}/*.o