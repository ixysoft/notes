/**
 *  代码来源于维基百科.
 **/
#include<stdio.h>
#include<stdlib.h>

//获取x,y中的最小值
int min(int x,int y){
    return x < y ? x : y;
}

void merge_sort(int arr[],int len){
    int *a = arr;
    int *b = (int*)malloc(len*sizeof(int));
    int seg,start;  //seg为段的大小,start为开始位置
    for(seg = 1; seg < len; seg<<=1){   //从最小段(长度为1)逆推到整个问题
        for(start = 0; start < len; start+= seg<<1){
            int low = start;    //最低位开始下标
            int k = low;
            int mid = min(start+seg,len);   //中间位置下标
            int high = min(start+2*seg,len);    //最高位置下标
            int start1 = low,end1 = mid;
            int start2 = mid,end2 = high;
            while(start1 < end1 && start2 < end2){
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            }
            while(start1 < end1)
                b[k++] = a[start1++];
            while(start2 < end2)
                b[k++] = a[start2++];
        }
        int *temp = a;
        a = b;
        b = temp;   //交换a,b的指针值
    }
    if(a != arr){   //a与数组的地址不相同,说明a只想b的指针
        int i;
        for(i = 0; i < len; i++)    //将临时空间的值赋给数组
            b[i] = a[i];
        b = a;  //将临时空间的地址赋给b
    }
    free(b);//释放临时空间
}

//递归部分
void merge_sort_rec(int arr[],int reg[],int start,int end){
    if(start >= end) return;    //结束条件
    int len = end - start;
    int mid = (len >> 1) + start;
    int start1 = start,end1 = mid;
    int start2 = mid+1,end2 = end;
    merge_sort_rec(arr,reg,start1,end1);
    merge_sort_rec(arr,reg,start2,end2);
    int k = start;
    while(start1 <= end1 && start2 <= end2)
        reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
    while(start1 <= end1)
        reg[k++] = arr[start1++];
    while(start2 <= end2)
        reg[k++] = arr[start2++];
    for(k = start; k <= end; k++)
        arr[k] = reg[k];
}

void merge_sort2(int arr[],int size){
    int *reg = (int*)malloc(size*sizeof(int));
    merge_sort_rec(arr,reg,0,size-1);
    free(reg);
}

int main(){
    int arr[] = {
        1,3,4,0,0,5,8,5,9,0
    };
    int size = sizeof(arr) / sizeof(arr[0]);
    int i;

    //merge_sort(arr,size);
    merge_sort2(arr,size);
    for(i = 0; i < size; i++)
        printf("%d ",arr[i]);
    puts("");
}
