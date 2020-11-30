all : main.o
	gcc -o prog main.o
main.o: main.c
	gcc -c main.c

.PHONY: clean run 
clean: 
	-rm *.o *.txt
run: prog
	./prog