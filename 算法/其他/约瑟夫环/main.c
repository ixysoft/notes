/*
 *  核心公式:
 *  F(N,M) = (F(N-1,M)+M) % N
 **/
#include<stdio.h>

int main(){
    int N,M;
    printf("输入参数人数和剔除间隔:");
    scanf("%d%d",&N,&M);
    int i;
    int res = 0;
    for(i = 2; i <= N; i++)
        res=(res+M)%i;

    printf("剩下第%d个人.\n",res+1);

    return 0;
}
