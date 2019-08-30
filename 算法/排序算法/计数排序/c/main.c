#include<stdio.h>

int main(){
    int arr[] = {
        1,3,4,0,0,5,8,5,9,0
    };
    int size = sizeof(arr)/sizeof(arr[0]);

    int tmp[10] = {0};  //临时空间,这里我们观察到所有需要排序的数字都在0~9之间,所以申请了长度为10的数组
    int i,j;
    for(i = 0; i < size; i++)
        tmp[arr[i]]++;

    //输出排序结果
    for(i = 0;i < 10; i++){
        for(j = 0; j < tmp[i]; j++)
            printf("%d ",i);//这里可以把值一次赋给arr
    }
    return 0;
}
