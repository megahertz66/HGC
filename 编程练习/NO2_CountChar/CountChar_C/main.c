#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char name[101]={0};
    int nameLengh = 0;
    printf("�����������ַ��������Ȳ��ó���100��\n�� ");
    gets(name);
    nameLengh = strlen(name);
    printf("��������%d�ĳ��ȵ��ַ���!\n", nameLengh);
    return 0;
}
