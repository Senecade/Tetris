#include "globalshit.h"
struct Blox {
	int points[4][2];
	int rgb;
	int size;
};
struct Blox Block[7] = {
			{
				{
					{ 0, 1 }, //____
					{ 1, 1 }, //XXXX
					{ 2, 1 }, //____
					{ 3, 1 } //____
				},
				RGB_INT(0, 255, 255), // 0, 255, 255
				4
			}, // I
			{
				{
					{ 0, 0 }, //X__
					{ 0, 1 }, //XXX
					{ 1, 1 }, //___
					{ 2, 1 }
				},
				RGB_INT(0, 0, 255), // 0, 0, 255

				3
			}, // J
			{
				{
					{ 2, 0 }, //__X
					{ 0, 1 }, //XXX
					{ 1, 1 }, //___
					{ 2, 1 }
				},
				RGB_INT(255, 165, 0), // 255, 165, 0
				3
			}, // L
			{
				{
					{ 0, 0 }, //XX
					{ 0, 1 }, //XX
					{ 1, 0 },
					{ 1, 1 }
				},
				RGB_INT(255, 255, 0), // 255, 255, 0
				2
			}, // O
			{
				{
					{ 1, 0 }, //_XX
					{ 2, 0 }, //XX_
					{ 0, 1 }, //___
					{ 1, 1 }
				},
				RGB_INT(0, 255, 0), // 0, 255, 0
				3
			}, // S
			{
				{
					{ 1, 0 }, //_X_
					{ 0, 1 }, //XXX
					{ 1, 1 }, //___
					{ 2, 1 }
				},
				RGB_INT(160, 32, 240), // 160, 32, 240
				3
			}, // T
			{
				{
					{ 0, 0 }, //XX_
					{ 1, 0 }, //_XX
					{ 1, 1 }, //___
					{ 2, 1 }
				},
				RGB_INT(255, 0, 0), // 255, 0, 0
				3
			} // Z
		};

struct Active {
    	int x;
    	int y;
	int shadow_offset;
    	struct Blox Blox;
};

struct Active ActiveBlox;

int queue[14];

