#include <GL/freeglut.h>
#include <string.h>
#include "functions.h"
#include "struct.h"
#include "globalshit.h"
#include <stdio.h>
/*#include <SDL/SDL.h>*/
#include <FTGL/ftgl.h>
#include <unistd.h>

float BLOCK_WIDTH = (2*GAME_WINDOW_WIDTH/(float)WINDOW_WIDTH)/10;
float BLOCK_BORDER_WIDTH = 3*(GAME_WINDOW_WIDTH/(float)WINDOW_WIDTH) / WINDOW_WIDTH;
float BLOCK_HEIGHT = (2*GAME_WINDOW_HEIGHT/(float)WINDOW_HEIGHT)/20;
float BLOCK_BORDER_HEIGHT =  1.5*(GAME_WINDOW_HEIGHT/(float)WINDOW_HEIGHT) / WINDOW_HEIGHT;
float BLOCK_OFFSET_X = 2 * OFFSET_X / (float)WINDOW_WIDTH;
float BLOCK_OFFSET_Y = 2 * OFFSET_Y / (float)WINDOW_HEIGHT;

void game_keyboard(unsigned char key, int x, int y);
void menu_keyboard(unsigned char key, int x, int y);

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
	char strlevel[50], strpoints[50], strlines[50], strperc[10];
	float x1,x2,y1,y2,lh,bb[6],bx1,bx2,by1,by2,off,plevel;
	int r,g,b,x,y,z;
	ftglSetFontFaceSize(font, 32, 32);
	lh = 2 * ftglGetFontLineHeight(font) / WINDOW_WIDTH;
	plevel = (float) lvl_blox / (level * BLOCKS_PER_LEVEL);
	sprintf(strlevel, "Level: %d", level);
	sprintf(strpoints, "Points: %d", points);
	sprintf(strlines, "Lines: %d", lines);
	sprintf(strperc, "%.0f%%", 100 * plevel);
	if(!font) {
		printf("Error loading Font\n");
		return;
	}
	x1 = -1 + 2 * (2 * OFFSET_X + GAME_WINDOW_WIDTH) / WINDOW_WIDTH;
	x2 = 1 - BLOCK_OFFSET_X;
	y1 = 1 - BLOCK_OFFSET_Y + BLOCK_BORDER_HEIGHT;
	y2 = y1 - 2 * lh;
	glColor3ub(255,255,255);
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1,y1);
		glVertex2f(x2,y1);
		glVertex2f(x2,y2);
		glVertex2f(x1,y2);
	glEnd();
	glRectf(x1 + 0.05 - 2 / WINDOW_WIDTH, y1 - 0.05 + 2 / WINDOW_HEIGHT, x2 - 0.05 + 2 / WINDOW_WIDTH, y2 + lh - 2 / WINDOW_HEIGHT);
	glColor3ub(0,0,0);
	glRectf(x1 + 0.05, y1 - 0.05, x1 + 0.05 + plevel * (x2 - x1 - 0.1) , y2 + lh);
	glColor3ub(150,150,150);
	glRasterPos2f(0.5 * (x1 + x2) - ftglGetFontAdvance(font,strperc) / WINDOW_WIDTH, y2 + lh);
	ftglRenderFont(font,strperc,FTGL_RENDER_ALL);
	glColor3ub(255,255,255);
	ftglGetFontBBox(font,strlevel,-1,bb);
	glRasterPos2f(x1 + 0.05, y2 + 0.5 * lh - (bb[4]-bb[2]) / WINDOW_HEIGHT);
	ftglRenderFont(font, strlevel, FTGL_RENDER_ALL);
	y1 = y2 - 0.5 * lh;
	y2 = y1 - lh;
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1,y1);
		glVertex2f(x2,y1);
		glVertex2f(x2,y2);
		glVertex2f(x1,y2);
	glEnd();
	ftglGetFontBBox(font,strpoints,-1,bb);
	glRasterPos2f(x1 + 0.05, 0.5 * (y1 + y2) - (bb[4]-bb[2]) / WINDOW_HEIGHT);
	ftglRenderFont(font, strpoints, FTGL_RENDER_ALL);
	y1 = y2 - 0.5 * lh;
	y2 = y1 - lh;
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1,y1);
		glVertex2f(x2,y1);
		glVertex2f(x2,y2);
		glVertex2f(x1,y2);
	glEnd();
	ftglGetFontBBox(font,strlines,-1,bb);
	glRasterPos2f(x1 + 0.05, 0.5 * (y1 + y2) - (bb[4]-bb[2]) / WINDOW_HEIGHT);
	ftglRenderFont(font, strlines, FTGL_RENDER_ALL);
	y1 = y2 - 0.5 * lh;
	y2 = 1 - BLOCK_OFFSET_Y - 20 * BLOCK_HEIGHT - 3 * BLOCK_BORDER_HEIGHT;
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1,y1);
		glVertex2f(x2,y1);
		glVertex2f(x2,y2);
		glVertex2f(x1,y2);
	glEnd();
	for (int num = 0; num < 3; num++) {
		z = queue[(block_num - 1) % 7 + num + 1];
		block_to_rgb(Block[z].rgb,&r,&g,&b);
		glColor3ub(r,g,b);
		if (z == 0) off = 0.25 * BLOCK_HEIGHT;
		else off = 0.5 * BLOCK_HEIGHT;
		for (int pt = 0; pt < 4; pt++) {
			x = Block[z].points[pt][X];
			y = Block[z].points[pt][Y];
			bx1 = x1 + 0.5 * (x2 - x1 - Block[z].size * 0.5 * BLOCK_WIDTH) + x * 0.5 * BLOCK_WIDTH + 2 / WINDOW_WIDTH;
			bx2 = bx1 + 0.5 * BLOCK_WIDTH - 2 / WINDOW_WIDTH;
			by1 = y1 - (5 * num + y + 1) * 0.5 * BLOCK_HEIGHT - 0.5 * (y1 - y2 - 16 * 0.5 * BLOCK_HEIGHT) - 2 / WINDOW_HEIGHT - off;
			by2 = by1 + 0.5 * BLOCK_HEIGHT - 2 / WINDOW_HEIGHT;
			glRectf(bx1,by1,bx2,by2);
		}
	}
}
void updateWindow(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	drawInterface();
	int R,G,B;
	float left,bottom;
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
	if (strcmp(message,"")) {
		glColor3ub(255,255,255);
		left = -1 + BLOCK_OFFSET_X + (5.0 * BLOCK_WIDTH - (ftglGetFontAdvance(font, message) / WINDOW_WIDTH));
		bottom = -0.98 + (WINDOW_HEIGHT - GAME_WINDOW_HEIGHT - OFFSET_Y - ftglGetFontLineHeight(font)) / WINDOW_HEIGHT;
		glRasterPos2f(left, bottom);
		ftglRenderFont(font, message, FTGL_RENDER_ALL);
	}
	float x1,x2,y1,y2;
	x1 = -1 + BLOCK_OFFSET_X;
	x2 = x1 + 10 * BLOCK_WIDTH;
	y1 = 1 - BLOCK_OFFSET_Y;
	y2 = y1 - 20 * BLOCK_HEIGHT;
	if (menu) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4ub(0,0,0,230);
		glBegin(GL_QUADS);
			glVertex2f(x1,y1);
			glVertex2f(x2,y1);
			glVertex2f(x2,y2);
			glVertex2f(x1,y2);
		glEnd();
		glDisable(GL_BLEND);
		glColor3ub(255,255,255);
		glRasterPos2f(-1 + BLOCK_OFFSET_X + (5.0 * BLOCK_WIDTH - (ftglGetFontAdvance(font, "[c]ontinue") / WINDOW_WIDTH)),
			      -1 + 2 * (WINDOW_HEIGHT - (1 - 0.55) * GAME_WINDOW_HEIGHT - OFFSET_Y) / WINDOW_HEIGHT);
		if (!gover) ftglRenderFont(font, "[c]ontinue", FTGL_RENDER_ALL);
		glRasterPos2f(-1 + BLOCK_OFFSET_X + (5.0 * BLOCK_WIDTH - (ftglGetFontAdvance(font, "[n]ew game") / WINDOW_WIDTH)),
			      -1 + 2 * (WINDOW_HEIGHT - (1 - 0.45) * GAME_WINDOW_HEIGHT - OFFSET_Y) / WINDOW_HEIGHT);
		ftglRenderFont(font, "[n]ew game", FTGL_RENDER_ALL);
		glRasterPos2f(-1 + BLOCK_OFFSET_X + (5.0 * BLOCK_WIDTH - (ftglGetFontAdvance(font, "[q]uit") / WINDOW_WIDTH)),
			      -1 + 2 * (WINDOW_HEIGHT - (1 - 0.35) * GAME_WINDOW_HEIGHT - OFFSET_Y) / WINDOW_HEIGHT);
		ftglRenderFont(font, "[q]uit", FTGL_RENDER_ALL);
	}
	x1 -= BLOCK_BORDER_WIDTH;
	x2 += 3 * BLOCK_BORDER_WIDTH;
	y1 += BLOCK_BORDER_HEIGHT;
	y2 -=  3 * BLOCK_BORDER_HEIGHT;
	glColor3ub(255,255,255);
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1,y1);
		glVertex2f(x2,y1);
		glVertex2f(x2,y2);
		glVertex2f(x1,y2);
	glEnd();
	glutSwapBuffers();
}
void display(){
    updateWindow();
}
void resize (int width, int height) {
	glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
}
void game_keyboard(unsigned char key, int x, int y){
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
            key_down = TRUE;
            FALL;
            break;
        case 'w':
            DOWN;
            break;
        case 'd':
            RIGHT;
            break;
	case 27 /*ESC*/:
	    running = FALSE;
	    menu = TRUE;
	    change_message("- paused -");
	    glutKeyboardFunc(menu_keyboard);
	    break;
    }
    updateWindow();
    return;
}
void game_arrowInput(int key, int x, int y){
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
void game_down_Release(unsigned char key, int x, int y){
	switch(key) {
	case 's':
		key_down = FALSE;
	}
	updateWindow();
}
void menu_keyboard(unsigned char key, int x, int y) {
	switch(key){
	case 'n':
		new_game();
		change_message("");
		glutKeyboardFunc(game_keyboard);
		break;
	case 'q':
		_exit(0);
		break;
	case 'c':
		if(!gover) {
			menu = FALSE;
			change_message("");
			glutKeyboardFunc(game_keyboard);
			running = TRUE;
		}
		break;
	case 27 /*ESC*/:
		menu = FALSE;
		change_message("");
		glutKeyboardFunc(game_keyboard);
		running = TRUE;
		break;
	}
}
void glutTimer(){
	glutPostRedisplay();
	glutTimerFunc(10, glutTimer, 0);
}
void initWindow(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH)/2-WINDOW_WIDTH/2,glutGet(GLUT_SCREEN_HEIGHT)/2-WINDOW_HEIGHT/2);
	glutCreateWindow("Tetris");
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(game_keyboard);
	glutKeyboardUpFunc(game_down_Release);
	glutSpecialFunc(game_arrowInput);
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
