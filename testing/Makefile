UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	CC ?= gcc-14
else
	CC ?= gcc
endif

CFLAGS := -Wall -Wextra -O0 -g -MMD -MP
TESTFLAGS := -fprofile-arcs -ftest-coverage

SRCS := test.c counter.c
OBJS := $(SRCS:.c=.o) # replaces .c with .o in SRCS, test.c -> test.o
TARGET := test

.PHONY: all clean

all: $(TARGET)

main: main.c counter.c
	$(CC) $(CFLAGS) -o main main.c counter.c
	./main

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(TESTFLAGS) -o $@ $^

$(TARGET)-run: $(TARGET)
	./$(TARGET)

$(TARGET)-run-cov: $(TARGET)
	./$(TARGET)
	gcov -c -p counter 

# TODO: update gcov command with test-counter when gcc is installed on laptop.

%.o: %.c
	$(CC) $(CFLAGS) $(TESTFLAGS) -c $< -o $@

-include $(OBJS:.o=.d)

clean:
	rm -f $(OBJS) $(TARGET) *.d *.gcno *.gcda

