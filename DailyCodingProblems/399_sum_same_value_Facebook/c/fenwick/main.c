#include<stdio.h>

#define SIZE  10000
int fenwick[SIZE];
int result[3][SIZE];

int lowbit(int num);   //获取该数字最小有效位(1)
void update(int i,int max,int val);  //
int sum(int i); //0 - i区间的数字和
int getResult(int arr[],int size,int result[3][SIZE]);

int main(){
    int arr[] = {
        1,1,1,3,4,2,8,1,1,2,2,2,2
    };
    int size = sizeof(arr) / sizeof(arr[0]);
    int i,j;
    if(!getResult(arr,size,result)){
        printf("null\n");
    }else{
        printf("[\n");
        for(i = 0; i < 3; i++){
            printf("    [");
            for(j = 0; result[i][j] >= 0; j++){
                printf("%d%c",result[i][j],result[i][j+1] == -1 ? '\0':',');
            }
            printf("]%c\n",i == 2 ? '\0' : ',');
        }
        printf("]\n");
    }
    return 0;

}

int lowbit(int num){
    return num & (-num);
}

void update(int i,int max,int val){
    i+=1;   //索引从1开始算
    while(i <= max){
        fenwick[i-1] += val;
        i += lowbit(i); //最低有效位进1
    }
}

int sum(int i){
    i+=1;
    int s = 0;
    while(i > 0){
        s+=fenwick[i-1];
        i -= lowbit(i);
    }
    return s;
}

int getResult(int arr[],int size,int result[3][SIZE]){
    int i,j,k;
    for(i = 0; i < size; i++)
        update(i,size,arr[i]);

    int s = sum(size - 1);  //获取序列的和
    if(s % 3 != 0) return 0;
    s /= 3;
    int start = 0;
    for(i = j = 0; i < 3; i++){
        for(k=0;j < size && (sum(j) - start <= s);j++,k++){
            result[i][k] = arr[j];
        }
        if(sum(j-1) - start != s) return 0;   //不能凑出s
        start = sum(j-1);
        result[i][k] = -1;
    }
    return 1;   //只要凑出2个等于s的,第三个区间的和必然是s
}
