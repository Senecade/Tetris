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
	font = ftglCreatePixmapFont("./Dimbo.ttf");
	pthread_t functions,interface;
	srandom((unsigned int) time(NULL) * getpid());
	new_game();
	int error;
	error = pthread_create(&functions,NULL,&gravity,NULL);
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
