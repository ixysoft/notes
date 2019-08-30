/**
 *  至少需要分配10*size的空间,因为存在极端情况所有的数字都相同
 */
#include<stdio.h>

int tmp[10][10000]; //这里为了方便理解代码,设置了一个固定的空间的数组,每行第一个元素表示该行数据的数目,所以这里最多能排9999个数字

int radix_sort(int arr[],int size){
    int ok = 0; //排序完成标志
    int radix;
    int i,j;
    for(i = 0; i < 10; i++) tmp[i][0] = 0; //计数归0
    for(radix = 1;ok == 0;radix *= 10){
        ok = 1; //假设排序完毕
        for(j = 0; j < size; j++){
            int left = arr[j]/radix;
            if(left >= 10) ok = 0; //存在没有除尽的数字,需要继续排序
            int idx = left%10;  //下标
            int offset = ++tmp[idx][0]; //偏移
            tmp[idx][offset] = arr[j];    //将当前元素存入tmp中
        }

        //整理在tmp中的数据
        int idx = 0;
        for(i = 0; i < 10; i++){
            for(j = 1; j <= tmp[i][0]; j++) arr[idx++] = tmp[i][j];
            tmp[i][0] = 0;
        }
    }
    return 0;
}

int main(){
    int arr[] = {
        1,3,4,0,0,5,8,5,9,0
    };

    int size = sizeof(arr)/sizeof(arr[0]);
    int i;
    printf("排序前:");for(i = 0; i < size; i++) printf("%d ",arr[i]);puts("");
    radix_sort(arr,size);
    printf("排序后:");for(i = 0; i < size; i++) printf("%d ",arr[i]);puts("");
    return 0;
}
