CC = g++
CFLAGS = -Wall -L/usr/local/lib

all: main.cpp
#	(sh -c "cd Release; make; cp checkers ../")
	$(CC) $(CFLAGS) -o checkers main.cpp

clean:
	rm checkers
