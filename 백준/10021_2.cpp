/**
 * @date 2023.08.12
 * https://www.acmicpc.net/problem/10021
 *
 * MST: PRIM
 */

#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie()->sync_with_stdio(0);
#define endl '\n'

#define MAX 2001
int N, C;
using pp = pair<int, int>;
vector<pp> points;
vector<pp> G[MAX];
vector<int> visited;

int revealCost(const pp &p1, const pp &p2)
{
    auto [x1, y1] = p1;
    auto [x2, y2] = p2;

    return pow(x1 - x2, 2) + pow(y1 - y2, 2);
}

int mst()
{
    int totalCost = 0;
    int numOfEdge = 0;

    priority_queue<pp> pq;

    const int initIndex = 0;
    pq.push({0, initIndex});

    while (!pq.empty())
    {
        auto [cost, cur] = pq.top();
        pq.pop();

        if (visited[cur])
        {
            continue;
        }

        visited[cur] = 1;
        totalCost += -cost;
        ++numOfEdge;

        if (numOfEdge == N)
        {
            return totalCost;
        }

        const pp &p1 = points[cur];
        for (int i = 0; i < N; i++)
        {
            if (i == cur || visited[i])
            {
                continue;
            }
            const pp &p2 = points[i];
            const int cost = revealCost(p1, p2);
            if (cost < C)
            {
                continue;
            }

            pq.push({-cost, i});
        }
    }

    return numOfEdge == N ? totalCost : -1;
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

    visited.resize(N);
    for (int i = 0; i < N; i++)
    {
        visited[i] = 0;
    }

    cout << mst() << endl;

    return 0;
}