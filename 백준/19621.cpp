// https://www.acmicpc.net/problem/19621

#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie(0)->sync_with_stdio(0)
#define endl '\n'
#define MAX 25

int N, last, s, e, p, dp[MAX + 3];
vector<tuple<int, int, int>> v;

int main()
{
    fastio;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        cin >> s >> e >> p;
        v.push_back({e, s, p});
    }

    for (size_t i = 2; i < N + 2; i++)
    {
        tie(e, s, p) = v[i - 2];
        dp[i] = max(dp[i - 1], dp[i - 2] + p);
    }

    cout << dp[N + 1] << endl;

    return 0;
}
