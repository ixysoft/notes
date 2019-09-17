#include<stdio.h>

#define swap(a,b) {int tmp=a;a=b;b=tmp;}

//鸡尾酒排序
void cocktail_sort(int arr[],int size){
    int i,j;
    int bottom = 0;
    int top = size - 1;
    char swaped = 1;    //交换标志
    while(swaped){
        swaped = 0;
        for(i = bottom; i < top; i++){
            if(arr[i] > arr[i+1]){
                swaped = 1;
                swap(arr[i],arr[i+1]);
            }
        }
        top--;  //右边界左移
        for(i = top; i > bottom; i--){
            if(arr[i-1] > arr[i]){
                swaped = 1;
                swap(arr[i],arr[i-1]);
            }
        }
        bottom++;   //左边界右移
    }
}

int main(){
    int arr[] = {
        1,3,4,0,0,5,8,5,9,0
    };
    int size = sizeof(arr) / sizeof(arr[0]);
    int i;
    puts("排序前:");for(i = 0; i < size; i++)printf("%d ",arr[i]);puts("");
    cocktail_sort(arr,size);
    puts("排序后:");for(i = 0; i < size; i++)printf("%d ",arr[i]);puts("");
    return 0;
}
