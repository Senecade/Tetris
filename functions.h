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
#define MOVE_BLOCK_DOWN ActiveBlox.y++;
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

int field[10][20] = {0}, block_num = 0, level = 0, delay = 1000;
clock_t last_move = 0;
char running = 1, next_block = 0;

void rotate(int direct) {
    int hx,hy,n = ActiveBlox.Blox.size - 1;
    
    for(int i = 0; i < 4; i++){
        hx = ActiveBlox.Blox.points[i][X];
        hy = ActiveBlox.Blox.points[i][Y];
        
        if (direct == ROTATION_LEFT_INT){
            ActiveBlox.Blox.points[i][X] = n - hy;
            ActiveBlox.Blox.points[i][Y] = hx;
        }
        else{
            ActiveBlox.Blox.points[i][X] = hy;
            ActiveBlox.Blox.points[i][Y] = n - hx;
        }
    }
}

int possible(int direct){
    if(direct != FALL_INT && 0.2 > (clock() - last_move) / CLOCKS_PER_SEC)
        return FALSE;
    
    last_move = clock();
    
    // EINFUEGEN: Pruefung, ob der Block fuer die Aktion Platz hat
    
    return TRUE;
}

int try_move(int direct){
    if(possible(direct) == FALSE)
        return FALSE;
    
    switch(direct){
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

void transform_block(){
    // EINFUEGEN: Aktuellen Block entfernen und in Matrix ueberfuehren
}

void spawn_block(){
    block_num++;
    
    ActiveBlox.x = 5;
    ActiveBlox.y = 0;
    
    for(int i = 0; i < 4; i++){
        ActiveBlox.Blox.points[i][X] = Block[next_block].points[i][X];
        ActiveBlox.Blox.points[i][Y] = Block[next_block].points[i][Y];
    }
    
    ActiveBlox.Blox.rgb = Block[next_block].rgb;
    ActiveBlox.Blox.size = Block[next_block].size;
    
    next_block = shuffle(0, 6);
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
