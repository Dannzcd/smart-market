CC=g++
CFLAGS=-std=c++17 -Wall

INCLUDE=include
SRC=src
OBJ=obj
LFLAGS=-lsqlite3 -pthread
LIBS=libs

OUTPUT=output
PROG=programa

all: criar_pastas main

criar_pastas:
	@mkdir -p ${OBJ} ${OUTPUT}
	@mkdir -p ${OUTPUT}/programa ${OUTPUT}/db

${OBJ}/messagehandler.o: ${INCLUDE}/MessageHandler.hpp ${SRC}/MessageHandler.cpp
	${CC} ${CFLAGS} -c ${SRC}/MessageHandler.cpp -I ${INCLUDE} -o ${OBJ}/messagehandler.o

${OBJ}/funcionario.o: ${INCLUDE}/Funcionario.hpp ${SRC}/Funcionario.cpp 
	${CC} ${CFLAGS} -c ${SRC}/Funcionario.cpp -I ${INCLUDE} -o ${OBJ}/funcionario.o

${OBJ}/filehandler.o: ${INCLUDE}/FileHandler.hpp ${SRC}/FileHandler.cpp
	${CC} ${CFLAGS} -c ${SRC}/FileHandler.cpp -I ${INCLUDE} -o ${OBJ}/filehandler.o

${OBJ}/sqlitehandler.o: ${INCLUDE}/SqliteHandler.hpp ${SRC}/SqliteHandler.cpp
	${CC} ${CFLAGS} -c ${SRC}/SqliteHandler.cpp -I ${INCLUDE} -o ${OBJ}/sqlitehandler.o

${OBJ}/queryhandler.o: ${INCLUDE}/QueryHandler.hpp ${SRC}/QueryHandler.cpp
	${CC} ${CFLAGS} -c ${SRC}/QueryHandler.cpp -I ${INCLUDE} -o ${OBJ}/queryhandler.o

${OBJ}/dir.o: ${INCLUDE}/Dir.hpp ${SRC}/Dir.cpp
	${CC} ${CFLAGS} -c ${SRC}/Dir.cpp -I ${INCLUDE} -o ${OBJ}/dir.o

${OBJ}/cliente.o: ${INCLUDE}/Cliente.hpp ${SRC}/Cliente.cpp
	${CC} ${CFLAGS} -c ${SRC}/Cliente.cpp -I ${INCLUDE} -o ${OBJ}/cliente.o

${OBJ}/clientecivil.o: ${INCLUDE}/ClienteCivil.hpp ${SRC}/ClienteCivil.cpp
	${CC} ${CFLAGS} -c ${SRC}/ClienteCivil.cpp -I ${INCLUDE} -o ${OBJ}/clientecivil.o

${OBJ}/marca.o: ${INCLUDE}/Marca.hpp ${SRC}/Marca.cpp
	${CC} ${CFLAGS} -c ${SRC}/Marca.cpp -I ${INCLUDE} -o ${OBJ}/marca.o

${OBJ}/produto.o: ${INCLUDE}/Produto.hpp ${SRC}/Produto.cpp
	${CC} ${CFLAGS} -c ${SRC}/Produto.cpp -I ${INCLUDE} -o ${OBJ}/produto.o

${OBJ}/main.o: ${INCLUDE}/Funcionario.hpp ${SRC}/main.cpp
	${CC} ${CFLAGS} -c ${SRC}/main.cpp -I ${INCLUDE} -o ${OBJ}/main.o ${LFLAGS}

main: ${OBJ}/main.o \
	${OBJ}/messagehandler.o \
	${OBJ}/funcionario.o \
	${OBJ}/filehandler.o \
	${OBJ}/sqlitehandler.o \
	${OBJ}/queryhandler.o \
	${OBJ}/dir.o \
	${OBJ}/cliente.o \
	${OBJ}/clientecivil.o \
	${OBJ}/marca.o \
	${OBJ}/produto.o

	${CC} ${CFLAGS} ${OBJ}/main.o \
	${OBJ}/messagehandler.o \
	${OBJ}/funcionario.o \
	${OBJ}/filehandler.o \
	${OBJ}/sqlitehandler.o \
	${OBJ}/queryhandler.o \
	${OBJ}/dir.o \
	${OBJ}/cliente.o \
	${OBJ}/clientecivil.o \
	${OBJ}/marca.o \
	${OBJ}/produto.o \
	-I ${INCLUDE} -o ${OUTPUT}/${PROG}/prog ${LFLAGS}

clean:
	rm -r ${OBJ} ${OUTPUT}
