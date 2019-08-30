#include<stdio.h>

int shell_sort(int arr[],int size){
    int i,j,k;
    int step;
    for(step = size / 2; step > 0; step /= 2){  //更新步长
        for(i = step; i < size; i++){
            int tmp = arr[i];
            for(j = i - step; j >= 0 && arr[j] > tmp; j -= step) arr[j+step] = arr[j];
            arr[j+step] = tmp;
        }
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
    shell_sort(arr,size);
    printf("排序后:");
    for(i = 0; i < size; i++) printf("%d ",arr[i]);
    puts("");
    return 0;
}
