CC=gcc
CFLAGS= -g -std=c99 -pedantic -Werror -Wall -Wextra
LDFLAGS= -lcriterion

main: src/main.o src/my_fnmatch.o
	$(CC) -o fnmatch $^ -g

check: src/my_fnmatch.o tests/tests.o
	$(CC) -o fnmatch $^ $(LDFLAGS) -g
	./fnmatch

library: src/my_fnmatch.o
	ar csr libfnmatch.a $^

clean:
	$(RM) *.o src/*.o tests/*.o fnmatch *.a .__a*
