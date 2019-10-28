# fixed元素失效
今天调整一个样式的时,需要在指定位置设定position属性为fixed,但是在设置之后发现使用fixed属性没有任何效果.  
经过google之后,了解到fixed属性的祖先元素的transform属性不为none会影响到元素的表现.  
