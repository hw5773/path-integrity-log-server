CC=gcc
RM=rm

BIN=log_server
SRC_DIRECTORY=log-server
SRCS := $(wildcard $(SRC_DIRECTORY)/*.c)
OBJS := $(SRCS:.c=.o)

default: all

all: $(OBJS)
	echo $(SRCS)
	echo $(OBJS)
	$(MAKE) -C $(SRC_DIRECTORY)
	$(CC) -o $(BIN) $^

clean:
	!(test -f $(BIN)) || $(RM) $(BIN)
	$(RM) $(OBJS)

