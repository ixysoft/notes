# Debian9安装mysql
由于社区在debian中移除了mysql的源,改为了mariadb源,这里如果需要安装mysql的话,我们需要加入对应的apt源,具体步奏如下:  
```
# 切入家目录(这里不一定是家目录,不影响当前工作的地方即可)
cd
# 下载apt配置文件
wget https://dev.mysql.com/get/mysql-apt-config_0.8.14-1_all.deb
# 执行这个deb文件
sudo dpkg -i mysql-apt-config_0.8.14-1_all.deb
# 将第一项修改为你需要的mysql版本即可
```
完成上述步奏后,我们需要执行一下`sudo apt update`更新一下源.  
之后再执行`sudo apt install mysql-server`即可安装mysql
