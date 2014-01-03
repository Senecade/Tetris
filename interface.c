#include <GL/glut.h>
#include "functions.h"
#include <stdio.h>

enum{
    WINDOW_HEIGHT = 600,
    WINDOW_WIDTH = 300
};
void drawBlock(int x, int y){
    float ox1,oy1,ox2,oy2,ix1,iy1,ix2,iy2;
    //Outline
    ox1 = -1 + x/5.0;
    oy1 = 1 - (y-2)/10.0 ;
    ox2 = ox1 + 1/5.0;
    oy2 = oy1 - 1/10.0;
    
    glColor3f(0,0,0);
    glRectf(ox1,oy1,ox2,oy2);
    
    ix1 = ox1 + 2.0/WINDOW_WIDTH;
    iy1 = oy1 - 2.0/WINDOW_HEIGHT;
    ix2 = ox2 - 2.0/WINDOW_WIDTH;
    iy2 = oy2 + 2.0/WINDOW_HEIGHT;
    
    glColor3f(0,1,1);
    glRectf(ix1,iy1,ix2,iy2);
    
}
void updateWindow(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
    printf("\n");
    printf("\n");
    for(int y = 0; y<22;y++){
        for(int x = 0;x<10;x++){
            printf("%i",field[x][y]);
        }
        printf("\n");
    }
    glFlush();  // Render now

}
void keyboard(unsigned char key, int x, int y){
}
void initWindow(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    glutInitWindowPosition(600,200);
    glutCreateWindow("Tetris");
    glutDisplayFunc(updateWindow);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}