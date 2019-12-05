#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void merge(int input[] ,int head, int middle, int tail)
{
    int i = 0;
    int phead_1 = head;
    int phead_2 = middle+1;
    int *output = (int *)malloc(sizeof(int)*(tail-head+1));

    while(phead_1<=middle && phead_2<=tail){
        output[i++] = input[phead_1] < input[phead_2] ? input[phead_1++] : input[phead_2++];
    }
    while(phead_1<=middle){
        output[i++] = input[phead_1++];
    }
    while(phead_2<=tail){
        output[i++] = input[phead_2++];
    }

    memcpy( &(input[head]), output, sizeof(int)*(tail-head+1));

    free(output);
}

void mergesort(int input[], int len)
{
    int step_new = 0;
    int step_old = 1;
    int head = 0; int tail = 0;
    int middle;
    int i = 1;

    while(step_new <= len){
        step_new = step_old << 1;
        while (head < len){
            tail = head + step_new - 1;
            if(tail > len){
                if(head + step_old - 1 == tail){
                    break;
                }
                middle = head +step_old;
                tail = len;
            }else{
                middle = (head + tail) >> 1;
            }
            merge(input, head, middle, tail);
            head = tail + 1;
        }
        step_old = step_new;
        head = 0;
    }
}

int main()
{
    int array[1000] = {0};
	int lengh = 0;
    int cnt = 0;

    while(1)
    {
        printf("输入0退出\n");
        printf("输入排序个数：\n");
        scanf("%d", &lengh);
        if(0 >= lengh)
        {
            break;
        }
        printf("待排序数组:\n");
        for(cnt = 0; cnt < lengh; cnt++)
        {
            array[cnt] = rand()%100;
            printf("%d ", array[cnt]);
        }
        mergesort(array, lengh-1);

        printf("\n排序结果：\n");
        for(cnt = 0; cnt < lengh; cnt++)
        {
            printf("%d ", array[cnt]);
        }
        printf("\n");
    }
    return 0;
}





