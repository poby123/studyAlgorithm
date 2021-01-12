#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <cstring>
using namespace std;

int N, M, map[8][8], ans = INT_MAX;
int directionN[] = {4, 2, 4, 4, 1};
int direction[5][4][4] = {
    //1번 : 4가지
    {
        //오 아래 왼 위
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    },
    //2번 : 2가지
    {
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
    },
    //3번 : 4가지
    {
        {1, 0, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 1},
    },
    //4번 : 4가지
    {
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 0},
        {0, 1, 1, 1},
    },
    //5번 : 1가지
    {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
    },
};

int getArea(const vector<pair<pair<int, int>, int>> &v)
{
    int mapCpy[8][8], ret = 0;
    memcpy(mapCpy, map, sizeof(map));

    for (auto it : v)
    {
        int y = it.first.first;
        int x = it.first.second;
        int d = it.second;

        //오 아래 왼 위
        int current_px = direction[map[y][x] - 1][d][0]; //+x
        int current_py = direction[map[y][x] - 1][d][1]; //+y
        int current_mx = direction[map[y][x] - 1][d][2]; //-x
        int current_my = direction[map[y][x] - 1][d][3]; //-y

        if (current_px)
        {
            for (int i = x; i < M; i++)
            {
                if (mapCpy[y][i] == 6)
                    break;
                mapCpy[y][i] = 9;
            }
        }

        if (current_py)
        {
            for (int i = y; i < N; i++)
            {
                if (mapCpy[i][x] == 6)
                    break;
                mapCpy[i][x] = 9;
            }
        }

        if (current_mx)
        {
            for (int i = x; i >= 0; i--)
            {
                if (mapCpy[y][i] == 6)
                    break;
                mapCpy[y][i] = 9;
            }
        }

        if (current_my)
        {
            for (int i = y; i >= 0; i--)
            {
                if (mapCpy[i][x] == 6)
                    break;
                mapCpy[i][x] = 9;
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (mapCpy[i][j] == 0)
            {
                ++ret;
            }
        }
    }

    return ret;
}

void check(vector<pair<pair<int, int>, int>> &v, int idx)
{
    if (idx == v.size())
    {
        ans = min(ans, getArea(v));
        return;
    }

    int y = v[idx].first.first;
    int x = v[idx].first.second;

    for (int i = 0; i < directionN[map[y][x] - 1]; i++)
    {
        v[idx].second = i;
        check(v, idx + 1);
    }
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    vector<pair<pair<int, int>, int>> v;
    v.reserve(8);

    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> map[i][j];
            if (0 < map[i][j] && map[i][j] < 6)
            {
                v.push_back({{i, j}, 0});
            }
        }
    }

    check(v, 0);
    cout << ans;

    return 0;
}