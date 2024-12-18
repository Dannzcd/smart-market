CC=g++
CFLAGS=-std=c++17 -Wall

INCLUDE=include
SRC=src
OBJ=obj
OUTPUT=output
LFLAGS=-lsqlite3
LIBS=libs

all: main

${OBJ}/messagehandler.o: include/MessageHandler.hpp src/MessageHandler.cpp
	${CC} ${CFLAGS} -c src/MessageHandler.cpp -I include -o ${OBJ}/messagehandler.o

${OBJ}/funcionario.o: include/Funcionario.hpp src/Funcionario.cpp 
	${CC} ${CFLAGS} -c src/Funcionario.cpp -I include -o ${OBJ}/funcionario.o

${OBJ}/filehandler.o: include/FileHandler.hpp src/FileHandler.cpp
	${CC} ${CFLAGS} -c src/FileHandler.cpp -I include -o ${OBJ}/filehandler.o

${OBJ}/sqlitehandler.o: include/SqliteHandler.hpp src/SqliteHandler.cpp
	${CC} ${CFLAGS} -c src/SqliteHandler.cpp -I include -o ${OBJ}/sqlitehandler.o

${OBJ}/main.o: include/Funcionario.hpp src/main.cpp
	${CC} ${CFLAGS} -c src/main.cpp -I include -o ${OBJ}/main.o ${LFLAGS}


main: ${OBJ}/main.o ${OBJ}/messagehandler.o ${OBJ}/funcionario.o ${OBJ}/filehandler.o ${OBJ}/sqlitehandler.o
	${CC} ${CFLAGS} ${OBJ}/main.o ${OBJ}/messagehandler.o ${OBJ}/funcionario.o ${OBJ}/filehandler.o ${OBJ}/sqlitehandler.o -I include -o ${OUTPUT}/prog ${LFLAGS}

clean:
	rm -f main ${OBJ}/*.o