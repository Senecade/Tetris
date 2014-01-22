#include <stdio.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include "struct.h"
#include "move.h"
#include "globalshit.h"
#include "interface.h"
#include "functions.h"

struct timespec timer;

int shuffle(int start, int stop);
void transform_block(void);
void newqueue(void);
void spawn_block(void);
void func_next_block(void);

int try_move(int movetype){
	if (!running) return FALSE;
	if (possible(movetype) == FALSE) {
		if (movetype == FALL_INT) {
		    func_next_block();
		}
		return FALSE;
	}
	switch (movetype) {
		case ROTATION_RIGHT_INT: ROTATE_BLOCK_RIGHT; SHADOW; break;
		case ROTATION_LEFT_INT:  ROTATE_BLOCK_LEFT; SHADOW; break;
		case RIGHT_INT:          MOVE_BLOCK_RIGHT; SHADOW; break;
		case DOWN_INT:           MOVE_BLOCK_DOWN; SHADOW; break;
		case LEFT_INT:           MOVE_BLOCK_LEFT; SHADOW; break;
		case FALL_INT:           MOVE_BLOCK_FALL; SHADOW; break;
		case SHADOW_FALL_INT:    MOVE_SHADOW_FALL; break;
	}
	return TRUE;
}

void next_level(void) {
    	double b = 1000, a = 250 /*in ms*/, k = pow(10,-4), e = 2.71828182846;
	delay = a / (1 + (pow(e,(-k * a * (level- 1)))) * ((a / b) - 1));
	delay *= 1000000;
	timer.tv_sec = (int) (delay / 1000000000);
	timer.tv_nsec = (int) delay % 1000000000;
}

int shuffle(int start, int stop) {
	if(start >= stop) return 0;
	return start + (double) random() / ((double) RAND_MAX / (stop - start + 1) + 1);
}

int block_to_rgb(int rgb, int *r, int *g, int *b) {
	if ((rgb % 2) == 0) return FALSE;
	rgb = rgb >>1;
	*r = (rgb & 0xff0000) >>16;
	*g = (rgb & 0x00ff00) >>8;
	*b = (rgb & 0x0000ff);
	return TRUE;
}

void transform_block(void) {
	int x,y;
	for (int i=0;i<4;i++) {
		x = ActiveBlox.x + ActiveBlox.Blox.points[i][X];
		y = ActiveBlox.y + ActiveBlox.Blox.points[i][Y];
		if (y>=2 && y<22 && x>=0  && x<10) field[x][y] = ActiveBlox.Blox.rgb;
		else {
			game_over();
			return;
		}
	}
}

void newqueue(void) {
	int z,help;
	for (int i=0;i<7;i++) {
		queue[i] = queue[i + 7];
	}
	for (int i=6;i>0;i--) {
		z = shuffle(0,i);
		help = queue[i + 7];
		queue[i + 7] = queue[z + 7];
		queue[z + 7] = help;
	}
}

void spawn_block(void) {
	if (block_num % 7 == 0) newqueue();
	next_block = queue[block_num % 7];
	for (int i = 0; i < 14; i++) printf("%d ",queue[i]);
	puts("");
	for (int i = 0; i < block_num % 7; i++) printf("  ");
	puts("X");
	if (next_block == 3) ActiveBlox.x = 4;
	else ActiveBlox.x = 3;
	ActiveBlox.y = 0;
	memcpy(&(ActiveBlox.Blox), &(Block[next_block]), sizeof Block[next_block]);
	block_num++;
}

void hsv_to_rgb(const double H, const double S, const double V, unsigned char *R, unsigned char *G, unsigned char *B) {
	int h_i;
	double f,p,q,t;
	h_i = (int) (H/60);
	f = H/60 - h_i;
	p = V * (1 - S);
	q = V * (1 - S * f);
	t = V * (1 - S * (1 - f));
	switch (h_i) {
		case 0: *R = (int) 255*V;
			*G = (int) 255*t;
			*B = (int) 255*p;
			break;
		case 1: *R = (int) 255*q;
			*G = (int) 255*V;
			*B = (int) 255*p;
			break;
		case 2: *R = (int) 255*p;
			*G = (int) 255*V;
			*B = (int) 255*t;
			break;
		case 3: *R = (int) 255*p;
			*G = (int) 255*q;
			*B = (int) 255*V;
			break;
		case 4: *R = (int) 255*t;
			*G = (int) 255*p;
			*B = (int) 255*V;
			break;
		case 5: *R = (int) 255*V;
			*G = (int) 255*p;
			*B = (int) 255*q;
			break;
		case 6: *R = (int) 255*V;
			*G = (int) 255*t;
			*B = (int) 255*p;
	}
}

void rgb_to_hsv(const unsigned char R, const unsigned char G, const unsigned char B, double *H, double *S, double *V) {
	double max,min,r,g,b,C;
	r = R / 255.0;
	g = G / 255.0;
	b = B / 255.0;
	min = (r < g) ? r : g;
	min = (min < b) ? min : b;
	max = (r > g) ? r : g;
	max = (max > b) ? max : b;
	*V = max;
	C = max - min;
	if (C == 0) *H = 0;
	else if (max == r) *H = 60 * (0 + ((g - b) / C));
	else if (max == g) *H = 60 * (2 + ((b - r) / C));
	else  *H = 60 * (4 + ((r - g) / C));
	if (*H < 0) *H = *H + 360;
	if (max == 0) *S = 0;
	else *S = (max - min) / max;
}

void func_next_block(void) {
	struct timespec wait;
	wait.tv_sec = 0;
	wait.tv_nsec = 300000000;
	transform_block();
	spawn_block();
	if (destroy_rows(MARK_ROWS_INT) == TRUE) {
		updateWindow();
		nanosleep(&wait,NULL);
		destroy_rows(DEL_ROWS_INT);
	}
	else {
		chain = 0;
		if (!gover) change_message("");
	}
}

void new_game(void) {
	int z,help;
	level = 1;
       	block_num = 0;
	lines = 0;
       	lvl_blox = 0;
       	points = 0;
       	chain = 0;
       	running = TRUE;
	key_down = FALSE;
       	menu = FALSE;
	gover = FALSE;
	memset(field, 0, sizeof field);
	ActiveBlox.shadow_offset = 0;
	for (int i=0;i<7;i++) {
		queue[i + 7] = i;
	}
	for (int i=6;i>0;i--) {
		z = shuffle(0,i);
		help = queue[i + 7];
		queue[i + 7] = queue[z + 7];
		queue[z + 7] = help;
	}
	spawn_block();
	next_level();
}

void * gravity(void * thing) {
	while (TRUE) {
		nanosleep(&timer,NULL);
		if(!key_down) FALL;
	}
	return NULL;
}


void gen_shadow(void) {
	ActiveBlox.shadow_offset = 0;
	while (try_move(SHADOW_FALL_INT));
}

void game_over(void) {
	    change_message("- Game Over -");
	    running = FALSE;
	    menu = TRUE;
	    gover = TRUE;
	    glutKeyboardFunc(menu_keyboard);
}

void change_message(const char * string) {
	message = realloc(message, sizeof (char) * (1 + strlen(string)));
	message = strcpy(message,string);
}
