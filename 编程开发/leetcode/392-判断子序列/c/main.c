#include<stdio.h>

typedef enum{
    false = 0,
    true = 1
}bool;

bool isSubsequence(char * s, char * t){
    int i,j;
    for(i = j = 0; s[i] != '\0'; i++){
        for(;t[j] != '\0' && s[i] != t[j];j++);
        if(t[j] == '\0') return false;
        j++;
    }
    return true;
}

int main(){
    char s[128],t[128];
    while(~scanf("%s%s",s,t)){
        printf("%s\n",isSubsequence(s,t)?"true":"false");
    }
    return 0;
}
