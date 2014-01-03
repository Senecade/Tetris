#include <stdio.h>

int main() {
	printf("%d\n",(((0 <<8) + 255 <<8) + 255<<1) + 1); // 0, 255, 255
	return 0;
}
