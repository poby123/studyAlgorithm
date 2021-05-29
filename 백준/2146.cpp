/*
문제
여러 섬으로 이루어진 나라가 있다. 이 나라의 대통령은 섬을 잇는 다리를 만들겠다는 공약으로 인기몰이를 해 당선될 수 있었다. 
하지만 막상 대통령에 취임하자, 다리를 놓는다는 것이 아깝다는 생각을 하게 되었다. 
그래서 그는, 생색내는 식으로 한 섬과 다른 섬을 잇는 다리 하나만을 만들기로 하였고, 그 또한 다리를 가장 짧게 하여 돈을 아끼려 하였다.

이 나라는 N×N크기의 이차원 평면상에 존재한다. 
이 나라는 여러 섬으로 이루어져 있으며, 섬이란 동서남북으로 육지가 붙어있는 덩어리를 말한다. 
다음은 세 개의 섬으로 이루어진 나라의 지도이다.


위의 그림에서 색이 있는 부분이 육지이고, 색이 없는 부분이 바다이다. 
이 바다에 가장 짧은 다리를 놓아 두 대륙을 연결하고자 한다. 
가장 짧은 다리란, 다리가 격자에서 차지하는 칸의 수가 가장 작은 다리를 말한다. 
다음 그림에서 두 대륙을 연결하는 다리를 볼 수 있다.

물론 위의 방법 외에도 다리를 놓는 방법이 여러 가지 있으나, 위의 경우가 놓는 다리의 길이가 3으로 가장 짧다(물론 길이가 3인 다른 다리를 놓을 수 있는 방법도 몇 가지 있다).

지도가 주어질 때, 가장 짧은 다리 하나를 놓아 두 대륙을 연결하는 방법을 찾으시오.

입력
첫 줄에는 지도의 크기 N(100이하의 자연수)가 주어진다. 
그 다음 N줄에는 N개의 숫자가 빈칸을 사이에 두고 주어지며, 0은 바다, 1은 육지를 나타낸다. 
항상 두 개 이상의 섬이 있는 데이터만 입력으로 주어진다.

출력
첫째 줄에 가장 짧은 다리의 길이를 출력한다.
*/

/*
    prebfs
      1. 섬마다 번호를 매긴다. 탐색하다가 섬을 만났을 때 이게 자기 섬인지 아니면 다른 섬인지 알 기 위해서이다.
      2. 섬에서 바다와 접하는 곳을 표시해준다. 바다와 접하는 곳만 탐색하면, 불필요한 탐색을 많이 줄일 수 있기 때문이다.

    bfs
      1. 자신의 섬과 다른 번호면 탐색한다.
        자신의 섬과 다른 번호면 다음의 두 가지 경우가 있다.
            첫 번째 경우는 바다인 경우다. 다리의 길이를 visit에 저장하면서 계속 진행한다.
            두 번째 경우는 다른 섬을 찾은 경우다. 다리의 길이를 통해 답을 업데이트하고, 탐색을 종료한다.

    각각의 섬에서 바다와 접하는 위치에 대해 bfs를 실행한다.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;

#define MAX 101

int N, ans = INT_MAX, dy[] = {0, 0, -1, 1}, dx[] = {-1, 1, 0, 0}, no;
int map[MAX][MAX], visit[MAX][MAX], boundary[MAX][MAX];

bool isIn(int y, int x)
{
    return 0 <= y && y < N && 0 <= x && x < N;
}

void prebfs(int y, int x)
{
    queue<pair<int, int>> q;

    visit[y][x] = 1;
    q.push({y, x});

    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();
        const int curY = cur.first;
        const int curX = cur.second;

        map[curY][curX] = no;

        for (int d = 0; d < 4; d++)
        {
            int nextY = curY + dy[d];
            int nextX = curX + dx[d];

            if (isIn(nextY, nextX) && !visit[nextY][nextX])
            {
                if (map[nextY][nextX])
                {
                    visit[nextY][nextX] = 1;
                    q.push({nextY, nextX});
                    continue;
                }
                boundary[curY][curX] = 1;
            }
        }
    }
}

void bfs(int y, int x, int curNo)
{
    queue<pair<int, int>> q;
    visit[y][x] = 1;
    q.push({y, x});

    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();
        const int curY = cur.first;
        const int curX = cur.second;
        const int curL = visit[curY][curX];

        for (int d = 0; d < 4; d++)
        {
            int nextY = curY + dy[d];
            int nextX = curX + dx[d];

            if (isIn(nextY, nextX) && !visit[nextY][nextX] && map[nextY][nextX] != curNo)
            {
                if (!map[nextY][nextX])
                {
                    visit[nextY][nextX] = curL + 1;
                    q.push({nextY, nextX});
                    continue;
                }
                ans = min(ans, curL - 1);
                return;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // input
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> map[i][j];
        }
    }

    // classification & boundary
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (map[i][j] && !visit[i][j])
            {
                ++no;
                prebfs(i, j);
            }
        }
    }

    memset(visit, 0, sizeof(visit));

    // search
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (boundary[i][j] && !visit[i][j])
            {
                memset(visit, 0, sizeof(visit));
                bfs(i, j, map[i][j]);
            }
        }
    }

    // output
    cout << ans;

    return 0;
}