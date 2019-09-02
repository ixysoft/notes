# 安装(elasticsearch版本6.8.0)
```
wget https://artifacts.elastic.co/downloads/elasticsearch/elasticsearch-6.8.0.zip
unzip elasticsearch-6.8.0.zip
cd elasticsearch-6.8.0
```  
执行
```shell
sudo sysctl -w vm.max_map_count=262144
sudo sysctl -p
```  
之后运行`./bin/elasticsearch`即可启动elasticsearch.  
这个窗口是阻塞式的,如果需要在后台运行,可以执行`./bin/elasticsearch -d`以守护进程的形式运行elasticsearch.  
elasticsearch启动后,在终端中执行:`curl localhost:9200`可以得到一个与当前运行的elasticsearch相关的json对象.  
elasticsearch默认是在本机运行,如果需要外网可用,可以在config/elasticsearch.yml文件中,去掉network.host的注释,将值改成0.0.0.0或者本机的外网ip.重启elasticsearch之后配置生效.  
