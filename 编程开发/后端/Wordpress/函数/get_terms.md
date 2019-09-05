# get_terms
**说明**  
检索分类法或分类法列表中的term.  
**用法**  
`get_term($taxonomies, $args = '')`  
传递变量按`wp_parse_args()`等函数所用的格式.  
`$myterms = get_terms('orderby=count&hide_empty=false');`  
未指定值的变量使用以下的默认值(下文中有说明).  
下面的列表中含有$args,将讲些默认值.  
```
$args = [
    'orderby'   =>  'name', //排序依据
    'order'     =>  'ASC',  //升序降序
    'hide_empty'=>  true,   //隐藏空条目
    'exclude'   =>  [],     //排除
    'exclude_tree'  =>  [],
    'include'   =>  [],
    'number'    =>  10,     //返回条目
    'fields'    => 'all',   //默认all
    'slug'      =>  '',     //任何含有slug的term都可以作为该变量的值
    'parent'    =>  '',
    'hierarchical'=>true,   //是否返回层级分类法,默认为true
    'child_of'  =>  0,      //默认为0,获取该term的所有后代
    'get'       =>  ,       //可以通过为'all'复制来改写'hide_empty'和'child_of'
    'name_like' =>  '',   //默认为''
    'pad_counts'=>  false,  //默认为false,为true时将计算包括$terms在内的所有子元素
    'offset'    =>  0,
    'search'    =>  ,
    'cache_domain'=>'core'
];
```
**e.g.**  
字符串形式:  
```php
$categories = get_terms('category','orderby=count&hide_empty=1');
```  
数组形式:  
```php
$categories = get_terms('category',[
    'orderby' => 'count',
    'hide_empty' => 0
]);
```
获取所有的友情链接的分类:  
```php
$link_categories = get_terms('link_category','orderby=count&hide_empty=0');
```
列出所有不带链接的自定义分类:  
```php
$terms = get_terms('my_taxonomy');
$count = count($terms);
if($count > 0){
    echo "<ul>";
    foreach ( $terms as $term ){
        echo "<li>" . $term->name . "</li>";
    }
    echo "</ul>";
}
```  
列出所有带上链接的自定义分类:  
```php
$args = ['taxonomy'=>'my_term'];

$terms = get_terms('my_term',$args);

$count = count($terms);
$i = 0;
if($count > 0){
    $cape_list = '<p class="my_term-archive">';
    foreach($terms as $term){
        $i++;
        $term_list .= '<a href="/term-base/"' . $term->slug . '" title="'. sprintf(__('View all post filed under %s', 'my_localization_domain'),$term->name). '">' . $term->name . '</a>';
        if($count != $i){
            $term_list .= ' - ';
        }else{
            $term_list .= '</p>';
        }
    }
    echo $term_list;
}
```
