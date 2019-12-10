#include<stdio.h>
#include<stdlib.h>

int count(int target,int coins[],int length){
    int i;
    for(i = 0; i < length; i++){
        if(coins[i] < target){  //可以继续下一步处理
            int cnt = count(target - coins[i],coins,length);
            if(cnt > 0)
                return 1+cnt;
        }else if(coins[i] == target){
            return 1;
        }
    }
    return 0;
}

//逆序排列
int cmp(const void* a,const void* b){
    return *(int*)a < *(int*)b;
}

int main(){
    int target = 15;
    int coins[] = {
        5,8
    };
    int length = sizeof(coins) / sizeof(coins[0]);
    qsort(coins,length,sizeof(coins[0]),cmp);

    printf("%d\n",count(target,coins,length));
    return 0;
}
