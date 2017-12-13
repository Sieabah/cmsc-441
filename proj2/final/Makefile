77;20003;0cOBJS =  main.o

main: $(OBJS)
	g++ -o main main.cpp -fopenmp


default: clean main.o run


main.o: main.cpp
	g++ -o main main.cpp -fopenmp

run:
	./main

test:
	./main test1.txt 5 test2.txt 5

testbig:
	./main test1.txt 1000 test2.txt 1000

testvbig:
	./main test1.txt 10000 test2.txt 10000

clean:
	rm main