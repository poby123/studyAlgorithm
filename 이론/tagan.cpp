/*
그래프 예시: https://blog.naver.com/ndb796/221236952158

노드번호, 연결된 정점들, -1
1 2 -1
2 3 -1
3 1 -1
4 2 5 -1
5 7 -1
6 5 -1
7 6 -1
8 5 9 -1
9 10 -1
10 11 -1
11 3 8 -1
*/

#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie(0)->sync_with_stdio(0)
#define endl '\n'
#define MAX 11

vector<int> G[MAX + 1];
vector<vector<int>> SCC;
stack<int> s;
int nodeId[MAX + 1], done[MAX + 1], id;

void input()
{
    for (int i = 1; i <= MAX; i++)
    {
        int node, connected;
        cin >> node;

        while (1)
        {
            cin >> connected;
            if (connected == -1)
            {
                break;
            }

            G[node].push_back(connected);
        }
    }
}

// 부모의 값을 반환
int dfs(int cur)
{
    // 노드마다 고유한 번호를 할당한다. 
    // 아래와 같이 하면 dfs로 탐색한 순서를 노드에 할당하는 것이기 때문에 우선순위를 정해줄 수 있다.
    // 노드의 번호로 하게 되면, 노드번호와 그 우선순위가 안맞는 경우가 있기 때문에 안된다.
    // ex) 4 -> 7 -> 2 -> 4 에서 2번 노드는 min(parent, nodeId[next])에서 부모로 2를 반환할 것이고, 제대로 동작하지 못한다.
    int parent = nodeId[cur] = ++id;
    s.push(cur);

    for (int next : G[cur])
    {
        // 방문하지 않은 이웃
        if (!nodeId[next])
        {
            parent = min(parent, dfs(next));
        }

        // 처리중인 이웃. 사이클 발견
        else if (!done[next])
        {
            parent = min(parent, nodeId[next]);
        }
    }

    // 부모 노드가 자기 자신
    if (parent == nodeId[cur])
    {
        vector<int> scc;

        while(1){
            int t = s.top();
            s.pop();
            scc.push_back(t);
            done[t] = 1;
            
            if(t == cur) break;
        }

        SCC.push_back(scc);
    }

    return parent;
}

int main()
{
    fastio;
    input();

    for (int i = 1; i <= MAX; i++)
    {
        if (!nodeId[i])
        {
            dfs(i);
        }
    }

    cout << "SCC의 개수 : " << SCC.size() << endl;
    for (auto v : SCC)
    {
        for (int i : v)
        {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}
