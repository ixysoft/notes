#include<stdio.h>

//数字交换
void swap(int *a,int *b){
    int c = *a;
    *a = *b;
    *b = c;
}

//调整某个节点
void adjust(int arr[],int i,int size){
    if(i >= size) return;
    int left = i*2+1;   //左子节点
    int right = i*2+2;  //又子节点
    int max = i;    //假设当前节点为最大节点
    if(left < size && arr[max] <= arr[left]) max = left;
    if(right < size && arr[max] <= arr[right]) max = right;
    if(max != i){   //存在节点调整
        swap(&arr[max],&arr[i]);

        adjust(arr,max,size);   //递归调整下一层
    }
}

//初始化堆
void heap_init(int arr[],int size){
    int i;
    for(i = size/2 - 1; i >= 0; i--){   //从最后一个元素的父元素逆序遍历调整
        adjust(arr,i,size);
    }
}

//堆排序
void heap_sort(int arr[],int size){
    heap_init(arr,size);    //初始化堆,此时堆顶最大
    int i;
    for(i = size-1; i > 0; i--){    //将堆顶元素与最后一个元素对调,从堆顶冲
        swap(&arr[0],&arr[i]); //交换两个数字
        adjust(arr,0,i);
    }
}

int main(){
    int arr[] = {
        1,3,4,0,0,5,8,5,9,0
    };
    int size = sizeof(arr)/sizeof(arr[0]);
    int i;

    puts("排序前");for(i = 0; i < size; i++) printf("%d ",arr[i]);puts("");
    heap_sort(arr,size);
    puts("排序后");for(i = 0; i < size; i++) printf("%d ",arr[i]);puts("");

    return 0;
}
