# 树莓派折腾笔记
1. 内置chromium无法启动  
右键菜单中的快捷方式，点击属性，桌面项，在《命令》输入框最後面加上--no-sandbox  
2. 树莓派4执行gpio readall显示找不到主板信息  
这是由于树莓派原装的wiringPi库没有及时更新导致的，只需要更新wiringPi库即可正常  
```
cd /tmp
wget https://project-downloads.drogon.net/wiringpi-latest.deb
sudo dpkg -i wiringpi-latest.deb
```
安装完成后，可以通过：`gpio -v`检查是否安装成功.  
3. 切换桌面
在使用树莓派的时候,原装桌面有时候不一定好用,所以有时候就会需要切换桌面,此时我们可以使用:  
```
update-alternatives --config x-session-manager
```
该指令执行完之后,会出现一个选择界面,在界面中选择需要的桌面即可.  
4. 树莓派国内源
```
# 编辑 `/etc/apt/sources.list` 文件，删除原文件所有内容，用以下内容取代：
deb http://mirrors.tuna.tsinghua.edu.cn/raspbian/raspbian/ buster main non-free contrib
deb-src http://mirrors.tuna.tsinghua.edu.cn/raspbian/raspbian/ buster main non-free contrib

# 编辑 `/etc/apt/sources.list.d/raspi.list` 文件，删除原文件所有内容，用以下内容取代：
deb http://mirrors.tuna.tsinghua.edu.cn/raspberrypi/ buster main ui
```
5. 给树莓派添加LCD屏幕驱动  
```
1. 从github克隆LCD-show需要的驱动库
git clone https://github.com/goodtft/LCD-show.git
2. 克隆完成后,切换到库目录
cd LCD-show
3. 执行屏幕对应的驱动文件,我的是3.5寸的屏幕,所以执行LCD35-show
./LCD35-show
```
6. 添加自定义分辨率  
有时候树莓派支持的分辨率可能并不能跟自己电脑显示器的分辨率对应.  
这个时候我们可以自己新建一个分辨率  
```
1. 计算分辨率参数
cvt 1366 768
将会输出
# 1368x768 59.88 Hz (CVT) hsync: 47.79 kHz; pclk: 85.25 MHz
Modeline "1368x768_60.00"   85.25  1368 1440 1576 1784  768 771 781 798 -hsync +vsync
2. 新建分辨率
xrandr --newmode "1368x768_60.00"   85.25  1368 1440 1576 1784  768 771 781 798 -hsync +vsync
3. 将分辨率添加到显示输出
xrandr --addmode HDMI-1 1368x768_60.00
如果不知道显示输出怎么填可以执行一次xrandr
4. 设置显示输出使用该分辨率
xrandr --output HDMI-1 --mode 1368x768_60.00
5. 持久化
现在终端中执行这些指令,如果出现什么问题,重启即可,如果没有问题,可以将2,3,4步的命令写入到
/etc/X11/Xsession.d/30x11-set_resolution中
```
6. 安装屏幕键盘  
```
apt install florence
执行florence命令将会弹出屏幕键盘.
如果出现org.florence没有安装的信息,则执行sudo glib-compile-schemas /usr/share/glib-2.0/schemas/
之后再次执行florence命令即可.  
```
安装可以在登陆界面显示的屏幕键盘
sudo apt-get install lightdm-gtk-greeter
之后编辑配置文件
vim /etc/lightdm/lightdm-gtk-greeter.conf
编辑配置文件:
[greeter]
keyboard=florence --no-gnome --focus &

## 链接显示屏无反应的解决  
从github中下载LCD-Show库,运行其中的LCD-HDMI文件.