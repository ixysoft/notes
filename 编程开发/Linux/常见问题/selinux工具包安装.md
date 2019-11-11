# selinux工具包安装
今天sftp的时候需要用到setenforce命令,结果显示command not found.  
经过一番google,查到需要安装selinux工具包.  
Redhat:  
```
yum -y install libselinux-utils
```

Debian:  
```
apt install -y selinux-utils
```

安装好工具后,setenforce即可使用了.  
