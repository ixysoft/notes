# 记一次华为平板的刷机过程  
之前一段时间在国内的rom网站上找了一个看起来像模像样的ROM，刷完之后发现耗电特别快，想要刷回去，结果发现官方的刷机包不给下载了。。。。绝对是老用户与狗。。。  
无奈，这件事情搁置了很长时间，今天突然想到好久没用平板了，就折腾了一下，用中文关键词找了半天都没有有用的线索，无奈硬着头皮去找官方客服，给的答复就是不给。  
无奈就转为搜索英文关键词，终于在[http://huawei-update.com/device-list/m2-a01l](http://huawei-update.com/device-list/m2-a01l)找到了我需要的华为官方刷机包，刷机包的地址都是华为官方的。。。真的是对洋大人十分贴心的说，，，，，。
下载之后里面有2个pdf文件，一个dload文件夹，文件夹里面有一个UPDATE.APP文件，我看教程上说dload放在tf卡根目录会自动读取，然后我的并没有。  
继续搜索，发现UPDATE.APP可以解包（有一个官方的update.app解包工具）出来一堆的img文件，其中就包含`boot.img`,`recovery.img`,`system.img`，我把这三个单独提出来，放到电脑里，再利用提前装好的fastboot,adb命令，执行了如下操作：  
```
fastboot devices # 确认设备是否连接上
adb reboot bootloader # 进入bootloader准备载入img文件
# 进入后
fastboot flash system system.img
# 这里我发现每次拷入一个img文件都需要重新拔插一下usb口，否则无法写入数据
fastboot flash boot boot.img
fastboot flash recovery recovery.img

```
进行了这三步之后，fastboot reboot重启。
此时可以正常进入系统了，但是有一个问题，平板奇卡无比，等了好久都没加载出来桌面，而且也没有初始化的意思，所以我想应该是老的数据影响到了现有系统了，所以利用关机键+音量加键进入recovery，清空cache，恢复出厂设置。这两步做完之后，重启系统，此时系统就很流畅了。此时像是刚买平板时一样设置即可，因为是国外版本，所以自带了google全家桶，美滋滋。。。。
其中好多步骤并不像我说的这么云淡风轻的，好几次在变砖的边缘徘徊，好在最后的结果是好的，所以这里记一下笔记。防止下次忘记
