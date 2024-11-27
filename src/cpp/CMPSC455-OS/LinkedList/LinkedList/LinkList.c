//
//  main.c
//  LinkedList
//
//  Created by Michael DeLeo on 11/27/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>



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
void DisplayList(ListInfo *Linfo);

int main(){
    ListInfo *Linfo = malloc(sizeof(ListInfo)*1);
    Linfo->num_nodes = 0;
    Linfo->first = NULL;
    
    int end_time = 0;
    while(end_time == 0){
        printf("Enter a value to add to the list, Enter -1 to stop: ");
        int value = 0;
        scanf("%d",&value);
        if (value == -1){
            break;
        }
        node * N = malloc(sizeof(node)*1);
        N->data=value;
        Insert(Linfo,N);
    }
    DisplayList(Linfo);
    end_time = 0;
    while(end_time == 0){
        printf("Enter a value to delete from the list, Enter -1 to stop: ");
        int value = 0;
        scanf("%d",&value);
        if (value == -1){
            break;
        }
        Delete(Linfo,value);
    }
    DisplayList(Linfo);
    
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
        N->ID = 0;
    }
    else{   //there is a first node
        while (cursor->next != NULL){
            //iterate through linked list
            cursor = cursor->next;
        }
        //gets last node
        cursor->next = N;
        N->prev = cursor;
        N->ID = cursor->ID + 1;
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
    
    do{
        printf("Node %d Value %d\n",cursor->ID,cursor->data);
        cursor = cursor->next;
    } while (cursor->next != NULL);
    printf("Node %d Value %d\n",cursor->ID,cursor->data);
    return;
}
