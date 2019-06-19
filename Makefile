MAKE = make -r
CC = gcc -W -Wall

font:font.c font.h
	$(CC) -c font.c
	ar -r mylib.a font.o

sample:sample.c
	$(CC) -o sample sample.c mylib.a

run:
	$(MAKE) font
	$(MAKE) sample
	./sample

clean:
	rm ./*.o *.a sample
