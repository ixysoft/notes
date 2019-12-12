#coding=utf-8
#python3

raw_str=input() # 输入字符串

raw_str_list=list(raw_str)
res_dict = {}
for v in raw_str_list:
    if not v in res_dict:
        res_dict[v] = 0
    res_dict[v]+=1

def sort_by_val(d):
    items = d.items()
    tmp_items = [[v[1],v[0]] for v in items]
    tmp_items.sort(reverse=True)
    return [(tmp_items[i][0],tmp_items[i][1]) for i in range(0,len(tmp_items))]

res_list=sort_by_val(res_dict)
ret = ''
for v in res_list:
    for i in range(0,v[0]):
        print(v[1],end='')
print()
