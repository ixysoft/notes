/**
 *  这个解法假设一定存在超过半数的元素.
 *  如果没有这个假设,可以在找出符合条件的元素后,验证该元素是否超过半数.
 * */
#include<stdio.h>

int main(){
    int arr[] = {
        1,1,1,1,1,2,2,2,2
    };
    int size =sizeof(arr)/sizeof(arr[0]);
    int i,j;

    int num = 0;
    //int类型在32位的系统上长度为32位
    for(i = 0; i < 32; i++){
        int count = 0;  //对应数位上的1计数
        int mask = 1<<i;    //掩码
        for(j = 0; j < size; j++){  //遍历每个数字
            if(arr[j] & mask) count++;
        }
        if(count > size / 2)    //对应二进制位出现1的次数超过半数
            num |= mask;
    }

    printf("超过半数的元素:%d\n",num);

    return 0;
}
