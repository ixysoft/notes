#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

int out[100000];
int len;

void* routine(void *tm){
    int t = *(int*)tm;
    usleep(t*1000+666); //核心的睡觉部分
    //printf("%d ",t);    //输出结果
    out[len++] = t;
    //fflush(stdout);
    pthread_exit(NULL);
}

void sleep_sort(int arr[],int size){
    int i;
    pthread_t pids[10000];
    len = 0;
    for(i = 0; i < size; i++){
        pthread_create(&pids[i],NULL,routine,&arr[i]);
    }
    while(len < size);  //等待排序完毕
}

int main(){
    int arr[] = {1,3,4,0,0,5,8,5,9,0};
    int size = sizeof(arr) / sizeof(arr[0]);
    int i;
    puts("排序前");for(i = 0; i < size; i++) printf("%d ",arr[i]);puts("");
    sleep_sort(arr,size);
    puts("排序后");for(i = 0; i < size; i++) printf("%d ",out[i]);puts("");
    return 0;
}
