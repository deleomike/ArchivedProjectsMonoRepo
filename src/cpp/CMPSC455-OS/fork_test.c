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


int main() {
    
    fork();
    fork();
    fork();
    
    printf("hello world!\n");
    
    
    return 0;
}
