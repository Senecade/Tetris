all:
	c99 -pthread -Wall -o main main.c interface.c move.c functions.c struct.c -lglut -lGLU -lGL
