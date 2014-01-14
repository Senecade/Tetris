all:
	gcc -std=gnu99 -pthread -Wall -g -o main main.c interface.c move.c functions.c struct.c -lglut -lGLU -lGL -lm `pkg-config --cflags --libs ftgl freetype2`
