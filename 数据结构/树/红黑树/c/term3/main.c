#include "rb.h"
#include<sys/time.h>
#include<stdlib.h>
#include<time.h>
#define N 1000000


int main(){
    srand(time(NULL));
    treep t = tree();
    struct timeval start;
    struct timeval end;
    gettimeofday(&start,NULL);
    for(int i = 0; i < N; i++){
        insertNode(t,rand());
    }
    gettimeofday(&end,NULL);
    int us = (end.tv_usec - start.tv_usec);
    int s = (end.tv_sec - start.tv_sec) - (us < 0);
    us = (us + 1000000) % 1000000;
    printf("time:%d.%06d\n",s,us);
    printf("total: %d\n",t->size);

    // visit(t);
    // for(int i = 0; i < N; i++){
    //     visit(t);
    //     deleteNode(t,i);
    // }
    // visit(t);
    // printf("===========\n");
    // for(int i = 0; i < 20; i++){
    //     if(i % 2)
    //         deleteNode(t,i);
    // }
    // deleteNode(t,13);
    // visit(t);


    // nodep res = search(t,3);
    // if(res){
    //     printf("%d\n",Key(res));
    // }else{
    //     printf("记录不存在\n");
    // }
    return 0;
}