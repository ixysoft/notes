#coding=utf-8
from math import *
import os

# 获取16进制位数
def getBits(a):
    if a == 0:
        return 0
    return floor(log(a,16))+1

# 获取16进制数编码
def base64(a):
    tail = 1
    ret = ''
    table = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/'
    while a > 0:
        if a % 64 == 0 and tail == 1:
            ret = '=' + ret
        else:
            tail = 0
            ret = table[a%64] + ret
        a = a // 64
    return ret

try: # python2
    a = int(raw_input('请输入一串16进制数:').strip(),16)
except Exception: # python3
    a = int(input('请输入一串16进制数:'),16)
except: #异常处理
    print('数字格式错误')
    os._exit(1)

bits = getBits(a)
padBits = int((bits//6+1)*6 - bits)%6
na = a << (4*padBits)

print(base64(na))
