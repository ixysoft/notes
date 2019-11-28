# /dev/null权限问题
之前因为需要解决一个问题,直接把/etc/apt/下面的相关文件删除了,导致引入了一个很大的bug,余波至今.  
今天安装mysql的时候,这个问题有复现了.正好趁着这个机会研究了一下这个问题,在askubuntu.com上找到了一种可以的方案:  
`/dev/null` should have `0666` permissions and that is what `/etc/udev/rules.d/device-permissions.rules` says:
```
KERNEL=="null|zero|full|random|urandom", MODE="0666"
```
But unfortunately this is a virtual server. So the kernel has not been updated:
```
# uname -a
Linux memocamp 2.6.32-042stab063.2 #1 SMP Tue Oct 23 16:24:09 MSK 2012 x86_64 x86_64 x86_64 GNU/Linux
```
A temporary fix is to manually set the permissions:
```
chmod go+rw /dev/null
```

上面的方案执行之后在执行apt update就不会出现卡死的情况.  
