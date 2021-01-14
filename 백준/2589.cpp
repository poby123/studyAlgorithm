/*
문제
보물섬 지도를 발견한 후크 선장은 보물을 찾아나섰다. 보물섬 지도는 아래 그림과 같이 직사각형 모양이며 여러 칸으로 나뉘어져 있다. 
각 칸은 육지(L)나 바다(W)로 표시되어 있다. 이 지도에서 이동은 상하좌우로 이웃한 육지로만 가능하며, 한 칸 이동하는데 한 시간이 걸린다. 
보물은 서로 간에 최단 거리로 이동하는데 있어 가장 긴 시간이 걸리는 육지 두 곳에 나뉘어 묻혀있다. 
육지를 나타내는 두 곳 사이를 최단 거리로 이동하려면 같은 곳을 두 번 이상 지나가거나, 멀리 돌아가서는 안 된다.

보물 지도가 주어질 때, 보물이 묻혀 있는 두 곳 간의 최단 거리로 이동하는 시간을 구하는 프로그램을 작성하시오.

입력
첫째 줄에는 보물 지도의 세로의 크기와 가로의 크기가 빈칸을 사이에 두고 주어진다. 이어 L과 W로 표시된 보물 지도가 아래의 예와 같이 주어지며, 각 문자 사이에는 빈 칸이 없다. 
보물 지도의 가로, 세로의 크기는 각각 50이하이다.

출력
첫째 줄에 보물이 묻혀 있는 두 곳 사이를 최단 거리로 이동하는 시간을 출력한다.

예제 입력 1 
5 7
WLLWWWL
LLLWLLL
LWLWLWW
LWLWLLL
WLLWLWW
예제 출력 1 
8
*/

/*
    출발 지점이 정해져있지 않으므로, 모든 육지에서 다른 모든 육지에 대한 모든 경로의 최댓값을 구한다.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int N, M, cost[50][50], mvy[] = {0, 0, -1, 1}, mvx[] = {-1, 1, 0, 0}, ans;
char map[50][51];

bool isRange(const int &y, const int &x)
{
    return 0 <= y && y < N && 0 <= x && x < M;
}

void bfs(int y, int x)
{
    memset(cost, 0, sizeof(cost));
    queue<pair<int, int>> q;
    cost[y][x] = 1;
    q.push({y, x});

    while (!q.empty())
    {
        auto front = q.front();
        q.pop();
        int curY = front.first;
        int curX = front.second;
        int curCost = cost[curY][curX];
        ans = max(ans, curCost);

        for (int i = 0; i < 4; i++)
        {
            int nextY = curY + mvy[i];
            int nextX = curX + mvx[i];
            if (isRange(nextY, nextX) && map[nextY][nextX] == 'L' && !cost[nextY][nextX])
            {
                cost[nextY][nextX] = curCost + 1;
                q.push({nextY, nextX});
            }
        }
    }
}

int main()
{

    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        cin >> map[i];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (map[i][j] == 'L')
            {
                bfs(i, j);
            }
        }
    }

    cout << ans - 1;

    return 0;
}