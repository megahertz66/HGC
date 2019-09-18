#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define PERGALLONS  350

int str_isdigits(char *str, int strlen);


//TODO: 缺少挑战中的内容
int main()
{
    double mulNum1 , mulNum2, numProduct;
    char along[50] = {0};
    char wight[50] = {0};
    int resultGallon = 1;
    int resultArea =0;

    printf("请输入房间面积的长\n :");
    gets(along);
    if(!str_isdigits(along, strlen(along)) ){
        printf("please write again1\n");
        return 0;
    }
    printf("请输入房间面积的宽\n :");
    gets(wight);
    if(!str_isdigits(wight, strlen(wight))){
        printf("please write again2\n");
        return 0;
    }

    mulNum1 = atof(along);
    mulNum2 = atof(wight);
    numProduct = mulNum1 * mulNum2;

    resultArea = (int)numProduct ;
    if(resultArea < numProduct){

        resultArea++;
    }
    if(resultArea > PERGALLONS){
        resultGallon = resultArea / PERGALLONS;
        if(resultArea % PERGALLONS){
            resultGallon++;
        }
    }
    printf("You will need to purchase %d gallons of\n", resultGallon);
    printf("paint to cover %d square feet.\n", resultArea );

    return 0;
}

//   判断输入字符串为数值

int str_isdigits(char *str, int strlen)
{
    //char *strTmp = str;
    int flagDot = 0;
    int i;

    for(i=0; i<strlen; i++){
        if(str[i] == '.'){
            flagDot++;
        }
        if(flagDot > 1) {
            return 0;
        }
        if( !((str[i] >= '0') && (str[i] <= '9')) ){
            if(str[i] != '.')
                return 0;
        }
    }
    return 1;
}




