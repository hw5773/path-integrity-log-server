CC=gcc
RM=rm

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

default: all

all: $(OBJS)

%.o: %.c
	$(CC) -c $^

clean:
	$(RM) $(OBJS)

