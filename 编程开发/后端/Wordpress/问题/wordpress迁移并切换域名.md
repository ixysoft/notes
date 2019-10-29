# wordpress迁移并切换域名
[本文来源](https://www.centos.bz/2017/08/move-wordpress-change-domain/)
这个方法给了我很大的帮助:  
首先我们需要先迁移Wordpress:  
1. 打包源数据库与网站整站源码
2. 源码上传到新服务器上,数据库新建(重新安装一遍wordpress)后恢复(用打包的数据库sql恢复).  
3. 将域名解析到新服务器上
4. 删除新服务器wordpress根目录下的wp-config.php文件  
5. 打开域名,重新安装.(这一步有待确认)  

进行了上述操作后,我们接下来需要做得就是更改域名了,这一步涉及到数据库的操作.具体如下:  
```
UPDATE wp_options SET option_value = replace(option_value, 'www.mydomain.com','www.newdomain.com') ;
UPDATE wp_posts SET post_content = replace(post_content, 'www.mydomain.com','www.newdomain.com') ;
UPDATE wp_comments SET comment_content = replace(comment_content, 'www.mydomain.com', 'www.newdomain.com') ;
UPDATE wp_comments SET comment_author_url = replace(comment_author_url, 'www.mydomain.com', 'www.newdomain.com') ;
```
之后再访问网站就会发现原来的链接全部迁移完成了
