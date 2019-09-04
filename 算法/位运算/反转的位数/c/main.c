#include<stdio.h>

int main(){
    int a,b;
    while(~scanf("%d%d",&a,&b)){
        int count = 0;  //反转的次数
        int c = a^b;
        for(;c;c&=c-1,count++);
        printf("%d\n",count);
    }
}
