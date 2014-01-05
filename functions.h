//possible @move.h
//rotate @move.h
int field[10][22];
int try_move(int movetype);
void next_level();
int shuffle(int start, int stop);
int block_to_rgb(int rgb, int *r, int *g, int *b);
void transform_block();    
void newqueue();
void spawn_block();
void func_next_block();
void init();
