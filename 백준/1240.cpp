// https://www.acmicpc.net/problem/1240

/*
문제
N(2≤N≤1,000)개의 노드로 이루어진 트리가 주어지고 M(M≤1,000)개의 두 노드 쌍을 입력받을 때 두 노드 사이의 거리를 출력하라.

입력
첫째 줄에 노드의 개수 N이 입력되고 다음 N-1개의 줄에 트리 상에 연결된 두 점과 거리(10,000 이하의 정수)를 입력받는다. 
그 다음 줄에는 거리를 알고 싶은 M개의 노드 쌍이 한 줄에 한 쌍씩 입력된다.

출력
M개의 줄에 차례대로 입력받은 두 노드 사이의 거리를 출력한다.

예제 입력 1 
4 2
2 1 2
4 3 2
1 4 3
1 2
3 2
예제 출력 1 
2
7
*/

#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

#define MAX 1001

int N, M, visit[MAX];
vector<pair<int,int>> G[MAX]; // dest, cost

int bfs(int start, int end){
    queue<pair<int,int>> q; // next, accCost
    memset(visit, 0, sizeof(visit));

    q.push({start, 0});
    visit[start] = 1;

    while(!q.empty()){
        auto frt = q.front();
        int cur = frt.first;
        int accCost = frt.second;

        q.pop();

        if(cur == end){
            return accCost;
        }

        for(auto it : G[cur]){
            int next = it.first;
            int cost = it.second;

            if(!visit[next]){
                visit[next] = 1;
                q.push({next, accCost + cost});
            }
        }    

    }

    return -1;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    
    for(int i=0;i<N-1;++i){
        int a, b, c;
        cin >> a >> b >> c;
        G[a].push_back({b, c});
        G[b].push_back({a, c});
    }

    for(int i=0;i<M;++i){
        int a, b;
        cin >> a >> b;

        cout << bfs(a, b) << "\n";
    }


    return 0;
}