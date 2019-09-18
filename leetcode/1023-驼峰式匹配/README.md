# 1023-驼峰式匹配
## 题目
如果我们可以将**小写字母**插入模式串 pattern 得到待查询项 query，那么待查询项与给定模式串匹配。（我们可以在任何位置插入每个字符，也可以插入 0 个字符。）  

给定待查询列表 queries，和模式串 pattern，返回由布尔值组成的答案列表 answer。只有在待查项 queries[i] 与模式串 pattern 匹配时， answer[i] 才为 true，否则为 false。  

**示例 1：**  
```
输入：queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FB"
输出：[true,false,true,true,false]
示例：
"FooBar" 可以这样生成："F" + "oo" + "B" + "ar"。
"FootBall" 可以这样生成："F" + "oot" + "B" + "all".
"FrameBuffer" 可以这样生成："F" + "rame" + "B" + "uffer".
```
**示例 2：**  
```
输入：queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBa"
输出：[true,false,true,false,false]
解释：
"FooBar" 可以这样生成："Fo" + "o" + "Ba" + "r".
"FootBall" 可以这样生成："Fo" + "ot" + "Ba" + "ll".
```
**示例 3：**  
```
输出：queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBaT"
输入：[false,true,false,false,false]
解释：
"FooBarTest" 可以这样生成："Fo" + "o" + "Ba" + "r" + "T" + "est".
```

**提示：**  
1. 1 <= queries.length <= 100
2. 1 <= queries[i].length <= 100
3. 1 <= pattern.length <= 100
4. 所有字符串都仅由大写和小写英文字母组成。

## 思路
题目比较绕,我大致分析了一下,就是以大写字母为一个单元的起点将模式字符串和queries中的各个字符串分成不同的单词(或者称为组).queries中字符串对应的组要以该组对应模式字符串组开头.  
例如:  
```
假设
queries:["AppVersion","OldAppVersion"]
pattern:"AP"
则对于queries的第一个元素,我们可以分成["App","Version"]两组,第二个元素分成["Old","App","Version"];而pattern可以分成["A","P"]两组,我们拿第一个元素生成的组中对应的元素与pattern生成的组对应元素开头,App要以A或Ap或App开头.
```
```
题目比较简单,我们将queries中的元素成为query.那我们只需要考虑某个query的情况.  
对于某个query,遍历其中的字符:
如果是大写字符:  
    说明此时已经切换到一个新的组上面,此时query上的字符必须要与pattern对应的字符相同(因为此时pattern也必定需要切换到新的组).
如果不是大写字符:
    判断此时query与pattern当前位置的字符是否相同,如果相同,pattern当前位置后移一位.  
做完这些操作,我们可以判断出query所有分组与pattern分组对应项是否匹配,但是一种情况没有包含,在query所有字符遍历完之后,pattern还存在字符,说明此时pattern与query是不匹配的.
```
