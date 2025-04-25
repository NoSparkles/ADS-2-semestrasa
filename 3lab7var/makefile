build.exe : main.c queue.h clinic.h clinic.o queue.o
	gcc -std=c99 -o build main.c clinic.o queue.o -lm

clinic.o : clinic.c clinic.h queue.h
	gcc -std=c99 -c clinic.c

queue.o : queue.c queue.h
	gcc -std=c99 -c queue.c