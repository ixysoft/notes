#include<stdio.h>

#define swap(a,b) {int tmp=a;a=b;b=tmp;}

void gnome_sort(int arr[],int size){
    int pos = 0;
    while(pos < size){
        if(pos == 0 || arr[pos] >= arr[pos-1]) pos++;   //此处应该为>=,而不是>.否则有相同元素的情况下,会陷入死循环
        else{
            swap(arr[pos],arr[pos-1]);
            pos--;
        }
    }
}

int main(){
    int arr[] = {
        1,3,4,0,0,5,8,5,9,0
    };
    int size = sizeof(arr) / sizeof(arr[0]);
    int i;
    puts("排序前:");for(i=0;i<size;i++)printf("%d ",arr[i]);puts("");
    gnome_sort(arr,size);
    puts("排序后:");for(i=0;i<size;i++)printf("%d ",arr[i]);puts("");

    return 0;
}
