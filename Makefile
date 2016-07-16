CFLAGS := -Wall -O2

bf_interpreter: main.o
	g++ -o bf_interpreter main.o

clean:
	$(RM) *.o
	$(RM) bf_interpreter

