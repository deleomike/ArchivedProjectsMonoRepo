#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct numlist{
    int *list;
    int len;
    int min;
    int max;
    float avg;
}numlist;

void populate(numlist *nl){
    //prompt
    printf("Enter the length of the numlist: ");
    int len;
    scanf("%d", &len);
    nl->len = len;
    
    //have user enter len numbers
    nl->list = malloc(sizeof(int) * len);
    int i = 0;
    while (i < len){
        printf("Enter a Number: ");
        int temp;
        scanf("%d", &temp);
        nl->list[i] = temp;
        i++;
    }
    
    //calculate
    i = 0;
    int min_ = nl->list[0];
    int max_ = nl->list[0];
    float avg = 0;
    while (i < len){
        if (nl->list[i] > max_){
            max_ = nl->list[i];
        }
        if (nl->list[i] < min_){
            min_ = nl->list[i];
        }
        avg = nl->list[i] + avg;
        i++;
    }
    nl->min = min_;
    nl->max = max_;
    nl->avg = avg / len;
    //done calculating
    
    printf("numlist::list = {");
    i = 0;
    while (i < len){
        printf("%d,",nl->list[i]);
        i++;
    }
    printf("}\n");
    
    printf("numlist::len = %d\n",len);
    printf("numlist::min = %d\n",nl->min);
    printf("numlist::max = %d\n",nl->max);
    printf("numlist::avg = %f\n",nl->avg);
    return;
}

int main(){
    numlist *x = malloc(sizeof(struct numlist)*1);
    populate(x);
}
