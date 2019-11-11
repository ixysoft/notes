# Tar.php问题
今天由于升级了一下php-redis插件,导致php7.2redis插件突然就出问题了,无奈使用pecl install redis安装(apt install php-redis安装不报错,但是没有卵用).  
执行之后报错:
```
PHP Fatal error:  Cannot use result of built-in function in write context in /usr/share/php/Archive/Tar.php on line 639
```
从上面这句报错可以看出639行出现错误,打开文件,发现语句如下:  
```
 $v_att_list =& func_get_args();
```
我们将func_get_args方法前面的&去掉,这个bug即解决了.  
