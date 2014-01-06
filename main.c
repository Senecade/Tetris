#include "interface.h"
#include "functions.h"
#include "move.h"
#include <stdio.h>
#include "globalshit.h"
#include <pthread.h>

#define SDL 0

int main(int argc, char** argv) {
    pthread_t functions,interface;
    int error;
    error = pthread_create(&functions,NULL,init,NULL);
    if(error){
        printf("Error: %d",error);
    }
    if(SDL){
        initWindowSDL();
    }
    else initWindow(argc,argv);
    return 0;
}
