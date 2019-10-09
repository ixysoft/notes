# git push错误
在git push时出现
```
  fatal: remote error:
  You can't push to git://github.com/xxx/xxx.git
  Use https://github.com/xxx/xxx.git
```
错误,此时执行
```
git remote remove origin
git remote add origin https://github.com/xxx/xxx.git
```
再执行git push时会要求输入用户名,密码.  
在网上找到的方案:  
```
执行:
git remote remove origin
git remote add origin git@github.com:/xxx/xxx.git
```
此时再执行git push可以正常执行.  
**原因分析:**  
github中默认的方式是git@github.com:/xxx/xxx.git的方式,而在clone时错误的使用了git协议的方式.  
