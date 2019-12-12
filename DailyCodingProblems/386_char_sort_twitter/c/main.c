#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int cmp(const void* a,const void* b){
    int pa = ((int*)a)[0];
    int pb = ((int*)b)[0];
    return pa < pb;
}

int main(){
    int char_cnt[128][2] = {{0,0}};  //字符出现次数统计
    char str[1024]; //字符串
    int len;
    int i,j,k;

    fgets(str,1024,stdin);
    len = strlen(str);
    str[len-1] = '\0';
    for(i = 0; str[i] != '\0'; i++){
        char_cnt[str[i]][0]++;
        char_cnt[str[i]][1]=str[i];
    }
    qsort(char_cnt,128,sizeof(int)*2,cmp);
    for(i = k = 0; i < 128 && char_cnt[i][0] > 0; i++){
        //printf("%c[%d],%d\n",char_cnt[i][1],char_cnt[i][1],char_cnt[i][0]);
        //continue;
        for(j = 0; j < char_cnt[i][0]; j++){
            str[k++] = char_cnt[i][1];
        }
    }

    puts(str);
    
    return 0;
}
