# Debian上安装RabbitMQ-Server
我在RabbitMQ在debian上安装过程中遇到了很多坑,官网网站上的安装方法隐藏的比较深,而且讲的并不是特别详细,特别是,按照上面的方法安装还无法启动RabbitMQ.最后这个问题在Google上找到了答案:  
可以利用:`http://www.rabbitmq.com/releases/rabbitmq-server/v3.4.3/rabbitmq-server_3.4.3-1_all.deb`这个网址下载到一个可用的rabbitmq-server安装包,将这个安装包下载到本地之后,再利用`dpkg -i rabbitmq-server_3.4.3-1_all.deb`安装这个包,在安装过程中,可能会出现依赖问题,此时执行一下`sudo apt install -f`,该命令执行成功后,再重复执行刚刚的dpkg命令即可安装好rabbitmq-server.  
为了验证rabbitmq-server安装成功,可以执行`rabbitmqctl status`查看当前的状态.  
