CXX=gcc
CFLAGS=-std=c99 -Wall
TESTFLAGS=-fprofile-arcs -ftest-coverage

main:
	$(CXX) $(CFLAGS) -v -o main main.c counter.c

test: test.c counter.h counter.c
	$(CXX) $(CFLAGS) $(TESTFLAGS) -v -o test test.c counter.c
	./test

coverage:
	gcov -c -p counter

clean:
	rm -f *.o test *.gcov *.gcda *.gcno main