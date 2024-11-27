//
//  main.c
//  Lab6
//
//  Created by Michael DeLeo on 10/2/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <stdio.h>


int main(){
    while(1){
        printf("Please select a choice\n");
        printf("Numical Conversion: A\n");
        printf("Convert Decimal Values to String: B\n");
        printf("Exit: C\n");
        
        char input[2];
        
        scanf("%s",input);
        getchar();
        //numerical conversion
        if (input[0] == 'A'){
            printf("Please enter a string");
            
            char word[30];
            scanf("%s",word);   //NEEDS TO ACCEPT WHITESPACE
            
            char * list[3][30];
            list[0][0] = "char";
            list[1][0] = "dec";
            list[2][0] = "hex";
            
            printf("char | dec | hex\n");
            int i = 0;
            while(1){
                if (word[i] == '\0'){
                    break;
                }
                else{
                    printf("%c    | %d | %X\n",word[i],word[i],word[i]);
                }
                i = i + 1;
            }
            
            
            //TODO
            
        }
        else if (input[0] == 'B'){
            printf("Please enter all integer sequences on line, seperate them with a space. hit enter when you are done\n");
            char word[1000];
            scanf("%[^\n]s", word);
            
            //good number, if the program is here
            int i = 0;
            int count = 0;
            char tempword[4];
            while (1){
                   if (word[i] == ' '){
                       int temp = 0;
                       temp = atoi(tempword);
                       printf("%c",temp);
                       i = i + 1;
                       count = 0;
                       int j = 0;
                       while (j < 4){
                           tempword[j] = '\0';
                           j = j + 1;
                       }
                   }
                   else if (word[i] == '\0'){
                       int temp = 0;
                       temp = atoi(tempword);
                       printf("%c",temp);
                       break;
                   }
                   else{
                       tempword[count] = word[i];
                       count = count + 1;
                       i = i + 1;
                   }

               }
                
        }
        else{
            break;
        }
        printf("\n");
    }
}
