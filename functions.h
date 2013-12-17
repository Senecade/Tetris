#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define BLOCKS_PER_LEVEL 5

#define UP_INT 0
#define RIGHT_INT 1
#define DOWN_INT 2
#define LEFT_INT 3
#define FALL_INT 4

#define RIGHT go(RIGHT_INT);
#define DOWN go(DOWN_INT);
#define LEFT go(LEFT_INT);
#define FALL go(FALL_INT);

#define TURN_RIGHT turn(RIGHT);
#define TURN_LEFT turn(LEFT);

int field[100][200] = {0}, block_num = 0, level = 0, delay = 1000;
char running = 1;

int go(int d){
    switch(d){
        case RIGHT_INT:
                        break;
        case DOWN_INT:
                        break;
        case LEFT_INT:
                        break;
        case FALL_INT:
                        break;
    }
    return 0;
}

int turn(int d){
    switch(d){
        case RIGHT_INT:
                        break;
        case LEFT_INT:
                        break;
    }
    return 0;
}

void next_level(){
    level++;
    delay = (int) (1000.0f / sqrt(level));
}

void create_block(){
    block_num++;
}

void spawn_block(){
    
}

void next_block(){
    if(!(block_num % BLOCKS_PER_LEVEL))
        next_level();
    
    create_block();
    spawn_block();
}

void *background(){
    
    while(running){
        sleep(delay);
        FALL
    }
    
    return NULL;
}





