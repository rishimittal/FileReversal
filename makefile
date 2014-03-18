all : reverse_tool

reverse_tool : main_reverse.o fileReversal.o
	       gcc -o reverse_tool main_reverse.o fileReversal.o

main_reverse.o : main_reverse.c OS_HEADER.h
		 gcc -c main_reverse.c

fileReversal.o : fileReversal.c OS_HEADER.h
		 gcc -c fileReversal.c

clean : 
		rm -rf *.o 
