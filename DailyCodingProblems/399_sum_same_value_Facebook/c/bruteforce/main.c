/**
 * 讲真,这个Hard类型的题目看着有点蒙,可能是我没看懂题吧.
 * 在这里我把我心里理解的这道题用我的思路解决出来
 * */
#include<stdio.h>
#define SIZE 1000
int result[3][SIZE];

int getResult(int arr[],int size,int ret[3][SIZE]){
    int i,j,sum = 0;
    for(i = 0; i < size; i++)
        sum+=arr[i];
    if(sum % 3 != 0) return 0;  //不能被3整除
    sum /= 3;
    for(i = j = 0; i < 3; i++){
        int tmp = 0;
        int k = 0;
        for(;j < size && tmp < sum;j++,k++){
            tmp+=arr[j];
            ret[i][k] = arr[j];
        }
        if(tmp != sum) return 0;
        ret[i][k] = -1;
    }
    return j == size;   //遍历到了最后
}

int main(){
    int arr[] = {
        1,3,4,8,2,2,2,2
    };
    int size = sizeof(arr) / sizeof(arr[0]);
    int i,j;
    if(!getResult(arr,size,result)){
        printf("null\n");
    }else{
        printf("[\n");
        for(i = 0; i < 3; i++){
            printf("    [");
            for(j = 0; result[i][j] >= 0; j++){
                printf("%d%c",result[i][j],result[i][j+1] == -1 ? '\0':',');
            }
            printf("]%c\n",i == 2 ? '\0' : ',');
        }
        printf("]\n");
    }
    return 0;
}
