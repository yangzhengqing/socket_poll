
SRCS= poll_test.c
PROG= poll_test
CC=gcc
CFLAGS=-g
OBJS=$(SRCS:.c=.o)
$(PROG):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
$(OBJS):poll_test.h
clean:
	rm -rf $(OBJS)
