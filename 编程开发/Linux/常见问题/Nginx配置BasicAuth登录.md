# Nginx配置Basic Auth登录认证
1. 安装httpd-tools  
```
apt install httpd-tools
```
2. 创建授权用户及密码   
```
htpasswd -c -d 导出auth文件路径 用户名
```
3. 配置Nginx  
在对应配置文件的server配置中添加:  
```
auth_basic "名称";
auth_basic_user_file 认证文件路径;
```
4. 重新载入配置文件  
```
nginx -t # 测试配合文件是否存在错误
nginx -s reload # 重新载入配置文件
```
5. 访问对应的url  
访问对应的URL,此时会要求输入用户名密码.  
