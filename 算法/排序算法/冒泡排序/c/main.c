/**
 *  算法思路:
 *  依次比较相邻的元素,判断是否符合给定规则(大小),对于不符合规则的两个元素,
 *  交换对应的值,遍历到最后一个没有排序好的元素.排序的序列中最后一个元素将
 *  会是序列中的最大或最小值(根据给定规则).重复这个过程,直到所有的元素都确定
 *  位置
 **/

#include<stdio.h>

//交换两个数字
#define swap(a,b) {int tmp=a;a=b;b=tmp;}

//冒泡算法
int bubble_sort(int arr[],int size){
    int i,j;
    for(i = size-1; i > 0; i--){
        int swap_flag = 0;  //交换标志,用来减少交换步奏
        for(j = 0; j < i; j++){
            if(arr[j] > arr[j+1]){  //这里排成从小到大的顺序,前数比后数大,就交换位置
                swap(arr[j],arr[j+1]);
                swap_flag = 1;  //设置交换标志
            }
        }
        if(swap_flag == 0) return 0;    //过程中没有出现交换的情况,说明arr整体已经有序
    }
    return 0;
}

int main(){
    int arr[] = {
        1,3,4,0,0,5,8,5,9,0
    };

    int size = sizeof(arr)/sizeof(arr[0]);  //获取数组的长度
    int i;

    //排序前输出数组
    printf("交换前:\n");
    for(i = 0; i < size; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");

    bubble_sort(arr,size);
    
    //排序后输出数组
    printf("交换后:\n");
    for(i = 0; i < size; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");

    return 0;
}
