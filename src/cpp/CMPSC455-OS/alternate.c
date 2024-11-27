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
    
    
    int pid_0 = getpid();
    int pid_1 = 0;  //root process will have this value
    int pid_2 = -1;
    
    int pid = fork();
    if (pid == 0) {
        //only the child can be here
        //printf("%d has pid 0",getpid());
        pid_1 = getpid();  //now the second process id has been stored
        forknum = 1;
        gen++;
    }else wait(&status);
    

    //fork #2
    pid = 1;
    if (pid_1 == getpid()){ //First Control
        pid = fork();   //second process is now a parent, and not the first
    }
    
    if (pid== 0) {
        forknum = 2;
        gen++;
    }else wait(&status);
    
    pid = 1;
    pid = fork();
    if (pid == 0){
        if (getppid() == pid_0){
            pid_2 = getpid();
        }
        forknum = 3;
        gen++;
    }else wait(&status);

    pid = 1;
    if ((getpid() == pid_2 && forknum == 3) || (getppid() == pid_1 && forknum == 3)){  //SECOND CONTROL
        pid = fork();
    }
    
    if (pid == 0){
        forknum = 4;
        gen++;
    }else wait(&status);
    
    
    printf("gen=%d:fork=%d:pid=%d:ppid=%d\n", gen, forknum, getpid(), getppid());
    return 0;
}
