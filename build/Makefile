.PHONY = all build example clean

CC = gcc
CFLAGS = -std=c89 -Wall

PROJECT_NAME := logger
LIB_NAME := liblogger.a

SRCS := $(wildcard ../src/*.c)
HDRS := $(wildcard ../src/*h)
OBJS := $(SRCS:../src/%.c=%.o)

EXAMPLE_SRCS := $(wildcard ../example/*.c)

INC_PATH := -I/usr/local/include
LIB_PATH := -L/usr/local/lib

all:
	${CC} ${CFLAGS} ${INC_PATH} ${LIB_PATH} ${SRCS} -o ${PROJECT_NAME}

build: lib
	mkdir ../lib
	mv ${LIB_NAME} ../lib
	mkdir ../lib/includes
	cp -p ${HDRS} ../lib/includes

lib: obj
	ar rc ${LIB_NAME} ${OBJS} 
	ranlib ${LIB_NAME}

obj:
	${CC} ${CFLAGS} -c ${SRCS}

example:
	${CC} ${CFLAGS} -g ${INC_PATH} ${LIB_PATH} ${SRCS} ${EXAMPLE_SRCS} -o ${PROJECT_NAME}

clean:
	rm -r -f ${PROJECT_NAME} *.o *.a
	rm -r -f ../lib
