#include<stdio.h>
#include<stdlib.h>

#define SIZE 10000
int table[SIZE] = {0};

int lowbit(int num);    //最低位1
int update(int i,int val);  //更新指定位置的值
int delete(int i);  //删除指定index的值
int sum(int i);

int main(){
    int arr[] = {
        1,3,4,0,0,5,8,5,9,0
    };
    int size = sizeof(arr) / sizeof(arr[0]);
    int i;
    for(i = 0; i < size; i++)
        update(i,arr[i]);
    for(i = 0; i < size; i++)
        printf("%d\n",sum(i));
    return 0;
}

int sum(int i){
    int s = 0;
    i+=1;
    while(i > 0){
        s+=table[i-1];
        i-=lowbit(i);
    }
    return s;
}

int lowbit(int num){
    return num & (-num);
}

int update(int i,int val){
    i+=1;
    while(i < SIZE){
        table[i-1] += val;
        i += lowbit(i);
    }
    return val;
}

int delete(int i){
    return update(i,sum(i-1) - sum(i));
}
