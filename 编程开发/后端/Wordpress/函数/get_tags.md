# get_tags  
**原型**:  
`get_tags(string|array $args = '')`  
检索遍历所有文章标签.  
**参数**:  
```
$args (string|array) (Optional) 遍历标签时用到的参数,默认为''
```
**返回值**:  
(WP_Term[]|int) 关于'post_tag'条目对象的$tags数组或其中的一个计数(这半边不是特别理解)  
**实现**:  
```php
function get_tags($tags = '') {
    $tags = get_terms('post_tag',$args);

    if( empty($tags) ) {
        $return = array();
        return $return;
    }

    $tags = apply_filters( 'get_tags', $tags, $args );
    return $tags;
}
```
