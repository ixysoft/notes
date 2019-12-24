#!/usr/bin/env python3
#coding:utf-8
# 数据节点类
class Node:
    next = None
    val = 0
    def __init__(self,val):
        self.val = val

# 链表类
class List:
    first = None
    length = 0
    def __init__(self):
        self.first = None
        self.length = 0
    # 插入新节点
    def insert(self,val):
        node = Node(val)
        node.next = self.first
        self.first = node
        self.length += 1
        return self
    # 删除指定位置的节点
    def delete(self,k):
        if self.length == 0: #list长度为0
            return False
        if k == 0:
            first = self.first.next
            del self.first
            self.first = first
        else:
            first = self.first
            for i in range(1,k):
                first = first.next
            if not first.next is None:
                next = first.next
                first.next = first.next.next
                del next
        return True
 
    def visit(self):
        first = self.first
        while not first is None:
            print(first.val,end = '')
            if not first.next is None:
                print('->',end = '')
            first = first.next
        print('')

li = List()
li.insert(1)
li.visit()
li.insert(3)
li.visit()
li.insert(4)
li.visit()
li.delete(1)
li.visit()
