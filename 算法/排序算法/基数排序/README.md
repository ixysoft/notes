# 基数排序  
话说这个算法我都有点忘了  
这个写一下大致思路吧.....  
从低位到高位,以每个数位上的数字为标准确定位置,依次移动数位,知道所有的数位都排列完毕  
e.g.  
有数列`1,11,2,3,42,34,54`
1. 按个位分组(个位相同)  
```
1,11
2,42    
3
54
```  
合并得到一个新的数组:`1,11,2,42,3,54`  
2. 按十位分组(十位相同)
```
1 2 3
11
34
54
```  
合并:`1,2,3,11,34,54`  
得到最后排序完毕的数列  
