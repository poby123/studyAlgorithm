/**
 * @date 2023.08.12
 * https://www.acmicpc.net/problem/10021
 *
 * MST: Kruskal
 */

#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie()->sync_with_stdio(0);
#define endl '\n'

int N, C;
using pp = pair<int, int>;
vector<pp> points;
vector<tuple<int, int, int>> edges;
vector<int> parent;

int find(const int &x)
{
    if (parent[x] == x)
    {
        return x;
    }

    return parent[x] = find(parent[x]);
}

void _union(int a, int b)
{
    a = find(a);
    b = find(b);

    if (a < b)
    {
        parent[b] = a;
    }
    else
    {
        parent[a] = b;
    }
}

int revealCost(const pp &p1, const pp &p2)
{
    auto &[x1, y1] = p1;
    auto &[x2, y2] = p2;

    return pow(x1 - x2, 2) + pow(y1 - y2, 2);
}

int mst()
{
    int totalCost = 0;
    int numOfEdge = 0;

    const int edgeSize = edges.size();
    for (int i = 0; i < edgeSize; i++)
    {
        const tuple<int, int, int> cur = edges[i];
        auto &[cost, ai, bi] = cur;

        int aParent = find(ai);
        int bParent = find(bi);

        if (aParent != bParent)
        {
            _union(aParent, bParent);
            totalCost += cost;
            ++numOfEdge;
        }
    }

    return numOfEdge == N - 1 ? totalCost : -1;
}

int main()
{
    fastio;
    cin >> N >> C;

    // input points
    for (int i = 0; i < N; i++)
    {
        int x, y;
        cin >> x >> y;
        points.push_back({x, y});
    }

    // init union-find
    parent.resize(N);
    for (int i = 0; i < N; i++)
    {
        parent[i] = i;
    }

    // make edges
    for (int i = 0; i < N; i++)
    {
        pp p1 = points[i];
        for (int j = i + 1; j < N; j++)
        {
            pp p2 = points[j];
            const int cost = revealCost(p1, p2);

            if (cost < C)
            {
                continue;
            }

            edges.push_back({cost, i, j});
        }
    }
    sort(edges.begin(), edges.end());

    cout << mst() << endl;

    return 0;
}