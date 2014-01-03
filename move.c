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

int destroy_rows(int output) {
	int max = -1, ypos = -1, length = 0, full;
	for (int y = 0; y<22;x++) {
		full = TRUE;
		for (int x = 0; x<10;y++) {
			if (max != -1 && field[x][y] % 2 == 1) max = y;
			if (field[x][y] % 2 == 0 && full) full = FALSE;
		}
		if (full) {
			length++;
			if (ypos == -1) ypos = y;
		}
	}
	if (length == 0) return FALSE;
	if (output == CHANGE_INT) {
		for (int y = ypos; y < ypos + length; y++) {
			for (int x = 0; x<10;x++) field[x][y] = (((255 <<8) + 255 <<8) + 255 <<1) + 1;
		} // Felder weiß setzen (als Löschanzeige)
	}
	else {
		for (int y = ypos; y < ypos + length; y++) {
			for (int x = 0; x<10;x++) field[x][y] = 0;
		} //Felder löschen
		for (int y = ypos - 1;y>=max;y--) //Rückwärts durchlaufen um richtig zu kopieren
			for (int x = 0; x<10; x++) {
				field[x][y + length] = field[x][y];
			}
	}
	return TRUE;
}
