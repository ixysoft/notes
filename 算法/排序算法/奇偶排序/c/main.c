#include<stdio.h>

#define swap(a,b) {int tmp=a;a=b;b=tmp;}

void oe_sort(int arr[],int size){
    char sorted = 0;    //有序标志
    int i,base = 0;
    while(!sorted){
        sorted = 1; //有序
        for(i=base;i<size-1;i+=2){
            if(arr[i] > arr[i+1]){
                swap(arr[i],arr[i+1]);
                sorted = 0;
            }
        }
        base = 1 - base;
    }
}

int main(){
    int arr[] = {
        1,3,4,0,0,5,8,5,9,0
    };
    int size = sizeof(arr) / sizeof(arr[0]);
    int i;
    puts("排序前");for(i=0;i<size;i++)printf("%d ",arr[i]);puts("");
    oe_sort(arr,size);
    puts("排序后");for(i=0;i<size;i++)printf("%d ",arr[i]);puts("");

    return 0;
}
