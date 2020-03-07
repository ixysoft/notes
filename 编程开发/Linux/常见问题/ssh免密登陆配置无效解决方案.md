# SSH免密登陆配置正常但是无法登陆的问题  
1. 查看安全日志`cat /var/log/secure`，定位到是因为autothorized_keys文件及其所在目录的问题。  
2. 修改权限：`chmod g-w ~/.ssh/authorized_keys`,`chmod g-w ~/.ssh/`  
3. 再次登陆，此时成功
