# Laravel-Totem问题
1. migrate问题
在执行totem的migrate时,在mysql5.7中出现
```
CHARACTER SET utf8mb4 COLLATE `utf8mb4_unicode_ci`附近出错的问题.
```
在mysql中执行提示的语句,也的确有问题.  
经过排查发现是在执行mysql的change时,不能设置编码,故把CHARSET SET utf8mb4这部分去掉,再执行migrate成功.  
确定问题之后,在相应的migrate文件中,更改指定指端的后面加上`->charset('')`.  
操作之后,清空了原先的数据库,然后再执行一遍`php artisan migrate`之后,问题解决.  
2. 无法自动执行任务
在laravel中,无论执行`php artisan schedule:run`还是`php artisan schedule:list`都没有任何的效果.  
问题原因:laravel中存在配置缓存,在安装好totem之后,我们应该做一次`php artisan cache:clear`操作.  
3. totem创建新任务不成功.....
这个问题困恼了我两三天.在网上也没查到相关的问题,只能自己排查问题.在报错的地方,我发现是由于aliyunmns这个第三方库导致的问题,但是没有办法.经过逐步排查后,我怀疑是由于项目刚创建,这个地方没有配置好.回想了一下,应该还没有用到这个地方,所以在app.php中,把`App\Library\AliyunMns\LaravelMnsServiceProvider::class`这个provider注释掉了,然后再执行,之前的问题消失,但是出现了一个新问题.报错无法连接mns很容易看出导致这个错误的原因是还存在其他地方在使用mns.经过一番排查,在.env文件中找到`QUEUE_DRIVER=mns`想,将其改成`QUEUE_DRIVER=sync`之后再执行创建操作,之前的问题消失了,此时执行`php artisan schedule:list`显示也是正常的.计划任务顺利执行.  
原因分析:  
由于第三方库导致的问题.  
解决:  
如果对库不熟悉且该库目前阶段有更好的替代方案,关闭库比排查不熟悉的库更有效.  
