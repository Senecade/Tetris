#include <GL/glut.h>
#include "functions.h"
#include "struct.h"
#include "globalshit.h"
#include <stdio.h>
//#include <SDL/SDL.h>

float BLOCK_WIDTH = (2*GAME_WINDOW_WIDTH/(float)WINDOW_WIDTH)/10;
float BLOCK_BORDER_WIDTH = 3*(GAME_WINDOW_WIDTH/(float)WINDOW_WIDTH) / WINDOW_WIDTH;
float BLOCK_HEIGHT = (2*GAME_WINDOW_HEIGHT/(float)WINDOW_HEIGHT)/20;
float BLOCK_BORDER_HEIGHT =  1.5*(GAME_WINDOW_HEIGHT/(float)WINDOW_HEIGHT) / WINDOW_HEIGHT;
float BLOCK_OFFSET_X = 2 * OFFSET_X / (float)WINDOW_WIDTH;
float BLOCK_OFFSET_Y = 2 * OFFSET_Y / (float)WINDOW_HEIGHT;


void drawBlock(int x, int y, const int R, const int G, const int B, int blocktype){
	if (y<2 || y>21 || x<0 || x>9) return;
	float ox1,oy1,ox2,oy2;
	double H, S, V;
	unsigned char r, g, b;
	ox1 = -1 + x * BLOCK_WIDTH + BLOCK_BORDER_WIDTH + BLOCK_OFFSET_X;
	oy1 = 1 - (y - 2) * BLOCK_HEIGHT - BLOCK_BORDER_HEIGHT - BLOCK_OFFSET_Y;
	ox2 = ox1 + BLOCK_WIDTH - BLOCK_BORDER_WIDTH;
	oy2 = oy1 - BLOCK_HEIGHT + BLOCK_BORDER_HEIGHT;
	if (blocktype == SHADOW_INT) {
		rgb_to_hsv(R, G, B, &H, &S, &V);
		S = (S - 0.6 > 0) ? (S - 0.6) : 0;
		V = 0.25;
		hsv_to_rgb(H, S, V, &r, &g, &b);
		glColor3ub(r,g,b);
		glRectf(ox1,oy1,ox2,oy2);
	}
	else {
		float ix1,iy1,ix2,iy2;
		ix1 = ox1 + 10.0 / WINDOW_WIDTH;
		iy1 = oy1 - 10.0 / WINDOW_HEIGHT;
		ix2 = ox2 - 10.0 / WINDOW_WIDTH;
		iy2 = oy2 + 10.0 / WINDOW_HEIGHT;
		rgb_to_hsv(R, G, B, &H, &S, &V);
		S = (S - 0.5 > 0) ? (S - 0.5) : 0;
		V = 1;
		hsv_to_rgb(H, S, V, &r, &g, &b);
		glColor3ub(r, g, b);
		glBegin(GL_QUADS); //oben
			glVertex2f(ox1,oy1);
			glVertex2f(ox2,oy1);
			glVertex2f(ix2,iy1);
			glVertex2f(ix1,iy1);
		glEnd();
		rgb_to_hsv(R, G, B, &H, &S, &V);
		S = (S - 0.1 > 0) ? (S - 0.1) : 0;
		V = 0.6;
		hsv_to_rgb(H, S, V, &r, &g, &b);
		glColor3ub(r, g, b);
		glBegin(GL_QUADS); //rechts
			glVertex2f(ox2,oy1);
			glVertex2f(ox2,oy2);
			glVertex2f(ix2,iy2);
			glVertex2f(ix2,iy1);
		glEnd();
		rgb_to_hsv(R, G, B, &H, &S, &V);
		S = (S - 0.2 > 0) ? (S - 0.2) : 0;
		V = 0.3;
		hsv_to_rgb(H, S, V, &r, &g, &b);
		glColor3ub(r, g, b);
		glBegin(GL_QUADS); //unten
			glVertex2f(ox2,oy2);
			glVertex2f(ox1,oy2);
			glVertex2f(ix1,iy2);
			glVertex2f(ix2,iy2);
		glEnd();
		rgb_to_hsv(R, G, B, &H, &S, &V);
		S = (S - 0.1 > 0) ? (S - 0.1) : 0;
		V = 0.6;
		hsv_to_rgb(H, S, V, &r, &g, &b);
		glColor3ub(r, g, b);
		glBegin(GL_QUADS); //links
			glVertex2f(ox1,oy2);
			glVertex2f(ox1,oy1);
			glVertex2f(ix1,iy1);
			glVertex2f(ix1,iy2);
		glEnd();
		glColor3ub(R, G, B);
		glRectf(ix1,iy1,ix2,iy2); //Mitte
	}
}
void drawInterface(){
    ////////////////////////
    //Draw border of field//
    ////////////////////////
    float x1,x2,y1,y2;
    x1 = -1 + BLOCK_OFFSET_X - BLOCK_BORDER_WIDTH; // 2*(GAME_WINDOW_WIDTH/(float)WINDOW_WIDTH)+2.5 / WINDOW_WIDTH;
    x2 = x1 + 10 * BLOCK_WIDTH + 3 * BLOCK_BORDER_WIDTH;
    y1 = 1 - BLOCK_OFFSET_Y + BLOCK_BORDER_HEIGHT;
    y2 = y1 - 20 * BLOCK_HEIGHT - 3 * BLOCK_BORDER_HEIGHT;
    
    glColor3ub(255,255,255);
    glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y1);
        
        glVertex2f(x1,y2);
        glVertex2f(x2,y2);
        
        glVertex2f(x1,y1);
        glVertex2f(x1,y2);
        
        glVertex2f(x2,y1);
        glVertex2f(x2,y2);
    glEnd();
    
}
void updateWindow(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
    drawInterface();
    int R,G,B;
    for(int y = 2; y<22;y++){
        for(int x = 0;x<10;x++){
            if(FIELD_RGB(x,y,R,G,B)) drawBlock(x,y,R,G,B,FIELD_INT);
        }
    }
    BLOX_RGB(R,G,B);
    for (int i = 0; i<4;i++) {
	if (ActiveBlox.shadow_offset > 0) drawBlock(ActiveBlox.x + ActiveBlox.Blox.points[i][X], ActiveBlox.y + ActiveBlox.Blox.points[i][Y] + ActiveBlox.shadow_offset, R, G, B, SHADOW_INT);
    }
    for (int i = 0; i<4;i++) {
        drawBlock(ActiveBlox.x + ActiveBlox.Blox.points[i][X], ActiveBlox.y + ActiveBlox.Blox.points[i][Y], R, G, B, BLOX_INT);
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

void glutTimer(){
	glutPostRedisplay();
	if(running) glutTimerFunc(10, glutTimer, 0);
}
void initWindow(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH)/2-WINDOW_WIDTH/2,glutGet(GLUT_SCREEN_HEIGHT)/2-WINDOW_HEIGHT/2);
    glutCreateWindow("Tetris");
    glutDisplayFunc(display);
    glutKeyboardFunc(&keyboard);
    glutSpecialFunc(arrowInput);
    glutTimerFunc(10,glutTimer , 1);
    glutMainLoop();
}

/*
void initWindowSDL(){
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(WINDOW_WIDTH,WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    
    if(!screen){
        SDL_Quit();
        return;
    }
    
    int running = 1;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = 0;
                    break;
            }
        }
        SDL_Flip(screen);
        SDL_Delay(10);
    }
    
    SDL_Quit();
}
*/
void * initWindowSDL(void * thing){
	return NULL;
}
