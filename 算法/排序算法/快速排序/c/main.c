/**
 *  C语言里面是内置了快速排序函数的....
 *  详情参考qsort函数
 *
 *  我们主要是研究这个算法的思想,所以对一些东西进行了假定,
 *  比如qsort中的cmp函数,我们已经假定成排序成从小到大的顺序,所以省略了cmp函数
 *  又在示例中使用的是int类型的数组,所以我们没必要指定每个数据块的大小.
 *  了解了原理之后,我们可以很容易将函数实现成满足需求的方式
 **/

#include<stdio.h>

int quick_sort(int arr[],int size){
    //快速排序排序的边界
    int left = 0;
    int right = size - 1;
    int stack[10000];   //这里用数组实现栈结构,用于存储需要排序的边界,根据自己的需求可以改成对应的结构
    int st = 0;    //栈下标
    int i,j;
    //将初始的边界压入栈中
    stack[st++] = left;
    stack[st++] = right;
    while(st > 0){  //栈非空
        //从栈中弹出表示边界的元素
        j = right = stack[--st];
        i = left = stack[--st];
        //将第一个元素当成标兵元素,所有的元素跟它比较
        int tmp = arr[i];
        while(i < j){
            for(;i<j && arr[j] >= tmp; j--);arr[i] = arr[j];
            for(;i<j && arr[i] <= tmp; i++);arr[j] = arr[i];
        }
        arr[i] = tmp;
        //经过上面的过程,标兵元素的位置被选出

        //分解成子问题,求解tmp左边部分
        if(left < i - 1){
            stack[st++] = left;
            stack[st++] = i-1;
        }
        //以相同的原理,排列tmp右边的部分
        if(right > j + 1){
            stack[st++] = j+1;
            stack[st++] = right;
        }
    }
    return 0;
}

int main(){
    int arr[] = {
        1,3,4,0,0,5,8,5,9,0
    };
    int size = sizeof(arr)/sizeof(arr[0]);
    int i;

    printf("排序前:");for(i = 0; i < size; i++) printf("%d ",arr[i]);puts("");
    quick_sort(arr,size);
    printf("排序后:");for(i = 0; i < size; i++) printf("%d ",arr[i]);puts("");
    return 0;
}
