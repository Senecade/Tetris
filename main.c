#include "interface.h"
#include "functions.h"
#include "move.h"
#include <stdio.h>
#include "globalshit.h"
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define SDL 0
int main(int argc, char** argv) {
	int R = 255,G = 255,B = 255;
	double H,S,V;
	srandom((unsigned int) time(NULL) * getpid());
	rgb_to_hsv(R,G,B,&H,&S,&V);
	printf("H:%f\nS:%f\nV:%f\n",H,S,V);
	pthread_t functions,interface;
	int error;
	error = pthread_create(&functions,NULL,&init,NULL);
	if(error){
		printf("Error: %d",error);
	}
	if(SDL){
		error = pthread_create(&interface,NULL,&initWindowSDL,NULL);
		if(error){
			printf("Error: %d",error);
		}
	}
	else initWindow(argc,argv);
	return 0;
}
