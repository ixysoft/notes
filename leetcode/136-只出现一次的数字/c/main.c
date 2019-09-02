#if 0
这个题目整体比较简单.
可以利用二进制位出现次数统计的方法得出结果,但是不是特别优秀.
根据这个题目的特殊性,我们可以利用位异或运算的特点解题.
很容易知道两个相同的数字位异或后为0,即a^a == 0.
异或运算也存在交换律性质,所以a^b^a == a^a^b == b
有了这个性质,题目也就不难解决了.
#endif

#include<stdio.h>

int main(){
    int N;
    while(~scanf("%d",&N)){ //这种写法并不适用于leetcode的解题提交形式,我这里主要是讲解题思路
        int res = 0;
        int i;
        int num;
        for(i = 0; i < N; i++){
            scanf("%d",&num);   //获取数列中的某个数字
            res^=num;
        }
        printf("%d\n",res);
    }
    return 0;
}
