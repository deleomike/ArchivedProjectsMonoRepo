//
//  main.c
//  winner
//
//  Created by Michael DeLeo on 10/9/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

//two.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
    int gen = 0; //num. generations removed from original process
    int forknum = 0;
    int status;
    //fork #1
    
    //printf("%d is the root process\n",getpid());
    
    
    int pid = fork();
    if (pid == 0) {
        //only the child can be here
        //printf("%d has pid 0",getpid());
        forknum = 1;
        gen++;
    }else wait(&status);
    
    //fork #2
    
    pid = fork();
    if (pid== 0) {
        forknum = 2;
        gen++;
    }else wait(&status);
    
    pid = fork();
    if (pid == 0){
        forknum = 3;
        gen++;
    }else wait(&status);
    
    printf("gen=%d:fork=%d:pid=%d:ppid=%d\n", gen, forknum, getpid(), getppid());
    return 0;
}
