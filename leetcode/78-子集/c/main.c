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
    for(i = begin; i < end; i++){
        for(tmp = i,bit=0; tmp > 0; tmp>>=1,bit++){
            if(tmp%2)printf("%d ",arr[bit]);
        }
        puts("");
    }
}
