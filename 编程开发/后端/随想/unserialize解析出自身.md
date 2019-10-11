# unserialize解析出自身
**描述:**  
unserialize是一个用来解析由serialize函数序列化数据的.如何做到unserialize一个变量,使得解析后的数据与解析前的参数相同呢?  
对于这个问题,我们进行分析,unserialize首先解析的是一个字符串,那么解析前的数据也应该是一个字符串,但是,假设解析之前是一个常规意义上的字符串的话,经过serialize串行话之后,肯定会加上相应的标记,所以此时不会满足要求.我们需要找到一种在不同环境下类型"会变"的类型.可以想到,对象是有这样的功能的,PHP对象有一个__tostring魔术方法,可以将对象转为字符串.  
```
<?php
function Model{
    public $name;
    public $age;
    public $sex;

    function __construct(){
        $this->name = 'Francis';
        $this->age = 24;
        $this->sex = '男';
    }

    //在这里,我们返回对当前对象序列化之后的字符串
    function __tostring(){
        return serialize($this);
    }
}
$model = new Model;
var_dump($model == unserialize($model));    //此时会显示true
```
当然这并不是严格意义上的相同,反序列化之后会生成一个新的对象,只不过对象的内容与原对象内容一致.对反序列化之后的对象依然可以进行反序列化,得到的内容依然是相同的.  
