// https://www.acmicpc.net/problem/25639

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

using ll = long long;
using pp = pair<int, int>;
using tp = tuple<int, int, int>; // {min, max, count}

#define MAX 100001

int N, Q;
vector<int> arr(MAX);
vector<tp> tree(4 * MAX);

tp merge(const tp &l, const tp &r)
{
    const auto [lMin, lMax, lAns] = l;
    const auto [rMin, rMax, rAns] = r;
    return {min(lMin, rMin),
            max(lMax, rMax),
            max({rMax - lMin, lAns, rAns})};
}

// node: [l, r]
void init(int l, int r, int node)
{
    // leaf
    if (l == r)
    {
        tree[node] = {arr[l], arr[r], 0};
        return;
    }

    int m = (l + r) / 2;
    init(l, m, node * 2);
    init(m + 1, r, node * 2 + 1);

    tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
}

// node: [l, r], arr[i] = v
void update(int i, int v, int l, int r, int node)
{
    if (i < l || r < i)
    {
        return;
    }

    // leaf
    if (l == r)
    {
        arr[i] = v;
        tree[node] = {v, v, 0};
        return;
    }

    int m = (l + r) / 2;
    if (i <= m)
        update(i, v, l, m, node * 2);
    else
        update(i, v, m + 1, r, node * 2 + 1);

    tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
}

// node: [l, r], search: [s, e]
tp query(int s, int e, int l, int r, int node)
{
    if (e < l || r < s)
    {
        return {1e9, -1e9, -1};
    }

    if (s <= l && r <= e)
    {
        return tree[node];
    }

    int m = (l + r) / 2;
    return merge(query(s, e, l, m, node * 2), query(s, e, m + 1, r, node * 2 + 1));
}

void print()
{
    cout << endl;
    cout << "min: ";
    for (int i = 1; i <= 4 * N; i++)
    {
        cout << get<0>(tree[i]) << " ";
    }
    cout << endl;

    cout << endl;
    cout << "max: ";
    for (int i = 1; i <= 4 * N; i++)
    {
        cout << get<1>(tree[i]) << " ";
    }
    cout << endl;

    cout << endl;
    cout << "ans: ";
    for (int i = 1; i <= 4 * N; i++)
    {
        cout << get<2>(tree[i]) << " ";
    }
    cout << endl;
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

    // query
    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        if (a == 1)
        {
            update(b, c, 1, N, 1);
            print();
            continue;
        }
        tp result = query(b, c, 1, N, 1);
        cout << get<2>(result) << endl;
    }

    return 0;
}