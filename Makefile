#
#  Makefile
#  Copyright © 2020-2021 Andrei Pascu. All rights reserved.
#

CC = gcc
CFLAGS = -std=c99 -g3 -Wall -pedantic
BIN = ./bin
SRC = ./src
INCLUDE = ./include
OBJ = ./src

all:	${BIN}/lzw20 ${BIN}/lzw20.encode ${BIN}/lzw20.decode

${BIN}/lzw20:	${OBJ}/main.o
	${CC} ${CFLAGS} $^ -o $@

${BIN}/lzw20.encode:	${OBJ}/lzw.o ${OBJ}/code.o ${OBJ}/table.o
	${CC} ${CFLAGS} $^ -o $@

${BIN}/lzw20.decode:	${BIN}/lzw20.encode
	ln $^ $@

${OBJ}/main.o:	${INCLUDE}/lzw.h

${OBJ}/lzw.o:	${INCLUDE}/lzw.h

${OBJ}/code.o:	${INCLUDE}/code.h

${OBJ}/table.o:	${INCLUDE}/table.h

clean:
	rm -f ${BIN}/lzw20 ${BIN}/lzw20.encode ${BIN}/lzw20.decode ${OBJ}/*.o
