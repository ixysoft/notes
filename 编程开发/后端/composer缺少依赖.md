今天公司有一个新需求,需要从公司代码库里面拉取一个laravel项目.因为对laravel不是特别了解.所以在安装第三包依赖包的时候就出来了问题.  
执行composer命令,出现一大堆的依赖缺失.看第一个报错,项目要求的PHP最少要7.1以上的版本,查看了一下,本地的php版本是7.0.需要升级PHP.因为本人的环境安装的是debian,所以下意识的运行:`apt search php`,发现软件源里面只有7.0的php.在google上搜索了一下,最终在[tecadmin.net](https://tecadmin.net/install-php-debian-9-stretch/)上找到了解决方法:  
```
sudo apt install ca-certificates apt-transport-https
wget -q https://packages.sury.org/php/apt.gpg -O- | sudo apt-key add -
echo "deb https://packages.sury.org/php/ stretch main" | sudo tee /etc/apt/sources.list.d/php.list
sudo apt update # 刷新软件源
```  
执行完上面的代码,过程一切顺利,然后在终端执行`sudo apt search php`,最新的几个PHP版本都在软件源里,这里我下载了php7.2,php7.2-fpm.  
安装完新的PHP之后,因为在nginx中依然是7.0的sock,所以把nginx站点配置中与7.0相关的配置全部改成了7.2  
上面的问题解决之后,在项目根目录执行`composer install`,依然报错,不过PHP版本的问题已经解决,仔细观察了一下各个问题,都有ext-xxx类似的字段,所以大概知道是PHP扩展缺失导致的问题,ext-后面的xxx表示扩展的名字,在debian里面需要什么扩展直接输入`sudo apt install php7.2-xxx`,不同的扩展对应不同的xxx.  所有的扩展问题解决后,执行`composer install`就完成了远程项目在本地的构建了.

