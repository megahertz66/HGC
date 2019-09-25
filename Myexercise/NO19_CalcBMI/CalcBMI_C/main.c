#include <stdio.h>
#include <stdlib.h>

/*
    bmi = (weight / (height × height)) × 703
    WTO: 理想BMI(18.5～23.9) = 体重(单位Kg) ÷ 身高的平方 (单位m)
*/


int main()
{
    char weight[20]={0};
    char height[20]={0};
    double NumWeight , NumHeight;
    double bmi = 0.0;

    printf("Please send your height :");
    gets(height);
    printf("please send your weight :");
    gets(weight);

    NumWeight = atof(weight);
    NumHeight = atof(height);
    bmi = NumWeight / (NumHeight * NumHeight);

    if(bmi <= 18.5){
        printf("your BMI is %.02f\nYou are so thin.\n", bmi);
    }
    else if((bmi>=18.5) && (bmi <= 22.9)){
        printf("your BMI is %.02f\nYou are normal.\n", bmi);
    }
    else if((bmi>22.9) && (bmi <= 26.9)){
        printf("your BMI is %.02f\nYou are fat.", bmi);
    }
    else if((bmi>26.9) && (bmi <= 29.9)){
        printf("your BMI is %.02f\nYou are so fat.", bmi);
    }
    else if((bmi>29.9) && (bmi < 40)){
        printf("your BMI is %.02f\nYou are Severe obesity.", bmi);
    }
    else{
        printf("your BMI is %.02f\nYou are Super Severe obesity.", bmi);
    }

    return 0;
}
