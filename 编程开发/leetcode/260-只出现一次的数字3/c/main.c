#include<stdio.h>

int main(){
    int arr[] = {
        1,3,4,3,1,4,5,9,5,6
    };

    int size = sizeof(arr) / sizeof(arr[0]);
    int i;

    int mix = 0;    //或者获得的结果
    for(i = 0; i < size; i++){
        mix ^= arr[i];
    }
    int lsb = mix&-mix; //最低有效位,两个唯一的数字混合结果最低位1对应的二进制位必然不同,根据该二进制位进行区分
    int a[2] = {0};
    for(i = 0; i < size; i++){
        int idx = (lsb&arr[i]) ? 1:0;
        a[idx] ^= arr[i];
    }
    printf("%d,%d\n",a[0],a[1]);
    return 0;
}
