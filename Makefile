# Makefile for the Complex Numbers Project

CC = gcc
CFLAGS = -ansi -Wall -pedantic
LDFLAGS = -lm

TARGET = mycomp
OBJS = mycomp.o complex.o commands.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

mycomp.o: mycomp.c complex.h commands.h
	$(CC) $(CFLAGS) -c mycomp.c

complex.o: complex.c complex.h
	$(CC) $(CFLAGS) -c complex.c

commands.o: commands.c complex.h commands.h
	$(CC) $(CFLAGS) -c commands.c

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
