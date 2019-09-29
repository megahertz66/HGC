#include <stdio.h>
#include <unistd.h>

// TODO :

int main(int argc, char *args[])
{
    int i = 0;
    char a;
    char passWd[20] = {0};
    while(i<10){
        //printf("6");
        a = getchar();
        fprintf(stdin, "\n");
        passWd[i] = a;
        i++;
    }
    passWd[i] = '\0';

    printf("%s \n", passWd);

	return 0;
}
