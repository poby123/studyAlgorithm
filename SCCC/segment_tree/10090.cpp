#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

using ll = long long;
using pp = pair<int, int>;
using tp = tuple<int, int, int>;

int N;
vector<ll> arr, tree;
ll ans;

// search: [s, e], node: [l, r]
ll query(int s, int e, int l, int r, int node)
{
    if (e < l || r < s)
    {
        return 0LL;
    }

    if (s <= l && r <= e)
    {
        return tree[node];
    }

    int m = (l + r) / 2;
    return query(s, e, l, m, node * 2) + query(s, e, m + 1, r, node * 2 + 1);
}

// node: [l, r], update i
ll add(int i, int l, int r, int node)
{
    if (i < l || r < i)
    {
        return tree[node];
    }

    if (l == r)
    {
        return tree[node] = 1;
    }

    int m = (l + r) / 2;
    return tree[node] = add(i, l, m, node * 2) + add(i, m + 1, r, node * 2 + 1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    arr.resize(N + 1);
    tree.resize(4 * N + 1);
    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
    }

    for (int i = 1; i <= N; i++)
    {
        ll cur = arr[i];
        ll value = cur - 1 - query(1, cur - 1, 1, N, 1);
        ans += value;
        add(cur, 1, N, 1);
    }

    cout << ans << endl;

    return 0;
}