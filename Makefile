
CC=clang
CFLAGS=-Wall -g
BINS=staticFindFile

all: VSPr FindFile.a

Semaphore.o: Semaphore.cpp Semaphore.h
	$(CC) $(CFLAGS) -c Semaphore.cpp

FindFile.o: FindFile.cpp FindFile.h
	$(CC) $(CFLAGS) -c FindFile.cpp

VSPr: main.cpp Semaphore.o FindFile.o
	$(CC) $(CFLAGS) -o $@ $^

FindFile.a: Semaphore.o FindFile.o
	ar rcs $@ $^

staticFindFile: Semaphore.cpp FindFile.cpp
	$(CC) $(CFLAGS) -o $@ $^ -L. -lFindFile

clean:
	rm -f VSPr *.o *.a $(BINS)