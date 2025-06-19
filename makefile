CC=gcc
CFLAGS=-Wall -Wpedantic -lrt -lpthread -pthread
INC=-iquote ./include/
SRC=./src
OBJDIR=./obj/
LIB=./lib/
LDFLAGS=-lm

CFILES=$(wildcard $(LIB)*.c)

OBJFILES=$(patsubst $(LIB)%,$(OBJDIR)%,$(patsubst %.c,%.o,$(CFILES)))

./src/main: ./src/main.c $(OBJFILES)
	$(CC) $(INC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)%.o: $(LIB)%.c
	$(CC) $(INC) $(CFLAGS) -c -o $@ $^

.PHONY: clean exec

clean:
	-rm -f $(OBJDIR)*.o

exec:
	make
	./src/main
