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
 *  ��ʹ��fgets����¼�س�
 *  ��ʹ��gets�򲻻��¼�س�����
*/
