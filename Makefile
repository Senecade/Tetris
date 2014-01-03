all:
	gcc -Wall -o main main.c interface.c functions.c move.c -lglut -lGLU -lGL
