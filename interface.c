#include <GL/glut.h>

void drawBlock(int x, int y){
    float ox1,oy1,ox2,oy2,ix1,iy1,ix2,iy2;
    //Outline
    ox1 = -1 + x/5.0;
    oy1 = 1 - y/10.0;
    ox2 = ox1 + 1/5.0;
    oy2 = oy1 - 1/10.0;
    
    glColor3f(1,1,1);
    glRectf(ox1,oy1,ox2,oy2);
    
    ix1 = ox1 + 2/300.0;
    iy1 = oy1 - 2/600.0;
    ix2 = ox2 - 2/300.0;
    iy2 = oy2 + 2/600.0;
    
    glColor3f(0,1,1);
    glRectf(ix1,iy1,ix2,iy2);
    
}
void updateWindow(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
    drawBlock(0,0);
    drawBlock(0,1);
    drawBlock(0,2);
    drawBlock(1,1);
    glFlush();  // Render now

}

