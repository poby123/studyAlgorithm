# 기본 알고리즘 이론 & 코드 정리
## 목차
- [이분 그래프](#이분-그래프)

<hr/>

### 이분 그래프

##### 이분 그래프란?

<img src="https://gmlwjd9405.github.io/images/data-structure-graph/bipartite-graph1.gif"/>
<p>인접한 정점끼리 서로 다른 색으로 칠해서 모든 정점을 두 가지 색으로만 칠할 수 있는 그래프를 말한다.</p>

##### 이분 그래프인지 확인하는 방법

-   BFS 또는 DFS 탐색을 하면서 노드을 방문한다.
-   노드를 방문할 때마다 두 가지 색 중, 한 가지 색으로 칠한다. 단, 현재 노드와 인접한 노드는 다른 색깔로 칠한다.
-   만약, 현재 노드와 인접한 노드가 같은 색이라면, 이분 그래프가 아니다.
-   노드 방문을 마치고, 모든 노드에 대해 인접한 노드의 색과 같은 경우가 없다면 이분 그래프다.

<span>※ 비연결 그래프인 경우도 고려해야한다.</span>

##### 이분 그래프 확인하는 코드
```c++
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int visit[20001], ans=1, V, E, T;
vector<int> G[20001]; // 인접 리스트
enum COLORS{ EMPTY, RED, BLACK };

void bfs(int);
void dfs(int);

int main()
{
    // 입력
    cin >> V >> E;
    for (int e = 0; e < E; e++)
    {
        int v1, v2;
        cin >> v1 >> v2;
        G[v1].push_back(v2);
        G[v2].push_back(v1);
    }

    // 비연결 그래프를 위해서, 반복문을 통해 모든 노드를 빠짐없이 방문한다.
    for (int v = 1; v <= V; v++)
    {
        if (!ans)
        {
            break;
        }

        if (!visit[v])
        {
            // bfs(v);
            dfs(v);
        }
    }

    cout << "ans : " << ans;

    return 0;
}

//////////////////////////////////
void bfs(int start)
{
    queue<int> q;

    // 시작 지점의 기본 색깔 지정.
    visit[start] = RED;
    q.push(start);

    while (!q.empty())
    {
        int cur = q.front();
        int curColor = visit[cur];
        q.pop();

        // 현재 노드의 인접 리스트를 돌면서 노드 방문
        for (int it : G[cur])
        {
            // 방문한 적이 없다면 다른 색깔로 색칠
            if (!visit[it])
            {
                visit[it] = (curColor == RED ? BLACK : RED);
                q.push(it);
            }

            // 현재 노드와 색깔이 같다면 이분 그래프가 아니다
            else if (visit[it] == curColor)
            {
                ans = 0;
                return;
            }
        }
    }
}

//////////////////////////////////
void dfs(int start)
{
    // 초기 기본 색깔 설정
    if (!visit[start])
    {
        visit[start] = RED;
    }

    int curColor = visit[start];

    // 현재 노드의 인접 리스트를 돌면서 노드 방문
    for (auto it : G[start])
    {
        // 방문한 적이 없다면 다른 색깔로 색칠
        if (!visit[it])
        {
            visit[it] = (curColor == RED ? BLACK : RED);
            dfs(it);
        }

        // 현재 노드와 색깔이 같다면 이분 그래프가 아니다
        else if (visit[it] == curColor)
        {
            ans = 0;
            return;
        }
    }
}
```
