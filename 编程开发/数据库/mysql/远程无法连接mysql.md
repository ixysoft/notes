# 问题描述
由于在执行mysql_secure_installation时,选择了禁止远程访问,导致远程无法访问.  
这个问题之前已经遇到过,所以很快就有了方案,这里记录一下:  
```
进入mysql配置目录下的/etc/mysql/mariadb.conf.d目录,编辑50-server.cnf文件,将其中的bind-address = 127.0.0.1改成bind-address = 0.0.0.0即可,这里的0.0.0.0也可以改成能被外部访问的其他本机ip
```
