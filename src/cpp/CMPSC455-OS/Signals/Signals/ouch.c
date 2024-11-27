//
//  main.c
//  Signals
//
//  Created by Michael DeLeo on 10/9/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void ouch(int sig){
    printf("OUCH! - I got signal %d\n",sig);
    (void) signal(SIGINT, SIG_DFL);
    //SIGINT is terminal interrupt
    //SIG_DFL resets the signal
    return;
}

int main() {

    (void) signal(SIGINT, ouch);
    while(1){
        printf("Hello World!\n");
        sleep(1);
    }
    return 0;
}
