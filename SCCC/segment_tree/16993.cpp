#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

using ll = long long;

// {왼쪽을 포함하는 최대값, 오른쪽을 포함하는 최댓값, 최댓값, 구간합}
using tp = tuple<int, int, int, int>;

#define MAX 1e5 + 1

vector<int> arr(MAX);
vector<tp> tree(4 * MAX);
int N, M;

tp merge(const tp &left, const tp &right)
{
    const auto [llMaxSum, lrMaxSum, lMaxSum, lSum] = left;
    const auto [rlMaxSum, rrMaxSum, rMaxSum, rSum] = right;

    return {
        max({llMaxSum, lSum + rlMaxSum}),
        max({rrMaxSum, rSum + lrMaxSum}),
        max({lMaxSum, rMaxSum, lrMaxSum + rlMaxSum}),
        lSum + rSum};
}

// node: [l, r]
void init(int l, int r, int node)
{
    if (l == r)
    {
        int v = arr[l];
        tree[node] = {v, v, v, v};
        return;
    }

    int m = (l + r) / 2;
    init(l, m, node * 2);
    init(m + 1, r, node * 2 + 1);

    tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
}

// search: [s, e], node: [l, r]
tp query(int s, int e, int l, int r, int node)
{
    if (e < l || r < s)
    {
        return {-1e5, -1e5, -1e5, 0};
    }

    if (s <= l && r <= e)
    {
        return tree[node];
    }

    int m = (l + r) / 2;
    return merge(query(s, e, l, m, node * 2), query(s, e, m + 1, r, node * 2 + 1));
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
    for (int i = 1; i <= M; i++)
    {
        int s, e;
        cin >> s >> e;
        tp ans = query(s, e, 1, N, 1);

        cout << get<2>(ans) << endl;
    }

    return 0;
}