//
//  main.c
//  Batch
//
//  Created by Michael DeLeo on 11/27/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>


typedef struct node{
    struct node *next;
    struct node *prev;
    int data;
    int ID;
} node;


typedef struct ListInfo{
    struct node *first;
    int num_nodes;
    
} ListInfo;

void Insert(ListInfo *Linfo, node *N);
void Delete(ListInfo *Linfo, int value);
void DeleteAll(ListInfo *Linfo);
void DisplayList(ListInfo *Linfo);
void DisplayListShort(ListInfo *Linfo);
void check_status(int res);
void *FCFS(void *args);
void *SJF(void *args);
void Sort(ListInfo *Linfo);

pthread_mutex_t LinkList;

int main(){
    ListInfo *Linfo = (ListInfo*)malloc(sizeof(ListInfo)*1);
    Linfo->num_nodes = 0;
    Linfo->first = NULL;
    
    int end_time = 0;
    printf("Enter Your List of Jobs\n");
    while(end_time == 0){
        printf("Enter an ID and a value to add to the list, Enter -1 to stop: ");
        char str[512];
        int value = 0;
        int ID = 0;
        scanf("%s",&str);
        //get the first token, ID
        
        ID = atoi(str);
        scanf("%s",&str);
        value = atoi(str);
        
        if (value == -1){
            break;
        }
        node * N = (node*)malloc(sizeof(node)*1);
        N->data=value;
        N->ID=ID;
        Insert(Linfo,N);
    }
    //List is setup
    
    pthread_t FCFS_thread, SJF_thread;
    check_status(pthread_mutex_init(&LinkList,NULL));
    //initialize threads and mutex
    check_status(pthread_mutex_init(&LinkList, NULL));
    check_status(pthread_create(&FCFS_thread,NULL,FCFS,Linfo));
    check_status(pthread_create(&SJF_thread,NULL,SJF,Linfo));
    
    sleep(1);
    
    //have a signal to show they are done
    //Do FCFS
    pthread_join(FCFS_thread,NULL);

    sleep(1);
    //Do SJF
    pthread_join(SJF_thread,NULL);
    
    DeleteAll(Linfo);
    
    printf("All Threads Completed\n\n");
    
    return 0;
}

void *FCFS(void *args){
    pthread_mutex_lock(&LinkList);
    printf("\n\nFCFS Job Order:\nFCFS Jobs will be executed in the order they arrived:\n");
    DisplayList(args);
    printf("FCFS Done\n\n");
    pthread_mutex_unlock(&LinkList);
    return 0;
}

void *SJF(void *args){
    sleep(2);
    
    pthread_mutex_lock(&LinkList);
    Sort(args);
    printf("SJF Jobs Order:\n");
    DisplayListShort(args);
    printf("SJF : All Jobs completed\n");
    pthread_mutex_unlock(&LinkList);
    return 0;
}



//////////////////////////////////////
//Precondition:
//Postcondition:
//Summary:
//////////////////////////////////////
void Insert(ListInfo *Linfo, node *N){
    node *cursor = Linfo->first;    //assign to first node
    if (Linfo->first == NULL){  //if there is no first node, make one
        Linfo->first = N;
        N->prev = NULL;
    }
    else{   //there is a first node
        while (cursor->next != NULL){
            //iterate through linked list
            cursor = cursor->next;
        }
        //gets last node
        cursor->next = N;
        N->prev = cursor;
    }
    
    //assign values that are not dependent on it being the first node
    Linfo->num_nodes = Linfo->num_nodes + 1;
    N->next = NULL;
    return;
}

//////////////////////////////////////
//Precondition:
//Postcondition:
//Summary:
//////////////////////////////////////
void Delete(ListInfo *Linfo, int value){
    node *cursor = Linfo->first;
    if (cursor == NULL){
        printf("Error: Cannot Delete nonexistent Node");
        return;
    }
    
    do{
        //iterate through list
        if (cursor->data == value){
            break;
        }
        cursor = cursor->next;
    } while(cursor->next != NULL);
    //cursor is now at the node with the value
    
    //Only one node left
    if (Linfo->num_nodes == 1){
        free(cursor);
        Linfo->first = NULL;
    }
    
    //check if the node is the last
    else if (cursor->next == NULL){
        cursor->prev->next = NULL;  //previous node is now final node
        cursor->next = NULL;
        cursor->prev = NULL;
        free(cursor);
        
    }
    //check if the node is the first
    else if (cursor->prev == NULL){
        cursor->next->prev = NULL;
        Linfo->first = cursor->next;
        cursor->next = NULL;
        free(cursor);
        
    }
    //node is in the middle somewhere
    else{
        cursor->prev->next = cursor->next;  //connect previous node to next node
        cursor->next->prev = cursor->prev;  //connect next node to previous node
        cursor->next = NULL;
        cursor->prev = NULL;
        free(cursor);  //free the node
    }
    
    Linfo->num_nodes = Linfo->num_nodes - 1;
    
    return;
}


void DeleteAll(ListInfo *Linfo){
    while(Linfo->num_nodes > 0){
        Delete(Linfo,Linfo->first->data);
    }
    free(Linfo);
    return;
}

//////////////////////////////////////
//Precondition:
//Postcondition:
//Summary:
//////////////////////////////////////
void DisplayList(ListInfo *Linfo){
    node *cursor = Linfo->first;
    printf("Linked List contain the following values:\nNumber of Nodes: %d\n",Linfo->num_nodes);
    if (cursor == NULL){
        return;
    }
    
    while (cursor->next != NULL){
        printf("Node ID %d With Value %d\n",cursor->ID,cursor->data);
        cursor = cursor->next;
    }
    printf("Node ID %d With Value %d\n",cursor->ID,cursor->data);
    return;
}

//////////////////////////////////////
//Precondition:
//Postcondition:
//Summary:
//////////////////////////////////////
void DisplayListShort(ListInfo *Linfo){
    node *cursor = Linfo->first;
    printf("Linked List contain the following values:\nNumber of Nodes: %d\n",Linfo->num_nodes);
    if (cursor == NULL){
        return;
    }
    
    while (cursor->next != NULL){
        printf("Shortest Job to run next is with ID: %d and Time: %d\n",cursor->ID,cursor->data);
        cursor = cursor->next;
    }
    printf("Shortest Job to run next is with ID: %d and Time: %d\n",cursor->ID,cursor->data);
    return;
}

void check_status(int res){
    if (res != 0) {
        perror("Failed");
        exit(EXIT_FAILURE);
    }
}



void Sort(ListInfo *Linfo){
    //Bubble Sort
    node* cursor = Linfo->first;
    int index = Linfo->num_nodes;
    //now i have the size
    cursor = Linfo->first;
    while (index>=0) {
        int j = 0;
        while(j < index-1){
            if (cursor->data > cursor->next->data){
                printf("switch\n");
                int temp = cursor->data;
                cursor->data = cursor->next->data;
                cursor->next->data=temp;
            }
            j++;
        }
        index--;
    }
    return;
}
