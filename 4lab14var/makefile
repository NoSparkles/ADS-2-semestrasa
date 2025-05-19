main.exe: main.c graph.o
	gcc -o main main.c graph.o

graph.o: graph.c graph.h
	gcc -c graph.c

clean:
	rm -f main graph.o