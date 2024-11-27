//
//  main.c
//  Sort_Numbers
//
//  Created by Michael DeLeo on 11/27/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

void check_status(int res, int type);
void *Count(void *args);
void *Capital(void *args);
void *Reverse(void *args);
void sort(void);

char arr[512];
int size;
int end_time;

sem_t flag_sem,count_sem,cap_sem,rev_sem,main_sem;

int main(){
    
    end_time = 0;
    
    pthread_t count_thread,capital_thread,rev_thread;
    
    check_status(sem_init(&count_sem,0,0),1);
    check_status(sem_init(&cap_sem,0,0),1);
    check_status(sem_init(&rev_sem,0,0),1);
    check_status(sem_init(&main_sem,0,0),1);
    check_status(sem_init(&flag_sem,0,1),1);
    check_status(pthread_create(&count_thread,NULL,Count,NULL),2);
    check_status(pthread_create(&capital_thread,NULL,Capital,NULL),2);
    check_status(pthread_create(&rev_thread,NULL,Reverse,NULL),2);
    while(1){
        printf("Enter a String, type end to stop: ");
        scanf("%s",&arr);
        //printf("done\n");
        sem_wait(&flag_sem);
        if (strcmp(arr,"end") == 0){
            printf("h");
            end_time = 1;
        }
        sem_post(&flag_sem);
        sem_post(&count_sem);
        sem_wait(&main_sem);
        //printf("back\n");
        //printf("done waiting\n");
        
        //printf("wait\n");
        //sem_wait(&flag_sem);
        if (end_time == 1){
            break;
        }
        else{
        }
        
    }
    
    pthread_join(count_thread,NULL);
    pthread_join(capital_thread,NULL);
    pthread_join(rev_thread,NULL);
    sem_destroy(&count_sem);
    sem_destroy(&rev_sem);
    sem_destroy(&cap_sem);
    sem_destroy(&main_sem);
    
    return 0;
    
}


void *Count(void *args){
    while (1){
        sem_wait(&count_sem);
        printf("Number of Characters in this string is: %d\n",strlen(arr));
        size = strlen(arr);
        sem_post(&cap_sem);
        
        sem_wait(&flag_sem);
        if (end_time == 1){
            sem_post(&flag_sem);
            break;
        }
        sem_post(&flag_sem);
    }
    return 0;
}

void *Capital(void *args){
    while(1){
        sem_wait(&cap_sem);
        int i = 0;
        printf("All Letters are capital: ");
        
        while (i < size){
            if (arr[i] >= 65 && arr[i] <= 90){
                printf("%c",arr[i]);
            }
            else{
                arr[i] = arr[i] - 32;
                printf("%c",arr[i]);
            }
            i++;
        }
        printf("\n");
        sem_post(&rev_sem);
        
        sem_wait(&flag_sem);
        if (end_time == 1){
            sem_post(&flag_sem);
            break;
        }
        sem_post(&flag_sem);
    }
}

void *Reverse(void *args){
    while(1){
        sem_wait(&rev_sem);
        
        printf("Reversed String: ");
        
        
        char str[5] = "hello";
        int i =  size-1;
        
        while (i >= 0){
            printf("%c",arr[i]);
            i--;
        }
        printf("\n");
        /*
         while(i < 5){
         printf("%s",arr[i]);
         i++;
         }
         /*
         i = strlen(size)-1;
         while (i >= 0){
         printf("%c",arr[i]);
         i--;
         }*/
        
        sem_post(&main_sem);
        
        sem_wait(&flag_sem);
        if (end_time == 1){
            sem_post(&flag_sem);
            break;
        }
        sem_post(&flag_sem);
        
    }
}

void check_status(int res, int type){
    if (res != 0) {
        if (type == 0){
            perror("Failed: Mutex");
        }
        else if (type == 1){
            perror("Failed: Semaphore");
        }
        else if (type == 2){
            perror("Failed: Thread");
        }
        exit(-1);
    }
}
