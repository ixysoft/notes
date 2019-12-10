#coding=utf-8

def base64decode(st):
    latex = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/'
    lcap = {}
    idx = 0
    for i in latex:
        lcap[i] = idx
        idx+=1
    ret = 0
    cnt = 0
    for i in st:
        if i == '=':
            cnt += 1
        else:
            ret = (ret << 6) | lcap[i]
    ret = ret >> (12 - 4 * cnt)
    return format(ret,'x')
print(base64decode('3q2+7w=='))
print(base64decode('bmV3IHlvcms='))
