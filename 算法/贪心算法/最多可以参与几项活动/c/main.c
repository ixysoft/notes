#include<stdio.h>
#include<stdlib.h>

struct activity{
    int start;  //开始时间
    int end;    //结束时间
}activity[100007];

//交换依据
int cmp(const void * a, const void * b){
    return ((struct activity*)a)->end > ((struct activity*)b)->end;
}

int main(){
    int N;
    int i,j;
    int sum;
    while(~scanf("%d",&N)){
        for(i = 0; i < N; i++)
            scanf("%d%d",&activity[i].start,&activity[i].end);
        qsort(activity,N,sizeof(struct activity),cmp);  //按结束时间排序
        sum = N>0;
        for(i = 1,j = 0; i < N && j < N; i++){
            if(activity[j].end <= activity[i].start){
                j=i;
                sum++;
            }
        }
        printf("%d\n",sum);
    }
    return 0;
}
