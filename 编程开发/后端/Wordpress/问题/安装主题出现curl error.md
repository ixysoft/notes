# 问题描述
今天在家里构建了一套Wordpress系统,安装主题时,出现
```
cURL error 18: transfer closed with 1600284 bytes remaining to read
```
的问题,经过一番谷歌找到了解决方法:
将/var/lib/nginx目录所有者改为www-data  
```
chown -R www-data:www-data /var/lib/nginx
```
这个问题的原因可能是wordpress在利用curl下载文件时,需要借助nginx做中间缓存,而此时php-fpm的运行者www-data没有对/var/lib/nginx的操作权限.导致一直安装不上主题.  
