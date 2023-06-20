.PHONY = all clean

PROJECT = demo

BUILD_DIR = build

LOGGER_DIR = ../

SRCS = $(wildcard *.c)

HDRS =

OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)

DIRS =  $(dir $(BUILD_DIR) $(OBJS))

CC = gcc
CFLAGS = -std=c89 -Wall -I$(LOGGER_DIR)

$(BUILD_DIR)/%.c.o:%.c
	@mkdir -p $(DIRS)
	${CC} $(CFLAGS) -c -o $@ $<

all:$(PROJECT)
	@echo Build complete

$(PROJECT):$(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -r -f ${PROJECT} ${BUILD_DIR}

