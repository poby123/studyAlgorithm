// https://www.acmicpc.net/problem/2243

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

using ll = long long;
using pp = pair<int, int>;
using tp = tuple<int, int, int>;

#define MAX 1000000
int N, arr[MAX + 1], tree[MAX * 4 + 4];

// node: [l, r], i번째 사탕
int query(int i, int l, int r, int node)
{
    if (l == r)
    {
        return l;
    }

    int m = (l + r) / 2;
    int left = tree[node * 2];
    int right = tree[node * 2 + 1];

    if (i <= left)
    {
        return query(i, l, m, node * 2);
    }

    return query(i - left, m + 1, r, node * 2 + 1);
}

// node: [l, r]
int update(int i, int v, int l, int r, int node)
{
    if (i < l || r < i)
    {
        return tree[node];
    }

    // leaf
    if (l == r)
    {
        return tree[node] = arr[i] += v;
    }

    int m = (l + r) / 2;
    return tree[node] = update(i, v, l, m, node * 2) + update(i, v, m + 1, r, node * 2 + 1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        int a;
        cin >> a;

        if (a == 1)
        {
            // b번째 사탕꺼내기
            int b;
            cin >> b;
            int index = query(b, 1, MAX, 1);
            cout << index << endl;
            update(index, -1, 1, MAX, 1);
        }
        else
        {
            // 맛인 b인 사탕 c개 넣기.
            int b, c;
            cin >> b >> c;
            update(b, c, 1, MAX, 1);
        }
    }

    return 0;
}

/**
5
2 1 3
2 2 2
2 3 7
2 4 1
1 7


6
2 1 3
2 2 2
2 3 7
2 4 1
1 7
1 12

5
2 1 3
2 2 2
2 3 3
2 4 1
1 1

2
2 1000000 1
1 1
*/