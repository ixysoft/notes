# Rules验证规则
1. **required**:必须验证属性,CRequiredValidator的别名,确保特性不为空  
```
[['字段名1','字段名2'],'required']    //字段1,字段2必填
[['字段名'],'required','requiredValue'=>'必填值','message'=>'提示信息']
```
2. **email**:邮箱验证||CEmailValidator的别名,确保特性的值为有效的邮箱地址  
```
['email','email']
```
3. **match**:正则验证||CRegularExpressionValidator的别名,确保特性匹配一个正则表达式  
```
[['字段名'],'match','pattern'=>'正则表达式','message'=>'提示信息']
[['字段名'],'match','not'=>'true','pattern'=>'正则表达式','message'=>'正则取反']
```
4. **url**:网址||CUrlValidator的别名,确保特性是一个有效的路径  
```
[['website'],'url','defaultScheme'=>'http']
```
5. **captcha**:验证码||CCaptchaValidator的别名,确保了特性的值始于CAPTCHA显示出来的验证码  
```
['verificationCode','captcha']
```
6. **safe**:安全  
['description','safe']
7. **campare**:比较||CCompareValidator的别名,确保一个值等于另一个特性或者常量  
```
['repassword','compare','compareAttribute'=>'password','message'=>'两次密码不一致']
['age','compare','compareAttribute'=>30,'operator'=>'>=']
```
8. **default**:默认值||CDefaultValidator的别名,为特性指派了一个默认值  
```
['age','default','value'=>null]
```
9. **exist**:存在||CExistValidator的别名,确保属性值存在于指定的数据表字段中.  
```
['字段名','exist']
```
10. **file**:文件||CFileValidator的别名,确保了特性包含了一个上传文件的名称  
```
['primaryImage','file','extensions'=>['png','jpg','gif']]
```
11. **filter**:过滤器||CFilterValidator的别名,使用一个filter转换属性  
```
[['username','email'],'filter','filter'=>'trim','skipOnArray'=>'true']
```
12. **in**:范围||CRangeValidator的别名,确保了特性出现在一个预定的值列表中  
```
['level','in','range'=>[1,2,3]]
```
13. **unique**:唯一性||CUniqueValidator的别名,确保了特性在数据表字段中是唯一的  
```
['字段名','unique']
```  
**唯一联合索引:**  
```
[
    ['app_id','group_id'],
    'unique',
    'targetAttribute'=>['app_id','group_id'],
    'message'=>'app_id和group_id已经被占用'
]
```
14. **integer**: 整数  
```
['age','integer']
```
15. **number**: 数字  
```
['salary','number']
```
16. **double**: 双精度浮点数  
['salary','double']
17. **date**: 日期  
```
[['from','to'],'date']
```
18. **string**: 字符串  
```
['username','string','length'=>[4,24]]
```
19. **boolean**: 布尔值||CBooleanValidator的别名  
```
['字段名','boolean','trueValue'=>true,'falseValue'=>false,'strict'=>true]
```
20. **image**:是否为一个有效的图片文件  
```
[
    'primaryImage',
    'image',
    'extensions'=>'png,jpg',
    'minWidth'=>100,
    'maxWidth'=>1000,
    'minHeight'=>100,
    'maxHeight'=>1000
]
```
21. **each**: 遍历,ids和product_ids是数字的集合  
```
[['ids','product_ids'],'each','rule'=>['integer']]
```
22. **自定义rules**:
```
['password','validatePassword']
/**
 * 创建验证密码发方法
 * @param string $attribute 正在被验证的字段
 * @param array $params 规则中附加的其他键值对
 */
public function validatePassword($attribute, $params)
{
    if (!$this->hasErrors()) {
        $user = $this->getUser();   //获取当前的用户
        if ( !$user || !$user->validatePassword($this->password)) {
            $this->addError($attribute, '账号或者密码错误');
        }
    }
}
```