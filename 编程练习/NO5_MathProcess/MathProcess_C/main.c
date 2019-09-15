#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

int main()
{
    char sum1[10]={0};
    char sum2[10]={0};
    int a, b;

    printf("please enter a integer!\n");
    printf("What is first number? \n:");
    gets(sum1);
    printf("What is first number? \n:");
    gets(sum2);

    a = atoi(sum1);
    b = atoi(sum2);

    printf("\n%d + %d = %d\n\
%d - %d = %d\n\
%d * %d = %d\n\
%d / %d = %d\n",\
       a, b, (a+b),\
       a, b, (a-b),\
       a, b, (a*b),\
       a, b, (a/b)
           );
    return 0;
}
