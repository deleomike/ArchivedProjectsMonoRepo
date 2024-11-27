//
//  main.c
//  billion
//
//  Created by Michael DeLeo on 10/9/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>



long count;


void handler(int sig){
    
    (void) signal(SIGINT,SIG_DFL);
    printf("You were stopped at: %ld \n", count);
    printf("You were off by: %d \n", abs(1000000000-count));
    exit(0);
}



int main() {
    count = 0;
    printf("Try to hit 1 Billion!");
    (void) signal(SIGINT,handler);

    while(1){
        count++;
    }

    return 0;
}
