// 구간합 구하기 https://www.acmicpc.net/problem/2042

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

using pp = pair<int, int>;
using tp = tuple<int, int, int>;
using ll = long long;

constexpr int MAX = 1e6 + 1;

int N, M, K;
ll arr[MAX];
ll tree[MAX * 4];

// [l, r] 범위를 담당하는 node
ll init(int l, int r, int node)
{
    if (l == r)
    {
        return tree[node] = arr[l];
    }

    int m = (l + r) / 2;
    return tree[node] = init(l, m, node * 2) + init(m + 1, r, node * 2 + 1);
}

// targetIndex: 변경할 인덱스, diff: 변화량, node: [l, r]
void update(int targetIndex, ll diff, int l, int r, int node)
{
    if (targetIndex < l || r < targetIndex)
    {
        return;
    }

    tree[node] += diff;

    if (l == r)
    {
        return;
    }

    int m = (l + r) / 2;
    if (targetIndex <= m)
    {
        update(targetIndex, diff, l, m, node * 2);
    }
    else
    {
        update(targetIndex, diff, m + 1, r, node * 2 + 1);
    }
}

// node: [l, r], search [s, e]
ll sum(int l, int r, int s, int e, int node)
{
    if (r < s || e < l)
    {
        return 0LL;
    }

    if (s <= l && r <= e)
    {
        return tree[node];
    }

    int m = (l + r) / 2;
    return sum(l, m, s, e, node * 2) + sum(m + 1, r, s, e, node * 2 + 1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
    }
    init(1, N, 1);

    for (int i = 0; i < M + K; i++)
    {
        ll a, b, c;
        cin >> a >> b >> c;

        if (a == 1LL)
        {
            ll temp = arr[b];
            arr[b] = c;
            update(b, c - temp, 1, N, 1);

            continue;
        }

        cout << sum(1, N, b, c, 1) << endl;
    }

    return 0;
}