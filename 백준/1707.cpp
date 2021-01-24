/*
문제
그래프의 정점의 집합을 둘로 분할하여, 각 집합에 속한 정점끼리는 서로 인접하지 않도록 분할할 수 있을 때, 그러한 그래프를 특별히 이분 그래프 (Bipartite Graph) 라 부른다.

그래프가 입력으로 주어졌을 때, 이 그래프가 이분 그래프인지 아닌지 판별하는 프로그램을 작성하시오.

입력
입력은 여러 개의 테스트 케이스로 구성되어 있는데, 첫째 줄에 테스트 케이스의 개수 K(2≤K≤5)가 주어진다. 
각 테스트 케이스의 첫째 줄에는 그래프의 정점의 개수 V(1≤V≤20,000)와 간선의 개수 E(1≤E≤200,000)가 빈 칸을 사이에 두고 순서대로 주어진다. 
각 정점에는 1부터 V까지 차례로 번호가 붙어 있다. 이어서 둘째 줄부터 E개의 줄에 걸쳐 간선에 대한 정보가 주어지는데, 각 줄에 인접한 두 정점의 번호가 빈 칸을 사이에 두고 주어진다.

출력
K개의 줄에 걸쳐 입력으로 주어진 그래프가 이분 그래프이면 YES, 아니면 NO를 순서대로 출력한다.

예제 입력 1 
2
3 2
1 3
2 3
4 4
1 2
2 3
3 4
4 2
예제 출력 1 
YES
NO
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int visit[20001], ans, V, E, T;
vector<int> G[20001]; // 인접 리스트
enum COLORS
{
    EMPTY,
    RED,
    BLACK
};

void bfs(int);
void dfs(int);

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> T;
    for (int t = 0; t < T; t++)
    {
        // 초기화
        ans = 1;
        memset(visit, EMPTY, sizeof(visit));

        // 입력
        cin >> V >> E;
        for (int e = 0; e < E; e++)
        {
            int v1, v2;
            cin >> v1 >> v2;
            G[v1].push_back(v2);
            G[v2].push_back(v1);
        }

        // 비연결 그래프일 수도 있으므로, 반복문을 이용해서 확인.
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

        // 그래프 초기화
        for (int v = 1; v <= V; v++)
        {
            G[v].clear();
        }

        if (ans)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }

    return 0;
}


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

void dfs(int start)
{
    if (!visit[start])
    {
        visit[start] = RED;
    }
    int curColor = visit[start];

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