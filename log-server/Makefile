CC=gcc
RM=rm

BIN=log_server
SRCS=log_server.o
OBJS=log_server.o


default: all

all: $(OBJS)
	$(CC) -o $(BIN) $^

.c.o: $(SRCS)
	$(CC) -c $^

clean:
	$(RM) $(BIN) $(OBJS)

