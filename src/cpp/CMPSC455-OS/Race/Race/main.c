//
//  main.c
//  Race
//
//  Created by Michael DeLeo on 10/9/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int sig){
    
    
    pid_t pid = getpid();
    int i = 1;
    while(i < 100){
        printf("%d:%d\n",pid,i);
        i++;
    }
    printf("%d:DONE\n",pid);
    (void) signal(SIGINT,SIG_DFL);
    exit(0);
}

int main() {
    
    pid_t pid;
    //sleep(2);
    pid = fork();
    pid = fork();   //total four processes
    
    //printf("Ready:%d\n",pid);
    fflush(stdout);
    
    (void) signal(SIGINT,handler);
    
    
    while(1)
    {}
    
    
    return 0;
}
