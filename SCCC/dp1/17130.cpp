// https://www.acmicpc.net/problem/17130

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

using ll = long long;
using pp = pair<int, int>;
using tp = tuple<int, int, int>;

#define MAX 1003
#define WALL '#'
#define SPACE '.'
#define RABBIT 'R'
#define CARROT 'C'
#define DOOR 'O'

int N, M, dp[MAX][MAX], ans = -1;
char G[MAX][MAX];
vector<pp> doors;

const int dy[] = {-1, 0, 1};
const int dx[] = {-1, -1, -1};

bool isRange(int y, int x)
{
    return 1 <= y && y <= N && 1 <= x && x <= M;
}

int main()
{
    memset(dp, -1, sizeof(dp));

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    cin.ignore();

    for (int i = 1; i <= N; i++)
    {
        cin.getline(&G[i][1], M + 1);
    }

    // set start
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            const char cur = G[i][j];
            if (cur == RABBIT)
            {
                dp[i][j] = 0;
            }
            else if (cur == DOOR)
            {
                doors.push_back({i, j});
            }
        }
    }

    for (int j = 1; j <= M; j++)
    {
        for (int i = 1; i <= N; i++)
        {
            const char cur = G[i][j];
            if (cur == WALL)
            {
                continue;
            }

            for (int d = 0; d < 3; d++)
            {
                int prevY = i + dy[d];
                int prevX = j + dx[d];

                if (isRange(prevY, prevX) && dp[prevY][prevX] >= 0)
                {
                    if (G[prevY][prevX] == CARROT)
                    {
                        dp[i][j] = max(dp[i][j], dp[prevY][prevX] + 1);
                        continue;
                    }
                    dp[i][j] = max(dp[i][j], dp[prevY][prevX]);
                }
            }
        }
    }

    for (auto [i, j] : doors)
    {
        ans = max({ans, dp[i][j]});
    }

    cout << ans << endl;

    return 0;
}
