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
#define ROTATION_INT UP_INT

#define X 0
#define Y 1

#define UP try_move(UP_INT);
#define RIGHT try_move(RIGHT_INT);
#define DOWN try_move(DOWN_INT);
#define LEFT try_move(LEFT_INT);
#define FALL try_move(FALL_INT);

#define ROTATE_BLOCK rotate_block();
#define MOVE_BLOCK_RIGHT move_block(RIGHT_INT);
#define MOVE_BLOCK_DOWN move_block(DOWN_INT);
#define MOVE_BLOCK_LEFT move_block(LEFT_INT);
#define MOVE_BLOCK_FALL move_block(FALL_INT);

#define UP_IS_POSSIBLE possible(UP_INT);
#define RIGHT_IS_POSSIBLE possible(RIGHT_INT);
#define DOWN_IS_POSSIBLE possible(DOWN_INT);
#define LEFT_IS_POSSIBLE possible(LEFT_INT);
#define FALL_IS_POSSIBLE possible(FALL_INT);
#define ROTATION_IS_POSSIBLE possible(ROTATION_INT);

int field[10][20] = {0}, block_num = 0, level = 0, delay = 1000;
clock_t last_move = 0;
char running = 1;

void rotate_block(){
    // EINFUEGEN: Block drehen
}

void move_block(int direct){
    // EINFUEGEN: Block bewegen 
}

int possible(int direct){
    if(direct != FALL_INT && 0.2 > (clock() - last_move) / CLOCKS_PER_SEC)
        return 0;
    
    last_move = clock();
    
    // EINFUEGEN: Pruefung, ob der Block fuer die Aktion Platz hat
    
    return 1;
}

int try_move(int direct){
    switch(direct){
        case UP_INT:    if(ROTATION_IS_POSSIBLE)
                            ROTATE_BLOCK   
                        else
                            return 0;
                        break;
        case RIGHT_INT: if(RIGHT_IS_POSSIBLE)
                            MOVE_BLOCK_RIGHT 
                        else
                            return 0;    
                        break;
        case DOWN_INT:  if(DOWN_IS_POSSIBLE)
                            MOVE_BLOCK_DOWN
                        else
                            return 0;
                        break;
        case LEFT_INT:  if(LEFT_IS_POSSIBLE)
                            MOVE_BLOCK_LEFT
                        else
                            return 0;
                        break;
        case FALL_INT:  if(FALL_IS_POSSIBLE)
                            MOVE_BLOCK_FALL
                        else
                            return 0;
                        break;
    }
    return 1;
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

void transform_block(){
    // EINFUEGEN: Aktuellen Block entfernen und in Matrix ueberfuehren
}

void create_block(){
    block_num++;
    
    // EINFUEGEN: Block an die Warteschlange anhaengen
}

void spawn_block(){
    // EINFUEGEN: Ersten Block der Warteschlange als aktuellen ins Spielfeld setzen
}

void next_block(){
    transform_block();

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
