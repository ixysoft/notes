# 阿里源
composer.phar下载地址:
```
https://mirrors.aliyun.com/composer/composer.phar
```

全局配置阿里源:
```
composer config -g repo.packagist composer https://mirrors.aliyun.com/composer/
```
取消配置:
```
composer config -g --unset repos.packagist
```
当前项目配置阿里源:
```
composer config repo.packagist composer https://mirrors.aliyun.com/composer/
```
取消阿里源:
```
composer config --unset repos.packagist
```
调试:
```
composer -vvv require alibabacloud/sdk(这里是需要下载的包)
```
