#if 0
    这里是构造的leetcode形式的源代码
#endif

#include<stdio.h>
#include<stdlib.h>

int ones(int n){
    int count = 0;
    for(;n > 0;n&=n-1,count++);
    return count;
}

int **subsets(int *nums,int numsSize,int *returnSize,int **returnColumnSizes){
    int end = 1<<numsSize;
    int **ret = (int**)malloc(sizeof(int*)*end);
    *returnColumnSizes = (int*)malloc(sizeof(int)*end);
    int tmp;
    for(int begin = 0;begin < end;begin++){
        int cnt = ones(begin);
        (*returnColumnSizes)[begin] = cnt;
        if(cnt == 0) ret[begin] = NULL;
        else{
            ret[begin] = (int*)malloc(sizeof(int)*cnt);
            tmp = begin;
            for(int i=0,j=0;tmp > 0; tmp>>=1,i++){
                if(tmp&0x01) ret[begin][j++] = nums[i]; 
            }
        }
    }
    *returnSize = end;
    return ret;
}

int main(){
    int nums[] = {
        1,2,3
    };
    int size = sizeof(nums)/sizeof(nums[0]);
    int i,j;
    int returnSize;
    int *returnColSize = NULL;
    int **ret = subsets(nums,size,&returnSize,&returnColSize);
    printf("%d,%d\n",returnSize,returnColSize[0]);
    for(i = 0; i < returnSize; i++){
        for(j = 0; j < returnColSize[i]; j++){
            printf("%d ",ret[i][j]);
        }
        puts("");
    }
    
    return 0;
}
