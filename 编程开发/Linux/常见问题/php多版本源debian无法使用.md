# 在debian中无法使用ondrej/php ppa源
在debian中无法使用ondrej/php源，添加源之后显示opengpg无效。  
遇到此问题时可以切换成另一个源，这里是操作的过程:
```
apt install apt-transport-https lsb-release ca-certificates
wget -O /etc/apt/trusted.gpg.d/php.gpg https://packages.sury.org/php/apt.gpg
echo "deb https://packages.sury.org/php/ $(lsb_release -sc) main" > /etc/apt/sources.list.d/php.list
apt update
```
经过这些操作之后，就可以安装多个php版本了.
