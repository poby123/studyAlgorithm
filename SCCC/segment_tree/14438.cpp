#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

using pp = pair<int, int>;
using tp = tuple<int, int, int>;

constexpr int MAX = 1e5 + 1;
constexpr int INF = INT_MAX;
int N, M, arr[MAX], tree[MAX * 4];

/* node: [l, r] */
void init(int l, int r, int node)
{
    if (l == r)
    {
        tree[node] = arr[l];
        return;
    }

    int m = (l + r) / 2;
    init(l, m, node * 2);
    init(m + 1, r, node * 2 + 1);

    tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

/* node: [l, r]*/
void update(int targetIndex, int value, int l, int r, int node)
{
    if (targetIndex < l || r < targetIndex)
    {
        return;
    }

    // leaf
    if (l == r)
    {
        tree[node] = value;
        return;
    }

    int m = (l + r) / 2;
    if (targetIndex <= m)
    {
        update(targetIndex, value, l, m, node * 2);
    }
    else
    {
        update(targetIndex, value, m + 1, r, node * 2 + 1);
    }

    tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

/* node: [l, r], search: [s, e] */
int query(int s, int e, int l, int r, int node)
{
    if (r < s || e < l)
    {
        return INF;
    }

    if (s <= l && r <= e)
    {
        return tree[node];
    }

    int m = (l + r) / 2;
    int left = query(s, e, l, m, node * 2);
    int right = query(s, e, m + 1, r, node * 2 + 1);

    return min(left, right);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
    }

    init(1, N, 1);

    cin >> M;
    for (int m = 0; m < M; m++)
    {
        int c, i, v;
        cin >> c >> i >> v;

        if (c == 1)
        {
            arr[i] = v;
            update(i, v, 1, N, 1);
        }
        else
        {
            cout << query(i, v, 1, N, 1) << endl;
        }
    }

    return 0;
}