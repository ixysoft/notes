# HTTP认证方式  
**核对的信息通常如下:**  
1. 密码: 只有本人知道的特定字符串信息
2. 动态令牌: 仅限本人持有的设备内显示的一次性密码
3. 数字证书: 仅限本人持有的信息
4. 生物认证: 指纹和虹膜等本人的生理信息
5. IC卡等: 仅限本人持有的信息  

**HTTP使用的认证方式:**  
- Basic认证(基本认证)  
- Digest认证(摘要认证)  
- SSL客户端认证  
- FormBase认证(基于表单认证)  
## 1. Basic认证  
Basic认证是从HTTP/1.0就定义的认证方式.即便现在仍然有部分网站会使用这种认证方式.是Web服务器与通信客户端之间进行的认证方式.  
过程:  
**发送请求**
```
GET / HTTP/1.1
Host: 127.0.0.1  
```
**1. 服务端返回401状态码**  
```
HTTP/1.1 401 unAuthorizied
WWW-Authenticate: Basic realm=/
```
realm说明了保护的范围  
**2. 输入用户,密码已base64方式编码后发送**
```
GET / HTTP/1.1
Host: 127.0.0.1
Authorization: Basic Zng6MTIzNDU2
```
**3. 认证成功后返回200,失败后继续401**
```
HTTP/1.1 200 OK
...
```
在PHP中可以通过`$_SERVER['PHP_AUTH_USER']`和`$_SERVER['PHP_AUTH_PW']`获取到传递过来的用户名和密码.可以通过这两个字段对用户进行认证.  
**缺点:**  
- Basic认证,账户密码以Base64方式编码,并没有进行加密处理  
- 浏览器无法注销认证  
- 达不到多数web网站期望的安全性等级  
## 2. Digest认证  
Digest认证同样采用质询/响应的方式(challenge/response),但不会像BASIC一样直接发送明文密码.  
质询响应方式:开始一方会发送认证要求给另一方,接着使用从另一方接收到的质询码生成响应码.最后将响应码返回给对方进行认证的方式.  
**发送请求**  
```
GET / HTTP/1.1
Host: 127.0.0.1
```
**1. 发送临时质询码(随机数,nonce)以及告知需要认证的状态码401**
```
HTTP/1.1 401 unAuthorized
WWW-Authenticate: Digest realm="DIGEST",nonce="MOSQZ0itBAA=44abb6784cc9cbf605a5b0893d36f23de95fcff",algorithm=MD5,qop="auth"
```
**2. 发送摘要以及由质询码计算出的响应码(response)**  
```
GET / HTTP/1.1
Host: 127.0.0.1
Authorization: Digest username="guest",realm="DIGEST",nonce="MOSQZ0itBAA=44abb6784cc9cbf605a5b0893d36f23de95fcff",uri="/",algorithm=MD5,response="df56389ba3f7c52e9d7551115d67472f",qop=auth,nc=00000001,cnonce="082c875dcb2ca740"
```
**3. 认证成功返回200,失败发送401**
```
HTTP/1.1 200 OK
Authentication-info: rspauth="f218e9ddb407a3d16f2f7d2c4097e900",cnonce="083c875dcb2ca740",nc=00000001,qop=auth
```
## 3. SSL认证
一般配合其他认证使用.  
## 4. 表单认证
一般常见的认证实现方式.  
