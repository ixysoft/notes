#if 0
思路来自: https://blog.csdn.net/Hpuer_Random/article/details/99128977
#endif
#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

struct Node{
    int a;
    int b;
} node[100007];

bool cmp(Node a,Node b){
    return a.a < b.a;
}

int main(){
    int N,M;
    while(cin >> N >> M){
        for(int i = 0; i < N; i++){
            cin >> node[i].a >> node[i].b;
        }
        sort(node,node+N,cmp);
        int idx = 0;
        int sum = 0;
        priority_queue<int> q;
        for(int i = 1; i <= M; i++){
            while(node[idx].a <= i && idx < N){
                q.push(node[idx].b);
                idx++;
            }
            if(!q.empty()){
                sum+=q.top();
                q.pop();
            }
        }
        cout << sum << endl;
    }
    return 0;
}

