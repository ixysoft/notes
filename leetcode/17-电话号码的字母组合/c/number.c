#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char letters[][5] = {
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz"
};

/**
 *  numbers 输入的数字字符串
 *  words   用于生成最后的字母组合的字符串
 *  cur     words当前位置的下标
 *  ret     最后的结果二维数组
 *  index   当前ret的下标指针
 **/
void trip(char *numbers,char *words,int cur,char **ret,int *index){
    int i = *index,j;
    if(*numbers != '\0'){   //numbers当前的字符不为尾部
        char idx = *numbers - '2';  //获取当前数字在letters数组中的下标
        for(j = 0; letters[idx][j]!='\0'; j++){ //遍历当前数字按键的所拥有的字母
            words[cur] = letters[idx][j];   //保存当前字母到words的当前位置
            trip(numbers+1,words,cur+1,ret,index);  //在当前字母的状态下,遍历下一个数字的所有情况
        }
    }else{  //已经到了numbers的尾部,此时生成了一个有效的组合
        words[cur] = '\0';  //字符串尾部填0
        ret[i] = (char*)malloc(cur+1);  //为当前的组合申请一块空间
        strcpy(ret[i],words);   //将当前组合存放到刚刚申请的空间
        *index = i+1;   //ret的下标加1
        //printf("%s\n",words);
    }
}

//拨号
char** dial(char *numbers,int *returnSize){
    if(numbers == NULL || numbers[0] == '\0'){  //不存在numbers的情况
        *returnSize = 0;
        return NULL;
    }
    char word[1024];
    int l = strlen(numbers);//输入数字的长度
    int size = 1;   //结果的总数
    int i;
    for(i = 0; numbers[i] != '\0'; i++)
        size*=strlen(letters[numbers[i]-'2']);  //获取所有可能的组合总数
    *returnSize = size; //将size赋给*returnSize
    char **ret = (char**)malloc(sizeof(char*)*size);    //申请存放所有可能情况指针的空间
    int index = 0;  //ret当前的下标
    trip(numbers,word,0,ret,&index);
    
    return ret;
}

int main(){
    int size = 0;
    char** ret = dial("94664",&size);   //传入94664
    int i;
    for(i = 0; i < size; i++){   //输出所有可能的结果
        printf("%s\n",ret[i]);
        free(ret[i]);   //释放掉申请的空间
        ret[i] = NULL;
    }
    free(ret);  //释放掉所有的情况
    ret = NULL;
    return 0;
}
