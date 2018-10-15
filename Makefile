CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -std=c++14

RM= /bin/rm -f

all: Project1

index.o: index.cpp index.h
	$(CC) $(CFLAGS) index.cpp -c


shakelookup.o: shakelookup.cpp index.h english_stem.h
	$(CC) $(CFLAGS) shakelookup.cpp -c

Project1: shakelookup.o index.o
	$(CC) $(CFLAGS) shakelookup.o index.o -o Project1

clean:
	rm -f *.o  Project1