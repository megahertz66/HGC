#include <stdio.h>
#include <stdlib.h>

int main()
{
    char name[100] = {0};

    printf("what is your name?\n:");
    gets(name);

    printf("Hello, %s, nice to meet you!\n", name);
    return 0;
}

/*
 *  如使用fgets则会记录回车
 *  如使用gets则不会记录回车换行
*/
