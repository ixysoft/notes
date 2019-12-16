#coding=utf-8
# 题目大意是求一个固定边界的数列中未出现的数字
import random

def getSet(size,cut): # 获取打乱并剔除指定数目的数据的集合
    li = list(range(1,size+1))
    random.shuffle(li)
    return set(li[cut:])
scale = 1000000 # 数据规模
cuted = 1000    # 数据剔除数
li = getSet(scale,cuted) #获取数据剔除后的集合
li_raw = set(range(1,scale+1)) # 获取1~100的集合
print(li_raw - li) # 取差集
