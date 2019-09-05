#include<stdio.h>
#include<time.h>
#include<stdlib.h>

//判断是否排序完毕
int isSorted(int arr[],int size){
    int i;
    for(i = 1; i < size; i++)
        if(arr[i] < arr[i-1]) return 0;
    return 1;
}

//排序主体
void monkey_sort(int arr[],int size){
    int rnd1,rnd2;
    while(!isSorted(arr,size)){
        rnd1 = rand() % size;
        rnd2 = rand() % size;
        //任意调换两个元素
        int tmp = arr[rnd1];
        arr[rnd1] = arr[rnd2];
        arr[rnd2] = tmp;
    }
}

int main(){
    srand(time(NULL));
    int arr[] = {1,3,4,0,0,5,8,5,9,0};
    int size = sizeof(arr) / sizeof(arr[0]);
    int i;

    puts("排序前");for(i = 0; i < size; i++) printf("%d ",arr[i]);puts("");
    monkey_sort(arr,size);
    puts("排序后");for(i = 0; i < size; i++) printf("%d ",arr[i]);puts("");
    return 0;
}
