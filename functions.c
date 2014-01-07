#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include "struct.h"
#include "move.h"
#include "globalshit.h"
#include "interface.h"
#include "functions.h"

int field[10][22] = {{0}}, level = 0, block_num = 0, del_blocks = 0, running = TRUE;

int try_move(int movetype){
	if (possible(movetype) == FALSE) {
		if (movetype == FALL_INT) {
		    func_next_block();
		}
		return FALSE;
	}
	switch (movetype) {
		case ROTATION_RIGHT_INT: ROTATE_BLOCK_RIGHT; break;
		case ROTATION_LEFT_INT:  ROTATE_BLOCK_LEFT; break;
		case RIGHT_INT:          MOVE_BLOCK_RIGHT; break;
		case DOWN_INT:           MOVE_BLOCK_DOWN; break;
		case LEFT_INT:           MOVE_BLOCK_LEFT; break;
		case FALL_INT:           MOVE_BLOCK_FALL; break;
	}
	return TRUE;
}

void next_level(){
    	double b = 1000000, a = 300000, k = pow(10,-7), e = 2.71828182846;
	delay = a / (1 + (pow(e,(-k * a * level))) * ((a / b) - 1));
}

int shuffle(int start, int stop) {
	if(start >= stop) return 0;
	srand(time(0));
	return (rand() % (stop - start + 1)) + start;
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
		queue[i] = i;
	}
	for (int i=6;i>=0;i--) {
		z = shuffle(0,i - 1);
		help = queue[i];
		queue[i] = queue[z];
		queue[z] = help;
	}
}

void spawn_block() { 
	if (block_num % 7 == 0) newqueue();
	next_block = queue[block_num % 7];
	if (next_block == 3) ActiveBlox.x = 5;
	else ActiveBlox.x = 3;
	ActiveBlox.y = -1;
	if (possible(FALL_INT)) ActiveBlox.y++;
	else /* TODO:Game Over Screen*/ exit(0);
	for (int i = 0; i < 4; i++) {
		ActiveBlox.Blox.points[i][X] = Block[next_block].points[i][X];
		ActiveBlox.Blox.points[i][Y] = Block[next_block].points[i][Y];
	}
	ActiveBlox.Blox.rgb = Block[next_block].rgb;
	ActiveBlox.Blox.size = Block[next_block].size;
	block_num++;
	destroy_rows();
}

void func_next_block() {
	transform_block();
	spawn_block();
}

int init() {
    spawn_block();
    next_level();
    while (running) {
        usleep((unsigned int) delay);
        FALL;
    }
    return 0;
}
