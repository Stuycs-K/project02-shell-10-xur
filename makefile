.PHONY: clean run compile
compile shell: main.o execute.o redirin.o redirout.o pipe.o
	@gcc -o shell main.o execute.o redirin.o redirout.o pipe.o
main.o: main.c 
	@gcc -c main.c
execute.o: execute.c
	@gcc -c execute.c
redirin.o: redirin.c
	@gcc -c redirin.c
redirout.o: redirout.c
	@gcc -c redirout.c
pipe.o: pipe.c
	@gcc -c pipe.c
run: shell
	@./shell
clean:
	rm -f *.o shell