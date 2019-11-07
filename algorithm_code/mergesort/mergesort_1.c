#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int input[] ,int head, int middle, int tail, int output[])
{
    int i = 0;
    int phead_1 = head;
    int phead_2 = middle+1;
    //int *output = (int *)malloc(sizeof(int)*(tail-head+1));

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

    //free(output);
}

 void recursion_sort(int input[], int head, int tail, int output[])
 {
     if(head < tail){
         int middle = (head + tail) >> 1;
         recursion_sort(input, head, middle, output);
         recursion_sort(input, middle+1, tail, output);
         merge(input, head, middle, tail, output);
     }
 }

 void mergeSort(int input[], int lenght)
 {
    int *output = (int *)malloc(sizeof(int)*lenght);
    recursion_sort(input, 0, lenght-1, output);
    free(output);
    return;
 }


int main()
{
    int i = 0;
    int input[] ={1,3,2,6,3,12,8,2,89,122,57,25,135,44,1234,553,22,44};
    int arrayLenght = sizeof(input)/sizeof(int);
    printf("arrayLenght = %d\n", arrayLenght);
    //merge(input, 1,1,2);
    mergeSort(input, arrayLenght);


    for(i=0; i<arrayLenght; i++){
        printf("--%d--", input[i]);
    }

    //printf("\n18>1 = %d \n", 18>>1);

    return 0;
}
