#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEEDTAX 0.055

int str_isdigits(char *str, int strlen);

//简单小链表，用于内存的释放
typedef
struct memList{
    double price;
    int quant;
    struct memList* next;
}MemList;



int main()
{
    char price[50]={0};
    char quant[50]={0};
    int count = 1;
    double Subtotal = 0.0 ,Tax = 0.0, Total = 0.0;
    MemList * structSave = (MemList *)calloc(1, sizeof(MemList));
    MemList * head = structSave;
    //MemList * tmp = head;
    printf("If you want to exit. Please enter q\n");
    while(1){
        MemList * tempStruct = NULL;

        printf("Enter the price of item(%d):", count);
        gets(price);
        if(!strcmp(price, "q"))break;
        printf("Enter the quantity of item(%d):", count);
        gets(quant);
        if(!strcmp(quant, "q"))break;
        count++;
        tempStruct = (MemList *)calloc(1, sizeof(MemList));
        tempStruct->price = atof(price);
        tempStruct->quant = atoi(quant);
        tempStruct->next = NULL;

        structSave->next = tempStruct;
        structSave = structSave->next;
    }
    for(head=head->next; head!=NULL; head=head->next){
        Subtotal += head->price * head->quant;
    }


    printf("Subtotal: %.2lf !\n", Subtotal);
    printf("Tax: %.2lf !\n", Tax = Subtotal * NEEDTAX);
    printf("Hello world %.2lf !\n", Total = Subtotal + Tax);
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
