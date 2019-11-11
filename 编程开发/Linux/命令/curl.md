# curl命令
用于向指定的地址发送请求并获取响应信息的命令.类似于postman  
在默认情况下`curl`命令发送`GET`请求  
```
curl https://api.ixysoft.cn/tel/17712345678
```
这个命令会向`https://api.ixysoft.cn/tel/17712345678`这个地址发送`GET`请求,服务器返回的内容会在命令行输出.  
**各个选项:**  
**-A** 指定客户端的用户代理表头,即`User-Agent`,默认情况下curl发送`curl/版本信息`
```
$ curl -A 'Wechat/hello' https://www.baidu.com
```
**-b** 向服务器发送cookie,可以用多个-b发送多个cookie选项,也可以指定cookie的文件发送  
```
$ curl -b 'name=Francis' https://www.baidu.com
```
**-c** 将从服务端获取的cookie写入文件  
```
$ curl -c cookie.txt https://www.baidu.com
```
**-d** 向指定地址发送`POST`请求的数据体,与`-b`选项一样,`-d`也可以指定一个文件  
```
$ curl -d 'name=Francis&age=24' http://www.baidu.com
```
**--data-urlencode** 跟`-d`功能相同,区别在于,该选项会对需要发送的数据进行`url`编码  
```
$ curl --data-urlencode 'msg=this is just a test!' https://www.baidu.com
```
**-e** 用于设置`HTTP`标头的`Referer`以指定请求源.  
```
$ curl -e 'https://www.baidu.com/s?wd=apple' https://www.baidu.com
```
**-F** 用于向地址上传二进制文件  
```
$ curl -F 'file=@test.c' https://www.baidu.com
```
该选项会在请求头中加入`Content-Type: multipart/form-data`,然后将`test.c`作为`file`字段上传.该选项可以指定`MIME`类型  
```
$ curl -F 'file=@test.c;type=text/plain' https://www.baidu.com
```
**-G** 采用`GET`方式发送数据
```
$ curl -G -d 'wd=Francis' http://www.baidu.com/s
```
如果没有`-G`选项`-d`默认发送`POST`请求  
`-G`选项可以结合`--data-urlencode`选项使用  
**-H** 添加请求头条目  
```
$ curl -H 'Content-Type: text/css;charset=UTF8' https://www.baidu.com
```
**-i** 输出结果中附带请求头信息  
```
curl -i https://www.baidu.com
```
**-I** 向服务器发送`HEAD`请求
```
$ curl -I https://www.baidu.com
```
等价于`--head`  
**-k** 跳过`SSL`检测  
```
$ curl -k https://www.baidu.com
```
该选项不会检查`SSL`证书的正确性  
**-L** 重定向跟随
```
$ curl -L 'http://blog.ixysoft.cn'
```
**--limit-rate** 设置请求与回应的带宽,模拟各种速度的网络环境  
```
$ curl --limit-rate 200k https://www.baidu.com
```
经测试好像没有作用,不知道是不是我测试姿势有问题  
**-o** 输出响应的内容到文件,与`wget`类似  
```
$ curl -L -o index.html https://blog.ixysoft.cn
```
**-O** 不需要指定文件名,自动将网址最后部分视作文件名  
**-s** 不输出错误和进度(以安静模式进行)  
**-S** 指定只输出的错误信息,常与`-s`一起使用  
**-u** 设置服务器认证的用户名和密码
```
$ curl -u 'fx:123456' https://www.baidu.com
命令设置用户名为fx,密码为123456,并将其转为请求头`Authorization: Basic Zng6MTIzNDU2`
```
**-v** 输出请求的整个过程,一般用于调试  
**-x** 指定请求代理  
```
$ curl -x sock5://username:password@127.0.0.1:8080 https://www.google.com
```
**-X** 指定请求方法  
