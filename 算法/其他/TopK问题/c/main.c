#include<stdio.h>

//交换两个数字
void swap(int *a, int *b){
    int c = *a;
    *a = *b;
    *b = c;
}

//调整堆
void adjust(int arr[],int i,int size){
    if(i >= size) return;
    int left = i*2+1;   //左孩子
    int right = i*2+2;  //右孩子
    int min = i;
    if(left < size && arr[min] > arr[left]) min = left;
    if(right < size && arr[min] > arr[right]) min = right;
    if(min != i){   //出现调整的情况
        swap(&arr[min],&arr[i]);
        adjust(arr,min,size);
    }
}

//创建堆
void build_heap(int arr[],int size){
    int i;
    for(i = size/2 - 1; i >= 0; i--){
        adjust(arr,i,size);
    }
}


//通过建堆获取最大的第K个数
int find_top_k_by_heap(int arr[],int k,int size){
    if(k > size) return -1; //k大于size,返回-1
    build_heap(arr,k);  //创建一个大小为k的堆
    int i;
    for(i = k; i < size; i++){
        if(arr[0] < arr[i]){    //当前的数比堆顶的数更大
            swap(&arr[0],&arr[i]);
            adjust(arr,0,k);    //调整堆
        }
    }
    return arr[0];  //返回堆顶元素
}


//Quick Select
int find_top_k_by_quick_select(int arr[],int k,int size){
    if(k > size) return -1; //没有第k大的数
    int left = 0, right = size - 1;
    int i = left,j = right;
    int tmp;
    do{  //i不是当前的数
        i = left;
        j = right;
        tmp = arr[i];    //将当前的元素作为基准元素
        while(i < j){
            for(;i < j && arr[j] <= tmp;j--);arr[i] = arr[j];
            for(;i < j && arr[i] >= tmp;i++);arr[j] = arr[i];
        }
        arr[i] = tmp;
        if(i > k - 1){   //左边元素比较多
            right = i-1;
        }else if(i < k - 1){    //右边元素比较多
            left = i+1;
        }
    }while(i != k - 1); //i == k - 1时退出

    return tmp;
}

int main(){
    int arr[] = {1,3,4,0,0,5,8,5,9,0};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 6;
    
    puts("---By Heap---");
    for(k = 1; k <= size; k++)
        printf("第%d大的数:%d\n",k,find_top_k_by_heap(arr,k,size));
    puts("---By Quick Select---");
    for(k = 1; k <= size; k++)
        printf("第%d大的数:%d\n",k,find_top_k_by_quick_select(arr,k,size));
    

    return 0;
}
