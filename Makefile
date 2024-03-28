CC=gcc

all: bitvector floatvector test

bitvector:	
	${CC} -Wall bitvector.c -lm -o bitvector
	
floatvector:	
	${CC} -Wall floatvector.c -lm -o floatvector

test:  
	./floatvector 
	./bitvector
	rm floatvector
	rm bitvector
