#include<stdio.h>
#include<string.h>

char rotate_table[] = {
  //0,1,2, 3, 4,5,6, 7,8,9
    0,1,2,-1,-1,5,9,-1,8,6
};

char isRotateNumber(char * num,int len){
    int i;
    int l = (len+1) / 2;
    char n1,n2;
    for(i = 0; i < l; i++){
        n1 = num[i] - '0';
        n2 = num[len - 1 - i] - '0';
        if(rotate_table[n1] != n2) return 0;
    }
    return 1;
}

int main(){
    int N;
    printf("输入数字位数:");
    scanf("%d",&N);
    char num[16];
    int res = 1;
    int i;
    for(i = 0; i < N; i++) res*=10;
    for(i =N == 1 ? 0 : res/10; i < res; i++){
        sprintf(num,"%d",i);
        if(isRotateNumber(num,N)) printf("%d\n",i);
    }

    return 0;
}
