#include "rb.h"
#include<time.h>

int cmp(const void* a,const void* b){
    return *(int*)a > *(int*)b;
}

#define SIZE 5
int data[SIZE];

void genData(int arr[],int size){
    int i;
    for(i = 0; i < size; i++){
        arr[i] = rand() % size;
    }
    qsort(arr,size,sizeof(int),cmp);
}

int main(){
    srand(time(NULL));
    node root = NULL;
    int size = sizeof(data) / sizeof(data[0]);
    genData(data,size);
    int i;
    for(i = 0; i < size; i++){
        insert(&root,i,data[i]);
    }

    for(i = 0; i < 1; i++)
        delete(&root,root->key);
    preOrderVisit(root);
    return 0;
}
