# Linux上编译51程序
在linux中,可以利用sdcc编译51的c程序.虽然与windows上的keil c有细微的差异,但是大体上相同.  
编译方法:`sdcc xxx.c`  
然后我们利用packihx生成hex文件:`packihx xxx.ihx > xxx.hex`  
之后利用stcflash(https://github.com/laborer/stcflash)进行hex文件烧录即可.  
