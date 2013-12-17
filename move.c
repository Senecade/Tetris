typedef struct Blox {
	int points[4][2];
	char rgb[3];
	int size;
} Block[7] = {
	{
		{ 
	    		{ 0, 0 } //X___
	    		{ 0, 1 } //X___
	   		{ 0, 2 } //X___
	    		{ 0, 3 } //X___
		},
		{ 0, 191, 255 },
		4
    	}, // I
    	{
		{ 
	    		{ 2, 0 } //__X
	    		{ 2, 1 } //__X
	    		{ 2, 2 } //_XX
	    		{ 1, 2 }
		},
		{ 0, 0, 139 },
		3
    	}, // J
    	{
		{ 
	    		{ 0, 0 } //X__
	    		{ 0, 1 } //X__
			{ 0, 2 } //XX_
	    		{ 1, 2 }
		},
		{ 255, 127, 0 },
		3
    	}, // L
    	{
		{ 
	    		{ 0, 0 } //XX
	    		{ 0, 1 } //XX
	    		{ 1, 0 } 
	    		{ 1, 1 }
		},
		{ 255, 255, 0 },
		2
    	}, // O
    	{
		{ 
	    		{ 0, 0 } //X__
	    		{ 0, 1 } //XX_
	    		{ 1, 1 } //_X_
	    		{ 1, 2 }
		},
		{ 0, 255, 0 },
		3
    	}, // S
    	{
		{ 
	    		{ 0, 0 } //XXX
	    		{ 1, 0 } //_X_
	    		{ 2, 0 } //___
	    		{ 1, 1 }
		},
		{ 139, 0, 139},
		3
    	}, // T
    	{
		{ 
	    		{ 0, 0 } //XX_
	    		{ 1, 0 } //_XX
	    		{ 2, 0 } //___
	    		{ 1, 1 }
		},
		{ 255, 0, 0 },
		3
    		} // Z
	};

typedef struct Active {
    	int x;
    	int y;
    	struct Blox;
};

struct Active ActiveBlox

int queue;

int turn(int direct) {
    	int hx,hy,n = ActiveBlox.Blox.size - 1;
    	for (int i = 0,i<4,i++) {
		hx = ActiveBlox.Blox.points[i][X];
		hy = ActiveBlox.Blox.points[i][Y];
		if (direct == LEFT_INT) {
			ActiveBlox.Blox.points[i][X] = n - hy;	
			ActiveBlox.Blox.points[i][Y] = hx;
		}
		else {
	   		ActiveBlox.Blox.points[i][X] = hy; 
			ActiveBlox.Blox.points[i][Y] = n - hx;
		}
    	}
}
