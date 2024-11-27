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
    
    int pid = 1;
    int i = 0;
    while (i < 3){
        //selects only the current row of the pyramid
        if (gen == i){
            //do left side
            pid_0 = getpid();   //this is the local root
            pid = fork();
            if (pid == 0){
                //corrupt local root
                pid_0 = -1;
                
                if (forknum%2 == 0){
                    //the fork is even, it is the right side branch
                    forknum++;
                }
                else{
                    //the fork is odd, it is the left side branch
                    forknum = forknum + 2;
                }
                gen++;
            }else wait(&status);
        
        
        
            //do right side
            pid = 1;
            if (pid_0 == getpid()){ //FIRST CONTROL
                pid = fork();
            }
            
            if (pid == 0){
                
                if (forknum%2 == 0){
                    //forknum is even, only add two
                    forknum = forknum + 2;
                }
                else{
                    //forknum is odd, add three
                    forknum = forknum + 3;
                }
                gen++;
            }else wait(&status);
        }
        
        i++;
    }
    
    
    printf("gen=%d:fork=%d:pid=%d:ppid=%d\n", gen, forknum, getpid(), getppid());
    return 0;
}
