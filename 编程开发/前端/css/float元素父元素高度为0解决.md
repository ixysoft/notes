# float父元素高度为0  
由于float属性的特点,其父元素高度会变成0.很多时候我们需要让父元素的高度与子元素的高度一致,这个时候可以用下面的方案解决:  
1. 方案1:在浮动元素下面放一个清楚浮动的元素:`div{clear:both;}`  
html  
```html
<div class="clearfix">
    <div style="float: left;">Div 1</div>
    <div style="float: left;">Div 2</div>
</div>
```
css  
```css
.clearfix:after{
    content: ' ';
    display:block;
    height:0;
    clear: both;
}
```
2. 将父元素设置为浮动  
html  
```html
<div style="float:left">
    <div style="float:left;">Div 1</div>
    <div style="float:left;">Div 2</div>
</div>
```
3. 为父元素显示的设置高度.  
4. 为父元素加入overflow:hidden或overflow:auto属性.  
上述方案中,方案一最好,兼容性最强.
