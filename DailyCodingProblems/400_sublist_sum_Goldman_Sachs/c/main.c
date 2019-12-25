#include<stdio.h>

#define SIZE 10000
int table[SIZE];

int lowbit(int num);
void update(int i,int size,int val);
int getSum(int i);
int sum(int i,int j);

int main(){
    int arr[] = {
        1,2,3,4,5,6
    };
    int size = sizeof(arr) / sizeof(arr[0]);
    int i;
    for(i = 0; i < size; i++)
        update(i,size,arr[i]);

    printf("%d\n",sum(1,3));

    return 0;
}

int lowbit(int val){
    return val & (-val);
}

void update(int i,int size,int val){
    i+=1;
    while(i <= size){
        table[i-1] += val;
        i += lowbit(i);
    }
}

int getSum(int i){
    i+=1;
    int s = 0;
    while(i > 0){
        s+=table[i-1];
        i-=lowbit(i);
    }
    return s;
}

int sum(int i,int j){
    return getSum(j-1)-getSum(i-1);
}
