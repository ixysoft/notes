#mysql 1366字符问题
1. 查看不正确的字符编码  
```
show variables like '%char%'
```
2. 修改编码  
在配置文件中(/etc/mysql/mysql.conf.d/mysqld.cnf)中修改服务端编码.  
3. 转换表编码  
```
alter table `表名` convert to charset utf8;
```
