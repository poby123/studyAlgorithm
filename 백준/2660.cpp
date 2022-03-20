// https://www.acmicpc.net/problem/2660

#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define MAX 50
#define INF 10000000

int N, G[MAX + 1][MAX + 1];
vector<pair<int, int>> ans;

void solve()
{
    for (int k = 1; k <= N; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }

    for (int i = 1; i <= N; i++)
    {
        int *it = max_element(&G[i][1], &G[i][N + 1]);
        ans.push_back({*it, i});
    }

    sort(ans.begin(), ans.end());
    int maxV = ans[0].first;
    int n = 0;

    for (; n < ans.size() && maxV == ans[n].first; n++);

    cout << maxV << " " << n << "\n";
    for (int i = 0; i < n; i++)
    {
        cout << ans[i].second << " ";
    }
}

int main()
{
    fastio;
    fill(&G[0][0], &G[MAX][MAX], INF);
    for (int i = 0; i <= MAX; i++)
    {
        G[i][i] = 0;
    }

    cin >> N;
    while (1)
    {
        int a, b;
        cin >> a >> b;
        if (a == -1 && b == -1)
        {
            break;
        }

        G[a][b] = 1;
        G[b][a] = 1;
    }

    solve();

    return 0;
}
