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
