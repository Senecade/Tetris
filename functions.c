#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "struct.h"
#include "move.h"
#include "globalshit.h"
#include "interface.h"
#include <sys/time.h>
#include <signal.h>
#include "functions.h"

int field[10][22] = {{0}}, level = 0, block_num = 0, del_blocks = 0, running = TRUE;
struct itimerval timer;
struct sigaction act = {{0}};

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
    	double b = 1000, a = 300 /*in ms*/, k = pow(10,-7), e = 2.71828182846;
	a *= 1000;
	b *= 1000;
	delay = a / (1 + (pow(e,(-k * a * level))) * ((a / b) - 1));
	timer.it_interval.tv_sec = (int) delay / 1000000;
	timer.it_interval.tv_usec = (int) delay % 1000000;
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
		field[x][y] = ActiveBlox.Blox.rgb;
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
	if (block_num % 7 == 0) newqueue();
	next_block = queue[block_num % 7];
	if (next_block == 3) ActiveBlox.x = 4;
	else ActiveBlox.x = 3;
	ActiveBlox.y = -1;
	for (int i = 0; i < 4; i++) {
		ActiveBlox.Blox.points[i][X] = Block[next_block].points[i][X];
		ActiveBlox.Blox.points[i][Y] = Block[next_block].points[i][Y];
	}
	ActiveBlox.Blox.rgb = Block[next_block].rgb;
	ActiveBlox.Blox.size = Block[next_block].size;
	if (possible(FALL_INT)) FALL;
	else /* TODO:Game Over Screen*/ exit(0);
	block_num++;
}

void func_next_block() {
	transform_block();	
	destroy_rows();
	spawn_block();
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
	act.sa_handler = &gravity;
	sigaction(SIGALRM, &act, NULL);
	timer.it_value.tv_sec = (int) delay / 1000000;
	timer.it_value.tv_usec = (int) delay % 1000000;
	timer.it_interval.tv_sec = (int) delay / 1000000;
	timer.it_interval.tv_usec = (int) delay % 1000000;
	setitimer(ITIMER_REAL, &timer, NULL);
	return NULL;
}


void gen_shadow() {
	ActiveBlox.shadow_offset = 0;
	while (try_move(SHADOW_FALL_INT));
}

void gravity(int signum) {
	FALL;
}
