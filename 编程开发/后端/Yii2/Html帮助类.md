# Yii Html帮助类
类:yii\helper\Html
1. 生成标签  
```
Html::tag(标签名,内容,属性)
```
如:  
```
Html::tag('p','Hello,World!',['class'=>'test']);
将会生成
<p class="test">Hello,World!</p>
这样一个元素
```
2. 生成CSS类和样式
```
Html::addCssClass(&$options,class属性值);   //添加新类属性
Html::removeCssClass(&$options,class属性值);//删除类属性值
```
示例:  
```
$options = ['class'=>'btn btn-default'];

if($type === 'success'){
    Html::removeCssClass($options,'btn-default');
    Html::addCssClass($options,'btn-success');
}

echo Html::tag('div','Hello,Test!',$options);
```
3. 标签内容的转码和解码  
为了让内容能够安全的显示,一些HTML特殊字符应该被转码.在PHP中,这个操作由`htmlspecialchars`和`htmlspecialchars_decode`完成
```
$userName = Html::encode($user->name);
echo $userName;
$decodeUserName = Html::decode($userName);
```
4. 表单  
处理表单标签是大量的重复性劳动并且容易出错.因此,Yii提供了一些列的方法来辅助处理表单标签.  
**创建表单:**  
```
Html::beginForm(地址ID,请求方法,表单数据方式);
Html::endForm();    //关闭表单
```
示例:  
```
echo Html::beginForm(['/test','id'=>'testForm'],'post',['enctype'=>'multipart/form']);
echo Html::endFOrm();
```
5. 按钮
```
Html::button(按钮值,按钮属性)   //普通按钮
Html::submitButton(按钮值,按钮属性) //提交按钮
Html::resetButton(按钮值,按钮属性)  //清空按钮
```
6. 输入栏  
input相关的方法有两组:以`active`开头的被称为`active inputs`,`active inputs`依据指定的模型和属性获取数据,而普通input则直接指定数据.  
```
Html::input(类型,输入框name,输入框值,属性); //普通输入
Html::activeInput(类型,模型,模型属性名,属性);   //active输入
```
还有一些其他的input类型参考手册
6.1. 单选复选框  
```
Html::radio(名,选择,属性);
Html::activeRadio(模型,名,属性)

Html::checkbox(名,选择,属性)
Html::activeCheckbox(模型,名,属性)
```
**示例:**  
```
echo Html::radio('agree',true,['label'=>'I agree']);
echo activeRadio($model,'agree',['class'=>'agreement']);

echo Html::checkbox('agree',true,['label'=>'I agree']);
echo Html::activeCheckbox($model,'agree',['class'=>'agreement']);
```
6.2. 下拉框
```
Html::dropDownList(名称,当前值,键值对)
Html::activeDropDownList(模式,名称,键值对)

Html::listBox(名称,当前值,键值对)
Html::activeListBox(模型,名称,键值对)
```
6.3. 多选框列表  
```
Html::checkboxList(名称,已选值,键值对)
Html::activeCheckboxList(模型,名称,键值对)
```
6.4 单选框列表
```
Html::radioList(名称,已选值,键值对)
Html::activeRadioList(模型,名称,键值对)
```
6.5. 标签和错误
```
Html::label(标签值,名称,属性)
Html::activeLabel(模型,名称,属性)

Html::error(模型,名称,属性) //显示单个错误
Html::errorSummary(模型,属性)   //显示单个或多个错误
```
6.6. Input的名和值  
```
此处方法看手册
```
7. 样式表和脚本
```
Html::style(样式)

外联外部css文件:
Html::cssFile('@web/css/ie5.css',['condition'=>'IE 5'])
生成
<!-- [if IE 5]>
    <link href="http://example.com/css/ie5.css" />
<![endif]-->
外联js文件
Html::jsFile('@web/js/main.js')
```
8. 超链接  
```
Html::a(标题,[地址,id],属性)

mailto:
Html::mailto(标题,地址)
```
9. 图片  
```
Html::img('@web/images/logo.png',['alt'=>'Logo'])
生成
<img src="http://example.com/image/logo.png" alt="Logo" />
```
10. 列表  
**无序列表生成:**  
```
echo Html::ul(模型,['item'=>function($item,$index){
    return Html::tag(
        'li',
        $this->render('post',['item'=>$item]),
        ['class'=>'post']
    );
});
```
