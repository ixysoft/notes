#include<stdio.h>

int main(){
    int arr[] = {
        1,2,3
    };

    int size = sizeof(arr) / sizeof(arr[0]);
    int i;
    int begin = 0;
    int end = 1 << size;
    int tmp,bit;
    for(i = begin; i < end; i++){   //遍历所有的情况
        for(tmp = i,bit=0; tmp > 0; tmp>>=1,bit++){ //依次遍历当前数字的有效二进制位
            if(tmp%2)printf("%d ",arr[bit]);    //输出符合要求的序列
        }
        puts("");
    }
}
