# 希尔排序
这个算法的时间复杂度比较难分析.  
这里讲讲思路,希尔排序可以看成插入排序的一种改良版本,跟常规的插入排序不同的是,希尔排序的步长是递减的(所以又被叫做递减增量排序算法),排序中最核心的部分在于步长的选择,希尔排序的效率跟步长有很大的关系.  
初始转态下,步长设置为数组总长度的一般,然后用插入排序的思想,遍历后半边的序列,这样保证了间隔当前步长的元素是有序的(虽然整体不一定有序),然后将步长减半,逐渐使控制更加精细,直到最后排序完毕.虽然表面上每一趟都是借用了插入排序,但是算法整体采用了一种分而治之的手法,使得整体的运算次数减少了很多,加上插入排序本身并没有像冒泡排序选择排序一样,频繁的调用交换,所以性能上整体优于O(N^2)的排序算法.  
