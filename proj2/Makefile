OBJS =  main.o

main: $(OBJS)
	g++ -o main $(OBJS)

default: main.o run clean

main.o: main.cpp
	g++ -c main.cpp -I../common

run:
	./main

test:
	./main test1.txt 1000 test2.txt 1000

clean:
	rm *.o
