# 计数排序
基数排序是一个典型的用空间换时间的算法,在需要排序的区间范围不大的时候.其效率远高于比较排序(快速排序等)  
思路:
给定一个可能容纳所有元素的缓存空间,初始化所有值为0,遍历待排序数组,每遍历一个数字,在数字对应的下标元素值+1.遍历完成待排序数组后,我们再遍历一遍缓存空间,想待排数组放入缓存数组下标对应的值的个数的下标.这句话说得有点糊涂,这里举个例子就懂了.   
e.g.  
`1,3,4,0,0,5,8,5,9,0`
申请一个临时空间,用于存储待排数组中数字出现的次数  
```
0 1 2 3 4 5 6 7 8 9 (申请的临时空间的下标值)
0 0 0 0 0 0 0 0 0 0
```  
按照上面的方法遍历:(申请了十个值)  
```
0 1 2 3 4 5 6 7 8 9
3 1 0 1 1 2 0 0 1 1
```  
下标对应待排数组中的数字,里面的值代表对应数字出现的次数  
从左到右遍历缓存数组即得到排好的数据:  
```0 0 0 1 3 4 5 5 8 9```
