#include<stdio.h>

int main(){
    int n;
    while(~scanf("%d",&n)){
        int res = 0;
        switch(n&0x03){
            case 0:
                res = n;
                break;
            case 1:
                res = 1;
                break;
            case 2:
                res = n+1;
                break;
            case 3:
                res = 0;
                break;
        }
        printf("%d\n",res);
    }
}
