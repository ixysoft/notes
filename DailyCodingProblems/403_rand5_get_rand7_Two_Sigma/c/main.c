#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int rand5();
int rand7();

int main(){
    srand(time(NULL));
    int i;
    int count[7] = {0};
    int N = 10000000;
    for(i = 0; i < N; i++){
        int idx = rand7();
        count[idx]++;
    }
    for(i = 0; i < 7; i++){
        printf("%d,%.04f\n",i,count[i] * 1.0 / N);
    }

}

//系统给定的函数
int rand5(){
    return rand() % 5;  //此处我们假设等概率
}


//我们需要实现的函数
int rand7(){
    int res;
    do{
        res = rand5() * 5 + rand5();  //可以等概率生成0~24之间的数
    }while(res >= 21);  //等概率生成0~20之间的数
    return res / 3; //等概率生成0~6之间的数
}
