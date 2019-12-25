#coding:utf-8
class Main:
    table = []
    # 初始化Main对象
    def __init__(self,size):
        self.table = [0] * size
    # 获得最低有效位
    def lowbit(self,v):
        return v & (-v)
    # 更新指定下标的值
    def update(self,i,size,val):
        i+=1
        while i <= size:
            self.table[i-1] += val
            i += self.lowbit(i)
    # 获取0~idx区间的和
    def getSum(self,idx):
        idx+=1
        s = 0
        while idx > 0:
            s += self.table[idx-1]
            idx -= self.lowbit(idx)
        return s
    # 获取[i,j)区间的和
    def sum(self,i,j):
        if i >= j or j < 1: # 给定的下标需要合法
            return 0
        return self.getSum(j-1) - self.getSum(i-1)

datas = [1,2,3,4,5]
size = len(datas)
solution = Main(size)
for i in range(size):
    solution.update(i,size,datas[i])
print(solution.sum(0,3))
