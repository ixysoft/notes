#include<stdio.h>

//交换两个数字
#define swap(a,b) {int tmp=a;a=b;b=tmp;}

int selection_sort(int arr[],int size){
    int i,j;
    int min = 0;
    for(i = 0; i < size - 1; i++){
        min = i;
        for(j = i+1; j < size; j++){
            if(arr[min] > arr[j]) min = j;  //选择最小的元素
        }
        swap(arr[min],arr[i]);
    }
    return 0;
}

int main(){
    int arr[] = {
        1,3,4,0,0,5,8,5,9,0
    };
    int size = sizeof(arr) / sizeof(arr[0]);
    int i;

    printf("排序前:");
    for(i = 0; i < size; i++) printf("%d ",arr[i]);
    puts("");
    selection_sort(arr,size);
    printf("排序后:");
    for(i = 0; i < size; i++) printf("%d ",arr[i]);
    puts("");
    return 0;
}
