#include <FTGL/ftgl.h>

int field[10][22], level, block_num, next_block, del_blocks, points, chain, running;
double delay;
FTGLfont *font;
int try_move(int movetype);
void next_level();
int shuffle(int start, int stop);
int block_to_rgb(int rgb, int *r, int *g, int *b);
void transform_block();
void newqueue();
void spawn_block();
void hsv_to_rgb(const double H, const double S, const double V, unsigned char *R, unsigned char *G, unsigned char *B);
void rgb_to_hsv(unsigned char R, unsigned char G, unsigned char B, double *H, double *S, double *V);
void func_next_block();
void * init(void * thing);
void gen_shadow();
void exit_func();
