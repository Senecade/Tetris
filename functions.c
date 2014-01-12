#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include "struct.h"
#include "move.h"
#include "globalshit.h"
#include "interface.h"
#include "functions.h"

int field[10][22] = {{0}}, level = 1, block_num = 0, del_blocks = 0, running = TRUE;
struct timespec timer;

int try_move(int movetype){
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

void next_level(){
    	double b = 1000, a = 250 /*in ms*/, k = pow(10,-10), e = 2.71828182846;
	a *= 1000000;
	b *= 1000000;
	delay = a / (1 + (pow(e,(-k * a * level))) * ((a / b) - 1));
	timer.tv_sec = (int) (delay / 1000000000);
	timer.tv_nsec = (int) delay % 1000000000;
	printf("Level:%d\n",level);
}

int shuffle(int start, int stop) {
	if(start >= stop) return 0;
	return start + (double) random() / ((double) RAND_MAX / (stop - start + 1) + 1);
}

int block_to_rgb(int rgb, int *r, int *g, int *b) {
	if (rgb % 2 == 0) return FALSE;
	rgb = rgb >>1;
	*b = rgb % 256;
	rgb = rgb >>8;
	*g = rgb % 256;
	rgb = rgb >>8;
	*r = rgb % 256;
	return TRUE;
}

void transform_block() {
	int x,y;
	for (int i=0;i<4;i++) {
		x = ActiveBlox.x + ActiveBlox.Blox.points[i][X];
		y = ActiveBlox.y + ActiveBlox.Blox.points[i][Y];
		if (x>=0 && x<10 && y>=0 && y<22) field[x][y] = ActiveBlox.Blox.rgb;
	}
}

void newqueue() {
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


void spawn_block() {
	for (int y = 0;y<2;y++) {
		for (int x=0;x<10;x++) if (field[x][y]) exit(0);
		// TODO:Game Over Screen
	}
	if (block_num % 7 == 0) newqueue();
	next_block = queue[block_num % 7];
	if (next_block == 3) ActiveBlox.x = 4;
	else ActiveBlox.x = 3;
	ActiveBlox.y = 0;
	for (int i = 0; i < 4; i++) {
		ActiveBlox.Blox.points[i][X] = Block[next_block].points[i][X];
		ActiveBlox.Blox.points[i][Y] = Block[next_block].points[i][Y];
	}
	ActiveBlox.Blox.rgb = Block[next_block].rgb;
	ActiveBlox.Blox.size = Block[next_block].size;
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

void func_next_block() {
	struct timespec wait;
	wait.tv_sec = 0;
	wait.tv_nsec = 300000000;
	transform_block();
	spawn_block();
	if(destroy_rows(MARK_ROWS_INT) == TRUE) {
		updateWindow();
		nanosleep(&wait,NULL);
		destroy_rows(DEL_ROWS_INT);
	}
}

void * init(void * thing) {
	int z,help;
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
	while (running) {
		nanosleep(&timer,NULL);
		FALL;
	}
	return NULL;
}


void gen_shadow() {
	ActiveBlox.shadow_offset = 0;
	while (try_move(SHADOW_FALL_INT));
}

void exit_func() {
	running = FALSE;
	nanosleep(&timer,NULL);
	nanosleep(&timer,NULL);
	exit(0);
}
