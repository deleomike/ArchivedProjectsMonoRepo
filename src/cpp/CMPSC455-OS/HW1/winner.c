//
//  main.c
//  winner
//
//  Created by Michael DeLeo on 10/9/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <regex.h>

int arrEq(const int sz, char * t, char * y);
#define BUFFERSIZE 100

int main() {
    // insert code here...
    //printf("Ready");
    fflush(stdout);
    
    int process[4] = {0,0,0,0};
    int winners[4] = {0,0,0,0};
    
    //using regex to find done
    //
    int i = 0;
    int counter = 0;
    while(i < 400){
        char buffer[BUFFERSIZE];
        fgets(buffer, BUFFERSIZE , stdin);
        //printf("Read: %s", buffer);
        regex_t rex;
        int regint = regcomp(&rex,"\DONE",0);
        
        if (regint){
            
        }
        
        
        regint = regexec(&rex,buffer,0,NULL,0);
        if (!regint){

            process[counter] = i+1;
            char temp[100];
            int j = 0;
            while(j < 100){
                if (':' != buffer[j]){
                    temp[j] = buffer[j];
                }
                else{
                    break;
                }
                j++;
            }
            winners[counter] = atoi(temp);
            //printf("match: %d\n", winners[counter]);
            counter++;
            
        }
        if (counter ==4){
            break;
        }

        i++;
        
    }
    
    printf("%d is the Winner!\n",winners[0]);
    printf("%d is Second! %d lines behind\n",winners[1],process[1]-process[0]);
    printf("%d is Third! %d lines behind\n",winners[2],process[2]-process[1]);
    printf("%d is Last! %d lines behind\n",winners[3],process[3]-process[2]);
    
    
    return 0;
}
