from random import *

def rand5():
    return int(random()*5)

def rand7():
    while True:
        res = rand5()*5+rand5()
        if res < 21:
            break
    return res//3

N = 100000
count = [0]*7
for i in range(0,N):
    idx = rand7()
    count[idx]+=1
for i in range(0,7):
    print(count[i]*1.0 / N)
