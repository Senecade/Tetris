#include "interface.h"
#include "functions.h"
#include "move.h"
#include <stdio.h>
#include "globalshit.h"
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define SDL 1

int main(int argc, char** argv) {
	pthread_t functions;
	srandom((unsigned int) time(NULL) * getpid());
	int error;
	error = pthread_create(&functions,NULL,&init,NULL);
	if(error){
		printf("Error: %d",error);
	}
	if(SDL)initWindowSDL();
	else initWindow(argc,argv);
	return 0;
}
