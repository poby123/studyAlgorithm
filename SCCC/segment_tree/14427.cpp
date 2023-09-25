#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

using pp = pair<int, int>;
using tp = tuple<int, int, int>;

constexpr int MAX = 1e5 + 1;
constexpr int INF = INT_MAX;
int N, M;
vector<int> arr;
vector<pp> tree;

/* node: [l, r] */
void init(int l, int r, int node)
{
    if (l == r)
    {
        tree[node] = {arr[l], l};
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
        tree[node] = {value, l};
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
pp query(int s, int e, int l, int r, int node)
{
    if (r < s || e < l)
    {
        return {INF, 4 * N};
    }

    if (s <= l && r <= e)
    {
        return tree[node];
    }

    int m = (l + r) / 2;
    return min(query(s, e, l, m, node * 2), query(s, e, m + 1, r, node * 2 + 1));
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

    init(1, N, 1);

    cin >> M;
    for (int m = 0; m < M; m++)
    {
        int c, i, v;
        cin >> c;

        if (c == 1)
        {
            cin >> i >> v;
            arr[i] = v;
            update(i, v, 1, N, 1);
        }
        else
        {
            cout << query(1, N, 1, N, 1).second << endl;
        }
    }

    return 0;
}