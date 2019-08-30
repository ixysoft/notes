#include<stdio.h>

int insertion_sort(int arr[],int size){
    int i,j;
    for(i = 1; i < size; i++){
        int tmp = arr[i];
        for(j = i-1; j >= 0 && arr[j] > tmp; j--) arr[j+1] = arr[j];
        arr[j+1] = tmp;
    }
    return 0;
}

int main(){
    int i;
    int arr[] = {
        1,3,4,0,0,5,8,5,9,0
    };
    int size = sizeof(arr)/sizeof(arr[0]);

    printf("排序前:");
    for(i = 0; i < size; i++)printf("%d ",arr[i]);
    puts("");
    insertion_sort(arr,size);
    printf("排序后:");
    for(i = 0; i < size; i++)printf("%d ",arr[i]);
    puts("");
    return 0;
}
