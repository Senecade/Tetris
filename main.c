#include <GL/glut.h>
#include "interface.h"
/*
#include "functions.h"
#include "move.h"
*/
#include <stdio.h>

enum{
    WINDOW_HEIGHT = 600,
    WINDOW_WIDTH = 300
};
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    glutInitWindowPosition(600,200);
    glutCreateWindow("Tetris");
    glutDisplayFunc(updateWindow);
    glutMainLoop();
    return 0;
}
