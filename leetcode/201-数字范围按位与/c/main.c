#include<stdio.h>

int main(){
    int a,b;
    while(~scanf("%d%d",&a,&b)){
        int mask = 1 << 30;
        int prod = a ^ b;
        int res = 0;
        for(;mask>0;mask>>=1){
            if((prod&mask) == 0){  //ab对应二进制位相同
                res|=(a & mask);
            }else{
                break;
            }
        }
        printf("%d\n",res);
    }
    return 0;
}
