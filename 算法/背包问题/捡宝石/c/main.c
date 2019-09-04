#include<stdio.h>

int values[1000];   //保存价值的数组
int weights[1000];  //重量的数组
int max_values[1000];   //保存最大重量的数组
int max(int a,int b){
    return a > b ? a : b;
}

int main(){
    int N;  //宝石的数目
    int M;  //最大可以容纳的重量
    int i,j;
    while(~scanf("%d%d",&N,&M)){
        for(i = 1; i <= N; i++){
            scanf("%d%d",&weights[i],&values[i]);   //输入石头的重量和价值
        }
        for(i = 0; i <= M; i++)
            max_values[i] = 0;  //初始化最大价值数组
        for(i = 0; i <= N; i++){    //遍历所有的宝石
            for(j = M; j > 0; j--){    //从后向前遍历各个当前石头对最大价值的影响
                max_values[j] = (weights[i] > j ? max_values[j] : max(max_values[j],values[i]+max_values[j-weights[i]])); //更新由于当前石块加入造成的最大价值变化
            }
        }
        printf("%d\n",max_values[M]);
    }
    return 0;
}
