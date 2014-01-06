#include "interface.h"
#include "functions.h"
#include "move.h"
#include <stdio.h>
#include "globalshit.h"
#include <pthread.h>

int main(int argc, char** argv) {
    pthread_t functions;
    int error;
    error = pthread_create(&functions,NULL,init,NULL);
    if(error){
        printf("Error: %d",error);
    }
    initWindow(argc,argv);
    return 0;
}
