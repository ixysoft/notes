# 大量用户访问去重统计
在某些情形下,我们可能需要统计某个网站或者网页的用户访问量.此时有哪些方案可以考虑.  
1. 使用Hash  
利用hash统计不重复的用户访问数量.  
**优点:**  
简单,易实现,准确.  
**缺点:**  
内存占用大,随着key的增加,性能会下降,对于巨量数据,可能不是一种好方式.  
2. 利用bitset  
一个二进制位代表一个用户坑,一个长度为32位变量里面可以表示32个用户的状态.  
**优点:**  
空间占用相对较少,查询方便.  
**缺点:**  
对于用户量不多的情况,其占用空间较大.  
除此之外,需要维护一个非登录用户的bitset.  
3. 使用概率算法  
利用HyperLogLog算法,不存储具体的值,只存放计算概率的相关数据.  
**优点:**  
内存占用少,对于一个指定的key,只需要占用12kb的空间.  
**缺点:**  
计算的数据并不是特别准确,理论上有0.89%的误差.  
