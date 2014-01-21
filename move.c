#include "struct.h"
#include "globalshit.h"
#include "functions.h"
#include <stdio.h>

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
	else if (movetype == SHADOW_FALL_INT) {
		for(int i=0;i<4;i++) {
			x = ActiveBlox.x + ActiveBlox.Blox.points[i][X];
			y = ActiveBlox.y + ActiveBlox.Blox.points[i][Y] + 1 + ActiveBlox.shadow_offset;
			if (y<0 || y>21 || x<0 || x>9 || field[x][y] % 2 == 1) return FALSE;
		}
	}
	return TRUE;
}

int destroy_rows(int type) {
	int full, todo = FALSE, rows = 0;
	for (int y = 0; y < 22; y++) {
		full = TRUE;
		for (int x = 0; x < 10; x++) {
			if (field[x][y] % 2 == 0) {
				full = FALSE;
				break;
			}
		}
		if (type == MARK_ROWS_INT && full) {
			todo = TRUE;
			for (int v = 0; v<10; v++) field[v][y] = RGB_INT(255,255,255);
		}
		if (type == DEL_ROWS_INT && full) {
			rows++;
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
	lines += rows;
	lvl_blox += rows;
	char strchain[50];
	switch (rows) {
		case 4:
			points += 1000 * (1 + chain++ / 10.0);
			change_message("- Tetris -");
			break;
		case 3:
			points += 600 * (1 + chain++ / 10.0);
			break;
		case 2:
			points += 300 * (1 + chain++ / 10.0);
			break;
		case 1:
			points += 100 * (1 + chain++ / 10.0);
			break;
		default: break;
	}
	if(chain > 1) {
		sprintf(strchain,"- chain +%d -",chain - 1);
		change_message(strchain);
	}
	if (lvl_blox >= level * BLOCKS_PER_LEVEL) {
		change_message("- Level up -");
		lvl_blox -= level++ * BLOCKS_PER_LEVEL;
		next_level();
	}
	return todo;
}
