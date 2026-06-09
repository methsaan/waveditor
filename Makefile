all: waveditor clean

waveditor.o: waveditor.c
	gcc -c waveditor.c

waveditor: waveditor.o
	gcc -o waveditor waveditor.o

.PHONY: clean

clean:
	rm waveditor.o
