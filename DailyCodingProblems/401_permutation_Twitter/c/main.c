#include<stdio.h>
#include<string.h>

int main(){
    char datas[][10] = {
        "a","b","c","d","e","f","g"
    };
    int permutation[] = {
        0,1,3,2,4,5,6
    };
    char results[100][10];
    int size = sizeof(permutation) / sizeof(permutation[0]);
    int i;
    for(i = 0; i < size; i++){
        strcpy(results[i],datas[permutation[i]]);
    }
    for(i = 0; i < size; i++){
        printf("%s\n",results[i]);
    }
}
