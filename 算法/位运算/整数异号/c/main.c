#include<stdio.h>

int isOp(int a,int b){
    return (a^b)<0;
}

int main(){
    printf("%d\n",isOp(-1,2));
    return 0;
}
