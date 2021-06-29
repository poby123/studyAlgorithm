/*
    https://www.acmicpc.net/problem/15591
*/

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define MAX 5001
#define INF 1000000001
using namespace std;

int N, Q;
vector<pair<int, int>> v[MAX];

int bfs(int start, int k)
{
    int visit[MAX] = {0}, ans = 0;

    queue<pair<int, int>> q;
    q.push({start, INF});
    visit[start] = 1;

    while (!q.empty())
    {
        auto front = q.front();
        q.pop();

        int cur = front.first;
        int w = front.second;

        if (w >= k)
        {
            ++ans;
        }

        for (int i = 0; i < v[cur].size(); i++)
        {
            int next = v[cur][i].first;
            int nextW = min(w, v[cur][i].second);

            // nextW >= k를 넣어도 맞는 이유가 뭘까?
            if (!visit[next] && nextW >= k)
            {
                visit[next] = 1;
                q.push({next, nextW});
            }
        }
    }

    // 맨 처음에 1을 넣었기 때문에 1을 빼야한다.
    return ans - 1;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // input
    cin >> N >> Q;

    for (int i = 1; i < N; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;
        v[a].push_back({b, w});
        v[b].push_back({a, w});
    }

    for (int i = 0; i < Q; i++)
    {
        int k, v, ans;
        cin >> k >> v;

        ans = bfs(v, k);

        cout << ans << "\n";
    }

    return 0;
}