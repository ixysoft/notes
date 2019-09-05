# wp_enqueue_style函数  
**作用**  
将css样式文件加入队列.  
**原型**  
```php
wp_enqueue_style($handle,$src,$deps,$ver,$media);
$handle 字符串  (必须)  样式表文件名  默认None
$src    字符串  (可选)  Wordpress根目录下的样式表路径(如/css/mystyle.css) 默认false
$deps   数组    (可选)  样式表所依靠的句柄组成的数组;加载该样式前需要加载其他样式表.若没有依赖关系,返回false   默认[]
$ver    字符串  (可选)  指示样式表版本号的字符串    默认false
$media  布尔型  (可选)  该字符串指定了为样式表而定义的媒体.如'all','screen','handeld','print'   默认false
该函数无返回值
```
