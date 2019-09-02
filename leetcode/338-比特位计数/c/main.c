#include<stdio.h>

int ones(int n){
    int count = 0;
    for(;n>0;n&=n-1,count++);
    return count;
}

int main(){
    int i;
    int dp[100] = {0};
    printf("0 ");
    for(i = 1; i < 100; i++){
        dp[i] = dp[i & (i-1)] + 1;
        printf("%d ",dp[i]);
    }
    return 0;
}
