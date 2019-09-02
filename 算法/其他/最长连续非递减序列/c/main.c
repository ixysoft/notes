/**
 *  连续1次的我们看成0次,这里需要该的话,只需要把max的初始值改为1即可
 **/
#include<stdio.h>
#include<limits.h>

int main(){
    int N;
    while(~scanf("%d",&N)){
        int max = 0;
        int cur = INT_MAX;
        int last;
        int move = 1;
        for(int i = 0; i < N; i++){
            last = cur;
            scanf("%d",&cur);
            if(cur >= last){
                move++;
                if(move > max) max = move;
            }else{
                move = 1;
            }
        }
        printf("%d\n",max);
    }
}
