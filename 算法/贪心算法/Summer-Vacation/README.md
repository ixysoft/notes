# Summer Vacation
```
Time Limit: 2 sec / Memory Limit: 1024 MB
```
**Problem Statement**  
There are `N` one-off jobs available. If you take the `i`-th job and complete it, you will earn the reward of Bi after Ai days from the day you do it.  
You can take and complete at most one of these jobs in a day.  
However, you cannot retake a job that you have already done.  
Find the maximum total reward that you can earn no later than `M` days from today.  
You can already start working today.  

**Constraints**  
- All values in input are integers.  
- 1 ≤ N ≤ 10^5  
- 1 ≤ M ≤ 10^5  
- 1 ≤ Ai ≤ 10^5  
- 1 ≤ Bi ≤ 10^4  
**Input**  
Input is given from Standard Input in the following format:
```
N M
A1 B1
A2 B2
.
.
.
AN BN
```
**Output**  
Print the maximum total reward that you can earn no later than `M` days from today.

**Sample Input 1**  
```
3 4
4 3
4 1
2 2
```
**Sample Output 1**  
```
5
```
You can earn the total reward of `5` by taking the jobs as follows:  
Take and complete the first job today. You will earn the reward of `3` after four days from today.  
Take and complete the third job tomorrow. You will earn the reward of `2` after two days from tomorrow, that is, after three days from today.  
**Sample Input 2**  
```
5 3
1 2
1 3
1 4
2 1
2 3
```
**Sample Output 2**  
```
10
```
**Sample Input 3**  
```
1 1
2 1
```
**Sample Output 3**  
```
0
```

# 思路
说实话,这个题目我一开始是当背包问题来写的.因为工作的结算时间虽然不同,但是工作时间是相同的,很多工作都是可以选择的,但是用解背包问题的思想,很多问题会交织在一起,难以解决.结算时间只能看做是一个维度,而在结算时间内还能做其他的事情.  
既然用解背包的思路比较困难,这种问题可以试试贪心算法.以剩余时间作为一个标准,选择在剩余时间内能做的工资最高的事情,将这个工作移除队列(剩最短的时间能做的事,能为其他的事空出更多的时间).然后依次按剩余时间递增的顺序遍历出所有在剩余时间内工资最高的工作.  
这样到最后即可获得最高的工资.  
