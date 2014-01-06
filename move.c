#include "struct.h"
#include "globalshit.h"
#include "functions.h"

void rotate(int direct) {
    	int hx,hy,n = ActiveBlox.Blox.size - 1;
    	for (int i = 0;i<4;i++) {
		hx = ActiveBlox.Blox.points[i][X];
		hy = ActiveBlox.Blox.points[i][Y];
		if (direct == ROTATION_LEFT_INT) {
			ActiveBlox.Blox.points[i][X] = n - hy;	
			ActiveBlox.Blox.points[i][Y] = hx;
		}
		else {
	   		ActiveBlox.Blox.points[i][X] = hy; 
			ActiveBlox.Blox.points[i][Y] = n - hx;
		}
    	}
}

int possible(int movetype) {
	int x,y;
	if (movetype == FALL_INT) {
		for(int i=0;i<4;i++) {
			x = ActiveBlox.x + ActiveBlox.Blox.points[i][X];
			y = ActiveBlox.y + ActiveBlox.Blox.points[i][Y] + 1;
			if (y<0 || y>21 || x<0 || x>9 || field[x][y] % 2 == 1) return FALSE;
		}
	}
	else if (movetype == RIGHT_INT) {
		for(int i=0;i<4;i++) {
			x = ActiveBlox.x + ActiveBlox.Blox.points[i][X] + 1;
			y = ActiveBlox.y + ActiveBlox.Blox.points[i][Y];
			if (y<0 || y>21 || x<0 || x>9 || field[x][y] % 2 == 1) return FALSE;
		}
	}
	else if (movetype == LEFT_INT) {
		for(int i=0;i<4;i++) {
			x = ActiveBlox.x + ActiveBlox.Blox.points[i][X] - 1;
			y = ActiveBlox.y + ActiveBlox.Blox.points[i][Y];
			if (y<0 || y>21 || x<0 || x>9 || field[x][y] % 2 == 1) return FALSE;
		}
	}
	else if (movetype == ROTATION_RIGHT_INT) {
		int n = ActiveBlox.Blox.size - 1;
		for(int i=0;i<4;i++) {
			x = ActiveBlox.x + ActiveBlox.Blox.points[i][Y];
			y = ActiveBlox.y + n - ActiveBlox.Blox.points[i][X];
			if (y<0 || y>21 || x<0 || x>9 || field[x][y] % 2 == 1) return FALSE;
		}
	}
	else if (movetype == ROTATION_LEFT_INT) {
		int n = ActiveBlox.Blox.size - 1;
		for(int i=0;i<4;i++) {
			x = ActiveBlox.x + n - ActiveBlox.Blox.points[i][Y];
			y = ActiveBlox.y + ActiveBlox.Blox.points[i][X];
			if (y<0 || y>21 || x<0 || x>9 || field[x][y] % 2 == 1) return FALSE;
		}
	}
	//DOWN_INT geht immer
	return TRUE;
}

void destroy_rows() {
	int full,ypos;
	for (int y = 0; y < 22; y++) {
		full = TRUE;
		for (int x = 0; x < 10; x++) {
			if (field[x][y] % 2 == 0) {
				full = FALSE;
				break;
			}
		}
		if (full) {
			del_blocks++;
			for (int v = 0; v < 10; v++) field[v][y] = 0;
			for (int w = y; w >= 0; w--) {
				for (int v = 0; v < 10; v++) {
					if (w == 0) {
						field[v][w] = 0;
					}
					else {
						field[v][w] = field[v][w - 1];
						field[v][w - 1] = 0;
					}
				}

			}
		}
	}
	ypos = del_blocks / BLOCKS_PER_LEVEL; //Recycling
	if (ypos > level) {
		level = ypos;
		next_level();
	}
	return;
}
