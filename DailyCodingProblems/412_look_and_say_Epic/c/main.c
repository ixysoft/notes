#include<stdio.h>

void look_and_say(char look[],int say[],int n){
    if(n <= 1){
        puts(look);
        return;
    }
    char tmp = look[0];
    int i = 0;
    int cnt = 0;
    int idx = 0;
    do{
        if(look[i] != tmp){
            say[idx<<1] = cnt;
            say[(idx<<1)|1] = tmp-'0';
            idx++;
            cnt = 0;
        }
        tmp = look[i];
        cnt++;
        i++;
    }while(look[i-1] != '\0');
    int last = idx << 1;
    look[0] = '\0';
    for(i = 0; i < last; i++){
        sprintf(look,"%s%d",look,say[i]);
    }
    look_and_say(look,say,n-1);
}

char look[1000000] = "1";
int say[1000000];
 
int main(){
    int N = 50;
   look_and_say(look,say,N);
    return 0;
}
