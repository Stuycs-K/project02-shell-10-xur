.PHONY: clean run compile
compile shell: main.o execute.o
	@gcc -o shell main.o execute.o
main.o: main.c 
	@gcc -c main.c
execute.o: execute.c
	@gcc -c execute.c
run: shell
	@./shell
clean:
	rm -f *.o shell