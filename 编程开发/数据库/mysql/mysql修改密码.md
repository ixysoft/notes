# mysql修改密码
```
alter user 'root'@'localhost' identified with mysql_native_password by '123456';
flush privileges;
```
