all:
	c99 -Wall -o main main.c interface.c move.c functions.c -lglut -lGLU -lGL
