# Laravel-Totem问题
在执行totem的migrate时,在mysql5.7中出现
```
CHARACTER SET utf8mb4 COLLATE `utf8mb4_unicode_ci`附近出错的问题.
```
在mysql中执行提示的语句,也的确有问题.  
经过排查发现是在执行mysql的change时,不能设置编码,故把CHARSET SET utf8mb4这部分去掉,再执行migrate成功.  
确定问题之后,在相应的migrate文件中,更改指定指端的后面加上`->charset('')`.  
操作之后,清空了原先的数据库,然后再执行一遍`php artisan migrate`之后,问题解决.  
