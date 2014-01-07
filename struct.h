struct Blox {
	int points[4][2];
	int rgb;	
	int size;
};
struct Blox Block[7];

struct Active {
    	int x;
    	int y;
	int shadow_offset;
    	struct Blox Blox;
};

struct Active ActiveBlox;

int queue[7];
