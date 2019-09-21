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
