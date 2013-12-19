void rotate(int direct) {
    	int hx,hy,n = ActiveBlox.Blox.size - 1;
    	for (int i = 0,i<4,i++) {
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
			y = ActiveBlox.x + ActiveBlox.Blox.points[i][Y] + 1;
			if (y>21 || field[x][y] % 2 == 1) return FALSE;
		}
	}
	else if (movetype == RIGHT_INT) {
		for(int i=0;i<4;i++) {
			x = ActiveBlox.x + ActiveBlox.Blox.points[i][X] + 1;
			y = ActiveBlox.x + ActiveBlox.Blox.points[i][Y];
			if (x>19 || field[x][y] % 2 == 1) return FALSE;
		}
	}
	else if (movetype == LEFT_INT) {
		for(int i=0;i<4;i++) {
			x = ActiveBlox.x + ActiveBlox.Blox.points[i][X] - 1;
			y = ActiveBlox.x + ActiveBlox.Blox.points[i][Y];
			if (x<0 || field[x][y] % 2 == 1) return FALSE;
		}
	}
	else if (movetype == ROTATION_RIGHT_INT) {
		int n = ActiveBlox.Blox.size - 1;
		for(int i=0;i<4;i++) {
			x = ActiveBlox.x + ActiveBlox.Blox.points[i][Y];
			y = ActiveBlox.x + n - ActiveBlox.Blox.points[i][X];
			if (field[x][y] % 2 == 1) return FALSE;
		}
	}
	else if (movetype == ROTATION_LEFT_INT) {
		int n = ActiveBlox.Blox.size - 1;
		for(int i=0;i<4;i++) {
			x = ActiveBlox.x + n - ActiveBlox.Blox.points[i][Y];
			y = ActiveBlox.x + ActiveBlox.Blox.points[i][X];
			if (field[x][y] % 2 == 1) return FALSE;
		}
	}
	//DOWN_INT geht immer
	return TRUE;
}
