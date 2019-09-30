# 自定义路由不生效
这两天,公司有一个需求需要用到wordpress自定义路由的东西,可是按照网上的教程一步步敲下来,最后却没有用.  
网上比较常见的教程:  
```
function new_rules(){
    add_rewrite_rule(
        'article/(\d+)/?$',//正则
        'index.php?pagename=tag&tag_id=$matches[1]',//实际路由
        'top'   //放在最前端
    );
}
add_action('init','new_rules');
```
然后上面的代码并没有什么卵用.  
之后经过一番查找,终于找到了原因:  
在加入新规则之后,需要对原有的规则进行刷新,否则新规则不生效.  
将上面的new_rules函数改成:  
```
function new_rules(){
    global $wp_rewrite;
    add_rewrite_rule(
        'article/(\d+)/?$',
        'index.php?pagename=tag&tag_id=$matches[1]',
        'top'
    );
    $wp_rewrite->flush_rules(); //加上这句即可
}
```
然后再刷新页面,新的规则就加好了.  
