#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char name[101]={0};
    int nameLengh = 0;
    printf("请输入任意字符串，长度不得超过100个\n： ");
    gets(name);
    nameLengh = strlen(name);
    printf("您输入了%d的长度的字符串!\n", nameLengh);
    return 0;
}
