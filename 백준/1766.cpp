/*
    https://www.acmicpc.net/problem/1766
    위상정렬 문제.
    그래프는 인접리스트로 표현하자.
    
    1. DFS 풀어보자.
    https://www.acmicpc.net/board/view/73021 이유 때문에 막히게 됐다..
    
    2. 진입차수를 이용한 우선순위 큐 이용.
*/

#include <bits/stdc++.h>
using namespace std;
#define MAX 32001

int N, M, inDegree[MAX];
vector<int> G[MAX];
priority_queue<int> pq;

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    
    for(int i=0;i<M;i++){
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        ++inDegree[b];
    }
    
    for(int i=1;i<=N;i++){
        // 진입차수가 0인 노드를 우선순위 큐에 넣습니다.
        // 음수로 만들어서 넣음으로써, 쉬운 문제부터 풀어야한다는 문제의 3번조건을 만족할 수 있게 합니다. 
        
        if(!inDegree[i]){
            pq.push(-i);
        }
    }
    
    while(!pq.empty()){
        int cur = -pq.top();
        pq.pop();
        cout << cur << " ";
            
        // 현재 노드와 연결된 노드들의 진입차수를 줄이고, 0이 됐으면 우선순위 큐에 넣습니다.
        for(auto i : G[cur]){
            if(!--inDegree[i]){
                pq.push(-i);
            }
        }
    }
    
    return 0;
}
