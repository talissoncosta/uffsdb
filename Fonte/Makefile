all: prog

prog: *.c interface/*.c interface/*.h
	gcc *.c interface/*.c -lfl -pthread -o Ibetres -Wall -g

clean:
	rm Ibetres
	rm data/ -R
