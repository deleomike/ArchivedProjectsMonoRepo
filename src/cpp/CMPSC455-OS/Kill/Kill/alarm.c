//
//  main.c
//  Kill
//
//  Created by Michael DeLeo on 10/9/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired = 0;

void ding(int sig){
    alarm_fired = 1;
    return;
}

int main() {
    pid_t pid;
    
    printf("alarm application starting\n");
    
    pid = fork();
    switch(pid){
    case -1:
        /* failure */
        perror("fork failed");
        exit(1);
    case 0:
        /*child*/
        sleep(5);
        kill(getppid(), SIGALRM);
        printf("It is over, %d. I have the high ground.\n",getppid());
        exit(0);
    }
    
    //the parent process then arranges to catch sigalrm with a call to signal and then waits for the inevitable
    
    printf("%d waiting for alarm to go off\n", getpid());
    (void) signal(SIGALRM, ding);
    
    pause();
    if (alarm_fired){
        printf("Ding\n");
    }
    
    printf("done\n");
    exit(0);

}
