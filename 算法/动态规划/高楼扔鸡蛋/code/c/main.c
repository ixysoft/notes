#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int DP[1000][1000];

int max(int a,int b){
    return a>b?a:b;
}

int min(int a,int b){
    return a>b?b:a;
}

int count(int k,int n){
    if(k == 0) return 0;
    if(k == 1) return n;
    //if(DP[k][n]) return DP[k][n];

    int i;
    int res = n;
    for(i = 1; i <= n; i++){
        res = min(res,max(count(k-1,i-1),count(k,n-i))+1);
    }
    return DP[k][n] = res;
}

int main(int argc,char** argv){
    if(argc != 3) return -1;
    int k = atoi(argv[1]);
    int n = atoi(argv[2]);
    if(k < 0 || k >= 1000 || n < 0 || n >= 1000) return -1;
    memset(DP,0,sizeof(int)*1000*1000);
    printf("%d\n",count(k,n));
    return 0;
}
