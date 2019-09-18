#include <stdio.h>
#include <stdlib.h>

#define CHANGE 0.09290304
#define INPUT_SUC  0
#define INPUT_ERR -1

int isDigits(char * str);
int isDigits1(char *str);

int main()
{
    int flag = 10;
    char wide[20]={0};
    char higth[20]={0};
    char tmp[2]={0};
    double Fwide = 0.0;
    double Fhigth= 0.0;
    double FareaFeet = 0.0;
    double FareaMeter = 0.0;

    while(1>0){
        printf("you will entry feet=1  meter=2 exit==0\n:");
        scanf("%d",&flag);
        gets(tmp);
        if(flag > 2){
            printf("Please entry 0~2 !\n");
            continue;
        }
        else if(0 == flag){
            break;
        }
        printf("Please entry the wide!\n:");
        gets(wide);
        printf("Please entry the higth!\n:");
        gets(higth);
        if( (INPUT_ERR == isDigits(wide)) || (INPUT_ERR == isDigits(wide)) ){
            printf("Please entry digit\n");
            continue;
        }

        Fwide = atof(wide);
        Fhigth= atof(higth);
        if(1 == flag){
            FareaFeet = Fwide * Fhigth;
            FareaMeter = FareaFeet / CHANGE;
        }
        else{
            FareaMeter = Fwide * Fhigth;
            FareaFeet = FareaMeter * CHANGE;
        }
        printf("The area is:\n%.5lf square feet.\n%.5lf square meters \n", FareaFeet, FareaMeter);
    }

    printf("Bye!Bye!\n");

    return 0;
}

int isDigits1(char *str)
{
    return 1;
}

int isDigits(char * str)
{
    char * tmp = str;
    int result = INPUT_SUC;
    int cnt;
    while(*tmp)
    {
        if(('0' <= *tmp) && (*tmp <= '9'))
        {
            tmp++;
        }
        else if('.' == *tmp)
        {
            for(cnt = 0; cnt < 6; cnt++)
            {
                tmp++;
                if('\0' == *tmp)
                {
                    return result;
                }
                if(('9' < *tmp) || (*tmp < '0'))
                {
                    result = INPUT_ERR;
                    goto err;
                }
            }
            break;
        }
        else
        {
            result = INPUT_ERR;
            goto err;
        }

    }
err:
    return result;
}





