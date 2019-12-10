#coding=utf-8
#python3

def divide(a,b):
    if b == 0:
        return None
    elif b == 1:
        return a
    left = 0
    right = a
    while left < right:
        cur = (left + right)>>1
        res = cur * b
        if res <= a and a - res < b:
            left = right = cur
        elif res > a:
            right = cur - 1
        else:
            left = cur + 1
    return (left,a - left * b)

print(divide(100,31))
