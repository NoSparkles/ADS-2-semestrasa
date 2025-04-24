run: build
	echo 0.3 > params.txt
	echo 10000 >> params.txt
	echo 1 >> params.txt
	echo 3 >> params.txt
	echo 15 >> params.txt
	echo 1 >> params.txt
	echo 3 >> params.txt
	echo 5 >> params.txt
	echo 7 >> params.txt
	./build params.txt

build : main.c clinic.o queue.o
	gcc -std=c99 -o build main.c clinic.o queue.o
   
clinic.o : clinic.c clinic.h
	gcc -c -std=c99 clinic.c

queue.o : queue.c queue.h
	gcc -c -std=c99 queue.c

clean : 
	rm -f build *.o