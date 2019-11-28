# Mysql签名无效
今天重新安装mysql的时候,有一步需要执行apt update.  
执行之后显示:  
```
W: GPG 错误：http://repo.mysql.com/apt/ubuntu bionic InRelease: 下列签名无效： EXPKEYSIG 8C718D3B5072E1F5 MySQL Release Engineering <mysql-build@oss.oracle.com>
E: 仓库 “http://repo.mysql.com/apt/ubuntu bionic InRelease” 没有数字签名。
N: 无法安全地用该源进行更新，所以默认禁用该源。
N: 参见 apt-secure(8) 手册以了解仓库创建和用户配置方面的细节。
W: GPG 错误：http://repo.mongodb.org/apt/ubuntu xenial/mongodb-org/3.6 Release: 下列签名无效： EXPKEYSIG 58712A2291FA4AD5 MongoDB 3.6 Release Signing Key <packaging@mongodb.com>
E: 仓库 “http://repo.mongodb.org/apt/ubuntu xenial/mongodb-org/3.6 Release” 没有数字签名。
N: 无法安全地用该源进行更新，所以默认禁用该源。
N: 参见 apt-secure(8) 手册以了解仓库创建和用户配置方面的细节。
```
跟上方错误类似的提示,经过一番查资料,发现是签名的问题,重新加上签名就好了.  
```

sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 8C718D3B5072E1F5
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 58712A2291FA4AD5
```
