run: build
	echo 0.3 > params.txt
	echo 100 >> params.txt
	echo 15 >> params.txt
	echo 5 >> params.txt
	echo 15 >> params.txt
	echo 3 >> params.txt
	echo 5 >> params.txt
	echo 5 >> params.txt
	echo 10 >> params.txt
	./build params.txt > result1.txt

build : main.c clinic.o longNum.o queue.o
	gcc -std=c99 -o build main.c clinic.o longNum.o queue.o
   
clinic.o : clinic.c clinic.h
	gcc -c -std=c99 clinic.c

longNum.o : longNum.c longNum.h
	gcc -c -std=c99 longNum.c

queue.o : queue.c queue.h
	gcc -c -std=c99 queue.c

clean : 
	rm -f build *.o