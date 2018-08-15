MAKE = make -r
CC = gcc -W -Wall

font:font.c font.h
	$(CC) -o font font.c

run:
	$(MAKE) font
	./font

clean:
	rm ./font
