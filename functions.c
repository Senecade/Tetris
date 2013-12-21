#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

#define BLOCKS_PER_LEVEL 10

#define UP_INT 0
#define RIGHT_INT 1
#define DOWN_INT 2
#define LEFT_INT 3
#define FALL_INT 4
#define ROTATION_RIGHT_INT 5
#define ROTATION_LEFT_INT 6

#define X 0
#define Y 1
#define TRUE 1
#define FALSE 0

#define MOVE_BLOCK_RIGHT ActiveBlox.x++;
#define MOVE_BLOCK_DOWN while (possible(DOWN_INT)) ActiveBlox.y++;
#define MOVE_BLOCK_LEFT ActiveBlox.x--;
#define MOVE_BLOCK_FALL ActiveBlox.y++;
#define ROTATE_BLOCK_RIGHT rotate(ROTATION_RIGHT_INT);
#define ROTATE_BLOCK_LEFT rotate(ROTATION_LEFT_INT);

#define RIGHT try_move(RIGHT_INT);
#define DOWN try_move(DOWN_INT);
#define LEFT try_move(LEFT_INT);
#define FALL try_move(FALL_INT);
#define ROTATE_RIGHT try_move(ROTATION_RIGHT_INT);
#define ROTATE_LEFT try_move(ROTATION_LEFT_INT);

#define CHANGE_INT 0
#define RESULT_INT 1

int field[10][22] /* angezeigt werden nur 20 Blöcke (horizontal) */ = {0},level = 1,block_num = 0,next_block,delay;
//possible @move.c
//rotate @move.c
int try_move(int movetype){
    if(possible(movetype) == FALSE)
        return FALSE;
    
    switch(movetype){
        case ROTATION_RIGHT_INT: ROTATE_BLOCK_RIGHT break;
        case ROTATION_LEFT_INT:  ROTATE_BLOCK_LEFT break;
        case RIGHT_INT:          MOVE_BLOCK_RIGHT break;
        case DOWN_INT:           MOVE_BLOCK_DOWN break;
        case LEFT_INT:           MOVE_BLOCK_LEFT break;
        case FALL_INT:           MOVE_BLOCK_FALL break;
    }
    
    return TRUE;
}

void next_level(){
    level++;
    delay = (int) (1000.0f / sqrt(level));
}

int shuffle(int start, int stop){
    if(start >= stop)
        return 0;
    
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
		y = ActiveBlox.x + ActiveBlox.Blox.points[i][Y];
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

void spawn_block(){ /*bitte mal Tetris-Guidelines durchlesen, Betreff: Spawning bezüglich Feld und bezüglich Random-Generator */
    if (block_num % 7 == 0) newqueue();
    next_block = queue[block_num % 7];

    ActiveBlox.x = 5;
    ActiveBlox.y = -1;
    if (possible(FALL_INT)) Active.Blox.y++;
    else exit();
    for(int i = 0; i < 4; i++){
        ActiveBlox.Blox.points[i][X] = Block[next_block].points[i][X];
        ActiveBlox.Blox.points[i][Y] = Block[next_block].points[i][Y];
    }
    ActiveBlox.Blox.rgb = Block[next_block].rgb;
    ActiveBlox.Blox.size = Block[next_block].size;
    
    block_num++;
}

void next_block(){
    transform_block();
    
    if(!(block_num % BLOCKS_PER_LEVEL))
        next_level();
    
    spawn_block();
}

void *background(){
    
    while(running){
        sleep(delay);
        FALL
    }
    
    return NULL;
}
