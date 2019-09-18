#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int currAge, retireAge;
    time_t currTime;
    struct tm *lt;
    int retireYears = 0;

    time(&currTime);
    lt = localtime(&currTime);

    printf("What is your current age? \n :");
    scanf("%d", &currAge);
    printf("At what age would you like to retire? \n :");
    scanf("%d", &retireAge);
    retireYears = retireAge - currAge;
    printf("You have %d years left until you can retire.\n",retireYears);
    printf("It's %d, so you can retire in %d.\n", lt->tm_year+1900, lt->tm_year+1900+retireYears);

    return 0;
}
