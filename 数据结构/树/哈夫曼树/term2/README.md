# huff文件格式
前4个字节:HUF\n
size: 4b key区域长度
key:len:code
...

code区:
size:   4b  二进制code的大小
code的二进制数据

需要的方法:
字符的code转存储形式
    二进制字符串转二进制数组    "10"    -> 0b10
