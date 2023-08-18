/**
 * 2023.08.17 21:04
 *
 * 왜 패딩을 주지 않으면 틀리는걸까...?
 * 그냥 입구가 있으면 비용을 0으로 간주하고, 문이 있으면 1로 해서 0-1 bfs 하면 왜 안되는거지...?
 * 내 로직에 문제가 있었나봄...
 */

#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie()->sync_with_stdio(0);
#define endl '\n'

using pp = pair<int, int>;
using tp = tuple<int, int, int>;

#define MAX 103
#define INF 100000

#define SPACE '.'
#define WALL '*'
#define TARGET '$'
#define DOOR '#'

int t, w, h;
char G[MAX][MAX];
const int dy[]{0, 0, -1, 1};
const int dx[]{-1, 1, 0, 0};
deque<pp> dq;

bool isInRange(int y, int x)
{
    return 0 <= y && y < h + 2 && 0 <= x && x < w + 2;
}

void findPath(int (*visited)[MAX])
{
    while (!dq.empty())
    {
        auto [y, x] = dq.front();
        dq.pop_front();
        const int curCost = visited[y][x];
        char &current = G[y][x];

        for (int d = 0; d < 4; d++)
        {
            const int nextY = y + dy[d];
            const int nextX = x + dx[d];

            if (!isInRange(nextY, nextX))
            {
                continue;
            }

            const char next = G[nextY][nextX];
            int &nextCost = visited[nextY][nextX];
            if (next == WALL || nextCost >= 0)
            {
                continue;
            }

            if (next == DOOR)
            {
                nextCost = curCost + 1;
                dq.push_back({nextY, nextX});
            }
            else
            {
                nextCost = curCost;
                dq.push_front({nextY, nextX});
            }
        }
    }
}

vector<pp> findTarget()
{
    vector<pp> ret;

    for (int i = 0; i < h + 2; i++)
    {
        for (int j = 0; j < w + 2; j++)
        {
            if (G[i][j] == TARGET)
            {
                ret.push_back({i, j});
            }
        }
    }

    return ret;
}

void solve()
{
    int helperMap[MAX][MAX];
    int p1Map[MAX][MAX];
    int p2Map[MAX][MAX];
    int ans = INF;

    fill(&helperMap[0][0], &helperMap[MAX - 1][MAX - 1], -1);
    fill(&p1Map[0][0], &p1Map[MAX - 1][MAX - 1], -1);
    fill(&p2Map[0][0], &p2Map[MAX - 1][MAX - 1], -1);

    vector<pp> targets = findTarget();
    auto [p1y, p1x] = targets[0];
    auto [p2y, p2x] = targets[1];

    dq.push_back({0, 0});
    helperMap[0][0] = 0;
    findPath(helperMap);

    dq.push_back({p1y, p1x});
    p1Map[p1y][p1x] = 0;
    findPath(p1Map);

    dq.push_back({p2y, p2x});
    p2Map[p2y][p2x] = 0;
    findPath(p2Map);

    for (int i = 0; i < h + 2; i++)
    {
        for (int j = 0; j < w + 2; j++)
        {
            const char cur = G[i][j];
            if (cur == WALL)
            {
                continue;
            }
            if (helperMap[i][j] < 0 || p1Map[i][j] < 0 || p2Map[i][j] < 0)
            {
                continue;
            }

            int sum = helperMap[i][j] + p1Map[i][j] + p2Map[i][j];
            if (cur == DOOR)
            {
                sum -= 2;
            }
            ans = min(ans, sum);
        }
    }

    cout << ans << endl;
}

int main()
{
    fastio;
    cin >> t;

    while (t--)
    {
        memset(G, 0, sizeof(G));

        cin >> h >> w;
        cin.ignore();

        for (int i = 0; i < h; i++)
        {
            cin.getline(&G[i + 1][1], w + 1);
        }

        solve();
    }

    return 0;
}

// https://www.acmicpc.net/board/view/52774