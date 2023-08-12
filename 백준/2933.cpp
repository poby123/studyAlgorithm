/**
 * 2023.08.12
 *
 * start: 21:50 대략
 * solve: 23:46
 *
 * 마지막 헤맨 이유
 * 여러번 drop 된다고 가졍했을 때, drop된 좌표에 대해서도 다시한 번 bfs를 진행하면서,
 * visited가 제대로 업데이트되지 않으므로 문제가 발생한다.
 */

#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie()->sync_with_stdio(0);
#define endl '\n'

#define MAX 101
#define ACTIVE 'A'
#define SPACE '.'
#define MINERAL 'x'
using pp = pair<int, int>;

const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};

int R, C, N;
char G[MAX][MAX];
bool visited[MAX][MAX];
vector<int> targetRows;
enum DIRECTION
{
    LEFT,
    RIGHT
};

inline bool isValid(int y, int x)
{
    return 0 <= y && y < R && 0 <= x && x < C;
}

void show()
{
    for (int i = 0; i < R; i++)
    {
        cout << G[i] << endl;
    }
}

int drop(vector<pp> &cluster)
{
    // make active
    for (auto [y, x] : cluster)
    {
        G[y][x] = ACTIVE;
    }

    int move = 0;
    bool canDrop = true;
    while (canDrop)
    {
        for (auto [y, x] : cluster)
        {
            int nextY = y + move + 1;
            int nextX = x;

            if (!isValid(nextY, nextX))
            {
                canDrop = false;
                break;
            }

            const char &nextType = G[nextY][nextX];
            if (nextType != SPACE && nextType != ACTIVE)
            {
                canDrop = false;
                break;
            }
        }

        if (canDrop)
        {
            ++move;
        }
    }

    // make SPACE
    for (auto [y, x] : cluster)
    {
        G[y][x] = SPACE;
    }

    // drop make MINERAL
    for (auto [y, x] : cluster)
    {
        G[y + move][x] = MINERAL;
    }

    return move;
}

void throwAStick(const int y, const DIRECTION &direction)
{
    if (direction == RIGHT)
    {
        for (int i = 0; i < C; i++)
        {
            char &cur = G[y][i];
            if (cur == MINERAL)
            {
                cur = SPACE;
                return;
            }
        }
    }
    else
    {
        for (int i = C - 1; i >= 0; i--)
        {
            char &cur = G[y][i];
            if (cur == MINERAL)
            {
                cur = SPACE;
                return;
            }
        }
    }
}

vector<pp> bfsForCluster(int y, int x)
{
    queue<pp> q;
    visited[y][x] = 1;
    q.push({y, x});
    vector<pp> cluster;

    while (!q.empty())
    {
        auto [y, x] = q.front();
        q.pop();
        cluster.push_back({y, x});

        for (int d = 0; d < 4; d++)
        {
            int nextY = y + dy[d];
            int nextX = x + dx[d];

            if (!isValid(nextY, nextX) || visited[nextY][nextX] || G[nextY][nextX] != MINERAL)
            {
                continue;
            }

            visited[nextY][nextX] = 1;
            q.push({nextY, nextX});
        }
    }

    return cluster;
}

void findCluster()
{
    for (int i = R - 1; i >= 0; i--)
    {
        for (int j = 0; j < C; j++)
        {
            if (!visited[i][j] && G[i][j] == MINERAL)
            {
                vector<pp> cluster = bfsForCluster(i, j);
                int move = drop(cluster);
                if (move > 0)
                {
                    return;
                }
            }
        }
    }
}

void throwStick()
{
    const int rows = targetRows.size();
    for (int i = 0; i < rows; i++)
    {
        if (i % 2)
        {
            throwAStick(R - targetRows[i], LEFT);
        }
        else
        {
            throwAStick(R - targetRows[i], RIGHT);
        }

        // drop
        memset(visited, 0, sizeof(visited));
        findCluster();
    }
}

int main()
{
    fastio;
    cin >> R >> C;
    cin.ignore();

    for (int i = 0; i < R; i++)
    {
        cin.getline(G[i], C + 1);
    }

    cin >> N;
    targetRows.reserve(N);
    for (int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        targetRows.push_back(x);
    }

    throwStick();
    show();

    return 0;
}

/**
마지막 헤맨 반례: 여러번 drop 된다고 가졍했을 때, drop된 이후에 좌표에 대한 visited가 제대로 업데이트되지 않으므로 문제가 발생한다.

3 8
...xxxxx
...xx...
...xx...
4
1 1 1 1


3 8
...xxxxx
...xx...
...xx...
2
1 1
*/