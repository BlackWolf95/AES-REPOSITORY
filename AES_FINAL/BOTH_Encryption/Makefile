all: ByteSubSR

ByteSubSR: main2.o
	gcc -o ByteSubSR main2.o

main2.o: main2.c
	gcc -c -O0  main2.c -Wall -pedantic -std=c99

clean:
	rm -f main2.o ByteSubSR
