#include<stdio.h>

int add1(int n){
    int carry = 1;
    while(n&carry){
        n^=carry;
        carry<<=1;
    }
    n^=carry;

    return n;
}

int main(){
    printf("%d\n",add1(127));

    return 0;
}
