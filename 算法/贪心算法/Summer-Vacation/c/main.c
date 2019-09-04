#if 0
这里利用构建的一个大根堆来实现优先队列(其实就是堆的一种形式)的功能,
#endif

#include<stdio.h>
#include<stdlib.h>

struct Node{
    int a;
    int b;
}node[100007];

int tmp[100007]; //临时空间
int tmp_length = 0; //临时空间长度

//重新调整堆
void sort(int idx){
    int left = idx*2+1;
    int right = idx*2+2;
    int max = idx;
    if(left < tmp_length && tmp[left] >= tmp[max]) max = left;
    if(right < tmp_length && tmp[right] >= tmp[max]) max = right;
    if(max != idx){
        //交换元素
        tmp[max]^=tmp[idx];
        tmp[idx]^=tmp[max];
        tmp[max]^=tmp[idx];
        sort(max);  //重新调整
    }
}

//压入一个数字
void push(int num){
    tmp[tmp_length++] = num;
    int i,idx;
    for(i = tmp_length-1; i > 0; i = idx){
        idx = (i-1)/2;
        sort(idx); //重新调整
    }
}

//弹出元素
int pop(){
    int ret = 0;
    if(tmp_length > 0){
        ret = tmp[0];
        tmp[0] = tmp[--tmp_length];
        sort(0);
    }
    return ret;
}

//判断是否为空
int empty(){
    return tmp_length == 0;
}

int cmp(const void * a,const void * b){
    return ((struct Node*)a)->a > ((struct Node*)b)->a;
}

int main(){
    int N,M;
    int i,j;
    int sum,max,idx;

    while(~scanf("%d%d",&N,&M)){
        for(i = 0; i < N; i++)
            scanf("%d%d",&node[i].a,&node[i].b);
        qsort(node,N,sizeof(struct Node),cmp);

        sum = 0;
        tmp_length = 0;
        idx = 0;
        for(i = 1; i <= M; i++){
            while(idx < N && node[idx].a <= i){
                push(node[idx++].b);  //压入一个数字
            }
            if(!empty()){
                sum+=pop();
            }
        }
        printf("%d\n",sum);
    }
}

