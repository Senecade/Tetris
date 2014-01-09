#include <GL/glut.h>
#include "functions.h"
#include "struct.h"
#include "globalshit.h"
#include <stdio.h>
#include <SDL/SDL.h>

enum{
    WINDOW_HEIGHT = 600,
    WINDOW_WIDTH = 300
};
void drawBlock(int x, int y, int R, int G, int B, int blocktype){
	float ox1,oy1,ox2,oy2;
	ox1 = -1 + x / 5.0 + 3.0 / WINDOW_WIDTH;
	oy1 = 1 - (y-2)/ 10.0 - 3.0 / WINDOW_HEIGHT;
	ox2 = ox1 + 1 / 5.0 - 3.0 / WINDOW_WIDTH;
	oy2 = oy1 - 1 / 10.0 + 3.0 / WINDOW_HEIGHT;
	if (blocktype == SHADOW_INT) {
		glColor3ub(R,G,B);
		glRectf(ox1,oy1,ox2,oy2);
	}
	else {
		float ix1,iy1,ix2,iy2;
		ix1 = ox1 + 12.0 / WINDOW_WIDTH;
		iy1 = oy1 - 12.0 / WINDOW_HEIGHT;
		ix2 = ox2 - 12.0 / WINDOW_WIDTH;
		iy2 = oy2 + 12.0 / WINDOW_HEIGHT;
		glColor3ub((unsigned char) R, (unsigned char) G, (unsigned char) B);
		glBegin(GL_QUADS);
			glVertex2f(ox1,oy1);
			glVertex2f(ox2,oy1);
			glVertex2f(ix2,iy1);
			glVertex2f(ix1,iy1);
		glEnd();
		glColor3ub((unsigned char) ((double) 0.7 * R), (unsigned char) ((double) 0.7 * G), (unsigned char) ((double) 0.7 * B));
		glBegin(GL_QUADS);
			glVertex2f(ox2,oy1);
			glVertex2f(ox2,oy2);
			glVertex2f(ix2,iy2);
			glVertex2f(ix2,iy1);
		glEnd();
		glColor3ub((unsigned char) ((double) 0.6 * R), (unsigned char) ((double) 0.6 * G), (unsigned char) ((double) 0.6 * B));
		glBegin(GL_QUADS);
			glVertex2f(ox2,oy2);
			glVertex2f(ox1,oy2);
			glVertex2f(ix1,iy2);
			glVertex2f(ix2,iy2);
		glEnd();
		glColor3ub((unsigned char) ((double) 0.9 * R), (unsigned char) ((double) 0.9 * G), (unsigned char) ((double) 0.9 * B));
		glBegin(GL_QUADS);
			glVertex2f(ox1,oy2);
			glVertex2f(ox1,oy1);
			glVertex2f(ix1,iy1);
			glVertex2f(ix1,iy2);
		glEnd();
		glColor3ub((unsigned char) ((double) 0.8 * R), (unsigned char) ((double) 0.8 * G), (unsigned char) ((double) 0.8 * B));
		glRectf(ix1,iy1,ix2,iy2);
	}
}
void updateWindow(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
    int R,G,B;
    for(int y = 2; y<22;y++){
        for(int x = 0;x<10;x++){
            if(FIELD_RGB(x,y,R,G,B))drawBlock(x,y,R,G,B,FIELD_INT);
        }
    }
    BLOX_RGB(R,G,B);
    for(int i = 0; i<4;i++){
	if (ActiveBlox.shadow_offset > 0) drawBlock(ActiveBlox.x+ActiveBlox.Blox.points[i][X],ActiveBlox.y+ActiveBlox.Blox.points[i][Y]+ActiveBlox.shadow_offset,130,130,130,SHADOW_INT);
    }
    for(int i = 0; i<4;i++){
        drawBlock(ActiveBlox.x+ActiveBlox.Blox.points[i][X],ActiveBlox.y+ActiveBlox.Blox.points[i][Y],R,G,B,BLOX_INT);
    }
    glFlush();  // Render now

}
void display(){
    updateWindow();
}
void keyboard(unsigned char key, int x, int y){
    switch(key){
        case 'q':
            ROTATE_LEFT;
            break;
        case 'e':
            ROTATE_RIGHT;
            break;
        case 'a':
            LEFT;
            break;
        case 's':
            FALL;
            break;
        case 'w':
            DOWN;
            break;
        case 'd':
            RIGHT;
            break;
    }
    updateWindow();
    return;
}
void arrowInput(int key, int x, int y){
    switch(key){
        case GLUT_KEY_UP:
            ROTATE_RIGHT;
            break;
        case GLUT_KEY_DOWN:
            DOWN;
            break;
        case GLUT_KEY_LEFT:
            LEFT;
            break;
        case GLUT_KEY_RIGHT:
            RIGHT;
            break;
    }
    updateWindow();
}

void glutTimer()
{
    glutPostRedisplay();
    glutTimerFunc(1, glutTimer, 0);
}
void initWindow(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    glutInitWindowPosition(600,200);
    glutCreateWindow("Tetris");
    glutDisplayFunc(display);
    glutKeyboardFunc(&keyboard);
    glutSpecialFunc(arrowInput);
    glutTimerFunc(1,glutTimer , 0);
    glutMainLoop();
}
void * initWindowSDL(void * thing){
	return NULL;
}
