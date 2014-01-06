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
void drawBlock(int x, int y, int R, int G, int B){
    float ox1,oy1,ox2,oy2,ix1,iy1,ix2,iy2;
    //Outline
    ox1 = -1 + x/5.0;
    oy1 = 1 - (y-2)/10.0 ;
    ox2 = ox1 + 1/5.0;
    oy2 = oy1 - 1/10.0;
    
    glColor3f(0,0,0);
    glRectf(ox1,oy1,ox2,oy2);
    
    //Inner Block
    ix1 = ox1 + 2.0/WINDOW_WIDTH;
    iy1 = oy1 - 2.0/WINDOW_HEIGHT;
    ix2 = ox2 - 2.0/WINDOW_WIDTH;
    iy2 = oy2 + 2.0/WINDOW_HEIGHT;
    glColor3ub(R,G,B);
    glRectf(ix1,iy1,ix2,iy2);
    
}
void updateWindow(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)

    //printf("%i | %i\n",ActiveBlox.x,ActiveBlox.y);
    int R,G,B;
    for(int y = 0; y<22;y++){
        for(int x = 0;x<10;x++){
            if(FIELD_RGB(x,y,R,G,B))drawBlock(x,y,R,G,B);
        }
    }
    BLOX_RGB(R,G,B);
    for(int i = 0; i<4;i++){
        drawBlock(ActiveBlox.x+ActiveBlox.Blox.points[i][X],ActiveBlox.y+ActiveBlox.Blox.points[i][Y],R,G,B);
    }
    glFlush();  // Render now

}
void display(){
    updateWindow();
}
void *keyboard(int key, int x, int y){
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
    glutTimerFunc(1, glutTimer, NULL);
}
void initWindow(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    glutInitWindowPosition(600,200);
    glutCreateWindow("Tetris");
    glutDisplayFunc(display);
    glutKeyboardFunc(&keyboard);
    glutSpecialFunc(arrowInput);
    glutTimerFunc(1,glutTimer , NULL);
    glutMainLoop();
}
void initWindowSDL(){
    
}