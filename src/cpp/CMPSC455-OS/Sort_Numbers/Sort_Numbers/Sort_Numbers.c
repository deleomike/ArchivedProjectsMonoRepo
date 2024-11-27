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
#include <string.h>
#include <semaphore.h>

void check_status(int res, int type);
void *Sort_Display(void *args);
void sort(void);

int arr[5];
int end_time;

pthread_mutex_t arr_mx;
sem_t flag_sem;

int main(){
    
    end_time = 0;
    
    pthread_t sort_thread;
    
    check_status(pthread_mutex_init(&arr_mx, NULL),0);
    check_status(sem_init(&flag_sem,0,0),1);
    check_status(pthread_create(&sort_thread,NULL,Sort_Display,NULL),2);
    int iterations = 0;
    pthread_mutex_lock(&arr_mx);
    while(1){
        if (iterations == 0){
            //already locked
            //sem_post(&flag_sem);
            
        }
        else{
            //pthread_mutex_lock(&arr_mx);
        }
        printf("Enter 5 Numbers: ");
        char str[512];
        int i = 0;
        while (i < 5){
            scanf("%s",&str);
            arr[i] = atoi(str);
            i++;
        }
        //printf("done\n");
        pthread_mutex_unlock(&arr_mx);
        
        //sleep(3);
        sem_wait(&flag_sem);
        //printf("done waiting\n");
        
        pthread_mutex_lock(&arr_mx);
        //printf("wait\n");
        //sem_wait(&flag_sem);
        printf("Would you like to continue? Enter (0) Yes, Enter (1) No: ");
        scanf("%d",&end_time);
        if (end_time == 1){
            sem_post(&flag_sem);
            break;
        }
        else{
            sem_post(&flag_sem);
        }
        iterations++;
    }
    
    pthread_join(sort_thread,NULL);
    sem_destroy(&flag_sem);
    
    return 0;
    
}


void *Sort_Display(void *args){
    while (1){
        //printf("sort_display\n");
        //TODO sort, and display
        pthread_mutex_lock(&arr_mx);
        sem_post(&flag_sem);
        sort();
        int i = 0;
        printf("Sort Array: ");
        while (i < 4){
            printf("%d, ",arr[i]);
            i++;
        }
        printf("%d\n",arr[i]);
        pthread_mutex_unlock(&arr_mx);
        
        sem_wait(&flag_sem);
        if (end_time == 1){
            //sem_post(&flag_sem);
            break;
        }
        else{
            //sem_post(&flag_sem);
        }
    }
    return 0;
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

void sort(void){
    //Bubble Sort
    //printf("sorting...\n");
    int index = 5;
    
    while (index >= 0){
        int j = 0;
        while (j < index - 1){
            if (arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
            j++;
        }
        index--;
    }
    //printf("done sorting\n");
    return;
}
