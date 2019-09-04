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
