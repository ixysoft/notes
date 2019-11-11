#if 0
√ Accepted
  √ 36/36 cases passed (0 ms)
  √ Your runtime beats 100 % of c submissions
  √ Your memory usage beats 100 % of c submissions (6.8 MB)
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum{
    false = 0,
    true = 1
}bool;
/*
 * @lc app=leetcode.cn id=1023 lang=c
 *
 * [1023] 驼峰式匹配
 */

#define isupper(c) ((c)>='A'&&(c)<='Z')
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* camelMatch(char ** queries, int queriesSize, char * pattern, int* returnSize){
    int i,j,k;
    bool* ret = (bool*)malloc(sizeof(bool) * queriesSize);
    int pattern_size = strlen(pattern);
    *returnSize = queriesSize;
    for(i = 0; i < queriesSize; i++){
        char *query = queries[i];
        bool tmp = true;
        for(j = k = 0; query[j] != '\0'; j++){
            if(isupper(query[j])){
                if(query[j] == pattern[k]){
                    k++;
                }else{
                    tmp = false;
                    break;
                }
            }else if(query[j] == pattern[k]){
                k++;
            }
        }
        ret[i] = (tmp && (k == pattern_size));
    }
    return ret;
}

int main(){
    char *queries[] = {
        "FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"
    };
    int size = sizeof(queries) / sizeof(queries[0]);
    int i;
    char *pattern = "FB";
    int retSize;
    bool *ret = camelMatch(queries,size,pattern,&retSize);
    for(i = 0; i < retSize; i++)
        printf("%s ",ret[i]?"true":"false");
    puts("");
    free(ret);
    return 0;
}
