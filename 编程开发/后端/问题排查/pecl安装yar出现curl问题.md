# pecl安装yar出现的问题
今天用pecl安装了一下yar,经过一系列过程之后,爆出了:
```
configure: error: Please reinstall the libcurl distribution - easy.h should be in <curl-dir>/include/curl/
```
问题.  
从描述中可以看出是curl库除了问题,经过一番谷歌,在github中找到了解决方案:  
```
# 创建curl链接
sudo ln -s /usr/include/x86_64-linux-gnu/curl /usr/local/include/curl
# 下载curl库
sudo apt-get install libcurl4-gnutls-dev
```
上面的过程一路正常之后,执行`pecl install yar`,一切安装顺利.  
