#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a_dic[][50] = {"Hert", "pull out all stop!",\
                    "Alex", "code is 6666!",\
                    "1", "this is 1 !",\
                    "2", "this is 2 !",\
                    "3", "this is 3 !"};



int main()
{
    int i = 0;
    char key[50]={0};
    printf("hello word!\n  :");

    gets(key);

    for(i=0; i<10; i+=2){
        if(!strcmp(key, a_dic[i])){
            printf("%s is said %s !\n", key, a_dic[i+1]);
        }
    }

    return 0;
}
