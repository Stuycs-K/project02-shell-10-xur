.PHONY: clean run compile
compile shell: main.o execute.o redirin.o
	@gcc -o shell main.o execute.o redirin.o
main.o: main.c 
	@gcc -c main.c
execute.o: execute.c
	@gcc -c execute.c
redirin.o: redirin.c
	@gcc -c redirin.c
run: shell
	@./shell
clean:
	rm -f *.o shell