#include<stdio.h>
#include<limits.h>

int max(int a,int b){
    return a>b?a:b;
}

int min(int a,int b){
    return a>b?b:a;
}

double find_middle(int arr1[],int size1,int arr2[],int size2){
    if(size1 > size2) return find_middle(arr2,size2,arr1,size1);    //确保size2 >= size1
    int size = size1 + size2;
    int L1,L2,R1,R2,c1,c2,lo = 0,hi = 2 * size1;
    while(lo <= hi){    //二分法
        c1 = (lo+hi) / 2;
        c2 = size - c1;
        L1 = (c1 == 0) ? INT_MIN:arr1[(c1-1)/2];
        R1 = (c1 == 2*size1) ? INT_MAX:arr1[c1/2];
        L2 = (c2 == 0)?INT_MIN:arr2[(c2-1)/2];
        R2 = (c2 == 2*size2) ? INT_MAX:arr2[c2/2];

        if(L1 > R2)
            hi = c1 - 1;
        else if(L2 > R1)
            lo = c1+1;
        else
            break;
    }
    return (max(L1,L2)+min(R1,R2))/2.0;
}

int main(){
    int arr1[] = {
        1
    };
    int arr2[] = {
        2,3,4,5,7,8,8,9
    };
    //1 2 3 3 4 4 5 5 7 7 8 8 9 9 -> 5
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("中位数:%0.6g\n",find_middle(arr1,size1,arr2,size2));

    return 0;
}
